#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
    string s;
    cout<<"Enter a string: ";
    getline(cin,s);
    char* c=new char[s.length()];
    for(int i=1;i<=s.length();i++)
    {
        c[i-1]=s.at(i-1);
        c[i-1]+=i;
    }
    fstream file("Encrypted text.txt",ios::out);
    if(!file)
    {
        cout<<"File cannot be opened!";
        return 0;
    }
    cout<<"Encrypted text: ";
    for(int i=0;i<s.length();i++)
    {
        file<<c[i];
        cout<<c[i];
    }
    file.close();
    file.open("Encrypted text.txt",ios::in);
    cout<<endl;
    cout<<"Decrypted from file: ";
    char* decrypt=new char[s.length()];
    string dec;
    getline(file,dec);
    for(int i=0;i<s.length();i++)
    {
        decrypt[i]=dec.at(i);
        decrypt[i]-=(i+1);
        cout<<decrypt[i];
    }
    file.close();
    delete[] decrypt;
    delete[] c;
}