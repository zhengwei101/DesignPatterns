#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Memento
{
    std::string state;
    //..
public:
    Memento(const std::string & s) : state(s) {}
    std::string getState() const { return state; }
    void setState(const std::string & s) { state = s; }
};

//在不破坏Originator封装性的前提下，捕获Originator的内部状态，并在该对象之外保存这个状态。
class Originator
{
    std::string state;
    //....
public:
    Originator() {}
    Memento createMomento() {
        Memento m(state);
        return m;
    }
    void setMomento(const Memento & m) {
        state = m.getState();
    }

    void ChangeState(const std::string& s)
    {
        state = s;
    }

    std::string GetState()
    {
        return state;
    }
};

int main()
{
    Originator orig;
    
    //开始状态
    orig.ChangeState("operator: 1024");
    cout << "State: " << orig.GetState() << endl;

    //捕获对象状态，存储到备忘录
    Memento mem = orig.createMomento();
    
    //改变orginator状态
    orig.ChangeState("operator: 2048");
    cout << "State: " << orig.GetState() << endl;
    //... 
    
    //从备忘录中恢复
    orig.setMomento(mem);
    cout << "State: " << orig.GetState() << endl;
    return 0;
}