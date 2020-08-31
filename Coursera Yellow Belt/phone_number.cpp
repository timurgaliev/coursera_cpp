#include "phone_number.h"

#include <sstream>
//#include <iostream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number){
    stringstream ss(international_number);
    if (ss.peek() != '+'){
        throw invalid_argument("wrong number +");
    }
    ss.ignore();
    if (ss.peek() == EOF){
        throw invalid_argument("wrong number country");
    }
    getline(ss, country_code_, '-');
    if (ss.peek() == EOF){
        throw invalid_argument("Wrong number city");
    }
    getline(ss, city_code_, '-');
    if (ss.peek() == EOF){
        throw invalid_argument("Wrong number local");
    }
    ss >> local_number_; 
}

string PhoneNumber::GetCountryCode() const{
    return country_code_;
}

string PhoneNumber::GetLocalNumber() const{
    return local_number_;
}

string PhoneNumber::GetCityCode() const{
    return city_code_;
}

string PhoneNumber::GetInternationalNumber() const{
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

/*int main(){
    PhoneNumber number("+8-953-482-40-77");
    string ru, kz, my;
    ru = number.GetCountryCode();
    kz = number.GetCityCode();
    my = number.GetLocalNumber();
    cout << ru << endl << kz <<endl <<  my << endl;
    cout << number.GetInternationalNumber();
    
    return 0;
}*/