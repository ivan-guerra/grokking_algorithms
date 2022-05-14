#include <cstdint>
#include <iostream>

uint32_t FactorialRecursive(uint32_t n)
{
    if (n <= 1)
        return 1;

    return n * FactorialRecursive(n - 1);
}

uint32_t FactorialIterative(uint32_t n)
{
    if (n <= 1)
        return 1;

    uint32_t accumulator = 1;
    while (n--)
        accumulator += accumulator * n;

    return accumulator;
}

int main(void)
{
    for (int i = 0; i < 10; ++i)
        std::cout << "FactorialRecursive(" << i << ") = "
                  << FactorialRecursive(i) << std::endl;

    return 0;
}
