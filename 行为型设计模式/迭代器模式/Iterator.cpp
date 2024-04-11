#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class Iterator
{
public:
    virtual void first() = 0;        //第一个元素
    virtual void next() = 0;         //下一下元素
    virtual bool isDone() const = 0; //到头了
    virtual T &current() = 0;        //当前的元素
};

template <typename T>
class MyCollection;

template <typename T>
class CollectionIterator : public Iterator<T>
{
    MyCollection<T> mc;
    T value;
public:
    CollectionIterator(const MyCollection<T> &c) : mc(c) {}

    void first() override
    {
        cout << "call first()" << endl;
    }
    void next() override
    {
        cout << "call next()" << endl;
    }
    bool isDone() const override
    {
        return true;
    }
    T &current() override
    {
        cout << "call current()" << endl;
        return value;
    }
};

template <typename T>
class MyCollection
{
public:
    Iterator<T>* GetIterator()
    {
        //...
        iter_ = new CollectionIterator(*this);
        return iter_;
    }
private:
    CollectionIterator<T>* iter_ = nullptr;
};

void MyAlgorithm()
{
    MyCollection<int> mc;

    Iterator<int> *iter = mc.GetIterator();

    cout << iter->current() << endl;

    for (iter->first(); !iter->isDone(); iter->next())
    {
        cout << iter->current() << endl;
    }
}

int main()
{
    MyAlgorithm();
    return 0;
}