#include <iostream>
using std::cout;
using std::endl;

//抽象基类
class House
{
public:
    virtual void HouseInfo() = 0;
    virtual ~House() {};
    //....
};

//抽象基类
class HouseBuilder
{
public:
    HouseBuilder(House* h) : pHouse(h) {}
    House *GetResult() { return pHouse; }
    virtual ~HouseBuilder() {}

    virtual void BuildPart1() = 0;
    virtual void BuildPart2() = 0;
    virtual bool BuildPart3() = 0;
    virtual void BuildPart4() = 0;
    virtual void BuildPart5() = 0;

protected:
    House *pHouse = nullptr;
};

class StoneHouse : public House
{
public:
    void HouseInfo() override { cout << "Stone House" << endl; }
};

class StoneHouseBuilder : public HouseBuilder
{
public:
    StoneHouseBuilder(House* h) : HouseBuilder(h) {}
    void BuildPart1() override
    {
        cout << "Stone House BuildPart1" << endl;
    }
    void BuildPart2() override
    {
        cout << "Stone House BuildPart2" << endl;
    }
    bool BuildPart3() override
    {
        cout << "Stone House BuildPart3" << endl;
        return true;
    }
    void BuildPart4() override
    {
        cout << "Stone House BuildPart4" << endl;
    }
    void BuildPart5() override
    {
        cout << "Stone House BuildPart5" << endl;
    }
};

//建造流程（稳定）
class HouseDirector
{
public:
    HouseDirector(HouseBuilder *pBuilder)
    {
        this->pHouseBuilder = pBuilder;
    }

    House *Construct()
    {
        pHouseBuilder->BuildPart1();

        for (int i = 0; i < 2; i++)
        {
            pHouseBuilder->BuildPart2();
        }

        bool flag = pHouseBuilder->BuildPart3();
        if (flag)
        {
            pHouseBuilder->BuildPart4();
        }

        pHouseBuilder->BuildPart5();

        return pHouseBuilder->GetResult();
    }
private:
    HouseBuilder *pHouseBuilder = nullptr;
};

int main()
{
    StoneHouse* stoneHouse = new StoneHouse();
    StoneHouseBuilder* stoneHouseBuilder = new StoneHouseBuilder(stoneHouse);

    HouseDirector director(stoneHouseBuilder);
    House* house = director.Construct();
    if(house)
    {
        house->HouseInfo();
    }
    return 0;
}
