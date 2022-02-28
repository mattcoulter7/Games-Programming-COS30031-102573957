#include <iostream>

//#region Task 7
class Person{
    private:
        std::string name;
        int age;
    public:
        Person(std::string _name,int _age){
            name = _name;
            age = _age;
        };
        void grow(int years = 1){
            age += years;
        };
        int getAge(){
            return age;
        }

        std::string getName(){
            return name;
        }
        
        std::string favouriteFood;
};
//#endregion