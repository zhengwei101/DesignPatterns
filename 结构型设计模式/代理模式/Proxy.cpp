#include <iostream>
using std::cout;
using std::endl;

class ISubject
{
public:
    virtual void process() = 0;
};

class RealSubject : public ISubject
{
public:
    virtual void process()
    {
        //....
        cout << "RealSubject doing sth." << endl;
    }
};

// Proxy的设计
class SubjectProxy : public ISubject
{
public:
    virtual void process()
    {
        // 对RealSubject的一种间接访问
        //....
        ISubject* subject = new RealSubject();
        subject->process();

    }
};

class ClientApp
{
    ISubject *subject;

public:
    ClientApp()
    {
        //subject = new RealSubject();
        subject = new SubjectProxy();
    }

    void DoTask()
    {
        //...
        subject->process();
        //....
    }
};

int main()
{
    ClientApp app;
    app.DoTask();
    
    return 0;
}