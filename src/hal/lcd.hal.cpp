#include "hal/lcd.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "util/delay.hpp"

namespace HAL
{
  uint8_t LcDisplay::cursorPosition = LCD_FIRST_LINE_BEGIN;

  void LcDisplay::init()
  {
    delay(15);
    writeInstruction(FUNCTION_SET | TWO_LINES | FONT_5X8);
    delay(39);
    writeInstruction(DISPLAY_CONTROL | DISPLAY_ON);
    delayMicros(39);
    writeInstruction(CLEAR_DISPLAY);
    delay(2);
  }

  void LcDisplay::write(uint8_t value, bool instruction)
  {
    uint8_t write_buffer[] = {instruction ? 0x80 : 0x40, value};
    HAL::I2C::send(LCD_I2C_ADDRESS, write_buffer, 2);
  }

  void LcDisplay::writeInstruction(uint8_t value)
  {
    write(value, true);
  }

  void LcDisplay::writeData(uint8_t value)
  {
    write(value, false);
  }

  void LcDisplay::printChar(char character)
  {
    if (cursorPosition == LCD_FIRST_LINE_BEGIN)
    {
      clearDisplay();
    }

    writeData(character);

    cursorPosition++;
    if (cursorPosition == LCD_FIRST_LINE_END)
    {
      // set cursor to beginning of next line
      cursorPosition = LCD_SECOND_LINE_BEGIN;
      writeInstruction(SET_DDRAM_ADDRESS | cursorPosition);
    }
    else if (cursorPosition == LCD_SECOND_LINE_END)
    {
      // set cursor to beginning of first line
      cursorPosition = LCD_FIRST_LINE_BEGIN;
    }
  }

  void LcDisplay::printString(const char *str)
  {
    if (str == NULL)
    {
      return;
    }
    char character = 0;
    while ((character = *str++) != '\0')
    {
      printChar(character);
    }
  }

  void LcDisplay::clearDisplay()
  {
    writeInstruction(CLEAR_DISPLAY);
    cursorPosition = 0;
    delay(2);
  }
}