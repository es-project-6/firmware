#include "hal/lcd.hal.hpp"
#include "hal/i2c.hal.hpp"
#include "util/delay.hpp"
#include "hal/lcd-font.hal.hpp"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

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

  void LcDisplay::print(char character)
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

  void LcDisplay::print(const char *str, size_t size)
  {
    if (str == NULL)
    {
      return;
    }
    for (size_t i = 0; i < size && i < LCD_CHARACTERS_PER_LINE; i++)
    {
      print(str[i]);
    }
  }

  void LcDisplay::print(const char *str)
  {
    return print(str, strlen(str));
  }

  void LcDisplay::printf(const char *format, ...)
  {
    char buff[100];
    va_list va;
    va_start(va, format);
    vsprintf(buff, format, va);
    va_end(va);

    return print(buff);
  }

  void LcDisplay::clearDisplay()
  {
    writeInstruction(CLEAR_DISPLAY);
    cursorPosition = 0;
    delay(2);
  }

  void LcDisplay::setCursor(uint8_t row, uint8_t column)
  {
    cursorPosition = (((row % LCD_LINES) * LCD_SECOND_LINE_BEGIN) + (column % LCD_CHARACTERS_PER_LINE));
    writeInstruction(SET_DDRAM_ADDRESS | cursorPosition);
  }

  /**
   * @brief select CG RAM Adress that the following read/write should be applied to
   * 
   * @param address CG RAM cell address, 0-7
   */
  void LcDisplay::setCgRamAddress(uint8_t address)
  {
    HAL::LcDisplay::writeInstruction(0b01000000 | address << 3);
  }

  void LcDisplay::addCustomChar(uint8_t address, const char *data)
  {
    LcDisplay::setCgRamAddress(address);
    for (size_t i = 0; i < 8; i++)
    {
      HAL::LcDisplay::writeData(data[i]);
    }
  }

  void LcDisplay::clearCustomChars()
  {
    for (size_t i = 0; i < 8; i++)
    {
      HAL::LcDisplay::addCustomChar(i, HAL::LcdFont::EMPTY);
    }
  }
}