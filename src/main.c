/*!
    \file  main.c
    \brief running led
    
    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f10x.h"
#include "gd32f10x_eval.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*  
 * See gd32f10x_eval.h for pin definitions
 * LEDS (not used here)
 * LED2: PC_0
 * LED3: PC_2
 * LED4: PE_0
 * LED5: PE_1
 * 
 * EVAL_COM0: USART0, TX: PA_9, RX: PA_10
 * EVAL_COM1: USART1, TX: PA_2, RX: PA_3
 *  
*/

/* prints null terminated string. */
void print_str_usart1(const char* str) {
    for(size_t i=0; i < strlen(str); i++) {
        usart_data_transmit(USART1, (uint16_t) str[i]);
        while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    }
}

void check_receive_usart1() {
    //check if receiver has received something
    if(SET == usart_flag_get(USART1, USART_FLAG_RBNE)) {
        char rx_buf[2] = {0,0};
        //read that data.
        rx_buf[0] = (char) usart_data_receive(USART1);

        //echo back instantly using null-terminated string print function
        print_str_usart1("Received: '");
        print_str_usart1(rx_buf);
        print_str_usart1("'\n");
    }
}

/* not used */
/* define LED for PB2 */
#define MY_LED_PIN                         GPIO_PIN_2
#define MY_LED_GPIO_PORT                   GPIOB
#define MY_LED_GPIO_CLK                   RCU_GPIOB

void custom_led_init() {
    /* enable the led clock */
    rcu_periph_clock_enable(MY_LED_GPIO_CLK);
    /* configure led GPIO port */ 
    gpio_init(MY_LED_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, MY_LED_PIN);
    /* bit clear, i.e. set LOW */
    GPIO_BC(MY_LED_GPIO_PORT) = MY_LED_PIN;
}

void custom_led_toggle() {
    GPIO_OCTL(MY_LED_GPIO_PORT) ^= MY_LED_PIN;
}

int main(void)
{
    systick_config();
    //init LED 
    custom_led_init();

    //init USART1 PA2, PA3.
    //important: Baud rate 115200 8N1
    gd_eval_com_init(EVAL_COM1);
    //change baud
    //usart_baudrate_set(EVAL_COM1, 9600U);

    while(1){
        //toggle
        custom_led_toggle();
        /* transmit stuff on the configured usart1 */
        print_str_usart1("looping!\n");
        //since we only check every 1000ms, and the
        //hardware's receive buffer is limited (I guess to 1 byte?)
        //one should only input 1 char at a time..
        //if more is needed, work with USART interrupts and receive buffers 
        //need to be implemented
        check_receive_usart1();
        delay_1ms(1000);
    }
}
