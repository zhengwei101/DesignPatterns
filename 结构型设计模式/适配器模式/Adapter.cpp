#include <iostream>
using std::cout;
using std::endl;

// STL中的stack和queue就是一种适配器模式，它们底层都依赖于deque来实现

// 目标接口（新接口）
class ITarget
{
public:
    virtual void process() = 0;
};

// 遗留接口（老接口）
class IAdaptee
{
public:
    virtual void foo(int data) = 0;
    virtual int bar() = 0;
};

// 遗留类型
class OldClass : public IAdaptee
{
    void foo(int data) override
    {
        cout << "foo() from OldClass" << endl;
    }
    int bar() override
    {
        cout << "bar() from OldClass" << endl;
        return 0;
    }
};

// 对象适配器，用来适配新的ITarget接口
class Adapter : public ITarget // 继承
{ 
protected:
    IAdaptee *pAdaptee; // 组合

public:
    Adapter(IAdaptee *pAd) : pAdaptee(pAd) {}

    virtual void process()
    {
        int data = pAdaptee->bar();
        pAdaptee->foo(data);
    }
};

/*
// 类适配器, 不建议使用
class Adapter : public ITarget,
                protected OldClass
{ // 多继承

}
*/

int main()
{
    IAdaptee *pAdaptee = new OldClass();

    ITarget *pTarget = new Adapter(pAdaptee);
    pTarget->process();

    return 0;
}