// test method of reading/writing numbers into buffers
// g++ test/test_file_io.cpp util/file_io_util.cpp -o test_file_io -Iutil -std=c++11
#include <stdio.h>
#include "file_io_util.h"

int main()
{
  char buffer[100];
  int bases[4] = { 16, 64, 128, 256 };
  for (int base_index = 0; base_index < 4; base_index++)
  {
    int base = bases[base_index];
    for (int i = 0; i < 30; i++)
    {
      int write_val = i * 10;
      FileUtil::writeToBuffer(buffer, i * 3, 3, write_val, base);
      int read_val = FileUtil::readFromBuffer(buffer, i * 3, 3, base);
      printf("Wrote %d Read %d (base %d)\n", write_val, read_val, base);
      if (write_val != read_val)
      {
        printf("ERROR\n");
      }
    }
  }
}
