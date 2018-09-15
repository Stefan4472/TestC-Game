#ifndef FILE_IO_UTIL_H
#define FILE_IO_UTIL_H

#include <stdio.h> // TODO: REMOVE IMPORT + DEBUG PRINT STATEMENTS

namespace FileUtil
{
    int readFromBuffer(char buffer[], int startIndex, int numDigits,
      int base=128);
    void writeToBuffer(char buffer[], int startIndex, int numDigits,
      int value, int base=128);
}

int intPower(int base, int exponent);

#endif
