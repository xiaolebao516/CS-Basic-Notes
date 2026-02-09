// subject委托observer，observer可以被多个不同功能的observer继承，并根据对应的类型做出对应的实现，
// 当subject的状态改变，可以notify所有的observer，observer根据自己的实现做出对应的反应

#include <iostream>
#include <vector>
using namespace std;

class Subject
{
    int m_value;
    vector<Observer*> observers;

public:
    // 添加观察者（通过订阅）
    void attach(Observer* observer)
    {
        observers.push_back(observer);
    }
    void setValue(int value)
    {
        m_value = value;
        notify();
    }
    void notify()
    {
        for (Observer* observer : observers)
        {
            // 通知所有观察者
            observer->update(this, m_value);
        }
    }
    void detach(Observer* observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
};

class Observer
{
public:
    virtual void update(Subject* subject, int value) = 0;
};

// 继承Observer的具体观察者要对update方法进行实现