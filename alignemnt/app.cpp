#include <iostream>
#include <cstring>
#include <vector>
#include <new>

using namespace std;

void punCharArray()
{
  alignas(sizeof(int)) char data[sizeof(int)];
  int32_t* i = new (data) int{12};
  std::cout << "\n n=" << *i;
  std::cout << "\n n=" << *reinterpret_cast<int32_t*>(data);
  std::vector<int> v;
  
}

int main()
{
	punCharArray();
}
