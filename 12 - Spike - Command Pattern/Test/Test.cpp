#include <iostream>

class Base {
public:
    Base(int &_a) {
        a = &_a;
    }
    virtual void foo() = 0;
protected:
    int *a;
};

class Child : public Base {
public:
    Child(int &_a) : Base(_a) {};
    void foo() {};
    void bar() {};
};

int main()
{
    int number = 1;
    Child test(number);
    std::cout << "Hello World!\n";
}