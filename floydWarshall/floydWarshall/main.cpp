//
//  main.cpp
//  floydWarshall
//
//  Created by Alexis Benter on 4/23/15.
//  Copyright (c) 2015 Alexis Benter. All rights reserved.
//

//
//  main.h
//  floyd
//
//  Created by Elana  on 4/23/15.
//  Copyright (c) 2015 Elana . All rights reserved.
//

#ifndef floyd_main_h
#define floyd_main_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


// Floyd's All pairs shortest path algorithm (O (n^3) )
// input is adjacency matrix output is matrix of shortest paths
// C is the adjacency matrix
// n is the order of the square matrix
// A is the all pairs shortest paths matrix
// we assume that A is allocated by the caller
int ComputeFloydAPSP(int *C, int n, int *e, string* s)
{
    
    int i,j,k;
    
    // set all connected positions to 1
    // and all unconnected positions to infinity
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if ( *(C+i*n+j) == 0)
            {
                *(e+i*n+j) = 999999999;    // Does this look like infinity?
            }
            else
            {
                *(e+i*n+j) = 1;
                char sz[3]="";
                sprintf(sz,"%d",j+1);
                s[i*n+j]=sz;
            }
        }
    }
    
    // set the diagonals to zero
    for (i=0; i<n; i++)
    {
        *(e+i*n+i) = 0;
    }
    
    // for each route via k from i to j pick any better routes and
    // replace A[i][j] path with sum of paths i-k and j-k
    for (k=0; k<n; k++)
    {
        for (i=0; i<n; i++)
        {
            for (j=0; j<n; j++)
            {
                if ( *(e+i*n+k) + *(e+k*n+j) < *(e+i*n+j) )
                {
                    *(e+i*n+j) = *(e+i*n+k)+ *(e+k*n+j);
                    
                    s[i*n+j]=s[i*n+k]+","+s[k*n+j];
                }
            }
        }
    }
    
    return 0;
}

#endif
