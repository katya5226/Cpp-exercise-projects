#include <iostream>

class IntegerArray {

public:
    int* data; int size;
    IntegerArray(int n) {
        data = new int[n];
        this->size = n;
    }
    IntegerArray(IntegerArray& o) {
        data = new int[o.size];
        size = o.size;
        for (int i = 0; i < size; ++i)
            data[i] = o.data[i];
    }
    ~IntegerArray() {
        delete[] data;
        std::cout << "Destructor called" << std::endl;
    }
};


int main() {
    IntegerArray a(2);//This call the constructor
    a.data[0] = 4; a.data[1] = 2;
    if (true) {
        IntegerArray b = a;
    }
    std::cout << a.data[0] << std::endl; // The result is 4
}