#pragma once
#ifndef main
#define main

# include <iostream>
using namespace std;


namespace DSTR {

    class Route
    {
    public:
        
        int id;
        string name;

        //prev station
        int prev_id;
        float prev_distance;
        float prev_price;
        float prev_time;

        //next station
        int next_id;
        float next_distance;
        float next_price;
        float next_time;

        Route* prev;
        Route* next;
    };


    class RouteList
    {
        public:
            
            Route* head;
            Route* tail;
            int size;
        
            RouteList() {
                cout << "--- Constructing the Route List ---" << endl;
                this->size = 0;
                this->head = nullptr;
                this->tail = nullptr;
            };
            
            void search_route(RouteList *route, bool move_right);

            void iterate_ll(RouteList *linked_list, bool move_right);

            void add_station_to_beginning(RouteList* route_data, bool move_right) {
                cout << "Insert to beginning = " << endl;
                cout << "Enter station name, previous station name & next station name = " << name1 << prev_name1 << next_name1 << endl;
                cout<< "Enter the "
                Route* newNode = new Route;
                newNode->name = name1;
                newNode->prev_name = prev_name1;
                newNode->next_name = next_name1;

                newNode->next = head;
                newNode->prev = NULL;
                head = newNode;

                /*if (head != nullptr) {
                    DoublyNode<T>* tail = head;
                    head = newDNode;
                    newDNode->next = tail;
                }*/
                if (tail == NULL) {
                    tail = newDNode;
                }
                else {
                    newDNode->next->prev = newDNode;
                }

                size++;
            };

            void edit_station(RouteList *route, RouteList *route_data, bool move_right);

            void delete_station(RouteList *route, bool move_right);

            float* calculate_path(string start_station_name, string end_station_name, bool move_right);

    };

    class Transaction {
        public:
            int id;
            int ticket_id;
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

            void push(Transaction transaction);

            void add_transaction(Transaction transaction);

            void edit_transaction(int transaction_id, Transaction new_transaction);

            void delete_transaction(int transaction_id);
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

    };
}


#endif
