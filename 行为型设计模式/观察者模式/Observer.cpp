#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

// 进度通知接口
class IProgress
{
public:
    virtual void DoProgress(float value) = 0;
    virtual ~IProgress() {}
};

// 大文件分割类
class FileSplitter
{
    std::string m_filePath;
    int m_fileNumber;

    std::vector<IProgress*> m_list; // 抽象通知机制，支持多个观察者

public:
    FileSplitter(const std::string &filePath, int fileNumber)
        : m_filePath(filePath), m_fileNumber(fileNumber)
    {
    }

    // 具体实现
    void split()
    {
        // 1.读取大文件
        //...
        // 2.分批次向小文件中写入
        for (int i = 0; i < m_fileNumber; i++)
        {
            //...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            onProgress(progressValue); // 发送通知
        }
    }

    void addIProgress(IProgress *iprogress)
    {
        cout << std::hex << "add observer:: " << std::showbase << iprogress << '\n';
        m_list.emplace_back(iprogress);
    }

    void removeIProgress(IProgress *iprogress)
    {
        auto is_found = [&](IProgress *iter) { return iprogress == iter; };
        if (auto it = std::find_if(begin(m_list), end(m_list), is_found); it != std::end(m_list))
        {
            cout << std::hex << "remove observer:: " << std::showbase << *it << '\n';
            m_list.erase(it);
        }
    }

protected:
    virtual void onProgress(float value)
    {
        for (const auto &iter : m_list)
        {
            iter->DoProgress(value); // 更新进度条
        }
    }
};

// 窗口基类
class Form
{
public:
    virtual ~Form(){};
};

// 文体控件
class TextBox
{
public:
    TextBox(const std::string &txt)
        : m_text(txt)
    {
    }
    std::string getText()
    {
        return m_text;
    }
    virtual ~TextBox(){};

private:
    std::string m_text;
};

// 滚动条控件
class ProgressBar
{
public:
    void setValue(int value)
    {
        m_value = value;
    }
    virtual ~ProgressBar(){};

private:
    int m_value = 0;
};

class ConsoleNotifier : public IProgress
{
public:
    void DoProgress(float value) override
    {
        cout << "Console Get value from splitter:  " << value << endl;
    }
};

// MainForm 继承IProgress接口
class MainForm : public Form, public IProgress
{
public:
    MainForm()
    {
        txtFilePath = new TextBox("file.iso");
        txtFileNumber = new TextBox("4");
        progressBar = new ProgressBar();
    }
    ~MainForm()
    {
        delete txtFilePath;
        delete txtFileNumber;
        delete progressBar;
    }

    void Button1_Click()
    {
        std::string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        ConsoleNotifier console;

        FileSplitter splitter(filePath, number);
        splitter.addIProgress(this);     // 观察者订阅通知
        splitter.addIProgress(&console); // 观察者订阅通知

        splitter.split();
        splitter.removeIProgress(this);
        splitter.split();
    }

private:
    // 实现 IProgress的接口
    void DoProgress(float value) override
    {
        cout << "MainForm Get value frome splitter: " << value << endl;
        progressBar->setValue(value);
    }

private:
    TextBox *txtFilePath = nullptr;   // 文件路径
    TextBox *txtFileNumber = nullptr; // 分割文件数量
    ProgressBar *progressBar = nullptr;
};

int main()
{
    MainForm main;
    main.Button1_Click();
    return 0;
}