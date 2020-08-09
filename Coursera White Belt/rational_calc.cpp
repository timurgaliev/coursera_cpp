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
    	if (denominator == 0){
    	    		throw invalid_argument("gg");
    	    	}
        int c = __gcd(abs(numerator), abs(denominator));
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

// Вставьте сюда реализацию operator /, * ,+ ,-  для класса Rational

Rational operator/(const Rational& lhd, const Rational& rhd){
    if (rhd.Numerator() == 0){
        throw domain_error("Domain must not be 0");
    }
    int num = lhd.Numerator() * rhd.Denominator();
    int den = lhd.Denominator() * rhd.Numerator();
    Rational c(num, den);
    return c;
}

Rational operator*(const Rational& lhd, const Rational& rhd){
    int den = lhd.Denominator() * rhd.Denominator();
    int num = lhd.Numerator() * rhd.Numerator();
    Rational c(num, den);
    return c;
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

// Реализуйте для класса Rational операторы << и >>
ostream& operator<<(ostream& stream, const Rational& rational){
    stream << to_string(rational.Numerator()) << "/" << to_string(rational.Denominator());
    return stream;
}

istream& operator>>(istream& stream, Rational& rational){
    int a,b;
    if (stream >> a && stream.ignore(1) && stream >> b){
        rational = {a ,b};
    }
    return stream;
}

int main(){
    Rational r1, r2;
    char s;
    try{
        cin >> r1 >> s >> r2;

        if (s=='+'){
        cout << r1 + r2;
        }
        else if (s == '-'){
        cout << r1-r2;
        }
        else if (s== '*'){
        cout << r1*r2;
        }
        else if ( s== '/'){
        try {
            cout << r1 / r2;
        }catch(domain_error& ex){
            cout << "Division by zero";
        }
        }

    }catch(invalid_argument&){
        cout << "Invalid argument";
    }
    return 0;
}