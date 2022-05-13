#include <vector>
#include <iostream>

template <typename T>
int BinarySearch(const std::vector<T>& keys, const T& key)
{
    int low  = 0;
    int high = keys.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (keys[mid] == key)
            return mid;
        else if (keys[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(void)
{
    std::vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << "Sorted Search Keys = { ";
    for (const int& i : keys)
        std::cout << i << ' ';
    std::cout << "}" << std::endl;

    std::cout << "Search for 1 yields index: "
              << BinarySearch(keys, 1) << std::endl;
    std::cout << "Search for -1 yields index: "
              << BinarySearch(keys, -1) << std::endl;

    return 0;
}
