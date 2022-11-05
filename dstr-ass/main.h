#pragma once
#ifndef main
#define main

# include <iostream>
using namespace std;


namespace DSTR {
    class RouteList
    {
        public:
            int id;
            string name;
            float prev_distance;
            float next_distance;
            float prev_price;
            float next_price;
            float prev_time;
            float next_time;
            RouteList* prev;
            RouteList* next;
        
            RouteList();
            
            void search_route(RouteList *route, bool move_right);

            void iterate_ll(RouteList *linked_list, bool move_right);

            void add_station(RouteList *route_data, bool move_right);

            void edit_station(RouteList *route, RouteList *route_data, bool move_right);

            void delete_station(RouteList *route, bool move_right);

            float* calculate_path(string start_station_name, string end_station_name, bool move_right);

    };

    class Transaction {
        public:
            int id;
            std::string source_station;
            std::string target_station;
            float price;
            time_t purchase_date_time;
            time_t departure_date_time;
            std::string passenger_name;
        
            Transaction();

    };

    class TransactionQueue {
        private:
            Transaction *transactions;
        public:
            TransactionQueue();

            void push(Transaction *transaction);

            Transaction* pop();

            void add_transaction(Transaction transaction);

            void edit_transaction(int transaction_id, Transaction *new_transaction);

            void delete_transaction(int transaction_id);
            
            int get_size();
    };

    class Passenger {
        public:
            int id;
            std::string name;
            std::string ic;
            TransactionQueue* transactions;

            Passenger();

            int search_passenger(Passenger passenger);

            int search_passenger_id(int length, Passenger passenger);

            void add_passenger(Passenger passenger);

            Passenger *get(int i);

            int get_size();

    };
}


#endif
