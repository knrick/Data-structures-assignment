#pragma once
#ifndef main
#define main

# include <iostream>
using namespace std;


namespace DSTR {

    // The class for the stations. Linked list
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
        
            // The constructor for the RouteList class.
            // Basically the code will run when we create a variable
            // The code inside sets the arguments passed as the object's properties
            RouteList(
                int id, string name,
                float prev_distance, float next_distance,
                float prev_price, float next_price,
                float prev_time, float next_time
            );
            
            // Searches the station by its name. Linear search
            // move_right determines whether we iterate to the right or to the left
            void search_route(string name, bool move_right);

            // searches the position number of the station
            int search_route_position(string name);

            // when we iterate the linked list and to check whether the next/prev element is null
            // this function checks the righr variable based on move_right
            // like when we use while (node->next != NULL)
            bool iterate_ll(bool move_right);

            // adds a station either to the beginning or the end of the list
            // if move_right add it to the end (right), otherwise to the beginning (left)
            bool add_station(RouteList *station, bool move_right);

            // calculates the path metris from one sstation to another
            // returns a float array of 3 values
            //output[0] = total_distance
            //output[1] = total_time
            //output[2] = total_price
            float* calculate_path(string start_station_name, string end_station_name);

    };

// The class for a single transaction
    class Transaction {
        public:
            int id;
            std::string source_station;
            std::string target_station;
            float price;
            string purchase_date_time;
            string departure_date_time;
            std::string passenger_name;
        
            // The constructor that sets the properties
            Transaction(
                int id,
                string source_station,
                string target_station,
                float price,
                string purchase_date_time,
                string departure_date_time,
                string passenger_name
            );

    };

    // The class for the transaction queue.
    class TransactionQueue {
        // private properties and methods. Means we can only access them inside of the class
        private:
            Transaction *transactions; // stores our transactions
            int size; // the size of the queue

            // Adds a new transaction to the end of the queue and increments the size
            void push(Transaction *transaction);
        public:
            // the constructor. Just sets the size to 0
            TransactionQueue();

            // Removes the first element of the queue, returns it and decrements the size
            Transaction* pop();

            // Use this function to get the size outside of the class's scope
            // Because the size property is private
            int get_size();

            // when we want to create a new element, use this function to generate a new id
            // basically searches the maximum id and returns it incremented by 1
            int get_next_id();

            // just runs push but it's a public method
            void add_transaction(Transaction *transaction);

            // edits the transaction
            // finds it by id and then replaces the values
            bool edit_transaction(Transaction *new_transaction);

            // removes the transaction by its id
            bool delete_transaction(int transaction_id);
    };
//  The class for a single passenger
    class Passenger {
        public:
            int id;
            std::string name;
            std::string ic;
            TransactionQueue* transactions;
    };
    // The class for the array of passengers
    class PassengerArray {
        // private property size. Stores the size of the array
        int size;
        public:
            // The constructor
            PassengerArray();

            // returns the passenger by id
            // if the id is wrong, returns NULL
            Passenger *get(int i);

            // returns the size of the array.
            // Check get_size() of TransactionQueue for more
            int get_size();

            // searches the passenger by the name
            // uses binary search
            Passenger *search_passenger(string passenger_name);

            // searches the passenger from the specific position and for a specific length
            int search_passenger_id(int pos, int length, std::string passenger_name);

            // sames as the upper search_passenger_id but with pos = 0
            int search_passenger_id(size_t length, std::string passenger_name);

            // adds the passenger to the array
            // also sorts the array when doing
            // so the array is always sorted
            PassengerArray* add_passenger(Passenger *passenger);
    };

    // input function for float numbers
    // doesn't allow wrong input
    // prompt is what will be outputted to the user before accepting the input
    float read_float(string prompt);

    // input function for specific characters that we pass to the mask
    // for example, if mask is "YyNn" the input will accept only these characters
    // and only accepts a single character
    // so you can use it to ask a question and get a yes/no answer
    // cls is to determine whether to clear the screen before showing the prompt
    char read_char_cls(string prompt, string mask, bool cls);

    // same as read_char_cls but with cls=true
    char read_char(string prompt, string mask);

    // generates the initial stations
    // since the assignment requires to hardcode the stations
    RouteList* generate_stations();

    // generates the initial transactions
    TransactionQueue* generate_transactions();

    // generates the initial passengers
    PassengerArray* generate_passengers();

    // same as get_next_id of TransactionQueue but for the station
    int get_next_station_id(RouteList *stations);
    
    // displays a single station
    void show_station(RouteList *station);

    // displays all the stations from the list
    void view_stations(RouteList *stations);

    // ask the user to enter the station details and search for it and display
    RouteList *search_station(RouteList *stations);

    // ask the user to enter the station details and add it to the list
    RouteList* add_station(RouteList *stations);

    // displays a single transaction
    void show_transaction(Transaction *transaction);

    // displays all the transactions of the queue
    void view_transactions(TransactionQueue *transactions);

    // displays all the transactions of all passengers
    void view_transactions(PassengerArray *passengers);

    // ask the user to enter the transaction details and change the values
    void edit_transaction(TransactionQueue *transactions);

    // ask the user to enter the transaction details and delete it
    void delete_transaction(TransactionQueue *transactions);

    // ask the user to enter the passenger name, search it and return
    Passenger *search_passenger(PassengerArray *passengers);

    // returns current_time as string
    string get_current_time();

    // ask the user to enter two stations and departure time, and then creates a transaction
    void buy_ticket(RouteList *stations, Passenger *passenger);

    // ask the user to enter two stations and dispplays a path from one to another with the metrics
    void view_path(RouteList *stations);

    // shows the passenger menu
    // before opening it, asks to enter the passenger name and performs the search
    // returns the passenger array to update it
    PassengerArray* passenger_menu(RouteList *stations, PassengerArray *passengers);

    // shows the admin menu
    // returns station menu to update it
    RouteList* admin_menu(RouteList *stations, PassengerArray *passengers);
}


#endif
