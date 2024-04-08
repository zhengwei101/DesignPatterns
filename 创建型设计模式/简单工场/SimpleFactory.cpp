#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::endl;

using ctorFunc = void* (*)();

class ObjectFactory
{
public:
    static void registerObject(const std::string& className, ctorFunc ctor)
    {
        getObjCtors()[className] = ctor;
    }

    static void* createObject(const std::string& className) 
    {
        auto iter = getObjCtors().find(className);
        if( iter != getObjCtors().end())
        {
            ctorFunc func =  iter->second;
            if(func)
            {
                return (*func)();
            }
        } 
        cout << "Error, not found constructor of " << className << endl;
        return nullptr;
    }
private:
    static std::map<std::string, ctorFunc>& getObjCtors()
    {
        static std::map<std::string, ctorFunc> instance;
        return instance;
    }
};

//通过宏定义动态创建
#define REG_CLASS(class_name)                                                          \
class class_name##Helper {                                                             \
    public:                                                                            \
    class_name##Helper() {                                                             \
        ObjectFactory::registerObject(#class_name, class_name##Helper::createObjFunc);  \
    }                                                                                  \
    static void* createObjFunc() {                                                     \
        return new class_name;                                                         \
    }                                                                                  \
};                                                                                     \
class_name##Helper class_name##helper;                                                 


class Api
{
public:
    virtual void test(const std::string& s) = 0;
protected:
    Api(){}
};

class ImplOne : public Api 
{
public:
    void test(const std::string& s) override
    {
        cout << "call ImplOne test func() do, " << s << endl;
    }
};

class ImplTwo : public Api 
{
public:
    void test(const std::string& s) override
    {
        cout << "call ImplTwo test func() do, " << s << endl;
    }
};

class Factory
{
    public:
    static Api* createApi(int type)
    {
        Api* api = nullptr;
        if(type == 1){
            api = new ImplOne();
        }
        else if(type == 2) {
            api = new ImplTwo();
        }
        return api;
    }

    static Api* createApi() {
        return new ImplOne();
    }
};

class AutoFactory
{
public:
    static Api* createApi(){
        return static_cast<Api*>(ObjectFactory::createObject("ImplTwo"));
    }
};

void TestFactory()
{
    //实现了客户端调用和ImplOne, ImplTwo的解耦合
    Api* api = Factory::createApi(2);
    api->test("data from database");

    Api* api2 = Factory::createApi();
    api2->test("data from txt");
}

void TestCreateMacro()
{
    REG_CLASS(ImplOne);
    REG_CLASS(ImplTwo);

    ImplTwo* two = static_cast<ImplTwo*>(ObjectFactory::createObject("ImplTwo"));
    ImplOne* one = static_cast<ImplOne*>(ObjectFactory::createObject("ImplOne"));

    if(one) {
        one->test("yaml");
    }

    if(two) {
        two->test("json");
    }
}

int main()
{
    Api* pApi = AutoFactory::createApi();
    if(pApi)
    {
	    pApi->test("xml");
    }

    TestCreateMacro();
    return 0;
}