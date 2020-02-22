#include <iostream>
#include <charconv>
#include <array>

int main()
{
    std::array<char, 10> str{};
    std::to_chars(str.data(), str.data()+str.size(), 42);
    std::cout << str.data();
}
