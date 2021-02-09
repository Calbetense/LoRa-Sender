/*
    Sender: This code colects the info from the sensors and sends it Via LoRa.

    Process: Initialization, Calibration, and loop. 
    Loop: sampling, averaging, send and sleep.
*/


#include "main.h"

const char* TAG = "MAIN";

void main_task(void *p){

    //Declarations
    Data_t toSend;

    //Loop
    while(1){

        toSend.id = Temp;
        toSend.data = get_temp();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "TEMP send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY);

        /*      Allow the Oxygen just when the probe is ready
        toSend.id = O2;
        toSend.data = get_o2();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "O2 send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY);
        */

        #ifdef CONT
        toSend.id = Cont;
        toSend.data = get_cont();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "CONT send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY);
        #endif

        #ifdef ORP
        toSend.id = Orp;
        toSend.data = get_orp();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "ORP send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY);
        #endif

        //If more, just follow the schem

            
        //Sleep Wake configuration
        esp_sleep_enable_timer_wakeup(SLEEP_DELAY);            
        esp_deep_sleep_start();  //Sleeps 2h

        //Should never reach this point
    }
}

void app_main() {

    lora_utils_init();
    ds18b20_init(GPIO); // Temp Init
    analog_init();      // Analog sensors init

    #ifdef DEBUG
    ESP_LOGI(TAG, "Everything's init. (Teorically)");
    #endif

    xTaskCreate(main_task, "main", 2048, NULL, 1, NULL);

    vTaskDelete(NULL);
}