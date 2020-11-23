/*
    SENSORS

    Functions to get the data from sensors.
    All of them must return an average of several samples.
    Return value of FLOAT
*/


#include "main.h"

float get_temp(){
    uint8_t i;
    float   value = 0;

    for(i = 0; i < MAX_SAMPLES; i++){
        value += ds18b20_get_temp();
        vTaskDelay(SENSOR_DELAY);
    }

    return value/MAX_SAMPLES;
}

float get_o2(){
    uint8_t i;
    float   value = 0;

    for(i = 0; i < MAX_SAMPLES; i++){
        //value += libraryFunctionO2();
        vTaskDelay(SENSOR_DELAY);
    }

    return value/MAX_SAMPLES;
}

float get_cont(){
    uint8_t i;
    float   value = 0;

    for(i = 0; i < MAX_SAMPLES; i++){
        value += adc1_get_raw(ADC1_CHANNEL_0);           // Lectura analógica!! Las compensaciones se hacen después
        vTaskDelay(SENSOR_DELAY);      //Mínimo 5 segundos
    }

    return value/MAX_SAMPLES;
}

#ifdef cali
float contCompensate(float cont, float temp){                   /* Source: https://how2electronics.com/iot-based-tds-meter-using-esp8266-for-water-quality-monitoring/ */
    float temperatureCoefficient = 1.0 + 0.019 * (temp - 25.0);    
    return (cont / temperatureCoefficient) * ecCalibration; //Cuál es la calibración??
}
#endif