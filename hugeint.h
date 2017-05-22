#include <iostream>
#include <string>
#include <vector>
#include <list>

class HugeInt
{
public:
    HugeInt();
    HugeInt(const HugeInt &n);
    HugeInt(std::string str);
    HugeInt(int n);
    ~HugeInt();

    friend std::ostream&  operator<<(std::ostream &out, HugeInt   n);
    friend std::istream&  operator>>(std::istream  &in, HugeInt  &n);
    friend HugeInt operator+(HugeInt lhs, HugeInt rhs);
    friend HugeInt operator-(HugeInt lhs, HugeInt rhs);
    HugeInt& operator=(HugeInt rhs);


private:
    std::vector<int> number;
    void constructFromString(const std::string &str);

    static HugeInt& add(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
    static HugeInt& sub(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
};


HugeInt::HugeInt()
{
    number.push_back(0);
}

HugeInt::HugeInt(const HugeInt &n)
{
    number = n.number;
}

HugeInt::HugeInt(std::string str)
{
    constructFromString(str);
}

void HugeInt::constructFromString(const std::string &str)
{
    number.clear();
    for(int i=str.size()-1;i>=0;--i)
        number.push_back(str[i]-'0');
}

HugeInt::HugeInt(int n)
{
    while(n)
    {
        number.push_back(n%10);
        n /= 10;
    }
}

HugeInt::~HugeInt()
{
}

std::ostream& operator<<(std::ostream &out, HugeInt  n)
{
    for(int i=n.number.size()-1;i>=0;--i)
        out << n.number[i];
    return out;
}

std::istream& operator>>(std::istream &in, HugeInt &n)
{
    std::string str;
    in >> str;
    n.constructFromString(str);
    return in;
}

HugeInt operator+(HugeInt lhs, HugeInt rhs)
{
    return HugeInt::add(lhs, rhs);
}

HugeInt operator-(HugeInt lhs, HugeInt rhs)
{
    return HugeInt::sub(lhs, rhs);
}

HugeInt& HugeInt::operator=(HugeInt rhs)
{
    this->number = rhs.number;
    return *this;
}

HugeInt& HugeInt::add(HugeInt &lhs, const HugeInt &rhs)
{
    lhs.number.resize(std::max(lhs.number.size(), rhs.number.size()));
    for(int i=0;i<rhs.number.size();++i)
        lhs.number[i] += rhs.number[i];
    for(int i=1;i<lhs.number.size();++i)
    {
        if(lhs.number[i-1] >= 10)
        {
            lhs.number[i-1] -= 10;
            ++ lhs.number[i];
        }
    }
    if(lhs.number.back() >= 10)
    {
        lhs.number.back() -= 10;
        lhs.number.push_back(1);
    }
    return lhs;
}

HugeInt& HugeInt::sub(HugeInt &lhs, const HugeInt &rhs)
{
    lhs.number.resize(std::max(lhs.number.size(), rhs.number.size()));
    for(int i=0;i<rhs.number.size();++i)
        lhs.number[i] -= rhs.number[i];
    for(int i=0, end = lhs.number.size()-1 ; i<end ;++i)
    {
        if(lhs.number[i] < 0)
        {
            lhs.number[i] += 10;
            -- lhs.number[i+1];
        }
    }
    if(lhs.number.back() == 0)
        lhs.number.pop_back();
    return lhs;
}
