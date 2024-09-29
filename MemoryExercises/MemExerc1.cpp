#include <iostream>

class Foo {
public:
    Foo(void)
    {
        std::cout << "Foo constructor 1 called" << std::endl;
    }
    ~Foo(void)
    {
        std::cout << "Foo destructor called" << std::endl;
    }
};
/*int main()
{
    Foo f;
    f.~Foo();

    return 0;
}*/