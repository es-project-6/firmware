#include "stm32l0xx_hal.h"

UART_HandleTypeDef huart2;

void MX_USART2_UART_Init(void);
HAL_StatusTypeDef serialPrint(uint8_t data[], uint16_t size);
HAL_StatusTypeDef serialPrintNT(char *str);
void serialClearScreen();