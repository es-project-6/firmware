#include "hal/usart.hal.hpp"
#include "hal/hal.hpp"
#include "hal/pins.hal.hpp"

#include <string.h>

namespace HAL
{
  void USART::init(uint32_t baudRate)
  {
    USART::huart.Instance = USART2;
    USART::huart.Init.BaudRate = baudRate;
    USART::huart.Init.WordLength = UART_WORDLENGTH_8B;
    USART::huart.Init.StopBits = UART_STOPBITS_1;
    USART::huart.Init.Parity = UART_PARITY_NONE;
    USART::huart.Init.Mode = UART_MODE_TX_RX;
    USART::huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    USART::huart.Init.OverSampling = UART_OVERSAMPLING_16;
    USART::huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    USART::huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&USART::huart) != HAL_OK)
    {
      HAL::Error_Handler();
    }
  }

  HAL_StatusTypeDef USART::print(char data[], size_t size)
  {
    return HAL_UART_Transmit(&USART::huart, reinterpret_cast<uint8_t *>(data), size, 1000);
  }

  HAL_StatusTypeDef USART::print(char *str)
  {
    return print(str, strlen(str));
  }

  void USART::serialClearScreen()
  {
    print("\033c");
  }

}

/* MSP Functions */

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (huart->Instance == USART2)
  {
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = USART_TX_Pin | USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin | USART_RX_Pin);
  }
}
