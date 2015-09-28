//
//  main.cpp
//  hashtable
//
//  Created by Alexis Benter on 3/24/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "hashtable.h"

using namespace std;

int main(int argc, const char * argv[])
{

int tableSize;
    
        //first integer inputted defined the size of the table
        cin >> tableSize;
        
        HashTable* table = new HashTable(tableSize);
        
        int opCode = -1;
        string key;
    
        //the input afterwards is a code to insert or search, followed by the string
        while (opCode != 0) {
            cin >> opCode;
            cin >> key;
            
            //inserts string into the hashtable
            if (opCode == 1) {

                    table->insert(key);
            }
            
            //searches for string in the hashtable and returns yes or no
            else if(opCode == 2){
                    if (table->searchKey(key)) {
                        cout << "Yes\n";
                    } else {
                        cout << "No\n";
                    }
            }

           
        }
};
  





