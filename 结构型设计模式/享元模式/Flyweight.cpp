#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;

//何用共享技术，比较线程池，连接池之类的
class Font
{
private:
    // unique object key
    std::string key;

    // object state
    //....
public:
    Font(const std::string &k) : key(k)
    {
        //...
    }
    std::string name()
    {
        return key;
    }
};
class FontFactory
{
private:
    std::map<std::string, Font *> fontPool;

public:
    Font *GetFont(const std::string &key)
    {
        if (auto iter = fontPool.find(key); iter != fontPool.end())
        {
            return fontPool[key];
        }
        else
        {
            Font *font = new Font(key);
            fontPool[key] = font;
            return font;
        }
    }

    void clear()
    {
        //...
    }
};

int main()
{
    FontFactory factory;
    Font* font = factory.GetFont("Times_New_Roman");
    cout << "Font: " << font->name();
    return 0;
}