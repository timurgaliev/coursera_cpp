#include <iostream>
#include <exception>
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
        if( denominator == 0){
            throw invalid_argument("Denominator must not be 0");
        }
        if ( denominator < 0){
            num = numerator / -c;
            den = denominator / -c;
        }
        else{
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

// Вставьте сюда реализацию operator / для класса Rational

Rational operator/(const Rational& lhd, const Rational& rhd){
    if (rhd.Denominator() == 0){
        throw domain_error("Domain must not be 0");
    }
    int num = lhd.Numerator() * rhd.Denominator();
    int den = lhd.Denominator() * rhd.Numerator();
    Rational c(num, den);
    return c;
}


int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
