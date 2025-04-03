#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInteger
{
private:
    vector<int> digits;
    bool isNegative;
    void removeLeadingZeros()
    {
        while (digits.size() > 1 && digits.back() == 0)
        {
            digits.pop_back();
        }
    }

public:
    BigInteger() : isNegative(false) {}

    BigInteger(const string &str)
    {
        isNegative = (str[0] == '-');
        int start = (isNegative ? 1 : 0);

        for (int i = str.size() - 1; i >= start; --i)
        {
            digits.push_back(str[i] - '0');
        }

        removeLeadingZeros();
    }
    BigInteger operator+(const BigInteger &other) const
    {
        if (isNegative && !other.isNegative)
        {
            return other - (-(*this));
        }
        if (!isNegative && other.isNegative)
        {
            return *this - (-other);
        }

        BigInteger result;
        result.isNegative = isNegative;
        int carry = 0;
        int maxSize = (digits.size() > other.digits.size()) ? digits.size() : other.digits.size();

        for (int i = 0; i < maxSize || carry; ++i)
        {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];

            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }

        result.removeLeadingZeros();
        return result;
    }
    BigInteger operator-(const BigInteger &other) const
    {
        if (isNegative && !other.isNegative)
        {
            return -(-(*this) + other);
        }
        if (!isNegative && other.isNegative)
        {
            return *this + (-other);
        }
        if (*this < other)
        {
            return -(other - *this);
        }

        BigInteger result;
        result.isNegative = isNegative;
        int borrow = 0;

        for (int i = 0; i < digits.size(); ++i)
        {
            int sub = digits[i] - borrow;
            if (i < other.digits.size()) sub -= other.digits[i];

            if (sub < 0)
            {
                sub += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            result.digits.push_back(sub);
        }

        result.removeLeadingZeros();
        return result;
    }
    BigInteger operator*(const BigInteger &other) const
    {
        BigInteger result;
        result.digits.resize(digits.size() + other.digits.size(), 0);
        result.isNegative = isNegative != other.isNegative;

        for (int i = 0; i < digits.size(); ++i)
        {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; ++j)
            {
                long long prod = result.digits[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = prod % 10;
                carry = prod / 10;
            }
        }

        result.removeLeadingZeros();
        return result;
    }
    bool operator==(const BigInteger &other) const
    {
        return isNegative == other.isNegative && digits == other.digits;
    }
    bool operator!=(const BigInteger &other) const
    {
        return !(*this == other);
    }
    bool operator<(const BigInteger &other) const
    {
        if (isNegative != other.isNegative)
        {
            return isNegative;
        }

        if (digits.size() != other.digits.size())
        {
            return (digits.size() < other.digits.size()) != isNegative;
        }

        for (int i = digits.size() - 1; i >= 0; --i)
        {
            if (digits[i] != other.digits[i])
            {
                return (digits[i] < other.digits[i]) != isNegative;
            }
        }

        return false;
    }
    bool operator>(const BigInteger &other) const
    {
        return other < *this;
    }
    friend istream &operator>>(istream &is, BigInteger &num)
    {
        string str;
        is >> str;
        num = BigInteger(str);
        return is;
    }
    friend ostream &operator<<(ostream &os, const BigInteger &num)
    {
        if (num.isNegative)
        {
            os << "-";
        }

        for (int i = num.digits.size() - 1; i >= 0; --i)
        {
            os << num.digits[i];
        }

        return os;
    }
    BigInteger operator-() const
    {
        BigInteger neg = *this;
        neg.isNegative = !isNegative;
        return neg;
    }
};

int main()
{
    BigInteger num1, num2;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    cout << "Sum: " << num1 + num2 << endl;
    cout << "Difference: " << num1 - num2 << endl;
    cout << "Product: " << num1 * num2 << endl;

    return 0;
}
