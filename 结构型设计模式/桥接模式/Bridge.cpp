#include <iostream>
#include <string>
using std::cout;
using std::endl;

//图像类
class Image
{
private:
    std::string filePath_;
};

class MessagerImpl
{
public:
    virtual void PlaySound() = 0;
    virtual void DrawShape() = 0;
    virtual void WriteText() = 0;
    virtual void Connect() = 0;

    virtual ~MessagerImpl() {}
};

class Messager
{
public:
    Messager(MessagerImpl* msgImpl) : impl(msgImpl) {}
    virtual void Login(std::string username, std::string password) = 0;
    virtual void SendMessage(std::string message) = 0;
    virtual void SendPicture(Image image) = 0;

    virtual ~Messager() {}
protected:
    MessagerImpl *impl; //...
};

// 平台实现方向上的变化 n
class PCMessagerImpl : public MessagerImpl
{
public:
    void PlaySound() override
    {
        cout << "music on" << endl;
        //**********
    }
    void DrawShape() override
    {
        cout << "draw shape" << endl;
        //**********
    }
    void WriteText() override
    {
        cout << "write text" << endl;
        //**********
    }
    void Connect() override
    {
        cout << "connect server" << endl;
        //**********
    }
};

class MobileMessagerImpl : public MessagerImpl
{
public:
    void PlaySound() override
    {
        //==========
    }
    void DrawShape() override
    {
        //==========
    }
    void WriteText() override
    {
        //==========
    }
    void Connect() override
    {
        //==========
    }
};

// 业务抽象方向上的变化 m

// 类的数目：1+n+m

class MessagerLite : public Messager
{
public:
    MessagerLite(MessagerImpl* msgImpl) : Messager(msgImpl) {}
    void Login(std::string username, std::string password) override
    {
        cout << "...login begin..." << endl;
        impl->Connect();
        //........
        cout << " " << username << " login success" << endl;
    }
    void SendMessage(std::string message) override
    {
        impl->WriteText();
        //........
    }
    void SendPicture(Image image) override
    {
        impl->DrawShape();
        //........
    }
};

class MessagerPerfect : public Messager
{
public:
    MessagerPerfect(MessagerImpl* msgImpl) : Messager(msgImpl) {}
    void Login(std::string username, std::string password) override
    {
        cout << "...login begin..." << endl;
        impl->PlaySound();
        //********
        impl->Connect();
        //........
        cout << " " << username << " login success" << endl;
    }
    void SendMessage(std::string message) override
    {
        impl->PlaySound();
        //********
        impl->WriteText();
        //........
    }
    void SendPicture(Image image) override
    {
        impl->PlaySound();
        //********
        impl->DrawShape();
        //........
    }
};

void Process()
{
    // 运行时装配, 可自由组合平台和业务两个方向的具体类的对象。
    MessagerImpl *pImpl = new PCMessagerImpl();

    Messager *xx = new MessagerLite(pImpl);
    xx->Login("xx", "123");

    Messager *yy = new MessagerPerfect(pImpl);
    yy->Login("yy", "123");
}

int main()
{
    Process();
    return 0;
}