#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

class Colleague;
class Mediator
{
public:
    // 对象在自身改变的情况下，通知Mediator进行变更
    // 由Mediator这个总线，负责相应的同事对象的交互
    virtual void changed(Colleague *pColleague) = 0;

protected:
    Mediator(){};
};

class Colleague
{
public:
    Colleague(Mediator *pMediator) : m_pMediator(pMediator) {}
    virtual ~Colleague() {};
    Mediator *getMediator()
    {
        return m_pMediator;
    }
    virtual std::string type() = 0;
private:
    Mediator *m_pMediator;
};

class SoundCard : public Colleague
{
public:
    // 模拟声卡的工作
    SoundCard(Mediator *pMediator) : Colleague(pMediator) {}
    std::string type() { return "SoundCard"; }
    void soundData(std::string data)
    {
        //cout << "声卡在工作" << data << endl;
        cout << "SoundCard: " << data << endl;
    }
};

class VideoCard : public Colleague
{
public:
    VideoCard(Mediator *pMediator) : Colleague(pMediator) {}
    std::string type() { return "VideoCard"; }
    void videoData(std::string data)
    {
        //cout << "显卡在工作" << data << endl;
        cout << "VideoCard: " << data << endl;
    }
};

class CPU : public Colleague
{
public:
    CPU(Mediator *pMediator) : Colleague(pMediator) {}
    std::string type() { return "CPU"; }

    void executeData(std::string data[])
    {
        m_strVideoData = data[0];
        m_strSoundData = data[1];
        this->getMediator()->changed(this);
    }
    std::string getVideoData()
    {
        return m_strVideoData;
    }
    std::string getSoundData()
    {
        return m_strSoundData;
    }

private:
    std::string m_strVideoData;
    std::string m_strSoundData;
};

class MotherBoard : public Mediator
{
public:
    void changed(Colleague *pColleague)
    {
        if (pColleague->type() == "CPU")
        {
            this->openCPU((CPU *)pColleague);
        }
    }

    void SetColleague(Colleague* pColleague)
    {
        if(auto iter = std::find(begin(m_vColleague), end(m_vColleague), pColleague); iter == m_vColleague.end())
        {
            m_vColleague.emplace_back(pColleague);
        }
    }

private:
    void openCPU(CPU *pCPU)
    {
        // 主板开始进行各个部件的运行，首先调用CPU，将处理好的数据得到
        std::string strVideoData = pCPU->getVideoData();
        std::string strSoundData = pCPU->getSoundData();

        // 将这些处理好的数据交付给SoundCard, VideoCard，让他们工作
        for(const auto& iter : m_vColleague)
        {
            if(iter->type() == "VideoCard")
            {
                ((VideoCard*)iter)->videoData(strVideoData);
            }

            if(iter->type() == "SoundCard")
            {
                ((SoundCard*)iter)->soundData(strSoundData);
            }
        }
    }

private:
    std::vector<Colleague*> m_vColleague;
};

int main()
{
    // 创建Mediator
    MotherBoard *pMediator = new MotherBoard;

    // 创建同事类的对象
    CPU *pCPU = new CPU(pMediator);
    VideoCard *pVC = new VideoCard(pMediator);
    SoundCard *pSC = new SoundCard(pMediator);

    // 让Mediator都知道这些Colleague的对象
    pMediator->SetColleague(pCPU);
    pMediator->SetColleague(pVC);
    pMediator->SetColleague(pSC);

    // 让我们的数据运行起来
    std::string arr[] = {"Video Data", "Audio Data"};
    pCPU->executeData(arr); // 看上去，好像CPU就在做自己的事情

    //system("pause");

    return 0;
}
