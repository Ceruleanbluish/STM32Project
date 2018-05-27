/*
 * menu.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "menu.h"

struct MenuItem m0_main[2] =
{
    {2, "M1FFT",  Nop, m1_fft,  NULL},
    {2, "M2COMP", Nop, m1_comp, NULL},
	//{2, "M1FFT", FFT_Init, m1_fft, NULL},
	//{2, "M2COMP", COMP_Init, m1_comp, NULL},
};

struct MenuItem m1_fft[1] =
{
    {1, "FFT", FFT_Processing, m2_fft_unitconverter, m0_main},
};

struct MenuItem m2_fft_unitconverter[3] =
{
    {3, "m/s",  MeterPerSecond,   NULL, m1_fft},
    {3, "mph",  MilePerHour,      NULL, m1_fft},
    {3, "km/h", KilometerPerHour, NULL, m1_fft},
};

struct MenuItem m1_comp[1] =
{
    {1, "COMP", COMP_Processing, m2_comp_unitconverter, m0_main},
};

struct MenuItem m2_comp_unitconverter[3] =
{
    {3, "m/s",  MeterPerSecond,   NULL, m1_comp},
    {3, "mph",  MilePerHour,      NULL, m1_comp},
    {3, "km/h", KilometerPerHour, NULL, m1_comp},
};

//**************************************************************888

void MeterPerSecond(struct MenuItem *roam)
{
    float speed;
    speed = frequency / (float)(2 * 35.29); // 35.29 = 10.587GHz / (3*10^8)
    sprintf((char*)LCD_Display, "%f\n", speed);
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_DisplayString(LCD_Display);
}

void MilePerHour(struct MenuItem *roam)
{
    float speed;
    speed = 2.237 * frequency / (float)(2 * 35.29); // 35.29 = 10.587GHz / (3*10^8)
    sprintf((char*)LCD_Display, "%f\n", speed);
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_DisplayString(LCD_Display);
}

void KilometerPerHour(struct MenuItem *roam)
{
    float speed;
    speed = 3.6 * frequency / (float)(2 * 35.29); // 35.29 = 10.587GHz / (3*10^8)
    sprintf((char*)LCD_Display, "%f\n", speed);
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_DisplayString(LCD_Display);
}

/*
void FFT_Init(struct MenuItem *roam)
{
	if(HAL_COMP_DeInit(&COMP1Handle) != HAL_OK && HAL_TIM_IC_DeInit(&Timer2Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

    ADC_Config();
    TIM4_ADC_init();
}
*/

/*
void COMP_Init(struct MenuItem *roam)
{
	if(HAL_ADC_DeInit(&ADC1Handle) != HAL_OK && HAL_TIM_Base_DeInit(&Timer4Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

    COMP_Config();
    TIM2_COMP_IC_Init();
}
*/

void FFT_Processing(struct MenuItem *roam)
{
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);
	LED_4_Init();
	if(HAL_COMP_DeInit(&COMP1Handle) != HAL_OK && HAL_TIM_IC_DeInit(&Timer2Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

	ADC_Config();
	TIM4_ADC_init();
    float maxValue;
    uint32_t loc;

    // ************** sampling ****************
    FFT_index = 0;
    HAL_TIM_Base_Start_IT(&Timer4Handle);
    while(FFT_index < NUM);
    // ************** sampling ****************

    // ************** fft ****************
    arm_cfft_f32(&arm_cfft_sR_f32_len2048, AD_Result, 0, 1);
    arm_cmplx_mag_f32(AD_Result, result, NUM);
    result[0] = 0;
    arm_max_f32(result, NUM, &maxValue, &loc);
    // ************** fft ****************

    // ************** get frequency ****************
    if(loc < NUM / 2)
    {
        Freq_ADC_FFT = (float)(loc*FS/NUM);
    }
    else
    {
        Freq_ADC_FFT = (float)(FS) - (float)(loc*FS/NUM);
    }
    frequency = Freq_ADC_FFT;
    // ************** get frequency ****************
}

void COMP_Processing(struct MenuItem *roam)
{
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);
	if(HAL_ADC_DeInit(&ADC1Handle) != HAL_OK && HAL_TIM_Base_DeInit(&Timer4Handle) != HAL_OK)
	{
		while(1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_Delay(1000);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_Delay(1000);
		}
	}

	COMP_Config();
	TIM2_COMP_IC_Init();
    float total;

    // ***************** input capture ******************
    COMP_index = 0;
    HAL_TIM_IC_Start_IT(&Timer2Handle, TIM_CHANNEL_3);
    while(COMP_index < TIMES);
    // ***************** input capture ******************

    total = 0;
	for(uint8_t i = 0; i < TIMES; i++)
	{
		total += Freq_InputCapture[i];
	}
	frequency = (float)total / TIMES;
}

void Locate(struct MenuItem *roam)
{
    sprintf((char*)LCD_Display, "%s\n", roam->DisplayString);
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_DisplayString(LCD_Display);
}

void Run(struct MenuItem *roam)
{
    (*(roam->Subs))(roam);
}

void Nop(void)
{}

void GameOver(void)
{
    over = 1;
    sprintf((char*)LCD_Display, "Over\n");
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_DisplayString(LCD_Display);
}
