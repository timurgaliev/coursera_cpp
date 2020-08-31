#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& t) : Name(t) {
    }
    const string Name;
};


class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {
    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};


int main(){
    Dog d("haski");
    d.Bark();


    return 0;
}