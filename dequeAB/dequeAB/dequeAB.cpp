//
//  dequeAB.cpp
//  dequeAB
//
//  Created by Alexis Benter on 3/13/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

#include "sDeque.h"
#include <iostream>

//Constructor
Deque::Deque ()
{
    numElements = 0;
    sizeQueue = 8;
    queue = new std::string[sizeQueue];
    front = 0;
    back = 0;
}

//Deconstructor
Deque::~Deque ()
{
    delete []queue;
}
//Queue automatically doubles when the number of elements is at full capacity
void Deque::growArray()
{
    if (numElements == size()) {
        std::string* newArray = new std::string[(sizeQueue * 2)];
        
        for (int i = 0; i < size(); ++i) {
            newArray[i] = queue[i];
        }
        
        queue = newArray;
    }
}

//Queue automatically shrinks to half it's size when it is less than 1/4 full and greater than the minimum size of 8
void Deque::shrinkArray()
{
    if (numElements < (sizeQueue / 4) && sizeQueue != 8) {
        std::string* newArray = new std::string[(sizeQueue / 2)];
        
        for (int i = 0; i < size(); ++i) {
            newArray[i] = queue[i];
        }
        
        queue = newArray;
    }
}

//Inserts element at the front of the queue.
void Deque::push_front(std::string item)
{
    ++numElements;
    growArray();
    
    for (int i = back; i >= 0; --i) {
        queue[i+1] = queue[i];
    }
    
    ++back;
    
    queue[0] = item;
}

// Inserts element at the back of the queue
void Deque::push_back(std::string item)
{
    ++numElements;
    
    growArray();
    
    queue[++back] = item;
}


// Deletes element at the front of the queue.
std::string Deque::pop_front()
{
    std::string returnString = "";
    
    if (!empty()) {
        returnString = queue[0];
        
        for (int i = 0; i < back; ++i) {
            queue[i] = queue[i+1];
        }
        
        --numElements;
        --back;
    }
    
    shrinkArray();
    
    return returnString;
}

// Deletes the element at the back of the queue.
std::string Deque::pop_back()
{
    std::string returnString = "";
    
    if (!empty()) {
        returnString = queue[back];
        
        --numElements;
        --back;
    }
    
    shrinkArray();
    
    return returnString;
}

//Returns number of elements in the queue.
int Deque::size() {
    return numElements;
}

//Tells whether the queue is empty or not.
bool Deque::empty() {
    if (numElements == 0) {
        return true;
    }
    else {
        return false;
    }
}

std::string Deque::toStr()
//concatenates the contents of the queue from front to back into a return string with each string item followed by a new line character in the return string
{
    std::string returnString = "";
    
    for (int i = 0; i < size(); ++i) {
        returnString += queue[i];
        returnString += "\n";
    }
    
    return returnString;
}
