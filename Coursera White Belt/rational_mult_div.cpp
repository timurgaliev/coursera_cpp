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

// Вставьте сюда реализацию operator == для класса Rational из второй части
bool operator==(const Rational& rhd, const Rational& lhd){
    if (rhd.Numerator() == lhd.Numerator() && rhd.Denominator() == lhd.Denominator()){
        return true;
    }
    else{
        return false;
    }
}

// Реализуйте для класса Rational операторы * и /
Rational operator*(const Rational& lhd, const Rational& rhd){
    int den = lhd.Denominator() * rhd.Denominator();
    int num = lhd.Numerator() * rhd.Numerator();
    Rational c(num, den);
    return c;
}

Rational operator/(const Rational& lhd, const Rational& rhd){
    int num = lhd.Numerator() * rhd.Denominator();
    int den = lhd.Denominator() * rhd.Numerator();
    Rational c(num, den);
    return c;
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
