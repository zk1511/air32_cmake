#include "delay.h"

volatile static uint32_t delayms;	// 延时
volatile static uint32_t tick;		// 计时

void delay_init(void)
{
    RCC_ClocksTypeDef clocks;

    RCC_GetClocksFreq(&clocks);
    SysTick_Config( clocks.HCLK_Frequency / 1000);
}

void delay_handler(void)
{
    if (0 != delayms)
    {
        delayms--;
    }

    tick++;
}

void delay_ms(uint32_t count)
{
    delayms = count;

    while(0 != delayms)
    {

    }
}

void start_timer_count(uint32_t *cnt)
{
    *cnt  = tick;
}

uint32_t get_timer_count(uint32_t cnt)
{
    return (tick-cnt);
}
