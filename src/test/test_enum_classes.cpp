// testing out namespaced enum classes. Plain C-style enums have name collisions.
// g++ test/test_enum_classes.cpp -std=c++11 -o test_enums

#include <stdio.h>

enum class A { ZERO, ONE, TWO, THREE };
enum class B { ZERO, ONE, TWO, THREE };

int main()
{
  printf("A is %d %d %d %d\n", int(A::ZERO), int(A::ONE), int(A::TWO), int(A::THREE));
  printf("B is %d %d %d %d\n", int(B::ZERO), int(B::ONE), int(B::TWO), int(B::THREE));

  printf("In a loop:\n");
  A a_inst;
  for (int i = 0; i < 4; i++)
  {
    a_inst = A(i);
    printf("%d\n", int(a_inst));
  }
}
