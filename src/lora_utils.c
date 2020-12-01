/*
    LoRa

    Functions to expand LoRa library
*/


#include "main.h"

void lora_utils_init(){
    lora_init();

    lora_set_bandwidth(125E3);      // Couple of values for a good distance
    lora_set_spreading_factor(9);

    lora_set_frequency(915e6);      // Brasil's Legal frequancy

    lora_enable_crc();
}

void lora_utils_send(Data_t d){
    lora_send_packet((uint8_t*)&d, sizeof(d));     //CHECK! Si sólo se necesita esto igual esta librería sobra
    lora_close();
}