/**
  ******************************************************************************
  * @file    main.c
  * @author  Ceruleanbluish
  * @version V1.0
  * @date    05 06 2018
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l4xx.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "clock.h"
#include "adc.h"
#include "led.h"
//#include "fft.h"
#include "communication.h"
#include <stdio.h>
#include "arm_math.h"
#include "arm_const_structs.h"

/* Define to measure the CPU temperature 30-110 -------------------------------------*/
#define TS_110_CAL1 ((uint16_t *)((uint32_t)0x1FFF75CA))
#define TS_30_CAL2 ((uint16_t *)((uint32_t)0x1FFF75A8))

#define NUM 2048
#define FS 2048

TIM_HandleTypeDef Timer4Handle;
ADC_HandleTypeDef ADC1Handle;
UART_HandleTypeDef USART2Handle;
COMP_HandleTypeDef COMP1Handle;
TIM_HandleTypeDef Timer2Handle;

void Transmit_ADC_Data(void);
void Transmit_FFT_Result(void);

char LCD_Display[20];
char USART_Transmit[20];
float AD_Result[NUM * 2];
float out[NUM * 2];

float result[NUM];
float Signal_Generator;
uint32_t n = 0;
uint32_t fm = 128;

void TIM4_IRQHandler(void)
{
	Signal_Generator = (float)(1.65*sin(2*3.14159*fm*n/FS) + 1.65);
	n++;
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2); // TEST?????????????????????????????????????
	sprintf(USART_Transmit, "%f", Signal_Generator);
	HAL_UART_Transmit(&USART2Handle, (uint8_t *)USART_Transmit, strlen(USART_Transmit), 10);
	__HAL_TIM_CLEAR_FLAG(&Timer4Handle, TIM_FLAG_UPDATE);
	if(n >= NUM && fm < 1024)
	{
		n = 0;
		fm *= 2;
	}
	if(fm >= 1024)
		fm = 128;
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	BSP_LCD_GLASS_Init();
	BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_5);
	LED_Init();
	USART_UART_Config();
	//ADC_Config();
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	TIM4_ADC_init();

	HAL_TIM_Base_Start_IT(&Timer4Handle);
	while(1);
}

void Transmit_ADC_Data(void)
{
	HAL_UART_Transmit(&USART2Handle, (uint8_t *)&"\n\rADC samples:\r\n", strlen("\n\rADC samples:\r\n"), 10);
	for(int i = 0; i < NUM; i++)
	{
		sprintf(USART_Transmit, "%f\n", AD_Result[i * 2]);
		HAL_UART_Transmit(&USART2Handle, (uint8_t *)USART_Transmit, strlen(USART_Transmit), 10);
	}
}


void Transmit_FFT_Result(void)
{
	HAL_UART_Transmit(&USART2Handle, (uint8_t *)&"\n\rFFT Result:\r\n", strlen("\n\rFFT Result:\r\n"), 10);
	for(int i = 0; i < NUM; i++)
	{
		sprintf(USART_Transmit, "%f\n", result[i]);
		HAL_UART_Transmit(&USART2Handle, (uint8_t *)USART_Transmit, strlen(USART_Transmit), 10);
	}
}
