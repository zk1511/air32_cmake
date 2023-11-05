#ifndef __BSP_H
#define __BSP_H

//#ifdef __cplusplus
// extern "C" {
//#endif

#include "air32f10x.h"

// led
#define LED_RED_PORT                GPIOB
#define LED_RED_PIN                 GPIO_Pin_11

#define LED_GREEN_PORT              GPIOB
#define LED_GREEN_PIN               GPIO_Pin_10

#define LED_BLUE_PORT               GPIOB
#define LED_BLUE_PIN                GPIO_Pin_2


enum led{
LED_RED = 0,
LED_GREEN = 1,
LED_BLUE  = 2
};

typedef uint8_t led_t;


enum led_sta{
    LED_OFF = 0,
    LED_ON = 1,
};

typedef uint8_t led_sta_t;


void bsp_init(void);

void bsp_led(led_t led, led_sta_t sta);

void bsp_wdt_feed(void);

//#ifdef __cplusplus
//}
//#endif

#endif
