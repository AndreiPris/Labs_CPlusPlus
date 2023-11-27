#include <iostream>

int function(int num)
{
    int b = num;
    return b;
}

int main()
{
    //файл имеет валидно тело
    std::cout << function(100) << std::endl;
}
