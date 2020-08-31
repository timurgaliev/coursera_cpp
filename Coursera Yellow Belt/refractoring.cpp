#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human{
public:
    Human(const string& name, const string& status_) : Name(name), status(status_){

    }
    void WalkAction(const string& destination) const{
        cout << status << ": " << Name << " walks to: " << destination << endl;
    }
    virtual void Walk (const string& destination) const = 0;
    const string Name;
    const string status;
};


class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong) : 
        Human(name, "Student"), FavouriteSong(favouriteSong) {
        
    }
    void Learn() const{
        cout << Status << ": " << Name << " learns" << endl;
    }
    virtual void Walk(const string& destination) const override {
        WalkAction(destination);
        SingSong();
    }
    void SingSong() const {
        cout << Status << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
    const string Status = "Student";
};


class Teacher : public Human {
public:
    Teacher(const string& name, const string& subject) :
        Human(name, "Teacher"), Subject(subject) {
        
    }
    void Teach() const {
        cout << Status << ": " << Name << " teaches: " << Subject << endl;
    }
    virtual void Walk(const string& destination) const override {
        WalkAction(destination);
    }
private:
    const string Subject;
    const string Status = "Teacher";
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman"){
    }

    void Check(const Human& h) const{
        cout << Status << ": " << Name << " checks " << h.status <<". " 
             << h.status<< "'s name is: " << h.Name << endl;
    }
    virtual void Walk(const string& destination) const override{
        WalkAction(destination);
    }
private:
    const string Status = "Policeman";    
};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const string& p: places){
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}