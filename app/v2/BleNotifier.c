#include "bsp/bsp.h"
#include "bsp/buffer.h"
#include "bsp/ble/nina_b112.h"
#include "pmsis.h"
#include "setup.h"
#include "BleNotifier.h"

#define START_MESSAGE 0x02
#define END_MESSAGE   0x03
#define PI_AT_RESP_ARRAY_LENGTH 64
uint8_t message[200];
uint8_t detection_threshold;
uint8_t rx_buffer[PI_AT_RESP_ARRAY_LENGTH];

static struct pi_device ble;

int initHandler(){
    int status=1;
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_UART_RX_PAD_FUNC);
    #endif
    PRINTF("Enabling BLE module...\n");

    int32_t errors = 0;
    struct pi_nina_b112_conf conf = {0};
    pi_ble_nina_b112_conf_init(&ble, &conf);
    pi_open_from_conf(&ble, &conf);
    errors += pi_ble_open(&ble);
    if (errors){
        printf("Failed to open nina ble %ld\n", errors);
        pmsis_exit(-1);
    }
    PRINTF("BLE UART init done\n");
    pi_time_wait_us(50*1000);
    errors += pi_ble_ioctl(&ble, PI_NINA_B112_CLIENT_CONFIGURE, NULL);

    /* Retrieve BLE module name. */
    pi_ble_at_cmd(&ble, "+UBTLN?", (void *) rx_buffer, 1);
    PRINTF("BLE name: %s\n", rx_buffer);
    pi_time_wait_us(50 * 1000);
    /* Retrieve BLE HCI configuration. */
    pi_ble_at_cmd(&ble, "+UMRS?", (void *) rx_buffer, 1);
    PRINTF("BLE UART settings: %s\n", rx_buffer);
    pi_time_wait_us(50 * 1000);
    // After Reboot of NINA,  central connects to NINA and NINA will provide
    // unsollicited AT event: +UUBTACLC:<peer handle,0,<remote BT address>)
    // (...but sometimes just provides empty event instead !?)

    // Just make sure NINA sends something as AT unsolicited response, therefore is ready :
    pi_ble_ioctl(&ble, PI_NINA_B112_WAIT_FOR_EVENT, (void *) rx_buffer);
    PRINTF("Received Event after reboot: %s\n", rx_buffer);
    pi_time_wait_us(1000 * 1000);
    // Enter Data Mode
    pi_ble_ioctl(&ble, PI_NINA_B112_DATA_MODE_ENTER, NULL);
    PRINTF("Data Mode Entered!\n");

    /* Wait 50 ms. */
    pi_time_wait_us(50 * 1000);
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_HYPERRAM_DATA6_PAD_FUNC);
    #endif
    return errors;
}

uint8_t handleDetections(char *name, int size){
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_UART_RX_PAD_FUNC);
    #endif
    //insert start marker
    message[0] = START_MESSAGE;
    int i;
    for(i = 0; i < size; i++)    message[i+1] = name[i];
    //insert end marker
    message[i+1] = END_MESSAGE;
    PRINTF("Ble Sending: %s\n", message);

    pi_ble_data_send(&ble, message,  size+2);
    
    PRINTF("Data sent, wating for thereshold\n");
    pi_ble_data_get(&ble, &detection_threshold, 1);

    PRINTF("Ble receiving: %d\n", detection_threshold);
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_HYPERRAM_DATA6_PAD_FUNC);
    #endif

    return detection_threshold;
}

void closeHandler(){
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_UART_RX_PAD_FUNC);
    #endif
    pi_nina_b112_close(&ble);
    #ifdef __GAP8__
        pi_pad_set_function(CONFIG_HYPERBUS_DATA6_PAD, CONFIG_HYPERRAM_DATA6_PAD_FUNC);
    #endif
}
