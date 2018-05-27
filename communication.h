/*
 * communication.h
 *
 *  Created on: 12 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "led.h"

/** @defgroup UARTEx_Word_Length   UART Number of data bits transmitted or received in a frame
  * @{
  */
//#define UART_WORDLENGTH_8B                    0x00000000U                     /*!< UART word length with 8 bits  */
//#define UART_WORDLENGTH_9B                    ((uint32_t)USART_CR1_M0)        /*!< UART word length with 9 bits    */
//#define UART_WORDLENGTH_7B                    0x10000000U                     /*!< UART word length with 7 bits */
/**
  * @}
  */

extern UART_HandleTypeDef USART2Handle;

void USART_UART_Config(void);
void PD5_PD6_GPIO_Init(void);

#endif /* COMMUNICATION_H_ */
