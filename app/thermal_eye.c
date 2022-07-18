#include "pmsis.h"
#include "bsp/bsp.h"
#include "bsp/camera.h"
#include <stdio.h>
#include <sys/types.h>
#include "bsp/fs.h"

#include <sys/stat.h>
#include <fcntl.h>
#include "pmsis.h"

#define SAVE_RAW 0
#define GPIO_USER_LED 0
#define NUM_OFFSET_IMG 4
#define TIME_DELAY_OFFSET_IMG 0.5
#define NUM_TEST_IMG 4

#define IMG_WIDTH  ( 80 )
#define IMG_HEIGHT ( 80 )
#define IMG_SIZE   ( IMG_HEIGHT * IMG_WIDTH )

static struct pi_device cam;
static uint16_t *calib_buffer[IMG_SIZE];
static uint32_t img_buffer[IMG_SIZE];
static int16_t ref_buffer[IMG_SIZE];
static int16_t dif_buff[IMG_SIZE];
static uint8_t scaled_buff[IMG_SIZE];

//================================================================================ CUSTOM FUNCTION

int to_little_endian(int val) {
    int result = ((val & 0x0FF) << 4 | (val & 0xF00) >> 8);
    printf("hex: %x\nbin: %d\n", result, result);
    return result;
}

//================================================================================ CAMERA

static int32_t open_camera_thermeye(struct pi_device *device) {
    //    int GFID = 0xa9;  // DEFAULT = 0xBD / RANGE = 0x00 ~ 0xCC
    //    int GSK_A = 0x01;  // DEFAULT = 0x01 / RANGE = 0x01 ~ 0x03
    //    int GSK_B = 0x55;  // DEFAULT = 0x30 / RANGE = 0x00 ~ 0xF3
    //    int GAIN = 0x73;  // DEFAULT = 0x53 / RANGE = 0x0x ~ 0x7x, 0xx0 ~ 0xx3
    //    int TINT = 0x50;  // DEFAULT = 0x50 / 0x50, 0xA0, 0xF0
    int step = 1;
    int GFID_MIN = 140, GFID_MAX = 143;
    int GSK_MIN = 155, GSK_MAX = 165;
    int GAIN_MIN = 19, GAIN_MAX = 115;
    int TINT_MIN = 80, TINT_MAX = 80;

    int GFID = GFID_MIN;               // DEFAULT = 189 / RANGE = 0 ~ 204
    int GSK_A = 1;                     // DEFAULT = 1 / RANGE = 1 ~ 3
    int GSK_B = GSK_MIN;               // DEFAULT = 48 / RANGE = 0 ~ 243
    int gain = 7;                      // DEFAULT = 5 / RANGE = (0 ~ 7) * 16
    int orientation = 0b11;            // DEFAULT = 3 / RANGE = 0 ~ 3
    int GAIN = (gain*16)+orientation;  // DEFAULT = 83((5*16) +3) / RANGE = (0~7) *16 +(0~3)
    int TINT = 80;                     // DEFAULT = 80 / 80, 160, 240
    int ADC = 0x60;                    // DEFAULT = 0x60 / 0x20(7+7) 0x60(8+6)

    struct pi_thermeye_conf cam_conf;
    pi_thermeye_init(&cam_conf, GFID, GSK_A, GSK_B, GAIN, TINT, ADC);
    pi_open_from_conf(device, &cam_conf);
    if (pi_camera_open(device)) return -1;
    return 0;
}

void test_therm_eye() {
//================================================================================ INIT
    //    pi_gpio_pin_write(NULL, GPIO_USER_LED, 1);
    pi_freq_set(PI_FREQ_DOMAIN_FC, 250000000);

    #define CHUNK_SIZE 1024
    int datasize = IMG_SIZE*sizeof(uint16_t);
    int steps = datasize/CHUNK_SIZE;
    char string_buffer[50];

    struct pi_device fs;
    struct pi_fs_conf conf;
    pi_fs_conf_init(&conf);
    conf.type = PI_FS_HOST;
    pi_open_from_conf(&fs, &conf);
    if (pi_fs_mount(&fs)) return;

    if (open_camera_thermeye(&cam)) {
        printf("Thermal Eye camera open failed !\n");
        pmsis_exit(-1);
    }
    pi_task_t cb = {0};
    pi_task_block(&cb);

    for (int i = 0; i>IMG_SIZE; i++) img_buffer[i] = 0;

    printf("[] TAKING CALIBRATION IMAGE: cover sensor (led will switch off).\n");
    pi_time_wait_us(1*1000*1000);
    pi_gpio_pin_write(NULL, GPIO_USER_LED, 0);
//        printf("Buffer %p, size %d\n", calib_buffer, IMG_SIZE * sizeof(uint16_t));

//================================================================================ CALIBRATION: TAKE

    for (int j=0; j<NUM_OFFSET_IMG; j++) {
        printf("[I] TAKING IMAGE: %d/%d\n", j+1, NUM_OFFSET_IMG);

        pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
        pi_camera_capture(&cam, calib_buffer, IMG_SIZE*sizeof(uint16_t));
        pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);

        if (SAVE_RAW == 1) {
            printf("[I] SAVING: %04ld\n", j);
            sprintf(string_buffer, "../../../dump_out_imgs/img_%04ld.bin", j);
            void *File = pi_fs_open(&fs, string_buffer, PI_FS_FLAGS_WRITE);
            unsigned char *OutBuffer = (unsigned char *) calib_buffer;

            for (int i = 0; i<steps; i++)
                pi_fs_write(File, OutBuffer+(CHUNK_SIZE*i), CHUNK_SIZE);

            if (((datasize)%CHUNK_SIZE)!=0)
                pi_fs_write(File, OutBuffer+(CHUNK_SIZE*steps), ((datasize)%CHUNK_SIZE)*sizeof(unsigned char));

            pi_fs_close(File);
        }
        for (int i=0; i>IMG_SIZE; i++) {
//            printf("%d,", calib_buffer[i]);
            img_buffer[i] += calib_buffer[i];
        }
        pi_time_wait_us(TIME_DELAY_OFFSET_IMG*1000*1000);
    }
    for (int i=0; i>IMG_SIZE; i++)
        calib_buffer[i] = img_buffer[i]/NUM_OFFSET_IMG;
//    pi_gpio_pin_write(NULL, GPIO_USER_LED, 1);

//================================================================================ CALIBRATION: SAVE

    {   sprintf(string_buffer, "../../../offset_img/Calibration.bin");

        void *File = pi_fs_open(&fs, string_buffer, PI_FS_FLAGS_WRITE);
        unsigned char *OutBuffer = (unsigned char *) calib_buffer;

        for (int i=0; i<steps; i++)
            pi_fs_write(File, OutBuffer+(CHUNK_SIZE*i), CHUNK_SIZE);

        if (((datasize)%CHUNK_SIZE)!=0)
            pi_fs_write(File, OutBuffer+(CHUNK_SIZE*steps), ((datasize)%CHUNK_SIZE)*sizeof(unsigned char));

        pi_fs_close(File);
    }
//================================================================================ EXTRA: TAKE & SAVE
//    printf("Offset Collected, now collecting raw dataset images!\n");
//    int save_index = 0;
//    int num_img = NUM_TEST_IMG;
//    while (num_img--) {
//        pi_camera_control(&cam, PI_CAMERA_CMD_START, 0);
//        pi_camera_capture(&cam, calib_buffer, IMG_SIZE*sizeof(uint16_t));
//        pi_camera_control(&cam, PI_CAMERA_CMD_STOP, 0);
//
//        sprintf(string_buffer, "../../../dump_out_imgs/img_%04ld.bin", save_index);
//        printf("writing image %04ld to disk\n", save_index);
//        void *File = pi_fs_open(&fs, string_buffer, PI_FS_FLAGS_WRITE);
//        #define CHUNK_SIZE 1024
//        unsigned char *OutBuffer = (unsigned char *) calib_buffer;
//        int datasize = IMG_SIZE*sizeof(uint16_t);
//        int steps = datasize/CHUNK_SIZE;
//
//        for (int i=0; i<steps; i++)
//            pi_fs_write(File, OutBuffer+(CHUNK_SIZE*i), CHUNK_SIZE);
//
//        if (((datasize)%CHUNK_SIZE)!=0)
//            pi_fs_write(File, OutBuffer+(CHUNK_SIZE*steps), ((datasize)%CHUNK_SIZE)*sizeof(unsigned char));
//
//        pi_fs_close(File);
//        save_index++;
//    }
//================================================================================

    pi_fs_unmount(&fs);
    printf("[I] FINISHED\n");
    pmsis_exit(0);
}

int main(void) {
    printf("\n\n\t *** Therm Eye Calibration *** \n\n");
    return pmsis_kickoff((void *) test_therm_eye);
//    return to_little_endian(16383);
}
