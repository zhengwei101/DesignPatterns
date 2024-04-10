#include <iostream>
using std::cout;
using std::endl;

class Context
{
public:
    int revenue = 0;
};

//基类
class TaxStrategy
{
public:
    virtual double Calculate(const Context &context) = 0;
    virtual ~TaxStrategy() {}
};

class CNTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //...
        cout << "Calculate China Tax" <<endl;
        return 0;
    }
};

class USTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //...
        cout << "Calculate United States Tax" <<endl;
        return 0;
    }
};

// 扩展
//*********************************
class FRTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //...
        cout << "Calculate France Tax" <<endl;
        return 0;
    }
};

//工厂基类
class StrategyFactory
{
public:
    virtual TaxStrategy *NewStrategy() = 0;
    virtual ~StrategyFactory(){}
};

//具体工厂
class CNTaxFactory: public StrategyFactory{
public:
    TaxStrategy* NewStrategy() override{
        return new CNTax();
    }
};

class USTaxFactory: public StrategyFactory{
public:
    TaxStrategy* NewStrategy() override{
        return new USTax();
    }
};

// 新增
class FRTaxFactory: public StrategyFactory{
public:
    TaxStrategy* NewStrategy() override{
        return new FRTax();
    }
};

class SalesOrder
{
public:
    SalesOrder(StrategyFactory *factory)
    {
        this->strategy = factory->NewStrategy();
    }

    ~SalesOrder()
    {
        delete this->strategy;
    }

    double CalculateTax()
    {
        //...
        Context context;
        strategy->Calculate(context); // 多态调用
        //...
        return 0;
    }

private:
    TaxStrategy *strategy = nullptr;
};

int main()
{
    StrategyFactory *factory = new FRTaxFactory();
    SalesOrder salesOrder(factory);
    double value = salesOrder.CalculateTax();

    return 0;
}
