
#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    //Объект структуры TwoInts и значения его полей
    TwoInts i2 = { };
    i2.a = 5;
    i2.b = 7;

    //Значения полей структуры TwoInts
    std::cout << i2.a << std::endl;
    std::cout << i2.b << std::endl;

    //Объект структуры StructWithArray и значения его первого элемента
    StructWithArray s = { };
    s.arr[0] = 10;

    //Создание другого экземпляра структуры StructWithArray и установка значения его первого элемента
    StructWithArray s1 = { };
    s1.arr[0] = 15;

    //Указатель sPointer, который ссылается на структуру s
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    //Значения первого элемента массива s с использованием указателя sPointer 
    std::cout << s.arr[0] << std::endl;

    //Прямая модификация значения первого элемента массива s 
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl;

    //Модификация значения первого элемента массива s с использованием указателя sPointer 
    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl;

    //Изменение направления указателя sPointer чтобы он указывал на структуру s1
    sPointer = &s1;
    sPointer->arr[0] = 35;

    std::cout << s.arr[0] << std::endl; 
    std::cout << s1.arr[0] << std::endl;

    //массив из двух структур StructWithArray и инициализация элементов
    StructWithArray structArray[2] = { };
    structArray[0].arr[3] = 77;
    structArray[1].someNumber = &structArray[0].arr[3];

    sPointer = &s;

    //pointer, который указывает на четвертый элемент массива s
    int* pointer = &sPointer->arr[3];

    //изменение четвертого элемента массива s 
    s.arr[3] = 72;

    std::cout << *pointer;

    //memory и заполнение ее памяти нулями
    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));

    return 0;
}