#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

// 数据库访问有关的基类
class IDBConnection
{
public:
    virtual void ConnectionString(const std::string &dbname) = 0;
};

class IDataReader
{
public:
    virtual bool Read() = 0;
};

class IDBCommand
{
public:
    virtual void CommandText(const std::string &command) = 0;
    virtual void SetConnection(IDBConnection *conn) = 0;
    virtual IDataReader *ExecuteReader() = 0;
};

// 一系列相关联的接口类组合在一起，形成抽象工厂
class IDBFactory
{
public:
    virtual IDBConnection *CreateDBConnection() = 0;
    virtual IDBCommand *CreateDBCommand() = 0;
    virtual IDataReader *CreateDataReader() = 0;
};

// 支持MySQL
class MySQLConnection : public IDBConnection
{
public:
    virtual void ConnectionString(const std::string &dbname){ 
        cout << "MySQL connected: " << dbname << endl; 
    };
};

class MySQLDataReader : public IDataReader
{
public:
    virtual bool Read() { 
        cout << "read MySQL Data" << endl;
        return false; 
    }
};

class MySQLCommand : public IDBCommand
{
public:
    virtual void CommandText(const std::string &command) { cout << "Set MySQL command: " << command << endl; }
    virtual void SetConnection(IDBConnection *conn) { cout << "Set MySQL conn" << endl; }
    virtual IDataReader *ExecuteReader() { 
        cout << "Get MySQL dataReader" << endl;
        return new MySQLDataReader(); 
    }
};

class MySQLFactory : public IDBFactory
{
public:
    IDBConnection *CreateDBConnection() override { return new MySQLConnection(); };
    IDBCommand *CreateDBCommand() override { return new MySQLCommand(); };
    IDataReader *CreateDataReader() override { return new MySQLDataReader(); };
};

// 支持Redis
class RedisConnection : public IDBConnection
{
public:
    virtual void ConnectionString(const std::string &dbname){};
};
class RedisDataReader : public IDataReader
{
public:
    virtual bool Read() { return false; }
};

class RedisCommand : public IDBCommand
{
public:
    virtual void CommandText(const std::string &command) {}
    virtual void SetConnection(IDBConnection *conn) {}
    virtual IDataReader *ExecuteReader() { return new RedisDataReader(); }
};

class RedisFactory : public IDBFactory
{
public:
    IDBConnection *CreateDBConnection() override { return new RedisConnection(); };
    IDBCommand *CreateDBCommand() override { return new RedisCommand(); };
    IDataReader *CreateDataReader() override { return new RedisDataReader(); };
};

class EmployeeDAO
{
public:
    EmployeeDAO(IDBFactory *factory) : dbFactory(factory) {}
    void GetEmployees()
    {
        IDBConnection *connection = dbFactory->CreateDBConnection();
        connection->ConnectionString("employee");

        IDBCommand *command = dbFactory->CreateDBCommand();
        command->CommandText("select * from name");
        command->SetConnection(connection); // 关联性

        IDataReader *reader = command->ExecuteReader(); // 关联性
        while (reader->Read())
        {
        }
    }

private:
    IDBFactory *dbFactory;
};

int main()
{
    IDBFactory *dbFactory = new MySQLFactory();
    EmployeeDAO dao(dbFactory);
    dao.GetEmployees();

    return 0;
}