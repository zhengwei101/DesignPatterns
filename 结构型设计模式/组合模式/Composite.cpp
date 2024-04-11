#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;

class Component
{
public:
    virtual void process() = 0;
    virtual ~Component() {}
};

// 树节点
class Composite : public Component
{
    std::string name;
    std::list<Component *> elements;

public:
    Composite(const std::string &s) : name(s) {}

    void add(Component *element)
    {
        elements.push_back(element);
    }
    void remove(Component *element)
    {
        elements.remove(element);
    }

    void process()
    {
        // 1. process current node
        cout << "this is a tree node: " << name << " ,size: " << elements.size() << endl;
        
        // 2. process leaf nodes
        for (auto &e : elements)
        {
            e->process(); // 这里有多态的递归调用
        }
    }
};

// 叶子节点
class Leaf : public Component
{
    std::string name;
public:
    Leaf(std::string s) : name(s) {}

    void process()
    {
        // process current node
        cout << "this is a leaf node: " << name << endl;
    }
};

void Invoke(Component &c)
{
    //...
    c.process();
    //...
}

int main()
{
    Composite root("root"); //根节点
    Composite treeNode1("treeNode1"); //树节点
    Composite treeNode2("treeNode2"); //树节点
    Composite treeNode3("treeNode3"); //树节点
    Composite treeNode4("treeNode4"); //树节点
    Leaf leaf1("left1"); //叶子节点
    Leaf leaf2("left2"); //叶子节点

    root.add(&treeNode1);
    treeNode1.add(&treeNode2);
    treeNode2.add(&leaf1);

    root.add(&treeNode3);
    treeNode3.add(&treeNode4);
    treeNode4.add(&leaf2);

    Invoke(root);
    cout << "-------------------------" << endl;
    Invoke(leaf2);
    cout << "-------------------------" << endl;
    Invoke(treeNode3);

    return 0;
}
