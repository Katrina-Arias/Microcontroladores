#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>
#include "led_strip.h"
#include "esp_log.h"


//Aqui se definen constantes y variables globales

//pin al que esta conectado el LED RGB que trae integrado el ESP32-S3-DevKitC-1
#define RGB_LED 48
//declaracion de la cantidad de LEDs RGB
#define MAX_LEDS 1

//define la etiqueta para los menajes LOG
static const char *TAG = "LED STRIP";
//se declara un puntero que apunta a una estructura para asi controlar el RGB
static led_strip_t *pStrip_a ;

//funcion para inicializar y encender la tira led en una primera instancia
static void set_rgb_led(void)
{
    pStrip_a = led_strip_init(0, RGB_LED, MAX_LEDS);
    pStrip_a -> clear(pStrip_a, 100);
}

void app_main(void) 
{
    set_rgb_led();

    //bucle infinito en el cual se prende y apaga el RGB,
    //pero siempre cambiando de color de rojo, verde, azul y blanco
    //se repite este ciclo indefinidamente 
    while(1){
        ESP_LOGI(TAG, "LED RED");
        //configura el RGB al color deseado
        pStrip_a -> set_pixel(pStrip_a,0, 255, 0, 0);
        //actualiza el RGb para mostrar el resultado con una espera de 100ms
        pStrip_a -> refresh(pStrip_a, 100);
        //Delay de 1s
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED GREEN");
        pStrip_a -> set_pixel(pStrip_a,0, 0, 255, 0);
        pStrip_a -> refresh(pStrip_a, 100);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED BLUE");
        pStrip_a -> set_pixel(pStrip_a,0, 255, 0, 255);
        pStrip_a -> refresh(pStrip_a, 100);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI(TAG, "LED WHITE");
        pStrip_a -> set_pixel(pStrip_a,0, 255, 255, 255);
        pStrip_a -> refresh(pStrip_a, 100);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
