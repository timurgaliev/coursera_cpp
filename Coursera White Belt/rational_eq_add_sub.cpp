#include <iostream>
#include <algorithm>
using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        num = 0;
        den = 1;

    }
    Rational(int numerator, int denominator) {
        int c = __gcd(abs(numerator), abs(denominator));
        if ( denominator < 0 && numerator >= 0){
            num = numerator / -c;
            den = denominator / -c;
        }
        else if (denominator < 0 && numerator < 0){
            num = numerator / -c;
            den = denominator / -c;

        }else{
            num = numerator / c;
            den = denominator / c;
        }
        
    }

    int Numerator() const {
        // Реализуйте этот метод
        return num;
        
    }

    int Denominator() const {
        // Реализуйте этот метод
        return den;
    }

private:
    // Добавьте поля
    int num;
    int den;
};


// Реализуйте для класса Rational операторы ==, + и -
bool operator==(const Rational& rhd, const Rational& lhd){
    if (rhd.Numerator() == lhd.Numerator() && rhd.Denominator() == lhd.Denominator()){
        return true;
    }
    else{
        return false;
    }
}

Rational operator+(const Rational& rhd, const Rational& lhd){
    int den = rhd.Denominator() * lhd.Denominator();
    int num1 = lhd.Numerator() * rhd.Denominator();
    int num2 = rhd.Numerator()*lhd.Denominator();
    int num = num1 + num2;
    Rational c(num ,den);
    return c;
}


Rational operator-(const Rational& lhd, const Rational rhd){
    int den = rhd.Denominator() * lhd.Denominator();
    int num1 = lhd.Numerator() * rhd.Denominator();
    int num2 = rhd.Numerator() * lhd.Denominator();
    int num = num1 - num2;
    Rational c(num, den);
    return c;
}




int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
