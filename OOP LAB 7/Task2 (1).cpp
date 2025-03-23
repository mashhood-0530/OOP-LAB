#include<iostream>
#include<string>
using namespace std;
class Shape
{
    protected:
    string color;
    double x;
    double y;
    double border;
    public:
    Shape(string c,double a,double b,double bord):color(c),x(a),y(b),border(bord){}
    virtual void draw()=0;
    virtual double calculateArea()=0;
    virtual double calculatePerimeter()=0;
};
class Circle:public Shape
{
    double radius;
    public:
    Circle(string c,double a,double b,double bord,double rad):Shape(c,a,b,bord),radius(rad){}
    void draw() override
    {
        cout<<"Drawing cirlce of color "<<color<<" at:("<<x<<","<<y<<")"<<endl;
    }
    double calculateArea() override
    {
        return 3.14*radius*radius;
    }
    double calculatePerimeter() override
    {
        return 2*3.14*radius;
    }
};
class Rectangle:public Shape
{
    double length;
    double width;
    public:
    Rectangle(string c,double a,double b,double bord,double w,double l):Shape(c,a,b,bord),width(w),length(l){}
    void draw() override
    {
        cout<<"Drawing rectangle of color "<<color<<" at:("<<x<<","<<y<<")"<<endl;
    }
    double calculateArea() override
    {
        return length*width;
    }
    double calculatePerimeter() override
    {
        return 2*length+2*width;
    } 
};
int main()
{
    Shape* shape=new Circle("Red",1.5,2.2,0.5,2);
    cout<<"Circle:"<<endl;
    shape->draw();
    cout<<shape->calculateArea()<<endl;
    cout<<shape->calculatePerimeter()<<endl;
    delete shape;
    shape=new Rectangle("Blue",1,2,0.6,2,3);
    cout<<"Rectangle:"<<endl;
    shape->draw();
    cout<<shape->calculateArea()<<endl;
    cout<<shape->calculatePerimeter()<<endl;
    delete shape;
}