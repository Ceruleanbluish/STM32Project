/*
 * communication.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "communication.h"
/*
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//#include "stm32l476g_discovery.h"

PUTCHAR_PROTOTYPE
{
	HAL_USART_Transmit(&USART2Handle, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
*/
void USART_UART_Config(void)
{
	//USART_HandleTypeDef USART2Handle;
	PD5_PD6_GPIO_Init(); // PD5->UART4_Tx, PD6->UART4_Rx
	__HAL_RCC_USART2_CLK_ENABLE();

	USART2Handle.Instance = USART2;

	USART2Handle.Init.BaudRate = 57600; // not sure
	USART2Handle.Init.WordLength = UART_WORDLENGTH_9B; // not sure
	USART2Handle.Init.StopBits = UART_STOPBITS_1;
	USART2Handle.Init.Parity = UART_PARITY_EVEN; // not sure
	USART2Handle.Init.Mode = UART_MODE_TX_RX; // UART_MODE_TX
	//USART2Handle.Init.CLKPolarity = ; // not sure
	//USART2Handle.Init.CLKPhase = ; // not sure
	//USART2Handle.Init.CLKLastBit = ; // not sure

	//HAL_USART_DeInit(&USART2Handle);
	if(HAL_UART_Init(&USART2Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}
	//__HAL_USART_ENABLE(&USART2Handle);

	//HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(USART2_IRQn);
/*
	if(HAL_USART_Transmit_IT(&USART2Handle, (uint8_t *)buffer, 1) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}
*/
	//__HAL_UART_ENABLE_IT(&USART2Handle, UART_IT_RXNE);
	//__HAL_UART_ENABLE_IT(&USART2Handle, UART_IT_IDLE);
	//__HAL_USART_ENABLE_IT(&USART2Handle, USART_IT_TC);

}


/*
void PC10_PC11_GPIO_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_C_10;
	GPIO_InitTypeDef pinconf_C_11;

	// UART4 Tx --------------------------------------------------------
	pinconf_C_10.Pin = GPIO_PIN_10;
	pinconf_C_10.Mode = GPIO_MODE_AF_PP; // Push Pull Mode
	pinconf_C_10.Pull = GPIO_NOPULL;
	pinconf_C_10.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_C_10.Alternate = 0;

	// UART4 Rx --------------------------------------------------------
	pinconf_C_11.Pin = GPIO_PIN_11;
	pinconf_C_11.Mode = GPIO_MODE_INPUT; // Input Floating Mode
	pinconf_C_11.Pull = GPIO_NOPULL;
	pinconf_C_11.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_C_11.Alternate = 0;

	HAL_GPIO_Init(GPIOC, &pinconf_C_10);
	HAL_GPIO_Init(GPIOC, &pinconf_C_11);

}
*/

void PD5_PD6_GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_D_5;
	GPIO_InitTypeDef pinconf_D_6;

	/* USART2 Tx --------------------------------------------------------*/
	pinconf_D_5.Pin = GPIO_PIN_5;
	pinconf_D_5.Mode = GPIO_MODE_AF_PP; // Push Pull Mode
	pinconf_D_5.Pull = GPIO_NOPULL;
	pinconf_D_5.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_D_5.Alternate = GPIO_AF7_USART2; // not sure

	/* USART2 Rx --------------------------------------------------------*/
	pinconf_D_6.Pin = GPIO_PIN_6;
	pinconf_D_6.Mode = GPIO_MODE_AF_PP; // Push Pull Mode / Input Floating Mode GPIO_MODE_INPUT
	pinconf_D_6.Pull = GPIO_NOPULL;
	pinconf_D_6.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_D_6.Alternate = GPIO_AF7_USART2; // not sure

	HAL_GPIO_Init(GPIOD, &pinconf_D_5);
	HAL_GPIO_Init(GPIOD, &pinconf_D_6);

}
