#include <iostream>
using std::cout;
using std::endl;

// 程序库开发人员
class Library
{
public:
    // 稳定 template method
    void Run()
    {
        Step1();

        if (Step2()) // 支持变化 ==> 虚函数的多态调用
        {
            Step3();
        }

        for (int i = 0; i < 2; i++)
        {
            Step4(); // 支持变化 ==> 虚函数的多态调用
        }

        Step5();
    }
    virtual ~Library() {}

protected:
    void Step1()
    { // 稳定
        cout << "Lib Step1" << endl;
    }
    void Step3()
    { // 稳定
        cout << "Lib Step3" << endl;
    }
    void Step5()
    { // 稳定
        cout << "Lib Step5" << endl;
    }

    virtual bool Step2() = 0; // 变化
    virtual void Step4() = 0; // 变化
};

// 应用程序开发人员
class Application : public Library
{
protected:
    bool Step2() override
    {
        //... 子类重写实现
        cout << "App Step2" << endl;
        return true;
    }

    void Step4() override
    {
        //... 子类重写实现
        cout << "App Step4" << endl;
    }
};

int main()
{
    Library *pLib = new Application();
    pLib->Run();
    delete pLib;
}
