// vim: set ft=cpp ts=2 sw=2 et :
#include "numeric.hpp"

int main(int argc, char const* argv[])
{
  numeric::vector<float> x{0, 1, 2};
  numeric::vector<float> y{-1, -1, -1};
  numeric::vector<float> z{0, 2, 3};

  auto t = x + y - z;
  std::cout << static_cast<numeric::vector<float>>(t) << std::endl;
}
