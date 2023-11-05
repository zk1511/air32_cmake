#ifndef __DELAY_H
#define __DELAY_H

#include "bsp.h"

void delay_init(void);
void delay_ms(uint32_t count);

void start_timer_count(uint32_t *cnt);
uint32_t get_timer_count(uint32_t cnt);

#endif

