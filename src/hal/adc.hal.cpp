#include "hal/hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"
#include "stm32l0xx_hal.h"

namespace HAL
{
  AdConverter::AdConverter()
  {
    this->init();
  }

  void AdConverter::init()
  {
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc.Instance = ADC1;
    hadc.Init.OversamplingMode = DISABLE;
    hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ContinuousConvMode = DISABLE;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.DMAContinuousRequests = DISABLE;
    hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc.Init.LowPowerAutoWait = DISABLE;
    hadc.Init.LowPowerFrequencyMode = ENABLE;
    hadc.Init.LowPowerAutoPowerOff = DISABLE;
    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
      HAL::Error_Handler("HAL_ADC_Init failed");
    }
    /* Configure for the selected ADC regular channel to be converted.  */
    sConfig.Channel = ADC_CHANNEL_0;
    {
      HAL::Error_Handler("HAL_ADC_ConfigChannel failed");
    }
  }

  uint32_t AdConverter::getValue()
  {
    HAL_StatusTypeDef startStatus = HAL_ADC_Start(&hadc);
    if (startStatus != HAL_OK)
    {
      HAL::USART::printf("HAL_ADC_Start failed with code: %d\r\n", startStatus);
    }

    HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&hadc, 100);

    if (status != HAL_OK)
    {
      HAL::USART::printf("ADC read failed with code: %d\r\n", status);
    }

    uint32_t val = HAL_ADC_GetValue(&hadc);
    HAL_ADC_Stop(&hadc);
    return val;
  }

}

/* MSP Functions */

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (hadc->Instance == ADC1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC GPIO Configuration
    PA1     ------> ADC_IN1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC GPIO Configuration
    PA1     ------> ADC_IN1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
  }
}
