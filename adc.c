/*
 * adc.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "adc.h"

//#include "stm32l476g_discovery.h"

void ADC_Config(void)
{
	PA0_GPIO_Init(); // PA0--ADC_CHANNEL_5 as input
	__HAL_RCC_ADC_CLK_ENABLE();
	//__HAL_RCC_ADC_DMA1_ENABLE();

	//ADC_HandleTypeDef ADC1Handle;
	ADC_ChannelConfTypeDef sConfig;
	//DMA_HandleTypeDef DMA1Handle;
	//HAL_ADC_DeInit(ADC1Handle);
	//HAL_DMA_DeInit(DMA1);

	ADC1Handle.Instance = ADC1;

	ADC1Handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	ADC1Handle.Init.Resolution = ADC_RESOLUTION_12B;
	ADC1Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC1Handle.Init.ScanConvMode = ADC_SCAN_DISABLE;
	ADC1Handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	ADC1Handle.Init.LowPowerAutoWait = DISABLE; // Not sure
	ADC1Handle.Init.ContinuousConvMode = DISABLE;
	ADC1Handle.Init.NbrOfConversion = 1;
	/*
	ADC1Handle.Init.DiscontinuousConvMode = DISABLE; // This is discarded if ContinuousConvMode = ENABLE
	ADC1Handle.Init.NbrOfDisConversion = ; // This is discarded if DiscontinuousConvMode = DISABLE
	*/
	ADC1Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	/*
	ADC1Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T4_TRGO;
	ADC1Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING; // This is discarded if ExternalTrigConv = ADC_SOFTWARE_START
	*/
	//ADC1Handle.Init.Overrun = ADC_OVR_DATA_PRESERVED; // This is discarded
	//ADC1Handle.Init.OversamplingMode = DISABLE; // This is discarded

	//HAL_ADC_Init(&ADC1Handle);
	if(HAL_ADC_Init(&ADC1Handle) != HAL_OK)
	{
		//Error_Handler();
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

	sConfig.Channel = ADC_CHANNEL_5; // ADC_CHANNEL_17;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
	sConfig.Offset = 0x000;
	// Conversation time = sampling time + 12.5cycles, sampling frequency = ADC_CLK_FREQ / Conversation cycle = 80MHz / 25 = 3.2MHz
	//HAL_ADC_ConfigChannel(&ADC1Handle, &sConfig);
	if(HAL_ADC_ConfigChannel(&ADC1Handle, &sConfig) != HAL_OK)
	{
		//Error_Handler();
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(100);
		}
	}

	ADC_Enable(&ADC1Handle);
	//__HAL_ADC_ENABLE_IT(&ADC1Handle ,ADC_IT_EOC);
	//DMA1Handle.Instance = DMA1;
	//DMA1Handle.Init.Request = DMA_REQUEST_ADC1;
}


void PA0_GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_A;

	pinconf_A.Pin = GPIO_PIN_0;
	pinconf_A.Mode = GPIO_MODE_ANALOG_ADC_CONTROL; // not sure ? GPIO_MODE_ANALOG_ADC_CONTROL
	pinconf_A.Pull = GPIO_NOPULL;
	pinconf_A.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_A.Alternate = 0;

	HAL_GPIO_Init(GPIOA, &pinconf_A);
}

uint32_t ADC_Converter(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
	uint32_t AD_Result;
	HAL_ADC_Start(hadc);
	while(HAL_ADC_PollForConversion(hadc, Timeout) != HAL_OK);
	AD_Result = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	return AD_Result;
}

void TIM4_ADC_init(void)
{
	Timer4Handle.Instance = TIM4;
	Timer4Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Timer4Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Timer4Handle.Init.Prescaler = 99;
	Timer4Handle.Init.Period = 39; // 80MHz / 20kHz = 4000 = 99 * 39

	__HAL_RCC_TIM4_CLK_ENABLE();

	HAL_TIM_Base_Init(&Timer4Handle);
	HAL_NVIC_SetPriority(TIM4_IRQn, 7, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

/*
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
*/
