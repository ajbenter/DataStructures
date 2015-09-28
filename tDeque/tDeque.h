#include <iostream>
#include <stdexcept>
#include <new>
#include <string>
#include <sstream>

using namespace std;

template< typename T > class Deque {
    //Array holding queue
    T* queue;
    // Number of elements in the queue
    int numElements;
    // Size of the queue
    int sizeQueue;
    // Front of the queue
    int front;
    // Back of the queue
    int back;
    // Original Size
    static const int origSize = 8;

    //the array shrinks when it is 1/4 full by decreasing half the size and is used in the pop front and pop back methods
    void shrinkArray() {
        try{
            int newSize = 0;
    	    if(sizeQueue/2 < 8) {
        	newSize = 8;
    	    } else {
        	newSize = sizeQueue/2;
    	    }
    	    T *newArray = new T[newSize];
    	    int i,j;
                i=front;
                j=0;
    	    while(i != back) {
        	newArray[j]=queue[i];
        	i=(i+1)%sizeQueue;
        	j++;
    	    }
    	    newArray[j]=queue[back];
    	    sizeQueue = newSize;
	    front  = 0;
	    back = j;
    
	delete []queue;
   	    queue = newArray;
        }
        catch(exception &e){
            std::cerr << "bad_alloc caught: " << e.what() << endl;
            throw e;
        }
    }

    //the array doubles when it is full and is used in the push front and push back methods
    void growArray() {
        try{
            T *newArray = new T[sizeQueue*2];
    
    	    int i, j;
        	i=front;
       		j=0;
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
        catch (exception &e){
            std::cerr << "bad_alloc caught: " << e.what() << '\n';
            throw e;
        }
    }
    
public:

    Deque() {
        //variables defining the deque
        numElements = 0;
        sizeQueue = 8;
        queue = new T[sizeQueue];
        front = 0;
        back = 0;
    }

    ~Deque() {
        delete []queue;
    }

    //inserts an element at the front of the queue
    void pushFront(T item) {
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

    //inserts an element at the back of the queue
    void pushBack(T item) {
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

    //Deletes the element at the front of the queue.
    T popFront() {
        if (empty()) {
            throw std::runtime_error ("the deque is empty");
        }
        if (numElements <= sizeQueue*0.25) {
            shrinkArray();
        }
        T str;
        str=queue[front];
        if (back==front) {
            front = -1;
            back = -1;
        }
        else
            front=(front+1)%sizeQueue;
        numElements--;
        return(str);
    }
    
    //Deletes the element at the back of the queue
    T popBack() {
        if(empty()) {
            throw std:: runtime_error ("the deque is empty");
        
        }
        if (numElements <= sizeQueue*0.25) {
            shrinkArray();
        }
    
        T str;
        str=queue[back];
        if(back==front) {
            front = -1;
            back=-1;
        }
        else
            back=(back-1+sizeQueue)%sizeQueue;
        numElements--;
        return(str);
    }
    //Returns the size queue.
    int size() {
        return sizeQueue;
    }
    //Tells whether the queue is empty or not.
    bool empty() {
        if (numElements == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    //puts together the queue from the front to the back and returns the queue
    string toStr() {
    	stringstream ss;

        if (empty()) {
            return "";
        }
    
        int i;
        i=front;
        string q;

        while (i != back) {

            ss<<queue[i]<<"\n";
            i=(i+1)%sizeQueue;
        }
        	ss<<queue[back]<<"\n";
        	q = ss.str();

        return q;
    }
};
