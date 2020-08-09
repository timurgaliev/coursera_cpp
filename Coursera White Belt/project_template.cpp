#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public: 
  Date(int y, int m ,int d){
    year =y;
    month = m;
    day = d;
  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const{
    return day;
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs){
  return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() < 
         rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}

class Database {
public:
  void AddEvent(const Date& date, const string& event){
    data[{date.GetYear(), date.GetMonth(), date.GetDay()}].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event){
    set<string> value = data[{date.GetYear(), date.GetMonth(), date.GetDay()}];
    if (value.count(event) > 0){
      data[{date.GetYear(), date.GetMonth(), date.GetDay()}].erase(event);
      return true;
    }else{
      return false;
    }
  }
  int  DeleteDate(const Date& date){
    set<string> value = data[{date.GetYear(), date.GetMonth(), date.GetDay()}];
    if (value.size() != 0){
      data.erase({date.GetYear(), date.GetMonth(), date.GetDay()});
    }
    return value.size();
  }

  void Find(const Date& date) {
    set<string> value = data[{date.GetYear(), date.GetMonth(), date.GetDay()}];
    if (value.size() != 0){
      for (auto& item : value){
        /*cout << fixed << setw(4) << setfill('0') << to_string(date.GetYear()) << '-' << 
        setw(2) << setfill('0') << to_string(date.GetMonth()) << '-' << setw(2) << setfill('0') <<
        to_string(date.GetDay()) << " " << item << endl;*/
        cout << item << endl;
      }
    }
  }
  void Print() const{
    if (!data.empty()){
      for (const auto& item : data){
        for (const auto& it : item.second){
            cout << fixed << setw(4) << setfill('0') << to_string(item.first.GetYear()) << '-' <<
            setw(2) << setfill('0') << to_string(item.first.GetMonth()) << '-' << setw(2) << setfill('0') <<
            to_string(item.first.GetDay()) << " " << it << endl;
        }
      }
    }
  }
private:
  map<Date, set<string>> data;
};


Date TryParseDate(const string& date){
  stringstream ss(date);
  int year;
  int month;
  int day;
  ss >> year;
  if (ss.peek() != '-'){
    throw invalid_argument("Wrong date format: " + date);
  }
  ss.ignore();
  if (ss.peek() == EOF){
    throw invalid_argument("Wrong date format: " + date);
  }
  ss >> month;
  if (ss.peek() != '-'){
    throw invalid_argument("Wrong date format: " + date);
  }
  ss.ignore();
  if (ss.peek() == EOF){
    throw invalid_argument("Wrong date format: " + date);
  }
  ss >> day;
  if (!ss.eof()){
    throw invalid_argument("Wrong date format: " + date);
  }
  if (month > 12 || month < 1){
    throw invalid_argument("Month value is invalid: " + to_string(month));
  }
  if (day > 31 || day < 1){
    throw invalid_argument("Day value is invalid: " + to_string(day));
  }
  return Date({year, month, day});
}



int main() {
  Database db;
  string command;
  while(getline(cin, command)){
    stringstream stream(command);
    string com;
    stream >> com;
    if (com == "Add"){
      string date, event;
      stream >> date >> event;
      try{
        Date ymd = TryParseDate(date);
        db.AddEvent(ymd, event);
      }catch (invalid_argument& ex){
        cout << ex.what();
        break;
      }
    }
    else if ( com == "Del"){
      string ymd;
      stream >> ymd;
      Date date(1,1,1);
      try{
        date = TryParseDate(ymd);
      }catch (invalid_argument& ex){
        cout << ex.what();
        break;
      }
      string event;
      if (!stream.eof()){
        stream >> event;
      }
      if (event.empty()){
        int N =  db.DeleteDate(date);
        cout << "Deleted " << N << " events" << endl;
      }else{
        bool state = db.DeleteEvent(date, event);
        if (state){
          cout << "Deleted successfully" << endl;
        }else{
          cout << "Event not found" << endl;
        }
      }
    }
    else if (com == "Find"){
      string ymd;
      stream >> ymd;
      try{
        Date date = TryParseDate(ymd);
        db.Find(date);
      }catch (invalid_argument& ex){
        cout << ex.what();
        break;
      }
    }
    else if (com == "Print"){
      db.Print();
    }else{
      if (!com.empty()){
        cout << "Unknown command: " << command << endl;
      }  
    }
  }

  return 0;
}