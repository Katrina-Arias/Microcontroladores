
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


//declarando los gpio de entradas y salidas
#define LED 2
#define BT 1

void app_main()
{
  //indicando que el pin 2 es una salida
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  //indicando que el pin 1 es una entrada
  gpio_set_direction(BT, GPIO_MODE_INPUT);
  //poniendole una pull-down
  gpio_set_pull_mode(BT, GPIO_PULLDOWN_ONLY);


  while (1)
  {
    //prender el led con un boton
    //guardando valor como un entero de la entrada del boton
    int state_bt = gpio_get_level(BT);
    //imprimiendo por consola
    printf("%d\n", state_bt);
    //si el boton es presionado la salida para el led se pone en 1
    if (state_bt)
    {
      gpio_set_level(LED, 1);
    }
    //en cambio si no se presiona el boton la salida para el led se mantiene en 0
    else
    {
      gpio_set_level(LED, 0);
    }
    //Delay
    vTaskDelay(pdMS_TO_TICKS(200));

    //LED intermitente
    
    // gpio_set_level(LED, 1);
    // vTaskDelay(pdMS_TO_TICKS(1000));
    // gpio_set_level(LED, 0);
    // vTaskDelay(pdMS_TO_TICKS(1000));
  }

  
}