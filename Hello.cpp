#include "iostream"

int main(int argc, char *argv[])
{
  std::cout << "Hello cpp" << std::endl;
  /* The two ways to print is equal.
   * 'endl' is a manipulator, it ends the current line and lushes the buffer.
   */
  std::cout << "Hello cpp";
  std::cout << std::endl;

  return 0;
}
