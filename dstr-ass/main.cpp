
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
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
            this->prev = NULL;
            this->next = NULL;
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

        int search_route_position(string name) {
            int i = 0;
            RouteList* node = this;
            while (node != NULL) {
                if (node->name == name) {
                    return i;
                }
                node = node->next;
                i++;

            }
            return -1;

        }

        bool iterate_ll(bool move_right) {
            if (move_right && this->next != NULL)
                return true;
            if (!move_right && this->prev != NULL)
                return true;
            return false;
        }

        void reassign_metrics() {
            if (this->next != NULL) {
                this->next->prev_distance = this->next_distance;
                this->next->prev_time = this->next_time;
                this->next->prev_price = this->next_price;
            }
            if (this->prev != NULL){
                this->prev->next_distance = this->prev_distance;
                this->prev->next_time = this->prev_time;
                this->prev->next_price = this->prev_price;
            }
        }

        bool add_station(RouteList *station, bool move_right) {
            RouteList *node = this;
            if (node->name == station->name) {
                if (move_right) {
                    station->next = node->next;
                    station->next->prev = station;
                }
                else {
                    station->prev = node->prev;
                    station->prev->next = station;
                }
                return true;
            }
            while (node->iterate_ll(move_right)) {
                node = move_right ? node->next : node->prev;
                if (node->name == station->name) {
                    if (move_right) {
                        station->next = node->next;
                        station->prev = node;
                    } else {
                        station->prev = node->prev;
                        station->next = node;
                    }
                    station->next->prev = station;
                    station->prev->next = station;
                    return true;
                }
            }
            if (move_right) {
                station->prev = node;
                station->prev->next = station;
            } else {
                station->next = node;
                station->next->prev = station;
            }
            return false;
        }

        float* calculate_path(string start_station_name, string end_station_name) {
            RouteList *station = this->search_route(start_station_name, true);
            bool move_right = this->search_route_position(start_station_name) < this->search_route_position(end_station_name);
            float total_distance = 0.0;
            float total_time = 0.0;
            float total_price = 0.0;
            while (station != NULL && station->name != end_station_name) {
                if (move_right) {
                    total_distance += station->next_distance;
                    total_time += station->next_time;
                    total_price += station->next_price;
                    station = station->next;
                } else {
                    total_distance += station->prev_distance;
                    total_time += station->prev_time;
                    total_price += station->prev_price;
                    station = station->prev;
                }
            }
            if (station == NULL)
                return NULL;
            float *output = new float[3];
            output[0] = total_distance;
            output[1] = total_time;
            output[2] = total_price;
            return output;
        }

};

class Transaction {
    public:
        int id;
        string source_station;
        string target_station;
        float price;
        string purchase_date_time;
        string departure_date_time;
        string passenger_name;
        Transaction *next;

        Transaction() {

        }
    
        Transaction(
            int id,
            string source_station,
            string target_station,
            float price,
            string purchase_date_time,
            string departure_date_time,
            string passenger_name
        ) {
            this->id = id;
            this->source_station = source_station;
            this->target_station = target_station;
            this->price = price;
            this->purchase_date_time = purchase_date_time;
            this->departure_date_time = departure_date_time;
            this->passenger_name = passenger_name;
            this->next = NULL;
        }

};

class TransactionQueue {
    private:
        Transaction *transactions;
        int size;
        
        void push(Transaction *transaction) {
            Transaction *transactions = this->transactions;
            if (transactions == NULL)
                this->transactions = transaction;
            else{
                while (transactions->next != NULL){
                    transactions = transactions->next;
                }
                transactions->next = transaction;
            }
            this->size++;
        }
    public:
        TransactionQueue() {
            transactions = NULL;
            size = 0;
        }

        Transaction *pop() {
            Transaction * transaction = this->transactions;
            this->transactions = transactions->next;
            transaction->next = NULL;
            this->size --;
            return transaction;
        }

        int get_size() {
            return this->size;
        }

        int get_next_id() {
            int id = -1;
            Transaction *transaction;
            for (int i = this->get_size(); i > 0; i--) {
                transaction = this->pop();
                id = get_max_val(id, transaction->id);
                this->push(transaction);
            }
            return id+1;
        }

        void add_transaction(Transaction *transaction) {
            this->push(transaction);
        }

        bool edit_transaction(Transaction *new_transaction) {
            Transaction *transaction;
            bool found = false;
            for (int i = this->get_size(); i > 0; i--) {
                transaction = this->pop();
                if (transaction->id == new_transaction->id) {
                    found = true;
                    transaction = new_transaction;
                }
                this->push(transaction);
            }
            return found;
        }

        bool delete_transaction(int transaction_id) {
            bool found = false;
            for (int i = this->get_size(); i > 0; i--) {
                Transaction *transaction;
                transaction = this->pop();
                if (transaction->id == transaction_id) {
                    found = true;
                } else {
                    this->push(transaction);
                }
            }
            return found;
        }
};

class Passenger {
    public:
        string name;
        string ic;
        TransactionQueue* transactions;

        Passenger() {

        }

        Passenger(string name, string ic, TransactionQueue* transactions) {
            this->name = name;
            this->ic = ic;
            this->transactions = transactions;
        }
};

class PassengerArray {
    public:
        int size;
        Passenger *passengers;

        PassengerArray() {
            this->size = 0;
        }

        Passenger *get(int i) {
            if (i >= 0 && i < size)
                return &(this->passengers[i]);
            return NULL;
        }

        int get_size() {
            return size;
        }

        Passenger *search_passenger(string passenger_name) {
            return this->get(this->search_passenger_id(this->get_size(), passenger_name));
        }

        int search_passenger_id(int pos, int length, std::string passenger_name) {
            if (length == 0) {
                return -1;
            }
            int mid = length/2;
            if (passenger_name == this->get(mid)->name) {
                return mid;
            }
            if (passenger_name < this->get(mid)->name) {
                return this->search_passenger_id(0, mid, passenger_name);
            }
            return this[mid].search_passenger_id(mid, mid, passenger_name);
        }

        int search_passenger_id(int length, std::string passenger_name) {
            return search_passenger_id(0, length, passenger_name);
        }

        void add_passenger(Passenger *passenger) {
            bool swap = false;
            Passenger *new_array = new Passenger[this->get_size()+1];
            for (int i = 0; i < this->get_size(); i++) {
                if (swap) {
                    new_array[i+1] = this->passengers[i];
                } else if (passenger->name < this->get(i)->name) {
                    new_array[i] = *passenger;
                    i--;
                } {
                    
                    new_array[i] = this->passengers[i];
                    
                }

            }
            if (this->get_size() == 0)
                new_array[0] = *passenger;
            
            if (swap)
                new_array[this->size] = this->passengers[this->get_size()];
            this->size++;
            this->passengers = new_array;
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
        n = std::stof(buf);
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
        -1.0,
        4.0,
        -1.0,
        0.4,
        -1.0,
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
    TransactionQueue *queue = new TransactionQueue();
    Transaction *transaction = new Transaction(
        1,
        "test",
        "test",
        1.0,
        "test",
        "test",
        "test"
    );
    queue->add_transaction(transaction);
    return queue;
}

PassengerArray* generate_passengers() {
    PassengerArray *passengers = new PassengerArray();
    Passenger *passenger = new Passenger(
        "Customer",
        "123456",
        generate_transactions()
    );
    passengers->add_passenger(
        passenger
    );
    return passengers;
}

int get_next_station_id(RouteList *stations) {
    int id = stations->id;
    while(stations->next != NULL) {
        stations = stations->next;
        id = max(id, stations->id);
    }
    return id + 1;
}

void show_station(RouteList *station, bool preview) {
    cout << "Station name: " << station->name << endl;
    if (!preview)
        if (station->prev != NULL) {
            cout << "Previous station name: " << station->prev->name << endl;
        } else {
            cout << "No previous station!" << endl;
        }
    if (station->prev_distance  >= 0){
        cout << "Previous station distance: " << station->prev_distance << endl;
        cout << "Previous station time: " << station->prev_time << endl;
        cout << "Previous station price: " << station->prev_price << endl;
    }
    if (!preview)
        if (station->next != NULL) {
            cout << "Next station name: " << station->next->name << endl;
        } else {
            cout << "No next station!" << endl;
        }
    if (station->next_distance  >= 0){
        cout << "Next station distance: " << station->next_distance << endl;
        cout << "Next station time: " << station->next_time << endl;
        cout << "Next station price: " << station->next_price << endl;
    }
}

void show_station(RouteList *station) {
    show_station(station, false);
}

void view_stations(RouteList *stations) {
    while (stations != NULL){
        show_station(stations);
        stations = stations->next;
    }
}

RouteList *search_station(RouteList *stations) {
    string name;
    cout << "Enter the station name: ";
    cin >> name;
    stations = stations->search_route(name, true);
    if (stations == NULL) {
        cout << "Could not find the station";
        system("pause");
    }
    return stations;
}

RouteList* add_station(RouteList *stations) {
    bool add = true;
    bool add_right = true;
    string name;
    float prev_distance = -1;
    float next_distance = -1;
    float prev_price = -1;
    float next_price = -1;
    float prev_time = -1;
    float next_time = -1;
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
    station = new RouteList(
        station ? station->id : get_next_station_id(stations),
        name,
        prev_distance,
        next_distance,
        prev_price,
        next_price,
        prev_time,
        next_time
    );
    show_station(station, true);
    option = read_char_cls(
        "Do you want to add this station?\n(y/n): ",
        "YyNn",
        false
    );
    if (tolower(option) == 'y') {
        stations->add_station(station, add_right);
        station->reassign_metrics();
        if (!add_right)
            stations = stations->prev;
    }
    return add_right ? stations : station;
}

void show_transaction(Transaction *transaction) {
    cout << "Transaction id: " << transaction->id << endl;
    cout << "Transaction source station: " << transaction->source_station << endl;
    cout << "Transaction target station: " << transaction->target_station << endl;
    cout << "Transaction price: " << transaction->price << endl;
    cout << "Transaction purchase datetime: " << transaction->purchase_date_time;
    cout << "Transaction departure datetime: " << transaction->departure_date_time << endl;
}

void view_transactions(TransactionQueue *transactions) {
    Transaction *transaction;
    for (int i = transactions->get_size(); i > 0; i--) {
        transaction = transactions->pop();
        show_transaction(transaction);
        transactions->add_transaction(transaction);
    }
}

void view_transactions(PassengerArray *passengers) {
    if (passengers->get_size() == 0) {
        cout << "No transactions!" << endl;
    }
    cout << passengers->get_size();
    for (int i = 0; i < passengers->get_size(); i++) {
        cout << "Passenger name: " << passengers->get(i)->name << endl;
        view_transactions(passengers->get(i)->transactions);
    }
}

void edit_transaction(TransactionQueue *transactions) {
    int id;
    string source_station;
    string target_station;
    float price;
    string purchase_date_time;
    string departure_date_time;
    std::string passenger_name;
    id = read_float("Enter the transaction id: ");
    cout << "Enter the transaction source station: ";
    cin >> source_station;
    cout << "Enter the transaction arrival station: ";
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
    transactions->edit_transaction(transaction);
    
}

void delete_transaction(TransactionQueue *transactions) {
    view_transactions(transactions);
    int id = read_float("Enter the transaction id: ");
    Transaction *transaction;
    transactions->delete_transaction(id);
}

Passenger *search_passenger(PassengerArray *passengers) {
    string name;
    cout << "Enter the passenger name: ";
    cin >> name;
    return passengers->search_passenger(name);

}

string get_current_time() {
    time_t _tm = time(NULL );
    struct tm * curtime = localtime ( &_tm );
    return asctime(curtime);
}

void buy_ticket(RouteList *stations, Passenger *passenger) {
    view_stations(stations);
    string start_station_name, end_station_name;
    cout << "Enter your initial station: ";
    cin >> start_station_name;
    cout << "Enter your final station: ";
    cin >> end_station_name;
    string departure_time;
    cout << "Enter the departure time: ";
    cin >> departure_time;
    float *path_metrics = stations->calculate_path(start_station_name, end_station_name);
    Transaction *transaction = new Transaction(
        passenger->transactions->get_next_id(),
        start_station_name,
        end_station_name,
        path_metrics[2],
        get_current_time(),
        departure_time,
        passenger->name
    );
    system("cls");
    show_transaction(transaction);
    char option = read_char_cls(
        "This will be your ticket. Do you want to purchase it?\n(y/n): ",
        "YyNn",
        false
    );
    if (tolower(option) == 'y')
        passenger->transactions->add_transaction(transaction);
}

void view_path(RouteList *stations) {
    view_stations(stations);
    string start_station_name, end_station_name;
    cout << "Enter your initial station: ";
    cin >> start_station_name;
    cout << "Enter your final station: ";
    cin >> end_station_name;
    bool move_right = stations->search_route_position(start_station_name) < stations->search_route_position(end_station_name);
    RouteList *node = stations->search_route(start_station_name, true);
    system("cls");
    float *path_metrics = stations->calculate_path(start_station_name, end_station_name);
    while (node->iterate_ll(move_right)) {
        cout << node->name << endl;
        node = move_right ? node->next : node->prev;
        if (node->name == end_station_name) {
            cout << node->name << endl;
            cout << "Total distance: " << path_metrics[0] << endl;
            cout << "Total time: " << path_metrics[1] << endl;
            cout << "Total price: " << path_metrics[2] << endl;
            system("pause");
            break;
        }
    }
}

PassengerArray *passenger_menu(RouteList *stations, PassengerArray *passengers) {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    Passenger* passenger = passengers->search_passenger(name);
    if (passenger == NULL) {
        string ic;
        cout << "You are a new user, please enter your identity card number for the registration: ";
        cin >> ic;
        passenger;
        passengers->add_passenger(passenger);
    }
    for(;;) {
        //system("cls");
        int option;
        cout << "Welcome, " << passenger->name << "!" << endl;
        cout << "1. Buy ticket" << endl;
        cout << "2. View path between two stations" << endl;
        cout << "3. View station details" << endl;
        cout << "4. View transaction history" << endl;
        cout << "5. Delete transaction" << endl;
        cout << "6. Back" << endl;
        cout << "Select your option: ";
        cin >> option;
        system("cls");
        switch(option) {
            case 1:
                buy_ticket(stations, passenger);
                system("cls");
                break;
            case 2:
                view_path(stations);
                break;
            case 3:
                show_station(search_station(stations));
                system("pause");
                break;
            case 4:
                view_transactions(passengers->search_passenger(name)->transactions);
                system("pause");
                break;
            case 5:
                delete_transaction(passengers->search_passenger(name)->transactions);
                break;
            case 6:
                return passengers;
                break;
            default:
                break;
        }
    }
}

RouteList *admin_menu(RouteList *stations, PassengerArray *passengers) {
    int option;
    for(;;) {
        system("cls");
        int option;
        cout << "1. Add/edit station" << endl;
        cout << "2. View all transactions" << endl;
        cout << "3. View customer purchase information" << endl;
        cout << "4. Edit customer purchase information" << endl;
        cout << "5. Delete customer purchase information" << endl;
        cout << "6. Back" << endl;
        cout << "Select your option: ";
        cin >> option;
        system("cls");
        switch(option) {
            case 1:
                stations = add_station(stations);
                break;
            case 2:
                view_transactions(passengers);
                system("pause");
                break;
            case 3:
                view_transactions(search_passenger(passengers)->transactions);
                system("pause");
                break;
            case 4:
                edit_transaction(search_passenger(passengers)->transactions);
                break;
            case 5:
                delete_transaction(search_passenger(passengers)->transactions);
                break;
            case 6:
                return stations;
                break;
            default:
                break;
        }
    }
}



int main() {
    RouteList *stations = generate_stations();
    PassengerArray *passengers = generate_passengers();
    for(;;) {
        system("cls");
        generate_passengers();
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
            stations = admin_menu(stations, passengers);
            break;
        case 2:
            passengers = passenger_menu(stations, passengers);
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    
}