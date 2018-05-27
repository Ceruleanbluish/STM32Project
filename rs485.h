/*
 * rs485.h
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef RS485_H_
#define RS485_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "led.h"

extern UART_HandleTypeDef USART1Handle;

void USART_rs485_Config(void);
void PB6_PB7_TxRx_GPIO_Init(void);
void DE_GPIO_Init(void);
void TX(void);
void RX(void);

#endif /* RS485_H_ */
