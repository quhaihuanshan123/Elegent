/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#define NUM 6
float lh=0;
float rh=0;
float mh=0;
float rf=0;
float lf=0;
float Error=0;
//float Limit=0.6,Err=0;
float ADC[NUM]={0};
float ADC_VALUE[NUM][5]={0};//存放五路每路五个数据
float ADC_AVR[NUM]={0};
float ADC_ONE[NUM]={0};
float max[NUM]={0};//存放每路平均�????5个数�????
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_5|GPIO_PIN_6);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void get_adc(void)//获取adc的�??
{
int j=0,i=0,k=0;
	float adctemp=0;
	HAL_ADC_Start(&hadc1);
	for(j=0;j<5;j++)
	{
		for(i=0;i<6;i++)
		{
	if(HAL_ADC_PollForConversion(&hadc1,10)==HAL_OK)//转换完成
		{ADC_VALUE[i][j]=HAL_ADC_GetValue(&hadc1);}//采集数据
		}
		for(i = 0;i <NUM;i++)//从小到大排序
							{
								for(j= 0;j < 4;j++)
								{
                                for(k=0;k<4-j;k++)
                                {
                                	if(ADC_VALUE[i][k]<ADC_VALUE[i][k+1])
                                	{
                                		adctemp=ADC_VALUE[i][k];
                                		ADC_VALUE[i][k]=ADC_VALUE[i][k+1];
                                		ADC_VALUE[i][k+1]=adctemp;
                                	}
                                }

								}

							}
		for(i=0;i<NUM;i++)//三个中间平均
		{
		ADC_AVR[i]=ADC_VALUE[i][1]+ADC_VALUE[i][2]+ADC_VALUE[i][3];
		ADC[i]=ADC_AVR[i]/3;
		}
		for(i=0;i<NUM;i++)//均�?�赋给最后一�????
		{
			ADC_VALUE[i][4]=ADC[i];
		}
		for(i=0;i<4;i++)//滑动覆盖
		{
			ADC_VALUE[0][i]=ADC_VALUE[0][i+1];
			ADC_VALUE[1][i]=ADC_VALUE[1][i+1];
			ADC_VALUE[2][i]=ADC_VALUE[2][i+1];
			ADC_VALUE[3][i]=ADC_VALUE[3][i+1];
			ADC_VALUE[4][i]=ADC_VALUE[4][i+1];
			ADC_VALUE[5][i]=ADC_VALUE[5][i+1];

		}
		for(i=0;i<5;i++)//五个数据再求�????
		{
			ADC_AVR[0]+=ADC_VALUE[0][i];
			ADC_AVR[1]+=ADC_VALUE[1][i];
			ADC_AVR[2]+=ADC_VALUE[2][i];
			ADC_AVR[3]+=ADC_VALUE[3][i];
			ADC_AVR[4]+=ADC_VALUE[4][i];
			ADC_AVR[5]+=ADC_VALUE[5][i];
		}
		for(i=0;i<NUM;i++)//取平�????
				{
					ADC[i]=ADC_AVR[i]/NUM;
//					if(ADC[i]>MAX[i])
//						ADC[i]=MAX[i];
//					ADC_AVR[i]=0;
				}
	//归一�????==========================================================================
		/*for(i=0;i<NUM;i++)//归一化百分比
		{
			ADC_ONE[i]=(100*ADC[i]/max[i]);

		}



lh=ADC_ONE[1];
rh=ADC_ONE[2];
mh=ADC_ONE[4];
rv=ADC_ONE[0];
lv=ADC_ONE[3];
ms=ADC_ONE[5];
Err=Limit*(lh-rh)/(lh+rh);
*/
	}




}
/* USER CODE END 1 */
