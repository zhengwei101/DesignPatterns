
class NetworkState
{
public:
    NetworkState* pNext = nullptr;
    virtual ~NetworkState(){};
    virtual void GetState() = 0;
    virtual NetworkState*  Operation1() = 0;
    virtual NetworkState*  Operation2() = 0;
};

class OpenState : public NetworkState
{
public:
    static NetworkState* getInstance();
    void GetState() override;
    NetworkState*  Operation1() override;
    NetworkState*  Operation2() override;
};

class CloseState : public NetworkState
{
public:
    static NetworkState* getInstance();
    void GetState() override;
    NetworkState*  Operation1() override;
    NetworkState*  Operation2() override;
};

class ConnectState : public NetworkState
{
public:
    static NetworkState* getInstance();
    void GetState() override;
    NetworkState*  Operation1() override;
    NetworkState*  Operation2() override;
};
