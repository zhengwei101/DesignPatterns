#include <iostream>
using std::cout;
using std::endl;

// 抽象类
class ISplitter
{
public:
    virtual void split() = 0;
    virtual ~ISplitter() {}
};

// 工厂基类
class SplitterFactory
{
public:
    virtual ISplitter *CreateSplitter() = 0;
    virtual ~SplitterFactory() {}
};

// 具体类
class BinarySplitter : public ISplitter
{
public:
    void split() override
    {
        cout << "binary split" << endl;
    }
};

class TxtSplitter : public ISplitter
{
public:
    void split() override
    {
        cout << "text split" << endl;
    }
};

class VideoSplitter : public ISplitter
{
public:
    void split() override
    {
        cout << "video split" << endl;
    }
};

// 具体工厂
class BinarySplitterFactory : public SplitterFactory
{
public:
    virtual ISplitter *CreateSplitter()
    {
        return new BinarySplitter();
    }
};

class TxtSplitterFactory : public SplitterFactory
{
public:
    virtual ISplitter *CreateSplitter()
    {
        return new TxtSplitter();
    }
};

class VideoSplitterFactory : public SplitterFactory
{
public:
    virtual ISplitter *CreateSplitter()
    {
        return new VideoSplitter();
    }
};

class MainForm  //现在MainForm结构是稳定的，不依赖于具体类
{
    SplitterFactory *factory; // 工厂

public:
    MainForm(SplitterFactory *factory)
    {
        this->factory = factory;
    }

    void Button1_Click()
    {
        ISplitter *splitter = factory->CreateSplitter(); // 多态new
        splitter->split();
    }
};

int main()
{
    BinarySplitterFactory* binFactory = new BinarySplitterFactory();
    MainForm form(binFactory);
    form.Button1_Click();

    return 0;
}
