#include <vector>
#include <iostream>
#include <algorithm>
#include <cstddef>

/* Exercise 4.1 */
int Sum(const std::vector<int>& values, int low, int high)
{
    if (low == high)
        return values[low];

    return values[low] + Sum(values, low + 1, high);
}

/* Exercise 4.2 */
template <typename T>
std::size_t CountItems(const std::vector<T>& items, std::size_t i)
{
    if (i == items.size())
        return 0;

    return 1 + CountItems(items, i + 1);
}

/* Exercise 4.3 */
template <typename T>
int Max(const std::vector<T>& items, std::size_t i)
{
    if (i == items.size())
        return -1;

    int candidate_max = Max(items, i + 1);
    if (-1 == candidate_max)
        return i;

    return (items[i] > items[candidate_max]) ? i : candidate_max;
}

/* Exercise 4.4 */
template <typename T>
int BinarySearch(const std::vector<int>& keys, const T& key, int low, int high)
{
    while (low <= high) {
        int mid = (low + high) / 2;
        if (keys[mid] == key)
            return mid;
        else if (keys[mid] < key)
            return BinarySearch(keys, key, mid + 1, high);
        else
            return BinarySearch(keys, key, low, mid - 1);
    }
    return -1;
}

template <typename T>
int Partition(std::vector<T>& values, int l, int r)
{
    T pivot_value = values[r];
    int j = l - 1;
    for (int i = l; i < r; ++i) {
        if (values[i] < pivot_value) {
            j++;
            std::swap(values[i], values[j]);
        }
    }
    j++;
    std::swap(values[r], values[j]);

    return j;
}

template <typename T>
void QuickSort(std::vector<T>& values, int l, int r)
{
    if (l >= r)
        return;

    int pivot = Partition(values, l, r);
    QuickSort(values, l, pivot - 1);
    QuickSort(values, pivot + 1, r);
}

int main(void)
{
    std::vector<int> values = {5, 4, 3, 2, 1};
    QuickSort(values, 0, values.size() - 1);
    std::cout << "Sorted Values = { ";
    for (const int& i : values)
        std::cout << i << ' ';
    std::cout << "}" << std::endl;

    std::cout << "Sum of Values = " << Sum(values, 0, values.size() - 1)
              << std::endl;
    std::cout << "Number of Items = " << CountItems(values, 0) << std::endl;
    std::cout << "Largest Item = " << values[Max(values, 0)] << std::endl;
    std::cout << "Search for 4 yields index = "
              << BinarySearch(values, 4, 0, values.size() - 1) << std::endl;

    return 0;
}
