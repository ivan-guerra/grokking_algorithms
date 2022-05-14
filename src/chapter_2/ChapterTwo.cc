#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
void PrintKeys(const std::vector<T>& keys)
{
    std::cout << "{ ";
    for (const T& i : keys)
        std::cout << i << ' ';
    std::cout << "}" << std::endl;
}

template <typename T>
void SelectionSort(std::vector<T>& keys)
{
    for (std::size_t i = 0; i < keys.size(); ++i) {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < keys.size(); ++j) {
            if (keys[j] < keys[min_index])
                min_index = j;
        }

        if (i != min_index)
            std::swap(keys[i], keys[min_index]);
    }
}

int main(void)
{
    std::vector<int> keys = {3, 2, 1, 0};
    std::cout << "Unsorted Keys = ";
    PrintKeys(keys);

    SelectionSort(keys);

    std::cout << "Sorted Keys = ";
    PrintKeys(keys);

    return 0;
}
