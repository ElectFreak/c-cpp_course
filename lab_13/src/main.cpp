#include <iostream>
#include "my_array.h"

void test_bool_array() {
  using namespace lab_13;
  my_array<bool, 10> arr;
  arr[0] = true;
  assert(arr[0] == true);

  arr[1] = false;
  assert(arr[1] != arr[0]);

  arr[3] = true;
  assert(arr[3] == arr[0] && arr[3] == true);

  arr.fill(true);
  for (int i = 0; i < 10; i++)
    assert(arr.at(i) == true);

  my_array<bool, 8> arr1;
  arr1.fill(true);
  for (int i = 0; i < 8; i++)
    assert(arr1.at(i) == true);
  
  my_array<int, 100> arr_int;
  arr_int[0] = 50;
  assert(arr_int[0] == 50);
  
  arr_int[99] = 99;
  assert(arr_int[99] == 99);

  arr_int.fill(239);
  for (int i = 0; i < 100; i++)
    assert(arr_int.at(i) == 239);

  std::cout << "OK" << std::endl;

}

int main() {
  test_bool_array();

  return 0;
}