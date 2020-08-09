#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
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


int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
