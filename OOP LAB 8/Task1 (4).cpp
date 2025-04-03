#include<iostream>
using namespace std;
class magic
{
    int n;
    public:
    magic(int a):n(a){}
    magic operator--()
    {
        n*=4;  
    }
    magic operator--(int)
    {
        n/=4;
    }
    void display()
    {
        static int a=1;
        a++;
        cout<<n;
        if(a<=3)
        cout<<" - ";
    }
};
int main()
{
    magic m(4);
    m.display();
    m--;
    m.display();
    --m;
    m.display();
}