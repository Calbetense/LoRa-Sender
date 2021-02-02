/*
    SENSORS

    Functions to get the data from sensors.
    All of them must return an average of several samples.
    Return FLOAT value
*/


#include "main.h"

//Global - General ADC Calibration 
esp_adc_cal_characteristics_t adc_cal;

void analog_init(void){
    
    adc1_config_width(ADC_WIDTH_BIT_10);                        
    
    //O2 init (ADC1, Channel 0)
    adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_DB_11);   // O2

    #ifdef CONT
    //Cond init (ADC1, Channel 1)
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);   // Cont
    #endif

    #ifdef ORP
    //ORP init (ADC1, Channel 2)
    adc1_config_channel_atten(ADC1_CHANNEL_2,ADC_ATTEN_DB_11);   // ORP?
    #endif

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_10, 1100, &adc_cal);
}


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
        value += (float)adc1_get_raw(ADC1_CHANNEL_1);
        vTaskDelay(SENSOR_DELAY);
    }

    //Result in mV
    value = (float)esp_adc_cal_raw_to_voltage(value/MAX_SAMPLES, &adc_cal); 

    value *= 100/O2_CALIBRATION; 
    value += O2_SOLUTION_CALIBRATION;

    return value;     
}

#ifdef CONT         // If you finnaly work with this, reestructure the calibration part to be like the other parameters
float get_cont(){
    uint8_t i;
    float   value = 0;

    for(i = 0; i < MAX_SAMPLES; i++){
        value += (float)adc1_get_raw(ADC1_CHANNEL_1);           
        vTaskDelay(SENSOR_DELAY);                               
    }

    return esp_adc_cal_raw_to_voltage(value/MAX_SAMPLES, &adc_cal);
}
#endif 

#ifdef ORP
float get_orp(void){
    uint8_t i;
    float   value = 0;

    for(i = 0; i < MAX_SAMPLES; i++){
        value += (float)adc1_get_raw(ADC1_CHANNEL_2);
        //ESP_LOGI("PRUEBAS", "value = %f", value);
        vTaskDelay(SENSOR_DELAY);
    }
    value /= MAX_SAMPLES;
    //ESP_LOGI("PRUEBAS", "Average value = %f", value);

    value = (float)esp_adc_cal_raw_to_voltage(value, &adc_cal);
    //ESP_LOGI("PRUEBAS", "Voltage of value = %f", value);

    value -= (1500 + ORP_CALIBRATION);   
    //ESP_LOGI("PRUEBAS", "Result of value = %f", value);

    return value;
}
#endif