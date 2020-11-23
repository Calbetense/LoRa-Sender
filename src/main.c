/*
    Sender: This code colects the info from the sensors and sends it Via LoRa.

    Process: Initialization, Calibration, and loop. Loop: sampling, averaging, send and sleep.
*/


#include "main.h"

const char* TAG = "MAIN";

void main_task(void *p){

    //Declarations
    Data_t toSend;
    //float temp;

    //Loop
    while(1){
        toSend.id = Temp;
        toSend.data = get_temp();
        //temp = toSend.data;
        lora_utils_send(toSend);
        //ESP_LOGI(TAG, "TEMP send, %f", toSend.data);
        vTaskDelay(CHANGE_DELAY);

/*
        toSend.id = O2;
        toSend.data = get_o2();
        lora_send(toSend);
        ESP_LOGI(TAG, "O2 send, %f", toSend.data);
        vTaskDelay(CHANGE_DELAY);
*/
/*
        toSend.id = Cont;
        toSend.data = get_cont();
        contCompensate(toSend.data, temp);
        lora_send(toSend);
        ESP_LOGI(TAG, "CONT send, %f", toSend.data);
        vTaskDelay(CHANGE_DELAY);
*/

        //If more, just follow the schem
        
        //Everything_sleep();   //Sleeps 2h
    }
}

void app_main() {

    lora_utils_init();
    ds18b20_init(GPIO); // Temp Init
    //o2_init();
    
    //Cond init (ADC1, Channel 0)
    //adc1_config_width(ADC_WIDTH_BIT_12);
    //adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);

    ESP_LOGI(TAG, "Everything's init.");

    xTaskCreate(main_task, "main", 1024, NULL, 1, NULL);

    vTaskDelete(NULL);
}