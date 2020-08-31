#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};



class Rational {
public:
    Rational() {
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
        return num;

    }
    int Denominator() const {
        return den;
    }
private:
    int num;
    int den;
};

ostream& operator<<(ostream& stream, const Rational& rational){
    stream << to_string(rational.Numerator()) << "/" << to_string(rational.Denominator());
    return stream;
}

bool operator!=(const Rational& lhs, const Rational& rhs){
  if (lhs.Numerator() != rhs.Numerator() || lhs.Denominator() != rhs.Denominator()){
    return true;
  }
  return false;
}


void TestRational(){
  AssertEqual(Rational(0,15), Rational(0,1));
  AssertEqual(Rational(1,-5), Rational(-1,5));
  AssertEqual(Rational(10,2), Rational(5,1));
  AssertEqual(Rational(2,3), Rational(2,3));
  AssertEqual(Rational(-2,7), Rational(-2,7));
  AssertEqual(Rational(4,8), Rational(1,2));
  AssertEqual(Rational(4,-8), Rational(-1,2));
  AssertEqual(Rational(), Rational(0,1));
}

int main() {
  TestRunner runner;
  runner.RunTest(TestRational, "Rational");
  return 0;
}
