#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool linearSearch(int input, vector<int> array, int size)
{
// Do a linear search through the newly sorted array going through every number consectively and checking if the input matches
	for(int i = 0; i < size; ++i)
	{
		if(input == array[i]) {
            printf("Yes\n");
            return true;
        }
	}
    
	// If the input was not found in the array, return false
    printf("No\n");
	return false;
}
//binary search method through the array
//divides the array in half, checks if the midpoint is greater or less, and searches up or down one from the previous midpoint accordingly
bool binarySearch(int input, vector<int> array, int size)
{
	int frontIndex = 0;
	int backIndex = size - 1;
	int midpoint;
    
	while (frontIndex < backIndex)
	{
		midpoint = (frontIndex + backIndex)/2;
        
        if (input == array[midpoint])
        {
            printf("Yes\n");
            return true;
        }
		else if (input > array[midpoint])
		{
			frontIndex = midpoint + 1;
		}
		else
		{
			backIndex = midpoint;
		}
	}
    
	if (input == array[frontIndex])
    {
        printf("Yes\n");
        return true;
    }
	else
	{
        printf("No\n");
		return false;
	}
}

int main(int argc, char* argv[])
{
    vector<int> ints;
    vector<int> searches;
    int N,S;
    
    ifstream file;
    file.open(argv[0]);
    
    if (file.is_open()) {
        cin >> N;
        cin >> S;
        
        int temp;
        for (int i =0; i < N; ++i) {
            cin >> temp;
            ints.push_back(temp);
        }
        
        for (int i =0; i < S; ++i) {
            cin >> temp;
            searches.push_back(temp);
        }
    }
    
    clock_t clk;
    sort(ints.begin(), ints.end());
    
    //printf("Linear Search:\n");
    clk = clock();
    for (int i = 0; i < S; ++i) {
        linearSearch(searches[i], ints, N);
    }
    clk = clock() - clk;
    //printf("Search time: %f\n\n\n", ((float)clk)/CLOCKS_PER_SEC);
    
    //printf("Binary Search:\n");
    clk = clock();
    for (int i = 0; i < S; ++i) {
        binarySearch(searches[i], ints, N);
    }
    clk = clock() - clk;
    //printf("Search time: %f\n\n\n", ((float)clk)/CLOCKS_PER_SEC);
    
    return 0;
}





