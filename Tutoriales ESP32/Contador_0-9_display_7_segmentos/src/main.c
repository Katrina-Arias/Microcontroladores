#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


//definiendo los GPIO a utilizar

//GPIO en donde estara conectado el boton
#define BT 1
// #define LED 4

//declaracion e inicializacion del array que indica el numero de los GPIO a utlizar del esp32-s3
int display [] = {4, 5, 6, 7, 15, 16, 17};

//declaracion e inicializacion de la secuencia de encendido para el display de 7 segmentos
char number[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};


void init_hardware(void);

void app_main(){

  init_hardware();
  int cnt = 0;
  //mostrando en una primera instancia el numero 0
  for (int i = 0; i < 7; i++){
    //funcion para poner en 0 o 1 un pin
    gpio_set_level(display[i], number[0][i]);
  }

  //Se pone la logica en un bucle infinito para que siempre se ejecute
  while(1){

    //contador 0-9 automatico clk = 1s
    // cnt++;
    // cnt = cnt > 9 ? 0 : cnt;

    //Delay de 1s
    vTaskDelay(pdMS_TO_TICKS(1000));

    //Imprimiendo por serial los numeros del conteo
    printf("\n %d \n", cnt);
    for (int i = 0; i < 7; i++){
      //io_config.intr_type = GPIO_INTR_DISABLE;
      gpio_set_level(display[i], number[cnt][i]);
    }
    
    //contador 0-9 manual mediante un botón
    
    //Se guarda el valor obtenido por el boton (si se presiona o no)
    int state_bt =  gpio_get_level(BT);
    //se muestra el numero
    for (int i = 0; i < 7; i++){
      gpio_set_level(display[i], number[cnt][i]);
    }
    //se verifica si se esta presionando el boton y si el contador
    //no se a desbordado ya que el contador no puede pasar de 9
    if(state_bt && cnt < 10){
      cnt++;
    }
    //si el contador llega a 9 se reinicia el conteo
    if(cnt>9){
      cnt = 0;
    }

    //misma logica que con los dos if, pero utlizando operadores ternarios
    // cnt = (state_bt && cnt < 10) ? cnt++ : cnt;
    // cnt = cnt > 9 ? 0 : cnt;
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  
}

//Funcion para configurar los pines GPIO usando estructuras para
//mayor organizacion y legibilidad del codigo
void init_hardware(void){
  //inicializacionde una estructura tipo gpio_config_t
  //que permite configurar un GPIO en los ESP32
  gpio_config_t io_config;
  //indicando que el GPIO es una entrada
  io_config.mode = GPIO_MODE_INPUT;
  //indicando el pin
  io_config.pin_bit_mask = (1 << BT);
  //poniendole una pull-down (asignadole un estado 0  por defecto)
  io_config.pull_down_en = GPIO_PULLDOWN_ONLY;
  //desactivando la pull-up (estado en 1 por defecto)
  io_config.pull_up_en = GPIO_PULLUP_DISABLE;
  //deshabilitando las interrupciones
  io_config.intr_type = GPIO_INTR_DISABLE;
  //funcion a la que hay que mandarle la ubicacion en memoria de la estructura creada
  gpio_config(&io_config);

//En este caso se hizo el mismo proceso que en el caso anterior solo
//que ahora se declara los pines GPIO a usar para el display
  io_config.mode = GPIO_MODE_OUTPUT;
  io_config.pin_bit_mask =  (1 << display[0]) |
                            (1 << display[1]) |
                            (1 << display[2]) |
                            (1 << display[3]) |
                            (1 << display[4]) |
                            (1 << display[5]) |
                            (1 << display[6]);
  io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_config.pull_up_en = GPIO_PULLUP_DISABLE;
  io_config.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&io_config);

  
}