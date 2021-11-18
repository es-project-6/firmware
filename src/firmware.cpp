#include "firmware.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"
#include "hal/led.hal.hpp"
#include "hal/usart.hal.hpp"
#include "hal/adc.hal.hpp"

#include "stdio.h"

ADC_HandleTypeDef hadc;

void adcInit()
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
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
    HAL::USART::printf("State Code: %d\r\n", hadc.State);
    HAL::USART::printf("Error Code: %d\r\n", hadc.ErrorCode);
    HAL::Error_Handler("HAL_ADC_Init failed");
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    HAL::Error_Handler("HAL_ADC_ConfigChannel failed");
  }
}

void firmwareSetup()
{
  HAL::init();

  HAL::LED *onboardLED = new HAL::LED(ONBOARD_LED_PIN, ONBOARD_LED_GPIO_PORT);
  HAL::USART::init();
  // HAL::AdConverter *adc = new HAL::AdConverter();
  adcInit();

  while (1)
  {
    onboardLED->toggle();
    int val;

    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    val = HAL_ADC_GetValue(&hadc);

    HAL::USART::serialClearScreen();
    HAL::USART::printf("Analog Value:%d\r\n", val);

    char str[150];
    for (size_t i = 0; i < 150; i++)
    {
      if (((float)val / (float)4000) * 150 > i)
      {
        str[i] = '#';
      }
      else
      {
        str[i] = '\0';
        break;
      }
    }

    HAL::USART::print(str);

    HAL_Delay(80);
  }
}

void firmwareLoop()
{
}
