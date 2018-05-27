/*
 * led.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "led.h"

void LED_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_B;
	GPIO_InitTypeDef pinconf_E;

	pinconf_B.Pin = GPIO_PIN_2;
	pinconf_B.Mode = GPIO_MODE_OUTPUT_PP;
	pinconf_B.Pull = GPIO_NOPULL;
	pinconf_B.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_B.Alternate = 0;

	pinconf_E.Pin = GPIO_PIN_8;
	pinconf_E.Mode = GPIO_MODE_OUTPUT_PP;
	pinconf_E.Pull = GPIO_NOPULL;
	pinconf_E.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_E.Alternate = 0;

	HAL_GPIO_Init(GPIOB, &pinconf_B);
	HAL_GPIO_Init(GPIOE, &pinconf_E);
}

void LED_4_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_B;

	pinconf_B.Pin = GPIO_PIN_2;
	pinconf_B.Mode = GPIO_MODE_OUTPUT_PP;
	pinconf_B.Pull = GPIO_NOPULL;
	pinconf_B.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_B.Alternate = 0;

	HAL_GPIO_Init(GPIOB, &pinconf_B);
}

void LED_COMMUNICATION_ERROR(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_Delay(250);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_Delay(750);
}
