//
//  sDeque.h
//  dequeAB
//
//  Created by Alexis Benter on 3/13/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;
class Deque{
    
    std::string *queue;
    int numElements;//Number of elements in array.
    int sizeQueue; //how much the array can hold
    int front; //manipulates elements in front of deque.
    int back; //manipulates elements at end of deque.
    
    void growArray();
    void shrinkArray();

public:
    Deque();
    ~Deque();
    void push_front(string item);
    void push_back(string item);
    string pop_front();
    string pop_back();
    int size();
    bool empty();
    string toStr();
    
private:
    static const int origSize=8;
};

