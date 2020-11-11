/*
    LoRa

    Functions to expand LoRa library
*/


#include "main.h"

void lora_utils_init(){
    lora_init();
    lora_set_frequency(915e6);
    lora_enable_crc();
}

void lora_utils_send(Data_t d){
    lora_send_packet((uint8_t*)data_t, sizeof(Data_t));     //CHECK! Si sólo se necesita esto igual esta librería sobra
}