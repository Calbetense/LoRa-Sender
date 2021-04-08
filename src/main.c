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
    toSend.sender = BERCARIO_01;            // Change this data with the place the sensors are placed

    #ifdef CONVERT_DO
    float temp_now = 0;    
    #endif

    //Loop
    while(1){
        
        toSend.id = Temp;
        toSend.data = get_temp();
        lora_utils_send(toSend);
        #ifdef CONVERT_DO
        temp_now = toSend.data;
        #endif
        #ifdef DEBUG
        ESP_LOGI(TAG, "TEMP send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY_TEMP);

        toSend.id = O2;
        toSend.data = get_o2(temp_now);
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "O2 send, %f\n\n", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY_DO);

        #ifdef ORP
        toSend.id = Orp;
        toSend.data = get_orp();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "ORP send, %f", toSend.data);
        #endif
        vTaskDelay(CHANGE_DELAY_ORP);
        #endif

        #ifdef CONT
        toSend.id = Cont;
        toSend.data = get_cont();
        lora_utils_send(toSend);
        #ifdef DEBUG
        ESP_LOGI(TAG, "CONT send, %f", toSend.data);
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

void gpio_init(){
    //GPIO configuration
    gpio_config_t gpio_conf = {
        //disable interrupts
        .intr_type = GPIO_INTR_DISABLE,
        //set output mode
        .mode = GPIO_MODE_OUTPUT,
        //bit mask of the pins you want to set
        .pin_bit_mask = (1ULL << GPIO_ORP) | (1ULL << GPIO_DO),
        //disable pull up and pull down
        .pull_down_en = 0,
        .pull_up_en   = 0
    };

    gpio_config(&gpio_conf);
    gpio_set_level(GPIO_DO, 0);  
    gpio_set_level(GPIO_ORP, 0);  

}

void app_main() {

    lora_utils_init();
    ds18b20_init(GPIO); // Temp Init
    analog_init();      // Analog sensors init
    gpio_init();

    #ifdef DEBUG
    ESP_LOGI(TAG, "Everything's init. (Teorically)");
    #endif

    xTaskCreate(main_task, "main", 2048, NULL, 1, NULL);

    vTaskDelete(NULL);
}