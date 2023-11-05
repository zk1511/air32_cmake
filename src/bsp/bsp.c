#include "bsp.h"
#include "delay.h"
#include "ws2812.h"

void bsp_rcc_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
}

void bsp_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = LED_RED_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_RED_PORT, &GPIO_InitStruct);
    //GPIO_SetBits(LED_RED_PORT, LED_RED_PIN);
    GPIO_ResetBits(LED_RED_PORT, LED_RED_PIN);

    GPIO_InitStruct.GPIO_Pin = LED_GREEN_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);
    //GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN);
    GPIO_ResetBits(LED_RED_PORT, LED_GREEN_PIN);

    GPIO_InitStruct.GPIO_Pin = LED_BLUE_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_BLUE_PORT, &GPIO_InitStruct);
    //GPIO_SetBits(LED_BLUE_PORT, LED_BLUE_PIN);
    GPIO_ResetBits(LED_BLUE_PORT, LED_BLUE_PIN);
}

void bsp_wdt_init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    while(IWDG_GetFlagStatus(IWDG_FLAG_PVU));
    IWDG_SetPrescaler(IWDG_Prescaler_64);       // 40k / 64 -> 1.6ms

    while(IWDG_GetFlagStatus(IWDG_FLAG_RVU));
    IWDG_SetReload(1875);          // 1875 * 1.6ms = 3s

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
    IWDG_Enable();

    IWDG_ReloadCounter();
}

void bsp_wdt_feed(void)
{
    IWDG_ReloadCounter();
}


void bsp_init(void)
{
    //bsp_wdt_init();

    //bsp_rcc_init();

    delay_init();

    //bsp_led_init();

    //ws2812_init();
}

void bsp_led(led_t led, led_sta_t sta)
{
    if(led == LED_RED)
    {
        if(sta == LED_OFF)
        {
            GPIO_ResetBits(LED_RED_PORT, LED_RED_PIN);
        }
        else
        {
            GPIO_SetBits(LED_RED_PORT, LED_RED_PIN);
        }
    }
    else if(led == LED_GREEN)
    {
        if(sta == LED_OFF)
        {
            GPIO_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN);
        }
        else
        {
            GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN);
        }
    }
    else if(led == LED_BLUE)
    {
        if(sta == LED_OFF)
        {
            GPIO_ResetBits(LED_BLUE_PORT, LED_BLUE_PIN);
        }
        else
        {
            GPIO_SetBits(LED_BLUE_PORT, LED_BLUE_PIN);
        }
    }
    else
    {

    }
}
