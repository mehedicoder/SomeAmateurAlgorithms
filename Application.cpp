
#include <iostream>
#include "MHA.h"

int main()
{
   std::vector<int> v {3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2,
                        3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2,
                        3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2,
                        3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2,
                        3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2,
                       3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2, 3, -2, 1, 5, -9, 10, 3, -3, 2};

    MHA::sort(std::begin(v), std::end(v));

    for (auto i: v)
        std::cout << i << ' ';

}