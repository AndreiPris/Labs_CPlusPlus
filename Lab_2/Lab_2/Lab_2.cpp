#include <iostream>

int main()
{
    int i = 69;
    int number = 72;

    i += number;

    int arr[3] = {};

    int *iPointer;
    iPointer = &i;

    number = *iPointer;

    *iPointer = 15;

    iPointer = &arr[0];

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        std::cout << "Address N " << i << ": " << *iPointer << "\n";
        iPointer++;
    }
    iPointer--;
     
    arr[0] = 3;
    *iPointer = 6;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%i\n", i);
    }
}

