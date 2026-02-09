#include <iostream>
class Component
{
public:
    Component() {
        std::cout << "component ctor called" << std::endl;
    }

};  

class Based
{
public:
    Based() {
        std::cout << "based ctor called" << std::endl;
    }

};

class Derived : public Based
{
public:
    Component component;
    Derived() {
        std::cout << "derived ctor called" << std::endl;
    }
};

int main()
{
    Derived d;
    return 0;
}
