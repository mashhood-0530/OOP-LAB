#include<iostream>
#include<string>
using namespace std;
class Currency
{
    protected:
    double amount;
    int currencycode;
    string symbol;
    double erate;
    public:
    Currency(double amt,int curcode,string symb,double e):amount(amt),currencycode(curcode),symbol(symb),erate(e){}
    double converttobase()
    {
        return amount*erate;
    }
    virtual double converttoX(string X)
    {
        double baseValue = converttobase();
        double targetRate = 1.0;  

        if (X == "USD") targetRate = 1.0;
        else if (X == "EUR") targetRate = 1.1;
        else if (X == "INR") targetRate = 0.012;
        else
        {
            cout << "Error: Exchange rate for " << X << " not found." << endl;
            return -1;
        }
        return baseValue / targetRate;
    }
    virtual void displaycurrency()
    {
        cout<<amount;
    }
};
class Dollar:public Currency
{
    public:
    Dollar(double amt,int curcode,string symb,double e):Currency(amt,curcode,symb,e){}
    double converttoX(string X)override
    {
        double baseValue = converttobase();
        double targetRate = 1.0;  

        if (X == "EUR") targetRate = 1.1;
        else if (X == "INR") targetRate = 0.012;
        else
        {
            cout << "Error: Exchange rate for " << X << " not found." << endl;
            return -1;
        }
        return baseValue / targetRate;
    }
    void displaycurrency() override
    {
        cout<<"Dollars: "<<symbol<<amount;
    }  
};
class Euro:public Currency
{
    public:
    Euro(double amt,int curcode,string symb,double e):Currency(amt,curcode,symb,e){}
    double converttoX(string X)override
    {
        double baseValue = converttobase();
        double targetRate = 1.0;  

        if (X == "USD") targetRate = 1.0;
        else if (X == "INR") targetRate = 0.012;
        else
        {
            cout << "Error: Exchange rate for " << X << " not found." << endl;
            return -1;
        }
        return baseValue / targetRate;
    }
    void displaycurrency() override
    {
        cout<<"Euros: "<<symbol<<amount;
    }  
};
class PKR:public Currency
{
    public:
    PKR(double amt,int curcode,string symb,double e):Currency(amt,curcode,symb,e){}
    virtual double converttoX(string X)
    {
        double baseValue = converttobase();
        double targetRate = 1.0;  

        if (X == "USD") targetRate = 1.0;
        else if (X == "EUR") targetRate = 1.1;
        else
        {
            cout << "Error: Exchange rate for " << X << " not found." << endl;
            return -1;
        }
        return baseValue / targetRate;
    }
    virtual void displaycurrency()
    {
        cout<<"Rupees: "<<symbol<<amount;
    }
};
int main() {
    Dollar usd(100, 1, "$", 1.0);
    Euro eur(100, 2, "E", 1.1);
    PKR pkr(10000, 3, "Rs", 0.0058);

    cout << "Original Currencies:\n";
    usd.displaycurrency();
    cout << endl;
    eur.displaycurrency();
    cout << endl;
    pkr.displaycurrency();
    cout << endl << endl;

    cout << "Conversions:\n";
    cout << "100 USD to EUR: " << usd.converttoX("EUR") << " EUR\n";
    cout << "100 USD to INR: " << usd.converttoX("INR") << " INR\n";
    cout << "100 EUR to USD: " << eur.converttoX("USD") << " USD\n";
    cout << "100 EUR to INR: " << eur.converttoX("INR") << " INR\n";
    cout << "10000 PKR to USD: " << pkr.converttoX("USD") << " USD\n";
    cout << "10000 PKR to EUR: " << pkr.converttoX("EUR") << " EUR\n";

    return 0;
}