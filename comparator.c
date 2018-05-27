/*
 * comparator.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "comparator.h"

void COMP_Config(void)
{
	PB2_Init();
	//__HAL_RCC_COMP1_CLK_ENABLE(); // ???????????? not sure

	COMP1Handle.Instance = COMP1;
	COMP1Handle.Init.WindowMode = COMP_WINDOWMODE_DISABLE;
	COMP1Handle.Init.Mode = COMP_POWERMODE_HIGHSPEED;
	COMP1Handle.Init.NonInvertingInput = COMP_INPUT_PLUS_IO2; // The input pin is PB2
	COMP1Handle.Init.InvertingInput = COMP_INPUT_MINUS_1_4VREFINT; // COMP_INPUT_MINUS_3_4VREFINT
	COMP1Handle.Init.Hysteresis = COMP_HYSTERESIS_LOW;
	COMP1Handle.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
	COMP1Handle.Init.BlankingSrce = COMP_BLANKINGSRC_NONE; // ???????????????????? not sure
	//COMP1Handle.Init.TriggerMode = ;

	if(HAL_COMP_Init(&COMP1Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

}

void PB2_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef pinconf_B_10;
	GPIO_InitTypeDef pinconf_B_2;

	// COMP1 output -------------------------------------------------------- PB0->TIM3 CHANNEL3, PB10->TIM2 CHANNEL3
	//pinconf_B_10.Pin = GPIO_PIN_10;
	//pinconf_B_10.Mode = GPIO_MODE_AF_PP; // Push Pull Mode
	//pinconf_B_10.Pull = GPIO_NOPULL;
	//pinconf_B_10.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	//pinconf_B_10.Alternate = GPIO_AF12_COMP1; // not sure

	/* COMP1 INP --------------------------------------------------------*/
	pinconf_B_2.Pin = GPIO_PIN_2;
	pinconf_B_2.Mode = GPIO_MODE_ANALOG; // Input Analog Mode  ?? GPIO_MODE_INPUT
	pinconf_B_2.Pull = GPIO_NOPULL;
	pinconf_B_2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinconf_B_2.Alternate = GPIO_AF12_COMP1; // not sure

	HAL_GPIO_Init(GPIOB, &pinconf_B_10);
	HAL_GPIO_Init(GPIOB, &pinconf_B_2);
}

void TIM2_COMP_Init(void) // 0.5 second timer
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	TIM_IC_InitTypeDef TIM2sConfig;


	Timer2Handle.Instance = TIM2;
	Timer2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Timer2Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Timer2Handle.Init.Prescaler = 10000;
	Timer2Handle.Init.Period = 4000; // ?????????????? not sure
/*
	HAL_TIM_IC_Init(&Timer2Handle);

	TIM2sConfig.ICPolarity = TIM_ICPOLARITY_RISING;
	TIM2sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI; // ?????????????? not sure
	TIM2sConfig.ICPrescaler = TIM_ICPSC_DIV1;
	TIM2sConfig.ICFilter = 0x0;

	HAL_TIM_IC_ConfigChannel(&Timer2Handle, &TIM2sConfig, TIM_CHANNEL_3); // ????? HAL_TIM_IC_ConfigChannel(&Timer2Handle, &TIM2sConfig, 3);
*/
	HAL_NVIC_SetPriority(TIM2_IRQn, 6, 0); // ????????????????????????
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
