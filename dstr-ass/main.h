#pragma once
#ifndef main
#define main

# include <iostream>
using namespace std;

template<class T> //abstract type       
class Route
{
public:
    T data;
    Route<T>* prev;
    Route<T>* next;
};

template<class T>
class RouteList
{
    RouteLst()
    {
        cout << "--- Constructing the Doubly LinkedList object ---" << endl;
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    void search_route(T route, T head, T move_right ) {

    }

    void iterate_II(T linked_list, T head, T move_right) {

    }

    void add_station(T route_data, T head, T move_right) {

    }

    void edit_station(T route, T route_data, T head, T move_right) {

    }

    void delete_station(T route, T head, T move_right) {

    }

}


int search_passenger(T passengers, T passenger) {

}

int search_passenger_id(T arr, T length, T passenger) {

}

#endif
