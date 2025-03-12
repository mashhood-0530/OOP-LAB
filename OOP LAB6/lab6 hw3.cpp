#include <iostream>
#include <string>
#include<vector>
using namespace std;

class Student
{
    protected:
    string name;
    int id;
    public:
    Student(int i,string n):name(n),id(i){}
    void virtual display()
    {
        cout<<"Student name: "<<name<<endl;
        cout<<"Student id: "<<id<<endl;
    }
};
class Marks:public Student
{
    protected:
    double OOP;
    double DLD;
    double MVC;
    int subjectsize;
    public:
    Marks(string n,int i,double oop,double dld,double mvc):Student(i,n),OOP(oop),DLD(dld),MVC(mvc),subjectsize(3){}
    void virtual display()override
    {
        Student::display();
        cout<<"OOP marks: "<<OOP<<endl;
        cout<<"DLD marks: "<<DLD<<endl;
        cout<<"MVC marks: "<<MVC<<endl;
    } 
};
class Results:public Marks
{
    private:
    double total;
    double avg;
    public:
    Results(string n,int i,double oop,double dld,double mvc):Marks(n,i,oop,dld,mvc)
    {
        total=OOP+DLD+MVC;
        avg=total/subjectsize;
    }
    void display()override
    {
        Marks::display();
        cout<<"Total marks: "<<total<<endl;
        cout<<"Average marks: "<<avg<<endl;
    }
};
int main()
{
    vector<Results> students;
    students.push_back({"Ali Raza", 101, 85.5, 78.0, 90.0});
    students.push_back({"Mashood Riaz", 102, 92.0, 81.5, 88.5});
    students.push_back({"Rafay Ghouri", 103, 76.0, 84.5, 79.0});
    for (Results student : students)
    {
        cout << "------------------" << endl;
        student.display();
    }
    return 0;
}
