#include<iostream>
using namespace std;
class Person
{
    protected:
    int eid;
    public:
    Person(int id):eid(id){}
    int getdata(){return eid;}
    virtual void displaydata(){cout<<"Employee Id: "<<eid<<endl;}
};
class Admin:public Person
{
    double income;
    string name;
    public:
    Admin(int e,double i,string n):Person(e),income(i),name(n){}
    void bonus()
    {
        income*=0.05;
        cout<<"Incremented the salary!"<<endl;
    }
    void displaydata()override
    {
        cout<<"Name: "<<name<<endl;
        Person::displaydata();
        cout<<"Monthly income: "<<income<<endl;
    }
    double getincome()
    {
        return income;
    }
    string getname()
    {
        return name;
    }
};
class Accounts:public Person
{
    double income;
    string name;
    public:
    Accounts(int e,double i,string n):Person(e),income(i),name(n){}
    void bonus()
    {
        income*=0.05;
        cout<<"Incremented the salary!"<<endl;
    }
    void displaydata()override
    {
        cout<<"Name: "<<name<<endl;
        Person::displaydata();
        cout<<"Monthly income: "<<income<<endl;
    }
    double getincome()
    {
        return income;
    }
    string getname()
    {
        return name;
    }
};
int main()
{
    Admin adm(1,10000,"Ali Raza");
    Accounts acc(2,20000,"Rafay Ghouri");
    adm.displaydata();
    cout<<endl;
    acc.displaydata();
    adm.bonus();
    acc.bonus();
}