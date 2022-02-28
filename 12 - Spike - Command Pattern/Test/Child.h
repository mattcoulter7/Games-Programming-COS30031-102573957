#include "Base.h"

class Child : public Base {
public:
    explicit Child(int& _a) : Base(_a) {};
    void foo() override {};
    void bar() {};
};