#!/bin/bash

echo "compiling"
exe='./bTree'

if make; then
	echo "Looking for bTree..."
	if [ -f $exe ]; then
		echo "Found bTree"
	else
		echo "Executable bTree not Found.Return the assignment to the student and ask them to resubmit!!"
		exit 1
	fi
else
	echo "Makefile gave an error. Return the assignment to the student and ask them to resubmit!!"
	exit 1
fi

Total_Score=0


echo "Running Tests..."
$exe <TC1.txt >Res1.txt
$exe <TC2.txt >Res2.txt
$exe <TC3.txt >Res3.txt
$exe <TC4.txt >Res4.txt
$exe <TC5.txt >Res5.txt
$exe <TC6.txt >Res6.txt
$exe <TC7.txt >Res7.txt
$exe <TC8.txt >Res8.txt
$exe <TC9.txt >Res9.txt
$exe <TC10.txt >Res10.txt
$exe <TC11.txt >Res11.txt
$exe <TC12.txt >Res12.txt
$exe <TC13.txt >Res13.txt
$exe <TC14.txt >Res14.txt
$exe <TC15.txt >Res15.txt
$exe <TC16.txt >Res16.txt
$exe <TC17.txt >Res17.txt
$exe <TC18.txt >Res18.txt
$exe <TC19.txt >Res19.txt
$exe <TC20.txt >Res20.txt
$exe <TC21.txt >Res21.txt
$exe <TC22.txt >Res22.txt

difference1=$(diff -b -B -E Res1.txt OP1.txt)
difference2=$(diff -b -B -E Res2.txt OP2.txt)
difference3=$(diff -b -B -E Res3.txt OP3.txt)
difference4=$(diff -b -B -E Res4.txt OP4.txt)
difference5=$(diff -b -B -E Res5.txt OP5.txt)
difference6=$(diff -b -B -E Res6.txt OP6.txt)
difference7=$(diff -b -B -E Res7.txt OP7.txt)
difference8=$(diff -b -B -E Res8.txt OP8.txt)
difference9=$(diff -b -B -E Res9.txt OP9.txt)
difference10=$(diff -b -B -E Res10.txt OP10.txt)
difference11=$(diff -b -B -E Res11.txt OP11.txt)
difference12=$(diff -b -B -E Res12.txt OP12.txt)
difference13=$(diff -b -B -E Res13.txt OP13.txt)
difference14=$(diff -b -B -E Res14.txt OP14.txt)
difference15=$(diff -b -B -E Res15.txt OP15.txt)
difference16=$(diff -b -B -E Res16.txt OP16.txt)
difference17=$(diff -b -B -E Res17.txt OP17.txt)
difference18=$(diff -b -B -E Res18.txt OP18.txt)
difference19=$(diff -b -B -E Res19.txt OP19.txt)
difference20=$(diff -b -B -E Res20.txt OP20.txt)
difference21=$(diff -b -B -E Res21.txt OP21.txt)
difference22=$(diff -b -B -E Res22.txt OP22.txt)

if [ ! -z "$difference1" ]; then
   echo "Test Case 1 Failed: Given test case 1"
else
	echo "Test 1 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference2" ]; then
   echo "Test Case 2 Failed: Given test case 2"
else
	echo "Test 2 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference3" ]; then
   echo "Test Case 3 Failed: toString a node with 2 elements"
else
	echo "Test 3 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference4" ]; then
   echo "Test Case 4 Failed: toString a size 5 B tree with 4 elements"
else
	echo "Test 4 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference5" ]; then
   echo "Test Case 5 Failed: Test case 1 with toString"
else
	echo "Test 5 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference6" ]; then
   echo "Test Case 6 Failed: toString with 4 elements (size 3)"
else
	echo "Test 6 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference7" ]; then
   echo "Test Case 7 Failed: split -> delete -> toString"
else
	echo "Test 7 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference8" ]; then
   echo "Test Case 8 Failed: testing find on a node that has not split"
else
	echo "Test 8 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference9" ]; then
   echo "Test Case 9 Failed: inserting then deleting from left (uses find)"
else
	echo "Test 9 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference10" ]; then
   echo "Test Case 10 Failed: inserting then deleting from left/middle (uses find/toString)"
else
	echo "Test 10 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference11" ]; then
   echo "Test Case 11 Failed: inserting then deleting from right (uses find/toString)"
else
	echo "Test 11 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference12" ]; then
   echo "Test Case 12 Failed: basic delete"
else
	echo "Test 12 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference13" ]; then
   echo "Test Case 13 Failed: inserts/deletes and finds"
else
	echo "Test 13 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference14" ]; then
   echo "Test Case 14 Failed: Adding to left side of tree (uses find)"
else
	echo "Test 14 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference15" ]; then
   echo "Test Case 15 Failed: Adding to left-middle of tree (uses find)"
else
	echo "Test 15 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference16" ]; then
   echo "Test Case 16 Failed: Adding to right-middle of tree"
else
	echo "Test 16 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference17" ]; then
   echo "Test Case 17 Failed: Adding to right of tree"
else
	echo "Test 17 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference18" ]; then
   echo "Test Case 18 Failed: small numbers of inserts, deletes and finds without much splitting"
else
	echo "Test 18 Passed"
	Total_Score=$((Total_Score+2))
fi

if [ ! -z "$difference19" ]; then
   echo "Test Case 19 Failed: small numbers of inserts deletes with a toString"
else
	echo "Test 19 Passed"
	Total_Score=$((Total_Score+2))
fi

echo "--------------------------"
echo "Comprehensive test cases"
echo "--------------------------"

if [ ! -z "$difference20" ]; then
   echo "Test Case 20 Failed: comprehensive testing (inserts and finds)"
else
	echo "Test 20 Passed"
	Total_Score=$((Total_Score+4))
fi

if [ ! -z "$difference21" ]; then
   echo "Test Case 21 Failed: comprehensive testing (inserts and toString)"
else
	echo "Test 21 Passed"
	Total_Score=$((Total_Score+4))
fi

if [ ! -z "$difference22" ]; then
   echo "Test Case 22 Failed: comprehensive testing (inserts, toString, deletes, and finds)"
else
	echo "Test 22 Passed"
	Total_Score=$((Total_Score+4))
fi

rm Res*
echo "Total Score = $Total_Score"
