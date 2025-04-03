#include<iostream>
using namespace std;
class shape
{
    protected:
    double area;
    public:
    shape(double a):area(a){}
    shape operator+(const shape& s)const
    {
        return shape(area+s.area);   
    }
    void display()
    {
        cout<<"Area: "<<area<<endl;
    }
};
class circle:public shape
{
    double rad;
    public:
    circle(double r):shape(3.14*r*r),rad(r){}
};
class rectangle:public shape
{
    double length,width;
    public:
    rectangle(double l,double w):shape(l*w),length(l),width(w){}
};
int main()
{
    circle cir(11.5);
    rectangle rect(5.678,2.6667);
    shape total=cir+rect;
    total.display();
}