#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure{
public:
    Triangle(double a, double b, double c) : 
            a_(a), b_(b), c_(c) { }
    virtual string Name() const override{
        return name;
    }
    virtual double Perimeter() override{
        perimeter = a_ + b_ + c_;
        return perimeter;
    }
    virtual double Area() override {
        double p = (a_ + b_ + c_ )/ 2;
        area = sqrt(p * (p - a_) * (p - b_) * (p - c_)) ;
        return area;
    }
private:
    const double a_, b_, c_;
    const string name = "TRIANGLE";
    double perimeter = 0;
    double area = 0;
};

class Rect : public Figure {
public:
    Rect(double a, double b) : a_(a), b_(b) {}
    virtual string Name() const override{
        return name;
    }
    virtual double Perimeter() override {
        perimeter = 2*a_ + 2*b_;
        return perimeter;
    }
    virtual double Area() override {
        area = a_ * b_;
        return area;
    }
private:
    const string name = "RECT";
    const double a_, b_;
    double perimeter = 0;
    double area = 0;
};

class Circle : public Figure {
public:
    Circle(double r): r_(r){}
    virtual string Name() const override{
        return name;
    }
    virtual double Perimeter() override {
        perimeter = 2 * 3.14 * r_;
        return perimeter;
    }
    virtual double Area() override {
        area = 3.14 * r_ * r_;
        return area;
    }
private:
    const string name = "CIRCLE";
    const double r_;
    double perimeter = 0;
    double area = 0;
};

shared_ptr<Figure> CreateFigure(istream& is){
    string type;
    is >> type;
    if (type == "TRIANGLE"){
        double a,b,c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a,b,c);
    }
    else if (type == "CIRCLE"){
        double r;
        is >> r;
        return make_shared<Circle>(r);
    }else{
        double a, b;
        is >> a >> b;
        return make_shared<Rect>(a,b);
    }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}