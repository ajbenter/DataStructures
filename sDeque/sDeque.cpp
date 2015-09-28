//
//  sDeque.cpp
//  sDeque
//
//  Created by Alexis Benter on 3/13/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

#include "sDeque.h"
#include <iostream>

//Constructor
Deque::Deque()
{
    queue = new std::string[origSize];
    numElements = 0;
    sizeQueue = origSize;
    front = -1;
    back = -1;
    
}

//Queue automatically doubles when the number of elements is at full capacity
void Deque::growArray(){
    
    std::string *newArray = new std::string[sizeQueue*2];
    
    int i, j;
    while(i != back) {
        newArray[j] = queue[i];
        i = (i+1)%sizeQueue;
        j++;
    }
    newArray[j] = queue[back];
    sizeQueue = sizeQueue*2;
    front=0;
    back = j;
    delete []queue;
    queue = newArray;
}



//Queue automatically shrinks to half it's size when it is less than 1/4 full and greater than the minimum size of 8
void Deque::shrinkArray()
{
    int newSize = 0;
    if(sizeQueue/2 < 8) {
        newSize = 8;
    } else {
        newSize = sizeQueue/2;
    }
    std::string *newArray = new std::string[newSize];
    int i,j;
    i=front;
    j=0;
    while(i =! back) {
        newArray[j]=queue[i];
        i=(i+1)%sizeQueue;
        j++;
    }
    newArray[j]=queue[back];
    sizeQueue = newArray;
    front  = 0;
    back = j;
    
    delete []queue;
    queue = newArray;
}

//Deconstructor
Deque::~Deque ()
{
    delete []queue;
}

//Inserts element at the front of the queue.
void Deque::push_front(std::string item)
{
    if(numElements == sizeQueue) {
        growArray();
        
    }
    
    if (empty())
    {
        back = 0;
        front = 0;
        queue[0]=item;
        
    } else {
        front=(front-1+sizeQueue)%sizeQueue;
        queue[front]=item;
        
        
    }
    numElements++;
}


// Deletes element at the front of the queue.
std::string Deque::pop_front()
{
    if (empty()) {
        return "";
    }
    if (numElements <= sizeQueue*0.25) {
        shrinkArray();
    }
    std::string x;
    x=queue[front];
    if (back==front) {
        front = -1;
        back = -1;
    }
    else
        front=(front+1)%sizeQueue;
    numElements--;
    return(x);
}

// Inserts element at the back of the queue
void Deque::push_back(std::string item)
{
    if(numElements == sizeQueue) {
        growArray();
    }
    
    if(empty()) {
        back = 0;
        front = 0;
        queue[0]=item;
    }
    else
    {
        back=(back+1)%sizeQueue;
        queue[back]=item;
    }
    numElements++;
}



// Deletes the element at the back of the queue.
std::string Deque::pop_back()
{
    if(empty()) {
        return "";
        
    }
    if (numElements <= sizeQueue*0.25) {
        shrinkArray();
    }
    
    std::string x;
    x=queue[back];
    if(back==front) {
        front = -1;
        back=-1;
    }
    else
        back=(back-1+sizeQueue)%sizeQueue;
    numElements--;
    return(x);
}

//Returns number of elements in the queue.
int Deque::size() {
    return sizeQueue;
}

//Tells whether the queue is empty or not.
bool Deque::empty() {
    if (numElements == 0) {
        return true;
    }
    
    return false;
}

std::string Deque::toStr()
//concatenates the contents of the queue from front to back into a return string with each string item followed by a new line character in the return string
{
    if (empty()) {
        return "";
    }
    
    int i;
    i=front;
    std::string q;
    while (i != back) {
        q += queue[i] + "\n";
        i=(i+1)%sizeQueue;
    }
    q += queue[back] + "\n";
    return q;
    
};