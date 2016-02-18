// vim: set ft=cpp ts=2 sw=2 et :
#include "numeric.hpp"

int main(int argc, char const* argv[])
{
  numeric::vector<float> x{0, 1, 2}, y{-1, -1, -1}, z{0, 2, 3};
  numeric::vector<float> t = x + y - z;
  std::cout << t << std::endl;
}
