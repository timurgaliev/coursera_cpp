#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

struct IncomingParameters{
    int64_t time;
    string hotel_name;
    int client_id;
    int room_count;
};

class Booking{
public:
    void Book(int64_t time_,string hotel_name_,int client_id_,int room_count_){
        data.push_back({time_,hotel_name_, client_id_, room_count_});
        while(time_ - data.begin()->time >= 86400){
            data.pop_front();
        }
    }
    int Clients(string hotel_name);
    int Rooms(string hotel_name);
private:
    deque<IncomingParameters> data; 

};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Booking data;
    int query;
    cin >> query;
    string command;
    for (int i = 0; i < query; ++i){
        cin >> command;
        int64_t time;
        string hotel_name;
        int client_id;
        int room_count;
        if (command == "BOOK"){
            cin >> time >> hotel_name >> client_id >> room_count;
            data.Book(time, hotel_name, client_id, room_count);
        }
        else if (command == "CLIENTS"){
            cin >> hotel_name;
            cout << data.Clients(hotel_name) << "\n";
        }
        else if (command == "ROOMS"){
            cin >> hotel_name;
            cout << data.Rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
