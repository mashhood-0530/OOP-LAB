#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class PolynomialUtils;

class Polynomial
{
private:
    vector<int> coeffs;

public:
    Polynomial() {}

    Polynomial(const vector<int>& coefficients) : coeffs(coefficients)
    {
        while (coeffs.size() > 1 && coeffs.back() == 0)
        {
            coeffs.pop_back();
        }
    }

    vector<int> getCoeffs() const
    {
        return coeffs;
    }

    Polynomial operator+(const Polynomial& other) const
    {
        int maxSize = max(coeffs.size(), other.coeffs.size());
        vector<int> result(maxSize, 0);

        for (int i = 0; i < coeffs.size(); ++i)
        {
            result[i] += coeffs[i];
        }

        for (int i = 0; i < other.coeffs.size(); ++i)
        {
            result[i] += other.coeffs[i];
        }

        return Polynomial(result);
    }

    Polynomial operator-(const Polynomial& other) const
    {
        int maxSize = max(coeffs.size(), other.coeffs.size());
        vector<int> result(maxSize, 0);

        for (int i = 0; i < coeffs.size(); ++i)
        {
            result[i] += coeffs[i];
        }

        for (int i = 0; i < other.coeffs.size(); ++i)
        {
            result[i] -= other.coeffs[i];
        }

        return Polynomial(result);
    }

    Polynomial operator*(const Polynomial& other) const
    {
        int newSize = coeffs.size() + other.coeffs.size() - 1;
        vector<int> result(newSize, 0);

        for (int i = 0; i < coeffs.size(); ++i)
        {
            for (int j = 0; j < other.coeffs.size(); ++j)
            {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }

        return Polynomial(result);
    }

    friend ostream& operator<<(ostream& os, const Polynomial& p)
    {
        bool first = true;
        for (int i = p.coeffs.size() - 1; i >= 0; --i)
        {
            if (p.coeffs[i] != 0)
            {
                if (!first && p.coeffs[i] > 0)
                {
                    os << " + ";
                }
                if (p.coeffs[i] < 0)
                {
                    os << " - ";
                }
                if (abs(p.coeffs[i]) != 1 || i == 0)
                {
                    os << abs(p.coeffs[i]);
                }
                if (i > 0)
                {
                    os << "x";
                }
                if (i > 1)
                {
                    os << "^" << i;
                }
                first = false;
            }
        }
        if (first)
        {
            os << "0";
        }
        return os;
    }
};

class PolynomialUtils
{
public:
    static int evaluate(const Polynomial& p, int x)
    {
        vector<int> coeffs = p.getCoeffs();
        int result = 0;
        int power = 1;
        for (int i = 0; i < coeffs.size(); ++i)
        {
            result += coeffs[i] * power;
            power *= x;
        }
        return result;
    }

    static Polynomial derivative(const Polynomial& p)
    {
        vector<int> coeffs = p.getCoeffs();
        vector<int> result;
        for (int i = 1; i < coeffs.size(); ++i)
        {
            result.push_back(coeffs[i] * i);
        }
        return Polynomial(result);
    }
};

int main()
{
    Polynomial p1({1, -3, 2}); // 2x^2 - 3x + 1
    Polynomial p2({0, 1, 4});  // 4x^2 + x

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    cout << "Sum: " << sum << endl;

    Polynomial difference = p1 - p2;
    cout << "Difference: " << difference << endl;

    Polynomial product = p1 * p2;
    cout << "Product: " << product << endl;

    cout << "Evaluation of Polynomial 1 at x = 2: " << PolynomialUtils::evaluate(p1, 2) << endl;

    Polynomial derivative = PolynomialUtils::derivative(p1);
    cout << "Derivative of Polynomial 1: " << derivative << endl;

    return 0;
}