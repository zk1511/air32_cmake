#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "bsp.h"
#include "delay.h"
#include "ws2812.h"


#define PRINTF_LOG printf

USART_TypeDef *USART_TEST = USART1;

void UART_Configuration(uint32_t bound);

#define PI 3.14159265
static uint8_t Colors[WS2812_MAX_LED_COUNT * 3];

void delay_us(uint32_t nus)
{
    uint32_t temp = 0;
    SysTick->LOAD = (uint32_t)(nus * (SystemCoreClock / 1000000U / 8U));
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}
int main(void)
{
	RCC_ClocksTypeDef clocks;
    uint32_t sin_timer;

    //bsp_init();
    WS2812_SPI_DMA_Init();

//	UART_Configuration(115200); //默认为串口1，波特率115200
//	RCC_GetClocksFreq(&clocks); //获取系统时钟频率

//	PRINTF_LOG("\nSYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK1: %3.1fMhz, PCLK2: %3.1fMhz, ADCCLK: %3.1fMhz\n",
//			   (float)clocks.SYSCLK_Frequency / 1000000,
//               (float)clocks.HCLK_Frequency / 1000000,
//			   (float)clocks.PCLK1_Frequency / 1000000,
//               (float)clocks.PCLK2_Frequency / 1000000,
//               (float)clocks.ADCCLK_Frequency / 1000000);

    //start_timer_count(&sin_timer);

	while (1)
	{
        //bsp_wdt_feed();

        //delay_ms(1);
        
        for(uint8_t i = 0;i < WS2812_MAX_LED_COUNT;i ++) 
        {
              Colors[i*3+0] = 255;
              Colors[i*3+1] = 0;
              Colors[i*3+2] = 0;
        }
        WS2812_Write(Colors, WS2812_MAX_LED_COUNT);
        delay_us(10000);   
	}
}


void UART_Configuration(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
}

int SER_PutChar(int ch)
{
	while (!USART_GetFlagStatus(USART_TEST, USART_FLAG_TC))
		;
	USART_SendData(USART_TEST, (uint8_t)ch);

	return ch;
}

int fputc(int c, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	if (c == '\n')
	{
		SER_PutChar('\r');
	}
	return (SER_PutChar(c));
}
