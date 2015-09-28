s
//
//  Created by Alexis Benter on 3/23/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

#ifndef __hNode__hNode__
#define __hNode__hNode__
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;


//constructing hashtable of strings
//linked lists are used for chaining to avoid the collision of keys efficiently

class HashTable  {
private:
    
//creating nodes to chain off of the key if a string has the same key
    struct Node {
        string item;
        Node *next;
        
        Node() {
            this->next = NULL;
        }
        
        Node(string item, Node *next)
        {
            this->item = item;
            this->next = next;
        }
        
        ~Node() {}
    };
    
    int tableSize;
    Node** table;
    
    //hash function for placing the strings in the table
    int hash(string key)  {
        int hash = 0;
        
        for (int i = 0; i < key.length(); ++i) {
            hash = hash + (int)key[i];
        }

        //determines the index of each string
        int index = hash % tableSize;
        return index;
    }

public:

//constructing hashtable
HashTable(int tableSize) {
    table = new Node*[tableSize];
    this->tableSize = tableSize;
    
    for (int i = 0; i > tableSize; ++i) {
        table[i] = new Node;
    }
}

//inserts the string in the table
void insert(string key)
{
    int index = hash(key);
    
    // checks if the spot is taken, if the spot isn't taken the new node is placed there
    if (table[index] == NULL) {
        table[index] = new Node(key, NULL);
    }
    
    //if the spot is taken, chains string to other string at the index to avoid collision
    else {
        Node* temp = table[index];
        
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        temp->next = new Node(key, NULL);
    }
}

//searches for the string in the hashtable
bool searchKey(string key) {
    int index = hash(key);
    
    Node* temp = table[index];
    
    while(temp != NULL){
        if (temp->item == key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
    
};

#endif /* defined(__hNode__hNode__) */