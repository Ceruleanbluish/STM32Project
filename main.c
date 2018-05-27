/**
  ******************************************************************************
  * @file    main.c
  * @author  Ceruleanbluish
  * @version V1.0
  * @date    07-May-2018
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l4xx.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "clock.h"
#include "adc.h"
#include "led.h"
#include "communication.h"
#include <stdio.h>
#include "arm_math.h"
#include "arm_const_structs.h"

TIM_HandleTypeDef Timer4Handle;
ADC_HandleTypeDef ADC1Handle;
UART_HandleTypeDef USART2Handle;
COMP_HandleTypeDef COMP1Handle;
UART_HandleTypeDef USART1Handle;

char LCD_Display[10];
char USART_Transmit[20];

uint8_t ADC_FLAG = 0;

float AD_Result_For_Test;

void TIM4_IRQHandler(void) // for transmitting
{
	AD_Result_For_Test = (float)(ADC_Converter(&ADC1Handle, 1000) * 3.3 / 4096 ); // 4096 = 2^12

	sprintf(USART_Transmit, "%f\n", AD_Result_For_Test);
	HAL_UART_Transmit(&USART2Handle, (uint8_t *)USART_Transmit, strlen(USART_Transmit), 10);

	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	//__HAL_TIM_CLEAR_FLAG(&Timer4Handle, TIM_FLAG_UPDATE);

	//ADC_FLAG = 1;
	//HAL_TIM_Base_Stop_IT(&Timer4Handle);
	__HAL_TIM_CLEAR_FLAG(&Timer4Handle, TIM_FLAG_UPDATE);
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	BSP_LCD_GLASS_Init();
	BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_5);
	LED_Init();
	USART_UART_Config();
	//USART_rs485_Config();


	ADC_Config(); // ADC->TIM4

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

	TIM4_ADC_init();


	HAL_TIM_Base_Start_IT(&Timer4Handle);
	while(1)
	{
		//while(ADC_FLAG == 0);
		//sprintf(USART_Transmit, "%f\n", AD_Result_For_Test);
		//HAL_UART_Transmit(&USART2Handle, (uint8_t *)USART_Transmit, strlen(USART_Transmit), 10);

		//sprintf((char*)LCD_Display, "%f", AD_Result_For_Test);
		//BSP_LCD_GLASS_Clear();
		//BSP_LCD_GLASS_DisplayString(LCD_Display);

		//ADC_FLAG = 0;
		//HAL_TIM_Base_Start_IT(&Timer4Handle);
	}
}
