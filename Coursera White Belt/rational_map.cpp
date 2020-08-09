#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
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

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

bool operator>(const Rational& lhd, const Rational& rhd){
    return (lhd.Numerator() / (double)lhd.Denominator()) > (rhd.Numerator() / (double)rhd.Denominator());
}

bool operator<(const Rational& lhd, const Rational& rhd){
    return (lhd.Numerator() / (double)lhd.Denominator()) < (rhd.Numerator() / (double)rhd.Denominator());
}


int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
