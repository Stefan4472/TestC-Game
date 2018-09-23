#include "file_io_util.h"

int FileUtil::readFromBuffer(char buffer[], int startIndex, int numDigits, int base)
{
  int multiplier = 1;
  int result = 0;

  // read from least-significant to most-significant digit
  for (int i = startIndex + numDigits - 1; i >= startIndex; i--)
  {
    result += buffer[i] * multiplier;
    multiplier *= base;
  }

  return result;
}

void FileUtil::writeToBuffer(char buffer[], int startIndex, int numDigits,
  int value, int base)
{
  int place_val = intPower(base, numDigits - 1);

  // write digits. Note that we can't break the loop early--we need to write
  // every single digit from startIndex through startIndex + numDigits
  for (int i = startIndex; i < startIndex + numDigits; i++)
  {
    buffer[i] = value / place_val;
    value = value % place_val;
    place_val /= base;
  }
}

int intPower(int base, int exponent)
{
  int result = 1;
  for (int i = 0; i < exponent; i++)
  {
    result *= base;
  }
  return result;
}
