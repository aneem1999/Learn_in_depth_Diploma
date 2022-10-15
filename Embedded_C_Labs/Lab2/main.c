/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Naeem
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-ClauseS
 *
 ******************************************************************************
 */

#include <stdint.h>

typedef unsigned long unint32_t;

#define RCC_BASE 0x4002100
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR *(volatile unint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRH *(volatile unint32_t *)(GPIOA_BASE + 0x04)

unsigned char data_var[3] = {1, 2, 3};
unsigned char bss_var[3];

#define RCC_IOAPEN (1 << 2)

//#define GPIOA_ODR *(volatile unint32_t*) (GPIOA_BASE + 0x0c)

typedef union
{
	volatile unint32_t all_bits;
	struct
	{
		volatile unint32_t reserved : 13;
		volatile unint32_t P_13 : 1;
	} pin;

} GPIOA_ODR_t;

volatile GPIOA_ODR_t *ODR_R = (volatile GPIOA_ODR_t *)(GPIOA_BASE + 0x0c);

int main(void)
{
	RCC_APB2ENR |= RCC_IOAPEN;
	GPIOA_CRH &= 0xFF0FFFF;
	GPIOA_CRH |= 0x0020000;

	while (1)
	{
		ODR_R->pin.P_13 = 1;

		// for (uint8_t i = 0; i < 5000; i++)
		//;

		ODR_R->pin.P_13 = 0;

		// for (uint8_t i = 0; i < 5000; i++)
		//;
	}
}
