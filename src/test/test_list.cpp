// test using an STL list as a stack and linked list
// g++ test_list.cpp -o test_list -std=c++11

#include <stdio.h>
#include <list>
#include <string>

using namespace std;

int main()
{
  list<string> str_list = {"s1", "s2", "s3", "s4"};

  printf("Forwards iteration:\n");
  list<string>::iterator it;
  for (it = str_list.begin(); it != str_list.end(); it++)
  {
    printf("%s ", it->c_str());
  }

  printf("\nBackwards iteration:\n");
  list<string>::reverse_iterator r_it;
  for (r_it = str_list.rbegin(); r_it != str_list.rend(); r_it++)
  {
    printf("%s ", r_it->c_str());
  }

  printf("\nStack usage:\n");
  while (!str_list.empty())
  {
    printf("Popping %s\n", str_list.front().c_str());
    str_list.pop_front();
  }
}
