#include <iostream>
using std::cout;
using std::endl;

// 抽象类
class ISplitter
{
public:
    virtual void split() = 0;
    virtual ISplitter *clone() = 0; // 通过克隆自己来创建对象

    virtual ~ISplitter() {}
};

// 具体类
class BinarySplitter : public ISplitter
{
public:
    void split()
    {
        cout << "BinarySplitter" << endl;
    }
    virtual ISplitter *clone()
    {
        return new BinarySplitter(*this);
    }
};

class TxtSplitter : public ISplitter
{
public:
    void split()
    {
        cout << "TxtSplitter" << endl;
    }
    virtual ISplitter *clone()
    {
        return new TxtSplitter(*this);
    }
};

class MainForm
{
public:
    MainForm(ISplitter *prototype)
    {
        this->prototype = prototype;
    }

    void Button1_Click()
    {
        ISplitter *splitter = prototype->clone(); // 克隆原型
        splitter->split();
    }

private:
    ISplitter *prototype; // 原型对象
};

int main()
{
    ISplitter *prototype = new BinarySplitter();
    MainForm main(prototype);
    main.Button1_Click();

    return 0;
}