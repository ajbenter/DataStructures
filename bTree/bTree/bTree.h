#ifndef __bTree__bTree__
#define __bTree__bTree__

#include <iostream>
#include <vector>
#include <stdexcept>
#include <new>
#include <string>
#include <sstream>



using namespace std;
//classbTree
class bTree {
    
//structing node
    struct node {
        string* keys; //array of keys
        int r; //range for number of keys
        node** children; //array of children pointers
        int numKeys; //current number of keys
        bool leaf; //true if node is a leaf
       
        //constructor for bTree node
        node(int minDegree, bool nLeaf) {
            
            r = minDegree;
            leaf = nLeaf;
            
            keys = new string[2*r-1];
            children = new node *[2*r];
            
            //initializes number of keys to be 0
            numKeys = 0;
        }
        
        //traverses through all nodes of subtree rooted in rooted with this node
        void traverse() {
            int i;
            for (i = 0; i < numKeys; i++)
            {
                // traverse through subtree
                if (leaf == false)
                    children[i]->traverse();
                cout << keys[i] << "\n";
                
            }
            
            //print subtree with last child
            if (leaf == false) {
                children[i]->traverse();
            }
        }
        
        //finds if key exists in the tree
        node* find(string key)
        {
            //change first letter of key to uppercase
            int k = toupper(key.at(0));
            
            //finds the key is greater than k
            int i = 0;
            while (i < numKeys && k > toupper(keys[i].at(0)))
                i++;
            
            //if it is equal, return this node
            if (keys[i].compare(key)==0)
                return this;
            
            if (leaf == true)
                return NULL;
            
            // go to child to find key
            return children[i]->find(key);
        }
        
    //helper method of insert to insert a new key in this node when root is not full
    void insertHelper(string key)
        
        {
            //get value of uppercase letter for insertion
            int k = toupper(key.at(0));
            
            //initialize index as the right most element
            int i = numKeys-1;
            
            
            if (leaf == true)
            {
                //if node is a leaf - find index of new key to be inserted and move all greater keys ahead
                while (i >= 0 && toupper(keys[i].at(0)) > k)
                {
                    keys[i+1] = keys[i];
                    i--;
                }
                
                //insert new key at proper index and increase number of keys by 1
                keys[i+1] = key;
                numKeys = numKeys+1;
            }
            else
            {
                //find appropriate child to have new key
                while (i >= 0 && toupper(keys[i].at(0)) > k)
                    i--;
                
                //checks if child node is full
                if (children[i+1]->numKeys == 2*r-1)
                {
                    //split if full
                    split(i+1, children[i+1]);
                    
        
                    //middle key of child node goes up and node is splitted in to 2 where 1 is going to have new key
                    if (toupper(keys[i+1].at(0)) < k)
                        i++;
                }
                //determines which is going to have new key
                children[i+1]->insertHelper(key);
            }
        }
        
        void split(int i, node *a)
        {
            //creates new node
            node *b = new node(a->r, a->leaf);
            b->numKeys = r - 1;
            
            //(r-1) keys from a to b
            for (int j = 0; j < r-1; j++)
                b->keys[j] = a->keys[j+r];
            
            //last r children from a to b
            if (a->leaf == false)
            {
                for (int j = 0; j < r; j++)
                    b->children[j] = a->children[j+r];
            }
            
            //reduces number of keys in a
            a->numKeys = r - 1;
            
            //creates space for new child
            for (int j = numKeys; j >= i+1; j--)
                children[j+1] = children[j];
            
            children[i+1] = b;
            
            // A key of a moves to this node and all other nodes move one space ahead
            for (int j = numKeys-1; j >= i; j--)
                keys[j+1] = keys[j];
            
            //middle key of a to this node and key count goes up by 1
            keys[i] = a->keys[r-1];
            numKeys = numKeys + 1;
        }
        
        //returns the index of the first key that is greater than k
        int findKey(string key)
        
        {
            //changes first letter of string to capital and gives it integer value for comparison
            int k = toupper(key.at(0));
            
            int index=0;
            while (index<numKeys && toupper(keys[index].at(0)) < k)
                ++index;
            return index;
        }
        
        //main function to delete a key
        void delete_key(string key)
        {
            //changes first letter of string to capital and gives it integer value for comparison
            int k = toupper(key.at(0));
            
            //finds the key to delete
            int index = findKey(key);
            
            //checks if key to delete is present in this node
            if (index < numKeys && (index<numKeys && toupper(keys[index].at(0))) == k)
            {
                
                //if node is a leaf node call dFromLeaf - if not dFromNonLeaf
                if (leaf)
                    dFromLeaf(index);
                else
                    dFromNonLeaf(index);
            }
            else
            {
                
                //key was not found in the tree to delete
                if (leaf)
                {
                    cout << "Key not found\n";
                    return;
                }
                
                //checks if key is present in the subtree
                bool keyPresent = ( (index==numKeys)? true : false );
                
                //if the right child has less than r keys then fill that child
                if (children[index]->numKeys < r)
                    fill(index);
                
                //if the child was merged then recurse to the (index-1) child for deletion if not then (index-1)
                if (keyPresent && index > numKeys)
                    children[index-1]->delete_key(key);
                else
                    children[index]->delete_key(key);
            }
            return;
        }
        
        //removes the key present in the index position in this node which is a leaf node
        void dFromLeaf (int index)
        {
            for (int i=index+1; i<numKeys; ++i)
                keys[i-1] = keys[i];
            
            //reduces count of keys after deletion
            numKeys--;
            
            return;
        }
        
        //removes the key present in the index position in this node which is not a leaf node
        void dFromNonLeaf(int index)
        {
            string k = keys[index];
            
            //if child that is predeccesor child at the index has at least r keys - replace key by predecessor and recursively delete predecessor in index
            if (children[index]->numKeys >= r)
            {
                string predecessor = getPredecessor(index);
                keys[index] = predecessor;
                children[index]->delete_key(predecessor);
            }
          
            //if children at index have less than r keys - exammine children at index+1 - find successor and replace by k
            else if  (children[index+1]->numKeys >= r)
            {
                string successor = getSuccessor(index);
                keys[index] = successor;
                //recursively delete
                children[index+1]->delete_key(successor);
            }
            
            // If both places have less than r keys then merge the two and then recursively delete
            else
            {
                merge(index);
                children[index]->delete_key(k);
            }
            return;
        }
        
        string getPredecessor(int index)
        {
            //moves to the right most node until a leaf is reached
            node *c =children[index];
            while (!c->leaf)
                c = c->children[c->numKeys];
            
            //last key of the leaf
            return c->keys[c->numKeys-1];
        }
        
        string getSuccessor(int index)
        {
            //moves to the left most node starting from children[index+1] until leaf is reached
            node *c = children[index+1];
            while (!c->leaf)
                c = c->children[0];
            
            //return first key of the leaf
            return c->keys[0];
        }
        
        //fills up the child node
        void fill(int index)
        
        {
            //if previous child have more then r-1 keys borrow from that child to fill
            if (index!=0 && children[index-1]->numKeys>=r)
                takePrevious(index);
            
            //if not, check the next child to see if they have more than r-1 keys and borrow from that child
            else if (index!=numKeys && children[index+1]->numKeys>=r)
                takeNext(index);
            
            //merge children[index] with the appropriate sibling
            else
            {
                if (index != numKeys)
                    merge(index);
                else
                    merge(index-1);
            }
            return;
        }
        
        //borrows from the previous node and place it in the node at the index
        void takePrevious(int index)
        {
            
            node *child=children[index];
            node *sib=children[index-1];
            
            //moving all the keys of child node at index one step ahead
            for (int i=child->numKeys-1; i>=0; --i)
                child->keys[i+1] = child->keys[i];
            
            //if child is not a leaf move all keys on spot ahead
            if (!child->leaf)
            {
                for(int i=child->numKeys; i>=0; --i)
                    child->children[i+1] = child->children[i];
            }
            
            //moves childs first key one spot back
            child->keys[0] = keys[index-1];
            
            //moving siblings last child to children[index] first child
            if (!leaf)
                child->children[0] = sib->children[sib->numKeys];
            
            //moves keys from sibling to the parent
            keys[index-1] = sib->keys[sib->numKeys-1];
            
            child->numKeys += 1;
            sib->numKeys -= 1;
            
            return;
        }
        
        void takeNext(int index)
        {
            
            node *child=children[index];
            node *sib=children[index+1];
            
            // keys[index] is inserted as the last key in children[index]
            child->keys[(child->numKeys)] = keys[index];
            
            //siblings first child is inserted in the last child
            if (!(child->leaf))
                child->children[(child->numKeys)+1] = sib->children[0];
            
            //first key from sib is inserted into keys[index]
            keys[index] = sib->keys[0];
            
            // Moving all keys in sib one step behind
            for (int i=1; i<sib->numKeys; ++i)
                sib->keys[i-1] = sib->keys[i];
            
            //moves child pointers one spot behind
            if (!sib->leaf)
            {
                for(int i=1; i<=sib->numKeys; ++i)
                    sib->children[i-1] = sib->children[i];
            }
            
            //increases and decreases key count
            child->numKeys += 1;
            sib->numKeys -= 1;
            
            return;
        }
        
        
        //merges the index child with the index+1 child of the node
        void merge(int index)
        {
            node *child = children[index];
            node *sib = children[index+1];
            
            //pulls key and inserts it in position(r-1) to merge
            child->keys[r-1] = keys[index];
            
            //copies keys from children[index] to children[index+1]
            for (int i=0; i<sib->numKeys; ++i)
                child->keys[i+r] = sib->keys[i];
            
            //copies from children[index+1] to children[index]
            if (!child->leaf)
            {
                for(int i=0; i<=sib->numKeys; ++i)
                    child->children[i+r] = sib->children[i];
            }
            
            //fills the gap created by moving around keys
            for (int i=index+1; i<numKeys; ++i)
                keys[i-1] = keys[i];
            
            //moves child pointers one step before
            for (int i=index+2; i<=numKeys; ++i)
                children[i-1] = children[i];
            
            //updates the key count of child
            child->numKeys += sib->numKeys+1;
            numKeys--;
            delete(sib);
            return;
        }
    };

    node* root;
    int r;
    stringstream ss;
    
    
    
    
public:
    
    //constructs the bTree
    bTree(int x) {
        root = NULL;
        r = x;
    }
    
    void traverse() {
        if (root != NULL) root->traverse();
    }
    
    node* find(string k, string &value) {
        return (root == NULL)? NULL : root->find(k);
    }
    
    void insert(string k, string value)
    {
        // If tree is empty
        if (root == NULL)
        {
            //assigns memory for root
            root = new node(r, true);
            root->keys[0] = k;  //inserts key
            root->numKeys = 1;  //updates number of key for root
        }
        else
        {
            //if root is full tree grows dynamicallu
            if (root->numKeys == 2*r-1)
            {
                node *s = new node(r, false);
                
                //make old root as child for new root
                s->children[0] = root;
                
                //splits old root
                s->split(0, root);
                
                //new root has 2 hildren - one gets new key
            
                int firstKey = s->keys[0].at(0);
                int insertion = k.at(0);
                
                
                //inserts string appropriately according to integer value of first letter alphabetically
                firstKey = toupper(firstKey);
                insertion = toupper(insertion);
                
                int i = 0;
                if (firstKey < insertion)
                    i++;
                s->children[i]->insertHelper(k);
                
                //change root
                root = s;
            }
            else
                //if root is not full - call insert helper method
                root->insertHelper(k);
        }
    }
    
    void delete_key(string k)
    {
        if (!root)
        {
            cout << "The tree is empty\n";
            return;
        }
        
        //deletes key from root
        root->delete_key(k);
        
        //if root has 0 keys - make first child as the new root otherwise set to NULL
        if (root->numKeys==0)
        {
            node *temp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->children[0];
            
            //deletes old root
            delete temp;
        }
        return;
    }
    
    //prints the tree
    string toStr() {
        ss.str(" ");
        traverse();
        
        return "";
    }   
};


#endif

