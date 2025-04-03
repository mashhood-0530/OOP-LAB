#include<iostream>
using namespace std;
class fraction
{
    int num,den;
    int gcd(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    public:
    fraction(){}
    fraction(int n,int d):num(n),den(d)
    {
        if(den==0)
        {
            cout<<"Cant proceed with the program because denominator is zero!"<<endl;
            return;
        }
        int div=gcd(n,d);
        num/=div;
        den/=div;
        if(den<0)
        {
            den*=-1;
            num*=-1;
        }
    }
    fraction operator+(const fraction &f)const
    {
        return fraction(num*f.den+f.num*den,den*f.den);
    }
    fraction operator-(const fraction &f)const
    {
        return fraction(num*f.den-f.num*den,den*f.den);
    }
    fraction operator/(const fraction &f)const
    {
        return fraction(num*f.den,den*f.num);
    }
    fraction operator*(const fraction &f)const
    {
        return fraction(num*f.num,den*f.den);
    }
    bool operator==(const fraction &f)const
    {
        return num*f.den == f.num*den;
    }
    bool operator>=(const fraction &f)const
    {
        return num*f.den >= f.num*den;
    }
    bool operator!=(const fraction &f)const
    {
        return num*f.den != f.num*den;
    }
    bool operator<=(const fraction &f)const
    {
        return num*f.den <= f.num*den;
    }
    bool operator>(const fraction &f)const
    {
        return num*f.den > f.num*den;
    }
    bool operator<(const fraction &f)const
    {
        return num*f.den < f.num*den;
    }
    friend ostream& operator<<(ostream& os,const fraction &f)
    {
        os<<f.num<<"/"<<f.den;
        return os;
    }
    friend istream& operator>>(istream& is,fraction &f)
    {
        cout<<"numerator: ";
        is>>f.num;
        cout<<"denominator: ";
        is>>f.den;
        return is;
    }
};
int main()
{
    int num1, den1, num2, den2;
    cin >> num1 >> den1 >> num2 >> den2;
        fraction frac1(num1, den1), frac2(num2, den2);
        cout <<frac1<<" + "<<frac2<<"= "<< (frac1 + frac2) << endl;
        cout <<frac1<<" - "<<frac2<<"= " <<(frac1 - frac2) << endl;
        cout <<frac1<<" x "<<frac2<<"= " <<(frac1 * frac2) << endl;
        cout <<frac1<<" / "<<frac2<<"= " <<(frac1 / frac2) << endl;
        
        cout << "Equal: " << (frac1 == frac2) << endl;
        cout << "Not Equal: " << (frac1 != frac2) << endl;
        cout << "Less Than: " << (frac1 < frac2) << endl;
        cout << "Greater Than: " << (frac1 > frac2) << endl;
        cout << "Less Than or Equal: " << (frac1 <= frac2) << endl;
        cout << "Greater Than or Equal: " << (frac1 >= frac2) << endl;
    return 0;
}