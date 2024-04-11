#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;

class Command
{
public:
    virtual void execute() = 0;
};

class ConcreteCommand1 : public Command
{
    std::string arg;
public:
    ConcreteCommand1(const std::string & a) : arg(a) {}
    void execute() override
    {
        cout<< "#1 process..."<<arg<<endl;
    }
};

class ConcreteCommand2 : public Command
{
    std::string arg;
public:
    ConcreteCommand2(const std::string & a) : arg(a) {}
    void execute() override
    {
        cout<< "#2 process..."<<arg<<endl;
    }
};
        
class MacroCommand : public Command
{
    std::vector<Command*> commands;
public:
    void addCommand(Command *c) { commands.push_back(c); }
    void execute() override
    {
        for (auto &c : commands)
        {
            c->execute();
        }
    }
};
            
int main()
{

    ConcreteCommand1 command1("Arg ###");
    ConcreteCommand2 command2("Arg $$$");
    
    //一系列命令组合
    MacroCommand macro;
    macro.addCommand(&command1);
    macro.addCommand(&command2);

    //执行命令
    macro.execute();

    return 0;
}
