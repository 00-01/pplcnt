#include <stdio.h>
#include "BleNotifier.h"
#include "Gap.h"
#include "lynredKernels.h"
#include "pmsis.h"
#include "bsp/bsp.h"
#include "bsp/gapoc_b_v2.h"
#include "bsp/camera.h"
#include "bsp/fs.h"
#include "bsp/fs/readfs.h"
#include "bsp/camera/thermeye.h"
#include "shutterless/PreFiltering.h"
#include "shutterless/PreFilteringCluster.h"
#include "ImageDraw.h"
#include "setup.h"
#include "bsp/flash/spiflash.h"
#include "bsp/flash/hyperflash.h"

struct pi_device HyperRam;

#ifdef QSPI
    #define FLASH_NAME "QSPI"
    struct pi_device QspiRam;
    AT_QSPIFLASH_FS_EXT_ADDR_TYPE lynred_L3_Flash;
#else
    #define FLASH_NAME "HYPER"
//    struct pi_device HyperRam;
    AT_HYPERFLASH_FS_EXT_ADDR_TYPE lynred_L3_Flash;
#endif

#define MOUNT           1
#define UNMOUNT         0
#define CID             0
#define GPIO_USER_LED   0
unsigned int W = 80, H = 80;

#define FIX2FP(Val, Precision)    ((float) (Val) / (float) (1<<(Precision)))

PI_L2 bbox_t *out_boxes;
typedef struct{
    bbox_t * bbs;
    int16_t num_bb;
}    bboxs_t;

L2_MEM short int output_1[40];
L2_MEM signed char output_2[10];
L2_MEM signed char output_3[10];
PI_L2 bboxs_t bbxs;
PI_L2 int16_t *offset;
PI_L2 int16_t *img;
PI_L2 int16_t *saved;
PI_L2 int16_t *prev;
PI_L2 int16_t *now;
PI_L2 int16_t *modified_now;
PI_L2 unsigned char *now_to_char;

#define BUFFER_SIZE 1024
static struct pi_device cam;
static struct pi_device cluster_dev;

extern L1_CL_MEM AT_L1_POINTER lynred_L1_Memory;

void led(int cycle, int delay1, int delay2){
    for(int i=0; i<cycle; i++){
        pi_gpio_pin_write(NULL, GPIO_USER_LED, 0);
        pi_time_wait_us(delay1*10000);
        pi_gpio_pin_write(NULL, GPIO_USER_LED, 1);
        pi_time_wait_us(delay1*10000);
        pi_time_wait_us(delay2*10000);
    }
}

int imgTest(char name[], short data[], short num, short bit){
    printf("[I] %s : ", name, num);
    if (bit == 16) {
        for (int j = 0; j < num; j++) printf("%d,", ((short *) data)[j]);
        printf("..\n");
    } else if (bit == 8) {
        for (int j = 0; j < num; j++) printf("%d,", ((char *) data)[j]);
        printf("..\n");
    }
    return 0;
}

void drawBboxes(bboxs_t *boundbxs, uint8_t *img){
    for (int counter = 0; counter<boundbxs->num_bb; counter++){
        if (boundbxs->bbs[counter].alive) {
            DrawRectangle(img, 80, 80, boundbxs->bbs[counter].x, boundbxs->bbs[counter].y, boundbxs->bbs[counter].w, boundbxs->bbs[counter].h, 255);
        }    }
}

int save_img(int *img, char name[], char num, char draw, int16_t bit){
    char string_buffer[50];
    sprintf(string_buffer, "../../../dump_out_imgs/%s_%04ld.pgm", name, num);

//    int16_t min, max;
//    int16_t out_min = 0;
//    int32_t out_max = 255;
//    int32_t out_space = (out_max-out_min);
//    float div = 1./(max-min);
//    int32_t div_fix = FP2FIX(div, 15);
//    uint8_t *img8 = img;
//    for (int i = 0; i<W*H; i++) img8[i] = (uint8_t) (((out_space)*((((((int32_t) img[i])-(int32_t) min))*div_fix))) >> (15));
//    if (bit8 == 1){
//        if (draw==1) drawBboxes(&bbxs, img8);
//        WriteImageToFile(string_buffer, W, H, img8);
//    } else{
//        if (draw==1) drawBboxes(&bbxs, img);
//        WriteImageToFile(string_buffer, W, H, img);
//    }

    if (bit==8) {
        char img8;
        img8 = (unsigned char *) pmsis_l2_malloc(W*H*sizeof(char));
        memcpy(img8, img, W*H*sizeof(char));
        if (draw==1) drawBboxes(&bbxs, img8);
        WriteImageToFile(string_buffer, W, H, img8);
    } else{
        if (draw==1) drawBboxes(&bbxs, img);
        WriteImageToFile(string_buffer, W, H, img);
    }
    return 0;
}

void open_flash_filesystem(struct pi_device *flash, struct pi_device *fs){
    struct pi_readfs_conf fsconf;
    /* Init & open flash. */
    #ifdef QSPI
        struct pi_spiflash_conf flash_conf;
        pi_spiflash_conf_init(&flash_conf);
    #else
        struct pi_hyperflash_conf flash_conf;
        pi_hyperflash_conf_init(&flash_conf);
    #endif

    pi_open_from_conf(flash, &flash_conf);
    if (pi_flash_open(flash)){
        printf("Error flash open !\n");
        pmsis_exit(-1);    }
    pi_readfs_conf_init(&fsconf);

    fsconf.fs.flash = flash;

    pi_open_from_conf(fs, &fsconf);

    if (pi_fs_mount(fs)){
        printf("Error FS mounting !\n");
        pmsis_exit(-2);    }
}

void close_flash_filesystem(struct pi_device *flash, struct pi_device *fs){
    pi_fs_unmount(fs);
    pi_flash_close(flash);
}

//#ifdef INPUT_CAMERA
//#if !defined(INPUT_RAW_FILE) && !defined(INPUT_FILE)
static int32_t open_camera_thermeye(struct pi_device *device, int GFID, int GSK_A, int GSK_B, int GAIN, int TINT){
    struct pi_thermeye_conf cam_conf;
//    pi_thermeye_conf_init(&cam_conf);
    pi_thermeye_init(&cam_conf, GFID, GSK_A, GSK_B, GAIN, TINT);
    pi_open_from_conf(device, &cam_conf);
    if (pi_camera_open(device)) return -1;
    return 0;
}
//#endif

int initL3Buffers(){
    /* Init & open ram. */
    #ifdef QSPI
        struct pi_device *ram = &QspiRam;
        static struct pi_spiram_conf conf;
        pi_spiram_conf_init(&conf);
    #else
        struct pi_device *ram = &HyperRam;
        static struct pi_hyperram_conf conf;
        pi_hyperram_conf_init(&conf);
    #endif

    pi_open_from_conf(ram, &conf);
    if (pi_ram_open(ram)){
        printf("[!] Error ram open !\n");
        return -1;    }
    bbxs.bbs = pmsis_l2_malloc(sizeof(bbox_t)*MAX_BB);
    if(bbxs.bbs==NULL)  return 1;

    bbxs.num_bb = 0;
    return 0;
}

void printBboxes(bboxs_t *boundbxs) {
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("BoudingBox:  score    cx    cy     w    h   class");
    printf("\n--------------------------------------------------\n");
    for (int counter=0; counter < boundbxs->num_bb; counter++){
        if(boundbxs->bbs[counter].alive)
            printf("bbox [%02d] : %.5f   %03d   %03d   %03d   %03d   %02d\n", counter,
                   FIX2FP(boundbxs->bbs[counter].score,7 ),
                   boundbxs->bbs[counter].x, boundbxs->bbs[counter].y,
                   boundbxs->bbs[counter].w, boundbxs->bbs[counter].h, boundbxs->bbs[counter].class);
    }
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

static void RunNN(){
    unsigned int ti,ti_nn,ti_ssd;
    for(int i=0; i<10; i++){
        output_1[i]=0;
        output_2[i]=0;
    }
    for(int i=0; i<MAX_BB; i++)bbxs.bbs[i].alive=0;

    gap_cl_starttimer();
    gap_cl_resethwtimer();
    ti = gap_cl_readhwtimer();

    bbxs.num_bb = 0;
    lynredCNN(now_to_char, output_1,output_2,output_3);
    ti_nn = gap_cl_readhwtimer()-ti;

    for(int i=0; i<10; i++){
        //output_1 is bounding box ccordinates
        //output_2 is class number
        //output_3 is score
        if(output_2[i]==1 && output_3[i]!=0){
            bbxs.bbs[i].alive=1;
            bbxs.bbs[i].score=output_3[i];
            bbxs.bbs[i].class=output_2[i];
            bbxs.bbs[i].x = (output_1[4*i+1]*lynred_Output_1_OUT_SCALE)*80;
            bbxs.bbs[i].y = (output_1[4*i]*lynred_Output_1_OUT_SCALE)*80;
            bbxs.bbs[i].w = ((output_1[4*i+3]-output_1[4*i+1])*lynred_Output_1_OUT_SCALE)*80;
            bbxs.bbs[i].h = ((output_1[4*i+2]-output_1[4*i])*lynred_Output_1_OUT_SCALE)*80;
            bbxs.num_bb++;
        }
    }
    #ifndef SILENT
        printBboxes(&bbxs);
    #endif

    printf("[I] Cycles NN :%10d\n", ti_nn);
}

int32_t float_shutterless(int16_t* img_input_fp16, int16_t* offset_fp16, int w, int h, uint8_t q_output, float gamma){
    int min, max;
    int32_t out_min = 0;
    int32_t out_max = 255;
    uint8_t *img_input_fp8 = img_input_fp16;

    int error = shutterless_float(img_input_fp16,offset_fp16,40,&min,&max);

    for(int i=0; i<w*h; i++){
        img_input_fp16[i] = (int16_t)((out_max-out_min)* (pow(((float)img_input_fp16[i]-min)/(max-min),gamma) + out_min)) ;
        img_input_fp8[i] = img_input_fp16[i] << (q_output-8);
    }
    return error;
}

int32_t fixed_shutterless(int16_t *img_input_fp16, int16_t *offset_fp16, int w, int h, uint8_t q_output){
    int16_t min, max;
    uint8_t *img_input_fp8 = img_input_fp16;
//-------------------------------------------------------------------------------------
    imgTest("pre filter", img_input_fp8, 8, 8);

//    Optmized shutterless running on cluster (cluster must be open ahead and have enough free memory) g on fabric controller
//    int error = shutterless_fixed_cl(&cluster_dev, img_input_fp16, offset_fp16, 40, &min, &max);
    int error = shutterless_fixed_fc(img_input_fp16, offset_fp16, 40, &min, &max);
    //-------------------------------------------------------------------------------------
    imgTest("post filter", img_input_fp8, 8, 8);

    int16_t out_min = 0;
    int32_t out_max = 255;
    int32_t out_space = (out_max-out_min);
    float div = 1./(max-min);
    int32_t div_fix = FP2FIX(div, 15);
    //Normalizing to 8 bit and changing fixed point format for NN
    for(int i=0; i<w*h; i++){
        img_input_fp8[i] = (uint8_t)(((out_space)*((((((int32_t)img_input_fp16[i])-(int32_t)min))*div_fix)))>>(15-q_output+8));
    }
//-------------------------------------------------------------------------------------
    imgTest("16 to 8 bit - cal", img_input_fp8, 8, 8);
    return error;
}

//int aint_to_char = (uint8_t)((255*(((int32_t)219)-(int32_t)min)*((int)((1./(max-min))*((1 << 15)-1)))) >> 15);
//                                      (now, offset, W, H, 8)
//int32_t custom_prefilter(int16_t *img_input_fp16, int16_t *offset_fp16, int w, int h, uint8_t q_output){
////    int16_t min = 0, max = 255;

//
//    int16_t min, max;
//    int16_t out_min = 0;
//    int32_t out_max = 255;
//    int32_t out_space = (out_max - out_min);
//    uint8_t *img_input_fp8 = img_input_fp16;
////-------------------------------------------------------------------------------------
//    imgTest("pre filter", now, 6, 16);
////-------------------------------------------------------------------------------------
//
//    apply 0
//
////    //Optmized shutterless running on cluster (cluster must be open ahead and have enough free memory) g on fabric controller
//////     int error = shutterless_fixed_cl(&cluster_dev, img_input_fp16, offset_fp16, 40, &min, &max);
////    int error = shutterless_fixed_fc(img_input_fp16, offset_fp16, 40, &min, &max);
////    float div = 1./(max-min);
////    int32_t div_fix = FP2FIX(div, 15);
////-------------------------------------------------------------------------------------
//    imgTest("post filter", now, 6, 16);
////-------------------------------------------------------------------------------------
//
//    //Normalizing to 8 bit and changing fixed point format for NN
//    for(int i=0; i<w*h; i++){
//        img_input_fp8[i] = (uint8_t)(((out_space)*((((((int32_t)img_input_fp16[i])-(int32_t)min))*div_fix)))>>(15-q_output+8));
//    }
////-------------------------------------------------------------------------------------
//    imgTest("16 to 8 bit", now, 6, 8);
////-------------------------------------------------------------------------------------
//    return error;
//}

// SLEEP only works in pulpos: need to be support in freeRTOS when new api available
#ifdef SLEEP
    #define RTC_TIME 5
    void go_to_sleep(){
        rt_rtc_conf_t rtc_conf;
        rt_rtc_t *rtc;

        rtc_conf.clkDivider = 0xF000;
        rt_rtc_cntDwn_t cntDwn = { RTC_TIME, 0 };

        rtc = rt_rtc_open(&rtc_conf, NULL);
        if (rtc == NULL) return -1;

        rt_pm_wakeup_clear_all();

        rt_rtc_control(rtc, RTC_CNTDOWN_SET, (void *)&cntDwn, NULL);
        rt_rtc_control(rtc, RTC_CNTDOWN_START, NULL, NULL);

        if(rt_pm_state_switch(RT_PM_STATE_DEEP_SLEEP, RT_PM_STATE_FAST)==-1)
            printf("Error....\n");
    }
#endif

char bleDetString[200];
char tmpString[200];
int dt = 40;
int old_dt;
float thres;
void sendResultsToBle(bboxs_t *boundbxs){
    int stringLenght = 0;
    int AliveBBs=0;
    for (int counter=0; counter< boundbxs->num_bb; counter++){
        if(boundbxs->bbs[counter].alive && boundbxs->bbs[counter].score>= FP2FIX(thres,7)){
            AliveBBs++;    }    }
    if(AliveBBs>MAX_OUT_BB)    AliveBBs=MAX_OUT_BB;
    stringLenght+=sprintf(bleDetString,"%d;",AliveBBs);
    for (int counter=0; counter< boundbxs->num_bb; counter++){
        if(boundbxs->bbs[counter].alive && boundbxs->bbs[counter].score>= FP2FIX(thres,7)){
            boundbxs->bbs[counter].x = boundbxs->bbs[counter].x + (boundbxs->bbs[counter].w/2);
            boundbxs->bbs[counter].y = boundbxs->bbs[counter].y + (boundbxs->bbs[counter].h/2);
            stringLenght+=sprintf(tmpString,"%dx%d;",boundbxs->bbs[counter].x, boundbxs->bbs[counter].y);
            strcat(bleDetString,tmpString);     }
    }
    //stringLenght+=sprintf(tmpString,"Gap8 Power Consuption %f mW/FPS",((float)(1/(50000000.f/12000000)) * 16.800));
    stringLenght+=sprintf(tmpString,"A Project from GreenWaves and Lynred");
    strcat(bleDetString,tmpString);
    //printf("%s\n",bleDetString);
    //printf("String Size: %d\n",stringLenght);
    dt = handleDetections(bleDetString,stringLenght);
    if(dt < 10)    dt = 10;
    if(dt != old_dt){
        old_dt = dt;
        thres = ((float)old_dt)/100;    }
}
//int detSize = 3+(MAX_OUT_BB*12);
//char * raspDetString = (int *)malloc(detSize * sizeof(int *));
//uint cal = 0;
char raspDetString[3+(MAX_OUT_BB*12)];
void sendResultsToUART(struct pi_device *uart, char *img1, bboxs_t *boundbxs){
//void sendResultsToUART(struct pi_device *uart, unsigned char *img, bboxs_t *boundbxs){
    int stringLenght = 0;
    int AliveBBs = 0;

    for(int i=0; i<3+(MAX_OUT_BB*12); i++)    raspDetString[i] = '\0';

    for (int counter=0; counter < boundbxs->num_bb; counter++){
        if(boundbxs->bbs[counter].alive)    AliveBBs++;    }
    if(AliveBBs > MAX_OUT_BB)   AliveBBs = MAX_OUT_BB;

    stringLenght += sprintf(raspDetString, "%d;", AliveBBs);

    for (int counter=0; counter < boundbxs->num_bb; counter++){
        if(boundbxs->bbs[counter].alive){
            stringLenght += sprintf(tmpString,"%dx%dx%dx%d;", boundbxs->bbs[counter].x, boundbxs->bbs[counter].y, boundbxs->bbs[counter].w, boundbxs->bbs[counter].h);
            strcat(raspDetString, tmpString);    }
    }
//    stringLenght+=sprintf(tmpString,"Gap8 Power Consuption %f mW/FPS",((float)(1/(50000000.f/12000000)) * 16.800));
//    printf("String Size: %d\n",stringLenght);
//    pi_uart_read(uart, &dt, 2);
//    printf("[RX] dt: %d\n", dt);

    pi_uart_write(uart, raspDetString, 3+(MAX_OUT_BB*12));
    printf("[TX] detection\n");

    pi_uart_write(uart, img1, 80*80*sizeof(short));
    printf("[TX] image\n");

//    pi_uart_write(uart, img2, 80*80*sizeof(short));
//    printf("[TX] image\n");

//    dt = handleDetections(raspDetString,stringLenght);
    if(dt < 10)    dt = 10;
    if(dt != old_dt) {
        old_dt = dt;
        thres = ((float)old_dt)/100;
    }
}

uint cal = 0;
void rx_cal(struct pi_device *uart){
    printf("[I] reading cal\n");
    pi_uart_read(uart, &cal, 2);
    printf("[RX] cal: %d\n", cal);
}

pi_fs_file_t *file = NULL;
char *name = "Calibration.bin";
struct pi_device flash;
struct pi_device fs;

static int read_cal_file(){
    prev = (unsigned short *) pmsis_l2_malloc(80*80*sizeof(short));
    img = (unsigned short *) pmsis_l2_malloc(80*80*sizeof(short));
    modified_now = (unsigned short *) pmsis_l2_malloc(80*80*sizeof(short));

    int32_t size = 0;
    uint32_t size_total = 0;
    saved = (unsigned short *) pmsis_l2_malloc(80*80*sizeof(short));
    char *buff = saved;
    if (saved == NULL){
        printf("[!] Failed to allocate Memory for image Offset\n");
        pmsis_exit(-4);
    }
    open_flash_filesystem(&flash, &fs);
    file = pi_fs_open(&fs, name, 0);
    if (file == NULL){
        printf("[!] File %s open failed !\n", name);
        pmsis_exit(-4);
    } do{
        //Read from filesystem(on flash) to a buffer in L2 memory.
        size = pi_fs_read(file, buff+size_total, BUFFER_SIZE);
        size_total += size;
    } while (size_total < file->size);
    pi_fs_close(file);
    close_flash_filesystem(&flash, &fs);

    return 0;
}

#define NUM_OFFSET_IMG 1
#define IMG_SIZE (80*80)
//static struct pi_device cam;
static uint16_t calib_buffer[IMG_SIZE];
static uint32_t img_buffer[IMG_SIZE];
static uint32_t img_buffer1[IMG_SIZE];

static int write_cal_file(unsigned char *img) {
//    for (int i=0; i>IMG_SIZE; i++)    img_buffer1[i] += img[i];
    printf("[I] taking offset image - COVER SENSOR!\n");
    printf("[I] Buffer %p, size %d\n", calib_buffer, IMG_SIZE * sizeof(uint16_t));
    for (int i=0; i>IMG_SIZE; i++)    img_buffer[i]=0;
/* write capture to buffer */
    for (int j=0; j<NUM_OFFSET_IMG; j++) {
        pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
        pi_camera_capture(&cam, calib_buffer, IMG_SIZE*sizeof(uint16_t));
        pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);

        printf("[I] image %d/%d shot for offset image\n", j+1, NUM_OFFSET_IMG);
        for (int i=0; i>IMG_SIZE; i++)    img_buffer[i] += calib_buffer[i];
        pi_time_wait_us(1*100000);
    }
    for (int i=0; i>IMG_SIZE; i++) {
        calib_buffer[i] = img_buffer[i]/NUM_OFFSET_IMG;
    }
//    struct pi_fs_conf conf;
//    pi_fs_conf_init(&conf);
//    conf.type = PI_FS_HOST;
//    pi_open_from_conf(&fs, &conf);
//    if (pi_fs_mount(&fs)) return;
    unsigned char *OutBuffer = (unsigned char *) calib_buffer;
    int datasize = IMG_SIZE*sizeof(uint16_t);
    int steps = datasize/BUFFER_SIZE;
/* write bufffer to fs */
    open_flash_filesystem(&flash, &fs);
    void *File = pi_fs_open(&fs, name, PI_FS_FLAGS_WRITE);
    if (File == NULL){
        printf("[!] File %s open failed !\n", name);
        pmsis_exit(-4);
    }
    for (int i=0; i<steps; i++) {
        pi_fs_write(File, OutBuffer+(BUFFER_SIZE*i), BUFFER_SIZE);    }
    if (((datasize)%BUFFER_SIZE)!=0){
        pi_fs_write(File, OutBuffer+(BUFFER_SIZE*steps), ((datasize)%BUFFER_SIZE)*sizeof(unsigned char));    }
    pi_fs_close(File);
//    pi_fs_unmount(&fs);
    close_flash_filesystem(&flash, &fs);
    printf("[I] cal finished\n");

    return 0;
}

static int null_cal_file(){

    return 0;
}

#ifdef UART
    struct pi_device gpio;
    struct pi_device gpio_led;
    volatile uint8_t trigger = 0;
    void __pi_cb_gpio(void *arg){
        pi_gpio_e gpio_out_led = PI_GPIO_A0_PAD_12_A3;
        pi_gpio_pin_write(&gpio_led, gpio_out_led, 0);
        //wait and read again to be sure that it is not just a float pin
        pi_time_wait_us(5 * 10000);
        pi_gpio_e gpio_pin = (pi_gpio_e) arg;
        uint32_t val = 0;
        pi_gpio_pin_read(&gpio, gpio_pin, &val);

        if(val==1) trigger = 1;
        else trigger = 0;
        //printf("GPIO callback GPIO_A%d %d %d\n", gpio_pin & 0xFF, trigger, val);
    }
#endif

void uart_null_cb(){
    }

#define USER_GPIO 18
void peopleDetection(void){
    char *ImageName = "../../../samples/im2.pgm";
    char *RawImageName = "../../../raw_samples/dump_out_imgs/im_gap_20210125-14_15_04.bin";
    //To configure and use User LED
    //pi_pad_e pad = (GPIO_USER_LED >> PI_GPIO_NUM_SHIFT);
    //uint32_t pin = (GPIO_USER_LED & PI_GPIO_NUM_MASK);
    //pi_pad_set_function(pad, PI_PAD_FUNC0);
    //pi_gpio_pin_configure(NULL, GPIO_USER_LED, PI_GPIO_OUTPUT);
    //pi_gpio_pin_write(NULL, GPIO_USER_LED, 1);

    //To configure and use CONN3 pin8 on Gapoc_b boards that is connected to pad 24 gpio18 of Gap8
    //this can be use as analysis pin (i.e. connect and external osilloscope and check chip activity)
    //pi_pad_set_function(PI_PAD_32_A13_TIMER0_CH1, PI_PAD_32_A13_GPIO_A18_FUNC1);
    //pi_gpio_pin_configure(NULL, USER_GPIO, PI_GPIO_OUTPUT);
    //pi_gpio_pin_write(NULL, USER_GPIO, 1);
//    unsigned int Wi, Hi;
    printf("[I] Entering main controller\n");

     /* Configure And open cluster. */
    struct pi_cluster_conf cl_conf;
    cl_conf.id = 0;
    pi_open_from_conf(&cluster_dev, (void *) &cl_conf);
    if (pi_cluster_open(&cluster_dev)) {
        printf("[!] Cluster open failed !\n");
        pmsis_exit(-7);    }

    pi_freq_set(PI_FREQ_DOMAIN_FC,250000000);
    pi_freq_set(PI_FREQ_DOMAIN_CL,150000000);

    printf("[I] reading cal\n");
    if(read_cal_file()) {
        printf("[!] reading cal failed\n");
        return 1;    }
    printf("[I] Allocating Buffers in L3\n");
    if (initL3Buffers()) {
        printf("[!] L3 Allocation exited with an error\n");
        return 1;    }
    printf("[I] Constructor\n");
    if (lynredCNN_Construct(0)){
        printf("[!] Graph constructor exited with an error\n");
        return 1;    }
//    Deallocating L1 to be used by other cluster calls
    if (lynredCNN_Destruct(1)){
        printf("[!] Error deallocating L1 for cluster...\n");
        pmsis_exit(-1);    }
    #if !defined(INPUT_RAW_FILE) && !defined(INPUT_FILE)
        for (int i = 0; i<1; i++) {
            int GFID = 0xa9;  // DEFAULT = 0xBD / RANGE = 0x00 ~ 0xCC
            int GSK_A = 0x01;  // DEFAULT = 0x01 / RANGE = 0x01 ~ 0x03
            int GSK_B = 0x55;  // DEFAULT = 0x30 / RANGE = 0x00 ~ 0xF3
            int GAIN = 0x73;  // DEFAULT = 0x53 / RANGE = 0x0x ~ 0x7x, 0xx0 ~ 0xx3
            int TINT = 0x50;  // DEFAULT = 0x50 / 0x50, 0xA0, 0xF0
            printf("[I] Opening camera_%d\n", i);
            if (open_camera_thermeye(&cam, GFID, GSK_A, GSK_B, GAIN, TINT)) {
                printf("[!] Thermal Eye camera open failed !\n");
                pmsis_exit(-1);
            }
//        #ifdef OFFSET_IMAGE_EVERY_BOOT
            printf("[I] Shooting offset\n");
            pi_gpio_pin_write(NULL, GPIO_USER_LED, 0);
            pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
            pi_camera_capture(&cam, prev, W*H*sizeof(int16_t));
            pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);
            pi_gpio_pin_write(NULL, GPIO_USER_LED, 1);
//        #endif
        }
    #endif

    #ifdef SAVE_TO_PC
        save_img(saved, "1_saved", 1, 1, 16);
        save_img(prev, "2_prev", 1, 1, 16);
    #endif

    #ifdef BT
        printf("[I] Init BLE\n");
        int status;
        status = initHandler();
        if(status){
            printf("User manager init failed!\n");
            pmsis_exit(-5);
        }
    #endif

    printf("[I] Running NN\n");
    struct pi_cluster_task *task = pmsis_l2_malloc(sizeof(struct pi_cluster_task));
    if(task==NULL){
        printf("[!] Alloc Error! \n");
        pmsis_exit(-7);    }
    memset(task,0,sizeof(struct pi_cluster_task));
    task->entry = RunNN;
    task->arg = (void *) NULL;
    task->stack_size = (uint32_t) STACK_SIZE;
    task->slave_stack_size = (uint32_t) SLAVE_STACK_SIZE;

    #ifdef UART
        pi_pad_set_function(PI_PAD_12_A3_RF_PACTRL0, PI_PAD_FUNC1);
        pi_gpio_flags_e cfg_flags = PI_GPIO_OUTPUT;
        pi_gpio_e gpio_out_led = PI_GPIO_A0_PAD_12_A3;
        pi_gpio_pin_configure(&gpio_led, gpio_out_led, cfg_flags);
        pi_gpio_pin_write(&gpio_led, gpio_out_led, 1); //set off
        //Creating GPIO TASK INPUT
//        led(3, 20, 10);
        struct pi_gpio_conf gpio_conf = {0};
        pi_gpio_conf_init(&gpio_conf);
        pi_open_from_conf(&gpio, &gpio_conf);
        uint32_t errors = 0;
        errors = pi_gpio_open(&gpio);
        if (errors){
            printf("Error opening GPIO %d\n", errors);
            pmsis_exit(errors);    }
     //GPIO A18
        pi_task_t cb_gpio = {0};
        pi_gpio_e gpio_in = PI_GPIO_A18_PAD_32_A13;

        pi_gpio_notif_e irq_type = PI_GPIO_NOTIF_RISE;
        cfg_flags = PI_GPIO_INPUT|PI_GPIO_PULL_DISABLE|PI_GPIO_DRIVE_STRENGTH_HIGH;

        pi_task_callback(&cb_gpio, __pi_cb_gpio, (void *) gpio_in);
        /* Configure gpio input. */
        pi_gpio_pin_configure(&gpio, gpio_in, cfg_flags);
        pi_gpio_pin_task_add(&gpio, gpio_in, &cb_gpio, irq_type);
        pi_gpio_pin_notif_configure(&gpio, gpio_in, irq_type);
//    // GPIO CONN3-6
//        pi_gpio_e cal_pin = PI_GPIO_A2_PAD_10_A5;
//        pi_task_callback(&cb_gpio, __pi_cb_gpio, (void *) cal_pin);
//        /* Configure gpio input. */
//        pi_gpio_pin_configure(&gpio, cal_pin, cfg_flags);
//        pi_gpio_pin_task_add(&gpio, cal_pin, &cb_gpio, irq_type);
//        pi_gpio_pin_notif_configure(&gpio, cal_pin, irq_type);
    //Opening UART
        struct pi_device uart;
        struct pi_uart_conf conf;
    /* Init & open uart. */
        pi_uart_conf_init(&conf);
        conf.enable_tx = 1;
        conf.enable_rx = 1;
        conf.baudrate_bps = 115200;
        pi_open_from_conf(&uart, &conf);
        if (pi_uart_open(&uart)){
            printf("Uart open failed !\n");
            pmsis_exit(-1);    }
    #endif

    unsigned int save_index = 0;
    clock_t t;
    unsigned char l;

    #ifdef LOOP
        l = 0;
    #else
        l = 1;
    #endif


    uint loop_cnt = 1;
    while(loop_cnt){
        int t = pi_time_get_us();
        printf("\n[START] -------------------------------------------------\n");
        #ifdef UART
            printf("[RX] Waiting Pi Signal\n");
            while(!trigger){
                pi_yield();
            } trigger=0;
//            uint cal = 0;
//            struct pi_device *u = &uart;
//            pi_uart_read(u, &cal, 2);
            rx_cal(&uart);

            #ifdef RNN
                now_to_char = (unsigned char *) pmsis_l2_malloc(W*H*sizeof(short));
                if (now_to_char == 0) {
                    printf("Failed to allocate Memory for Image (%d bytes)\n", W * H * sizeof(uint16_t));
                    return 1;
                }
                now = (int16_t *) now_to_char;

                printf("[I] Caputring IR Image\n");
                pi_gpio_pin_write(NULL, USER_GPIO, 0); // on
                pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
                pi_camera_capture(&cam, now, W*H*sizeof(int16_t));
                pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);
                pi_gpio_pin_write(NULL, USER_GPIO , 1); // off

                /* offset image - max: 65535 */
                switch (cal) {
                case 11111:
                    printf("[S:11111] offset: prev\n");
                    offset = prev;
                    break;
                case 22222:
                    printf("[S:22222] offset: saved\n");
                    offset = saved;
                    break;
                case 33333:
                    printf("[S:33333] offset: prev\n");
                    offset = prev;
                    break;
                case 44444:
                    printf("[S:44444] overiding cal file\n");
                    if (write_cal_file(now)) {
                        printf("[!] Writing cal file failed\n");
                        pmsis_exit(-8);    }
                    break;
                case 55555:
                    printf("[S:55555] nulling cal file\n");
                    if (null_cal_file()) {
                        printf("[!] Writing cal file failed\n");
                        pmsis_exit(-8);    }
                    break;
                default:
                    printf("[S:0] offset: saved\n");
                    offset = saved;
                    break;
                }
            #endif
        #endif
        //        unsigned int *aaa = now;
        //        memcpy(aaa, img1, W*H*2*sizeof(short));

        #ifndef INPUT_FILE
            printf("[I] Calling shutterless filtering\n");
            #ifdef SHUTTERLESS_FILTER
                //shutterless floating point version was done just for reference.very slow on gap.
                //if(float_shutterless(now, offset,W,H,8,1)){
                if(fixed_shutterless(prev, saved, W, H, 8)) {
                    printf("[!] Error Calling prefiltering, exiting...\n");
                    pmsis_exit(-8);    }
            #elif CUSTOM_FILTER
                if(custom_prefilter(now, offset, W, H, 8)) {
                    printf("[!] Error Calling prefiltering, exiting...\n");
                    pmsis_exit(-8);    }
            #endif
        #endif

        #ifdef SAVE_TO_PC
            save_img(prev, "3_result", 0, 1, 0);
        #endif

        printf("[I] Call cluster\n");
        int nn = pi_time_get_us();
        //Explicitly allocating Cluster stack since it could also be used by shutterless
        task->stacks = pmsis_l1_malloc(STACK_SIZE+SLAVE_STACK_SIZE*7);
        //Calling warm constructor to allocate only L1
        if(lynredCNN_Construct(1)){
            printf("[I] Error allocating L1 for cluster...\n");
            pmsis_exit(-1);    }
        pi_cluster_send_task_to_cl(&cluster_dev, task);
        lynredCNN_Destruct(1);
        pmsis_l1_malloc_free(task->stacks, STACK_SIZE+SLAVE_STACK_SIZE*7);
        nn = pi_time_get_us() - nn;
        printf("[I] model runtime : %.02f s\n", ((float)nn)/1000000);

//        switch (cal) {
//            case 11111:
//                printf("[S:11111] img: now\n");
//                img = now;
//                break;
//            case 22222:
//                printf("[S:22222] img: now\n");
//                img = modified_now;
//                break;
//            case 33333:
//                printf("[S:33333] img: now\n");
//                img = modified_now;
//                break;
//            default:
//                printf("[S:0] img: now\n");
//                img = now;
//                break;
//            }
//        img = now;

        #ifdef UART
            printf("[I] TX Result to Pi\n");
            sendResultsToUART(&uart, prev, &bbxs);
            pi_gpio_pin_write(&gpio_led, gpio_out_led, 1); // led_off
        #endif

        #ifdef BT
            sendResultsToBle(&bbxs);
            #ifndef SAVE_TO_PC
                pi_time_wait_us(2 * 1000 * 1000);
            #endif
        #endif

        save_index++;

        loop_cnt -= l;
        printf("[I] loop : %d\n", loop_cnt);
        t = pi_time_get_us() - t;
        printf("[FINISH] -------------------------- total runtime : %.02f s\n\n", ((float)t)/1000000);

        #ifdef SLEEP
        //This is not the optimized deep sleep, when should take care of pad setting in sleep and to properly shutdown all external devices
            go_to_sleep();
        #endif
    }
    lynredCNN_Destruct(0);
    pi_cluster_close(&cluster_dev);
    printf("[I] Ended\n");
    pmsis_exit(0);
}

int main(void) {
    printf("\n\n\t *** Therm Eye ***\n");
//    printf("\tModel_Version: %1.1f\n\n", MODEL_VERSION);
    printf("\tBoard Number: %d\n", BOARD_NUM);
    return pmsis_kickoff((void *) peopleDetection);
}
