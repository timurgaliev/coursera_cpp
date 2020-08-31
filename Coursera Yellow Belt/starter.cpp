#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string command;
  is >> command;
  if (command == "NEW_BUS"){
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stops_num_;
    is >> stops_num_;
    q.stops.resize(stops_num_);
    for (string& input_stop: q.stops){
      is >> input_stop;
    }
  }
  else if( command == "BUSES_FOR_STOP"){
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  }
  else if (command == "STOPS_FOR_BUS"){
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  }
  else if (command == "ALL_BUSES"){
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()){
    os << "No stop";
  }else{
    for (const string bus_: r.buses){
      os << bus_ << ' ';
    }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<string> stops_with_interchange;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  for (const string& stop: r.stops_with_interchange){
    os << stop;
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> all_bus;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (!r.all_bus.empty()){
    int i=0;
  for( const auto& [key,value] : r.all_bus){
    os << "Bus " << key << ": ";
      for (const string& val : value){
        os << val << " ";
      }
      i +=1;
    if (i != r.all_bus.size()){
      os << endl;
    }
    }
  }
  else{
    os << "No buses";
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop_: stops){
        stops_to_buses[stop_].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse buses_;
    if (stops_to_buses.count(stop) != 0){
       buses_.buses = stops_to_buses.at(stop);
    }
    return buses_;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse stops_;
    stops_.bus = bus;
    string temp;
    if(buses_to_stops.count(bus) != 0){
      for (const string& stop_ : buses_to_stops.at(bus)){
        temp = "Stop " + stop_ +": "; 
        if (stops_to_buses.at(stop_).size() == 1){
          temp += "no interchange";
        }else{
        for (const string& bus_ : stops_to_buses.at(stop_)){
          if (bus_ != bus){
          temp += bus_ + ' ';
          }
        }
        }
        if (stops_.stops_with_interchange.size() != buses_to_stops.at(bus).size() - 1){
          stops_.stops_with_interchange.push_back(temp + '\n');
        }else{
        stops_.stops_with_interchange.push_back(temp);
        }
      }
    }else{
      stops_.stops_with_interchange.push_back("No bus");
    }
    return stops_;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse list;
    list.all_bus = buses_to_stops;
    return list;
  }
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
