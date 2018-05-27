/*
 * rs485.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "rs485.h"

void USART_rs485_Config(void)
{
	PB6_PB7_TxRx_GPIO_Init();
	DE_GPIO_Init();
	__HAL_RCC_USART1_CLK_ENABLE();

	USART1Handle.Instance = USART1;

	USART1Handle.Init.BaudRate = 57600; // not sure
	USART1Handle.Init.WordLength = UART_WORDLENGTH_9B; // not sure
	USART1Handle.Init.StopBits = UART_STOPBITS_1;
	USART1Handle.Init.Parity = UART_PARITY_EVEN;
	USART1Handle.Init.Mode = UART_MODE_TX_RX; // UART_MODE_TX

	if(HAL_UART_Init(&USART1Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}
}

void PB6_PB7_TxRx_GPIO_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_B_6;
	GPIO_InitTypeDef pinconf_B_7;

	/* USART1 Tx --------------------------------------------------------*/
	pinconf_B_6.Pin = GPIO_PIN_6;
	pinconf_B_6.Mode = GPIO_MODE_AF_PP; // Push Pull Mode
	pinconf_B_6.Pull = GPIO_NOPULL;
	pinconf_B_6.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_B_6.Alternate = GPIO_AF7_USART1; // not sure

	/* USART1 Rx --------------------------------------------------------*/
	pinconf_B_7.Pin = GPIO_PIN_7;
	pinconf_B_7.Mode = GPIO_MODE_AF_PP; // Push Pull Mode
	pinconf_B_7.Pull = GPIO_NOPULL;
	pinconf_B_7.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_B_7.Alternate = GPIO_AF7_USART1; // not sure

	HAL_GPIO_Init(GPIOB, &pinconf_B_6);
	HAL_GPIO_Init(GPIOB, &pinconf_B_7);

}

void DE_GPIO_Init(void) // DE not RE pin
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_A_3;

	pinconf_A_3.Pin = GPIO_PIN_3;
	pinconf_A_3.Mode = GPIO_MODE_OUTPUT_PP; // Push Pull Mode
	pinconf_A_3.Pull = GPIO_NOPULL;
	pinconf_A_3.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	//pinconf_A_3.Alternate = 0; // not sure

	HAL_GPIO_Init(GPIOA, &pinconf_A_3);
}

void TX(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
}

void RX (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}
