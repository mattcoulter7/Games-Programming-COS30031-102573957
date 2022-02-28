class Base {
public:
    explicit Base(int& _a) {
        a = &_a;
    }
    virtual void foo() = 0;
protected:
    int* a;
};