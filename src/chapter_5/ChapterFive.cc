#include <string>
#include <iostream>
#include <cstdint>

#include "Map.h"

int main(void)
{
    /* Give the map a stupidly low bucket count so that rehashes will get
       triggered. */
    Map<std::string, std::uint64_t> phonebook(1);

    phonebook.Insert("Ivan", 5803418882);
    phonebook.Insert("Taylor", 5801117777);
    phonebook.Insert("Jake", 4056667777);
    std::cout << "Load Factor After All Insertions = "
              << phonebook.LoadFactor() << std::endl;

    std::cout << "Ivan's Number = " << *phonebook.Get("Ivan") << std::endl;

    phonebook.Erase("Ivan");
    if (!phonebook.Get("Ivan"))
        std::cout << "Ivan has been erased." << std::endl;
    std::cout << "Load Factor After Deletion = "
              << phonebook.LoadFactor() << std::endl;

    return 0;
}
