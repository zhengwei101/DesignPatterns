#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::endl;

template <typename T>
class Singleton
{
public:
    static T &GetInstance();

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;

protected:
    Singleton() = default;
};

template <typename T>
T &Singleton<T>::GetInstance()
{
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static T instance{};
    return instance;
}

class Test final : public Singleton<Test>
{
public:
    Test() { cout << "Test Ctor" << endl; }
    ~Test() { cout << "Test Dtor" << endl; }

    void use() const { cout << " call use" << endl; }
};


void test_singleton()
{
    auto const &t = Test::GetInstance();
    t.use();

    //delete &Test::GetInstance();

    {
        Test::GetInstance().use();
    }
}

int main()
{
    test_singleton();
}
