#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <driver/ledc.h>

//declarando e inicilizacon el ADC y su canal
adc1_channel_t adc_pot = ADC1_CHANNEL_1;

//inicializando la salida pwm
ledc_channel_config_t pwm;


#define LED_2  14

void init_hw(void);

void app_main() {
  init_hw();
  while(1){
    //guardando la entrada analogica
    int pot = adc1_get_raw(adc_pot);
    //imprimiendo la entrada analogica
    printf("\n ADC = %d \n",pot);
    ledc_set_duty(pwm.speed_mode, pwm.channel, pot);
    ledc_update_duty(pwm.speed_mode,pwm.channel);

    vTaskDelay(pdMS_TO_TICKS(300));
    
  }
}

void init_hw(void){


  //configurando la entrada analogica
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(adc_pot, ADC_ATTEN_DB_11);


//configurando un CLK
  ledc_timer_config_t timer = {
    .duty_resolution = LEDC_TIMER_12_BIT,
    .freq_hz = 500,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .timer_num = LEDC_TIMER_0,
    .clk_cfg = LEDC_AUTO_CLK
  };
  
  ledc_timer_config(&timer);


 //configurando la salida PWM
  pwm.channel = LEDC_CHANNEL_0;
  pwm.duty = 0;
  pwm.gpio_num = LED_2;
  pwm.hpoint = 0;
  pwm.timer_sel = LEDC_TIMER_0;
  pwm.speed_mode = LEDC_LOW_SPEED_MODE;

  ledc_channel_config(&pwm);
}