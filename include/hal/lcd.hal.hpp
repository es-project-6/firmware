#pragma once

#include "stm32l0xx_hal.h"

#include <cstdint>

#define LCD_I2C_ADDRESS 62

// lcd_instructions
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define ENTRY_MODE_SET 0x04
#define DISPLAY_CONTROL 0x08
#define CURSOR_DISPLAY_SHIFT 0x10
#define FUNCTION_SET 0x20
#define SET_CGRAM_ADDRESS 0x40
#define SET_DDRAM_ADDRESS 0x80

// lcd_entry_mode_options
#define DECREMENT 0x00
#define INCREMENT 0x02
#define ACCOMPANIES_DISPLAY_SHIFT 0x01

// lcd_display_control_options
#define CURSOR_BLINK 0x01
#define CURSOR_ON 0x02
#define DISPLAY_ON 0x04

// lcd_cursor_display_shift_options
#define CURSOR_SHIFT 0x00
#define DISPLAY_SHIFT 0x08
#define SHIFT_LEFT 0x00
#define SHIFT_RIGHT 0x04

// lcd_function_set_options
#define FONT_5X8 0x00
#define FONT_5X10 0x04
#define ONE_LINE 0x00
#define TWO_LINES 0x08
#define DATA_4BIT 0x00
#define DATA_8BIT 0x10

#define LCD_LINES 2
#define LCD_CHARACTERS_PER_LINE 16
#define LCD_FIRST_LINE_BEGIN 0x00
#define LCD_FIRST_LINE_END (LCD_FIRST_LINE_BEGIN + LCD_CHARACTERS_PER_LINE)
#define LCD_SECOND_LINE_BEGIN 0x40 // the display can scroll horizontally through 64 characters
#define LCD_SECOND_LINE_END (LCD_SECOND_LINE_BEGIN + LCD_CHARACTERS_PER_LINE)

namespace HAL
{
  class LcDisplay
  {
  private:
    static uint8_t cursorPosition;

  public:
    static void init();
    static void write(uint8_t value, bool instruction);
    static void writeInstruction(uint8_t value);
    static void writeData(uint8_t value);
    static void printChar(char character);
    static void printString(const char *str);
    static void clearDisplay();
  };
}