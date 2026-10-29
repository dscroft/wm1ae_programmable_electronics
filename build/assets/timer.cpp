#define main altmain
#include "visible.h"
#undef main
#include <chrono>
#include <iostream>
int main()
{
     const auto start = std::chrono::steady_clock::now();
     const int result = altmain();
     const auto end = std::chrono::steady_clock::now();
     const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
     std::cout << "Took " << elapsed.count() << " ms\n";
     return result;
}