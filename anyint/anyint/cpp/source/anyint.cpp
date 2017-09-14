#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "anyint.h"


int add(int a, int b)
{
  return a + b;
}

int add_array(int arr[], size_t len)
{
  int total = 0;
  for (size_t i = 0; i < len; ++i)
  {
    total += arr[i];
  }
  return total;
}

int get_int()
{
  srand(time(NULL));
  return rand() % 10;
}
