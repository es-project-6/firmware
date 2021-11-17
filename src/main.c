#include "hal/system_conf_hal.h"
#include "hal/custom_hal.h"
#include "hal/usart_hal.h"
#include <string.h>
#include <stdio.h>

uint8_t data[10];

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  SystemConf_Init();
  CustomHAL_Init();

  serialClearScreen();
  int counter = 0;
  while (1)
  {
    uint32_t val = getADCValue();

    //HAL_UART_Receive(&huart2, data, 10, 1000);

    uint8_t data[100];

    sprintf(data, "Counter: %d\t\tother Counter: %d\r\nother Counter: %d\tCounter: %d\r\n", counter, counter * 2, counter * 3, counter * 4);
    serialClearScreen();
    serialPrintNT(data);
    counter++;

    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);

    HAL_Delay(100);
  }
}
