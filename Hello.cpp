#include "iostream"

int main(void)
{
  std::cout << "Hello cpp" << std::endl;
  /* The two ways to print is equal.
   * 'endl' is a manipulator, it ends the current line and lushes the buffer.
   */
  std::cout << "Hello cpp";
  std::cout << std::endl;

  int nums[] = {1, 2, 3};
  for (int i = 0; i < 3; ++i) {
	  std::cout << nums[i];
  }
  std::cout << std::endl;

  return 0;
}
