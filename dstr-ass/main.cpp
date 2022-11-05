
#include <iostream>
#include <string>
using namespace std;

#define get_max_val(x,y) x >= y ? x : y
#define get_min_val(x,y) x <= y ? x : y

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
    
        RouteList(
            int id, string name,
            float prev_distance, float next_distance,
            float prev_price, float next_price,
            float prev_time, float next_time
        ) {
            this->id = id;
            this->name = name;
            this->prev_distance = prev_distance;
            this->next_distance = next_distance;
            this->prev_price = prev_price;
            this->next_price = next_price;
            this->prev_time = prev_time;
            this->next_time = next_time;
        }
        
        RouteList* search_route(string name, bool move_right) {
            RouteList* node = this;
            while (node != NULL) {
                if (node->name == name) {
                    return node;
                }
                if (move_right)
                    node = node->next;
                else
                    node = node->prev;

            }
            return NULL;

        }

        bool iterate_ll(RouteList *linked_list, bool move_right) {
            if (move_right && linked_list->next != NULL)
                return true;
            if (!move_right && linked_list->prev != NULL)
                return true;
            return false;
        }

        void add_station(RouteList *route_data, bool move_right) {

        }

        void edit_station(RouteList *route, RouteList *route_data, bool move_right) {

        }

        void delete_station(RouteList *route, bool move_right) {

        }

        float* calculate_path(string start_station_name, string end_station_name, bool move_right) {

        }

};

class Transaction {
    public:
        int id;
        string source_station;
        string target_station;
        float price;
        time_t purchase_date_time;
        time_t departure_date_time;
        string passenger_name;
    
        Transaction(
            int id,
            string source_station,
            string target_station,
            float price,
            time_t purchase_date_time,
            time_t departure_date_time,
            string passenger_name
        ) {
            this->id = id;
            this->source_station = source_station;
            this->target_station = target_station;
            this->price = price;
            this->purchase_date_time = purchase_date_time;
            this->departure_date_time = departure_date_time;
            this->passenger_name = passenger_name;
        }

};

class TransactionQueue {
    private:
        Transaction *transactions;
    public:
        TransactionQueue(Transaction *transactions) {
            this->transactions = transactions;
        }

        void push(Transaction *transaction) {

        }

        Transaction *pop() {

        }

        void add_transaction(Transaction transaction) {

        }

        void edit_transaction(int transaction_id, Transaction *new_transaction) {

        }

        void delete_transaction(int transaction_id) {

        }

        int get_size() {

        }
};

class Passenger {
    public:
        int id;
        string name;
        string ic;
        TransactionQueue* transactions;

        Passenger(
            int id,
            string name,
            string ic,
            TransactionQueue* transactions
        ) {
            this->id = id;
            this->name = name;
            this->ic = ic;
            this->transactions = transactions;
        }

        Passenger *search_passenger(string passenger_name) {
            return this->get(this->search_passenger_id(this->get_size(), passenger_name));
        }

        int search_passenger_id(size_t length, std::string passenger_name) {
            if (length == 0) {
                return NULL;
            }
            int mid = length/2;
            if (passenger_name == this[mid].name) {
                return mid;
            }
            if (passenger_name < this[mid].name) {
                return this->search_passenger_id(mid, passenger_name);
            }
            return this[mid].search_passenger_id(mid, passenger_name);
        }

        void add_passenger(Passenger passenger) {

        }

        Passenger *get(int i) {

        }

        int get_size() {

        }

};

// reads a string from the input and checks whether it matches unsigned float, if it doesn't, it will ask to input again
// cleans the screen before showing prompt every time
float read_float(string prompt) {
    string buf;
    float n = -1;
    while (n && n <= 0) {
        system("cls");
        cout << prompt;
        cin >> buf;
        n = stof(buf);
	}
    return n;
}

// reads a string from the input and checks whether it's equal to one of the characters in a specified mask, if it doesn't, it will ask to input again
// cls parameter is needed to specify whether to clean the screen before showing the prompt
char read_char_cls(string prompt, string mask, bool cls) {
    char buf;
    do {
        if (cls)
            system("cls");
        cout << prompt;
        cin >> buf;
    } while (mask.find(buf) == string::npos);
    return buf;
}

// reads a string from the input and checks whether it's equal to one of the characters in a specified mask, if it doesn't, it will ask to input again
// cleans the screen before showing prompt every time
char read_char(string prompt, string mask) {
    return read_char_cls(prompt, mask, true);
}


RouteList* generate_stations() {
    RouteList* titiwangsa = new RouteList(
        1,
        "Titiwangsa",
        NULL,
        4.0,
        NULL,
        0.4,
        NULL,
        3.0
    );
    RouteList* pwtc = new RouteList(
        2,
        "PWTC",
        4.0,
        8.0,
        0.4,
        0.8,
        3.0,
        7.0
    );
    titiwangsa->next = pwtc;
    pwtc->prev = titiwangsa;
}

RouteList* generate_stations() {
    RouteList* titiwangsa = new RouteList(
        1,
        "Titiwangsa",
        NULL,
        4.0,
        NULL,
        0.4,
        NULL,
        3.0
    );
    RouteList* pwtc = new RouteList(
        2,
        "PWTC",
        4.0,
        8.0,
        0.4,
        0.8,
        3.0,
        7.0
    );
    titiwangsa->next = pwtc;
    pwtc->prev = titiwangsa;
    
    return titiwangsa;
}

TransactionQueue* generate_transactions() {
    Transaction *transactions = new Transaction(
        1,
        "test",
        "test",
        1.0,
        time(0),
        time(0),
        "test"
    );
    TransactionQueue *queue = new TransactionQueue(transactions);
    return queue;
}

Passenger* generate_passengers() {
    
    Passenger *passengers = new Passenger(
        1,
        "test",
        "test",
        generate_transactions()
    );
}

int get_next_station_id(RouteList *stations) {
    int id = stations->id;
    while(stations->next != NULL) {
        stations = stations->next;
        id = max(id, stations->id);
    }
    return id + 1;
}

void show_station(RouteList *station) {
    cout << "Station id: " << station->id << endl;
    cout << "Station name: " << station->name << endl;
    if (station->prev != NULL) {
        cout << "Previous station name: " << station->prev->name << endl;
        cout << "Previous station distance: " << station->prev_distance << endl;
        cout << "Previous station time: " << station->prev_time << endl;
        cout << "Previous station price: " << station->prev_price << endl;
    }
    if (station->next != NULL) {
        cout << "Next station name: " << station->next->name << endl;
        cout << "Next station distance: " << station->next_distance << endl;
        cout << "Next station time: " << station->next_time << endl;
        cout << "Next station price: " << station->next_price << endl;
    }
}

RouteList* add_station(RouteList *stations) {
    bool add = true;
    bool add_right;
    string name;
    float prev_distance;
    float next_distance;
    float prev_price;
    float next_price;
    float prev_time;
    float next_time;
    RouteList* prev;
    RouteList* next;
    cout << "Enter the station name:";
    cin >> name;
    RouteList *station = stations->search_route(name, true);
    char option;
    if (station == NULL) {
        option = read_char(
            "A station with such name doesn't exist. Do you want to create a new one?\n(y/n): ",
            "YyNn"
        );
        if (tolower(option) == 'n') {
            return stations;
        }
    } else {
        option = read_char(
            "A station with such name already exists. Do you want to edit it?\n(y/n): ",
            "YyNn"
        );
        if (tolower(option) == 'n') {
            return stations;
        } else {
            add = false;
        }
    }
    if (add) {
        option = read_char(
            "Do you want to add the station to the right or to the left?\n(l/r)",
            "LlRr"
        );
        add_right = tolower(option) == 'r';
    }
    if (!add || !add_right) {
        next_distance = read_float("Please enter the next station's distance:");
        next_time = read_float("Please enter the next station's time:");
        next_price = read_float("Please enter the next station's price:");
    }
    if (!add || add_right) {
        prev_distance = read_float("Please enter the previous station's distance:");
        prev_time = read_float("Please enter the previous station's time:");
        prev_price = read_float("Please enter the previous station's price:");
    }
    RouteList *new_station = new RouteList(
        station ? station->id : get_next_station_id(stations),
        name,
        prev_distance,
        next_distance,
        prev_price,
        next_price,
        prev_time,
        next_time
    );
    show_station(station);
    option = read_char(
        "Do you want to add this station?\n(y/n): ",
        "YyNn"
    );
    if (tolower(option) == 'y') {
        stations->add_station(new_station, add_right);
        if (!add_right)
            stations = stations->prev;
    }
    return stations;
}

void show_transaction(Transaction *transaction) {
    cout << "Transaction id: " << transaction->id << endl;
    cout << "Transaction source station: " << transaction->source_station << endl;
    cout << "Transaction target station: " << transaction->target_station << endl;
    cout << "Transaction price: " << transaction->price << endl;
    cout << "Transaction purchase datetime: " << transaction->purchase_date_time << endl;
    cout << "Transaction departure datetime: " << transaction->departure_date_time << endl;
}

void view_transactions(TransactionQueue *transactions) {
    Transaction *transaction;
    for (int i = transactions->get_size(); i > 0; i--) {
        transaction = transactions->pop();
        show_transaction(transaction);
        transactions->push(transaction);
    }
}

void view_transactions(Passenger *passengers) {
    
    for (int i = 0; i < passengers->get_size(); i++) {
        cout << "Passenger name: " << passengers->get(i)->name;
        view_transactions(passengers->get(i)->transactions);
    }
}

void edit_transaction(TransactionQueue *transactions) {
    int id;
    string source_station;
    string target_station;
    float price;
    time_t purchase_date_time;
    time_t departure_date_time;
    std::string passenger_name;
    id = read_float("Enter the transaction id: ");
    cout << "Enter the transaction source station: ";
    cin >> source_station;
    cout << "Enter the transaction source station: ";
    cin >> target_station;
    cout << "Enter the transaction price: ";
    cin >> price;
    cout << "Enter the transaction purchase datetime: ";
    cin >> purchase_date_time;
    cout << "Enter the transaction departure datetime: ";
    cin >> departure_date_time;
    Transaction *transaction = new Transaction(
        id,
        source_station,
        target_station,
        price,
        purchase_date_time,
        departure_date_time,
        passenger_name
    );
    transactions->edit_transaction(id, transaction);
    // Transaction *transaction;
    // bool found = false;
    // for (int i = transactions->get_size(); i > 0; i--) {
    //     transaction = transactions->pop();
    //     if (transaction->id == id) {
    //         found = true;
    //         show_transaction(transaction);
    //         if (tolower(read_char_cls("Found this transaction.\nDo you want to save the changes?\n(y/n): ", "YyNn", false)) == 'y') {
    //             transaction->source_station = source_station;
    //             transaction->target_station = target_station;
    //             transaction->price = price;
    //             transaction->purchase_date_time = purchase_date_time;
    //             transaction->departure_date_time = departure_date_time;
    //         }
    //     }
    //     transactions->push(transaction);
    // }
    // if (!found) {
    //     cout << "Could not find any transation with this id" << endl;
    //     system("pause");

    // }
}

void delete_transaction(TransactionQueue *transactions) {
    view_transactions(transactions);
    int id = read_float("Enter the transaction id: ");
    Transaction *transaction;
    transactions->delete_transaction(id);
}

Passenger *search_passenger(Passenger *passengers) {
    string name;
    cout << "Enter the passenger name";
    cin >> name;
    return passengers->search_passenger(name);

}

void passenger_menu(RouteList *stations, Passenger *passengers) {
    exit(0);
}

void admin_menu(RouteList *stations, Passenger *passengers) {
    int option;
    for(;;) {
        int option;
        cout << "1. Add/edit station" << endl;
        cout << "2. View all transactions" << endl;
        cout << "3. View customer purchase information" << endl;
        cout << "4. Edit customer purchase information" << endl;
        cout << "5. Delete customer purchase information" << endl;
        cout << "6. Exit" << endl;
        cout << "Select your option: ";
        cin >> option;
        system("cls");
        switch(option) {
            case 1:
                stations = add_station(stations);
                break;
            case 2:
                view_transactions(passengers);
                break;
            case 3:
                view_transactions(search_passenger(passengers)->transactions);
                break;
            case 4:
                edit_transaction(search_passenger(passengers)->transactions);
                break;
            case 5:
                delete_transaction(search_passenger(passengers)->transactions);
                break;
            case 6:
                exit(0);
                break;
            default:
                break;
        }
    }
}



int main() {
    RouteList *stations = generate_stations();
    Passenger *passengers = generate_passengers();
    for(;;) {
        int option;
        cout << "1. Admin" << endl;
        cout << "2. Passenger" << endl;
        cout << "3. Exit" << endl;
        cout << "Select your option: ";
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            admin_menu(stations, passengers);
            break;
        case 2:
            passenger_menu(stations, passengers);
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    
}