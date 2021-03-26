#pragma once

/********** Includes ***********/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <esp_log.h>
#include <esp_sleep.h>

#include "lora.h"               /*https://github.com/Inteform/esp32-lora-library*/
#include "ds18b20.h"            /*https://github.com/feelfreelinux/ds18b20*/

#include <driver/adc.h>         /*ADC*/
#include <esp_adc_cal.h>

#include <math.h>               // EXP and log

/********** Defines ***********/
#define NUM_SENSORS     3
#define SENSOR_DELAY    pdMS_TO_TICKS(800)  // Time each sensor waits between samples 
#define CHANGE_DELAY    pdMS_TO_TICKS(3*1000)  // Time machine waits while changing between sensors
//#define SLEEP_DELAY     5400000000ULL/*1.5 hour*/  // Time of the nap
//#define SLEEP_DELAY     1800000000ULL/*0.5 hour*/  // Time of the nap
#define SLEEP_DELAY     60*1000   // 1 minute

#define MAX_SAMPLES     20           

#define GPIO            17          // GPIO for OneWire (Temp)

#define DEBUG
//#define CONT                      // Not used yet
//#define ORP            
#define CONVERT_DO                  //CONVERT THE DO, TESTING

#define O2_CALIBRATION          870
#define O2_SOLUTION_CALIBRATION 0
#define PRES                    0.9910f      // contrasted. Units: atm
#define ORP_CALIBRATION         19.0


/*Defines needed of LoRa Library*/
#define CONFIG_CS_GPIO      18
#define CONFIG_RST_GPIO     14
#define CONFIG_MISO_GPIO    19
#define CONFIG_MOSI_GPIO    27
#define CONFIG_SCK_GPIO     5

/********** Structures *********/

// Parameter 
typedef enum {
    O2,
    Temp,
    Cont,
    Orp
}Id_t;

// Place
typedef enum {
    BERCARIO_01
}Id_sender_t;

/*The final results are sent with an identifier to the reciver*/
typedef struct{
    Id_t id;
    Id_sender_t sender;
    float data;
}Data_t;


/*********** Declarations *******/
    
// Sensors
void analog_init(void); //Here we initialize every analog channel we will use

float get_temp(void);
float get_o2(float);
#ifdef CONT
float get_cont(void);
#endif
#ifdef ORP
float get_orp(void);    
#endif
#ifdef CONVERT_DO
float convert_do(float, float);
#endif

// LoRa
void lora_utils_init();           
void lora_utils_send(Data_t d); 