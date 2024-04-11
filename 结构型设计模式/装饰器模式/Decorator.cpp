#include <iostream>
#include <string>
using std::cout;
using std::endl;

// 业务操作
class Stream
{
public:
    virtual std::string Read(int number) = 0;
    virtual void Seek(int position) = 0;
    virtual void Write(char data) = 0;
    virtual ~Stream(){};
};

// 主体类
class FileStream : public Stream
{
public:
    std::string Read(int number) override
    {
        // 读文件流
        cout << "FileStream Read: " << number << endl;
        return "";
    }
    void Seek(int position) override
    {
        // 定位文件流
    }
    void Write(char data) override
    {
        // 写文件流
    }
};

class NetworkStream : public Stream
{
public:
    std::string Read(int number) override
    {
        // 读网络流
        return "";
    }
    void Seek(int position) override
    {
        // 定位文件流
    }
    void Write(char data) override
    {
        // 写文件流
    }
};

class MemoryStream : public Stream
{
public:
    std::string Read(int number) override
    {
        // 读内存流
        return "";
    }
    void Seek(int position) override
    {
        // 定位内存流
    }
    void Write(char data) override
    {
        // 写内存流
    }
};

// 扩展操作
class DecoratorStream : public Stream //这里的继承是用来获取Stream中的接口
{
protected:
    Stream *stream = nullptr; //这里是指定要装饰的Stream对象
public:
    DecoratorStream(Stream *s) : stream(s) {}

    std::string Read(int number) override
    {
        return stream->Read(number);
    }
    void Seek(int position) override
    {
        stream->Seek(position);
    }
    void Write(char data) override
    {
        stream->Write(data);
    }
    //...
};

//加密流
class CryptoStream : public DecoratorStream
{
public:
    CryptoStream(Stream *s) : DecoratorStream(s)
    {
    }

    std::string Read(int number) override
    {
        // 额外的加密操作...
        cout << "CryptoStream Read: " << number << endl;
        stream->Read(number); // 读文件流
        return "";
    }
    void Seek(int position) override
    {
        // 额外的加密操作...
        stream->Seek(position); // 定位文件流
    }
    void Write(char data) override
    {
        // 额外的加密操作...
        stream->Write(data); // 写文件流
    }
};

//缓存流
class BufferedStream : public DecoratorStream
{
public:
    BufferedStream(Stream *s) : DecoratorStream(s) {}
    std::string Read(int number) override
    {
        // 额外的缓存操作...
        cout << "BufferedStream Read: " << number << endl;
        stream->Read(number); // 读文件流
        return "";
    }
    //...
};

void Process()
{
    // 运行时装配
    FileStream *s1 = new FileStream();
    s1->Read(1);

    CryptoStream *s2 = new CryptoStream(s1);
    s2->Read(2);

    BufferedStream *s3 = new BufferedStream(s1);
    s3->Read(3);

    BufferedStream *s4 = new BufferedStream(s2);
    s4->Read(4);
}

int main()
{
    Process();
    return 0;
}