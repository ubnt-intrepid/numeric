# Yet another numeric library for C++11

* single header
* expression template

## example

```cpp
#include <iostream>
#include "numeric.hpp"

int main()
{
  numeric::vector<double> a{ 1, 2, 3 };
  numeric::vector<double> b{ 2, 2 };

  numeric::vector<double> c = a + b;
  std::cout << c << std::endl;
```


## LICENSE

MIT License (see [LICENSE](LICENSE).)
