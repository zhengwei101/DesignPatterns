#include <iostream>

using std::cout;
using std::endl;

/*********************************************************/
//不好的实现
/*
enum NetworkState { Network_Open, Network_Close, Network_Connect};
class NetworkProcessor
{
    NetworkState state;
public:
    void Operation1(){
        if (state == Network_Open){
            //...
            state = Network_Close;
        }
        else if (state == Network_Close){
            //...
            state = Network_Connect;
        }
        else if (state == Network_Connect){
            //...
            state = Network_Open;
        }
    }

    void Operation2(){
        if (state == Network_Open){
            //...
            state = Network_Connect;
        }
        else if (state == Network_Close){
            //...
            state = Network_Open;
        }
        else if (state == Network_Connect){
            //...
            state = Network_Close;
        }
    }
    //新增状态操作
    void Operation3(){
        //...
    }
};
*/
/*********************************************************/
//使用State模式改造如下：
#include "State.h"

NetworkState* OpenState::getInstance()
{
    static OpenState ins;
    return &ins;
}
void OpenState::GetState()
{
    cout << "This is Open State" << endl;
}
NetworkState*  OpenState::Operation1()
{
    pNext = CloseState::getInstance();
    return pNext;
}
NetworkState*  OpenState::Operation2()
{
    pNext = ConnectState::getInstance();
    return pNext;
}

NetworkState* CloseState::getInstance()
{
    static CloseState ins;
    return &ins;
}
void CloseState::GetState()
{
    cout << "This is Close State" << endl;
}
NetworkState*  CloseState::Operation1()
{
    pNext = CloseState::getInstance();
    return pNext;
}
NetworkState*  CloseState::Operation2()
{
    pNext = ConnectState::getInstance();
    return pNext;
}

NetworkState* ConnectState::getInstance()
{
    static ConnectState ins;
    return &ins;
}
void ConnectState::GetState()
{
    cout << "This is Connect State" << endl;
}
NetworkState* ConnectState::Operation1()
{
    pNext = CloseState::getInstance();
    return pNext;
}
NetworkState*  ConnectState::Operation2()
{
    pNext = ConnectState::getInstance();
    return pNext;
}

//具体使用类
class NetworkProcessor
{
    NetworkState* pState = nullptr;
public:
    NetworkProcessor(NetworkState* s) : pState(s) {}
    void Operation1()
    {
        //...
        pState = pState->Operation1();
        pState->GetState();
        //...
    }
    void Operation2()
    {
        //...
        pState = pState->Operation2();
        pState->GetState();
        //...
    }
};

int main()
{
    NetworkState* pState = OpenState::getInstance();
    pState->GetState();

    NetworkProcessor processor(pState);
    processor.Operation1();
    processor.Operation2();

    return 0;
}