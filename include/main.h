
#pragma once

/*Includes*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <esp_log.h>

#include "lora.h"               /*https://github.com/Inteform/esp32-lora-library*/
#include "ds18b20.h"            /*https://github.com/feelfreelinux/ds18b20*/

#include <driver/adc.h>         /*ADC, conductivity*/

/*Defines*/
#define NUM_SENSORS     3
#define SENSOR_DELAY    pdMS_TO_TICKS(10*1000) //10seconds    
#define CHANGE_DELAY    pdMS_TO_TICKS(2/*Hour*/*60/*Minutes*/*60/*Seconds*/*1000/*Miliseconds*/)

#define MAX_SAMPLES     3

/*Defines needed of LoRa Library*/
#define CONFIG_CS_GPIO      18
#define CONFIG_RST_GPIO     14
#define CONFIG_MISO_GPIO    19
#define CONFIG_MOSI_GPIO    27
#define CONFIG_SCK_GPIO     5

/*Structures*/
typedef enum {
    O2,
    Temp,
    Cont
}Id_t;

typedef struct
{
    Id_t id;
    float data;
}Data_t;


/*declarations*/
    
    // Sensors
    float get_temp(void);
    float get_o2(void);
    float get_cont(void);

    float contCompensate(float cont, float temp);

    // LoRa
void lora_utils_init();           //TODO
void lora_utils_send(Data_t d); //TODO