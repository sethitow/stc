#include <iostream>

extern "C"
{
    int64_t F_Sample(int64_t, int64_t);
}

int main(int argc, char *argv[])
{
    std::cout << "4 + 3 = " << F_Sample(4, 3) << std::endl;
}