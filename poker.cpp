// Poker with no GUI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> 
#include <sstream> 
#include <thread>
#include <future>
//#include "Form1.h"
#include <math.h>

//#define DEBUG 1
//#include "arr.cpp"

//int calculate(int numhands, int hand1, int hand2);
using namespace std;
const int cardz[] = {
	403,404,405,406,407,408,409,410,411,412,413,414,
	302,303,304,305,306,308,309,310,311,312,313,314,
	202,203,204,205,206,207,208,209,210,211,212,213,
	102,103,104,105,106,107,108,109,110,111,112,113
};
const int cards[] = {
	402,403,404,405,406,407,408,409,410,411,412,413,414,
	302,303,304,305,306,308,309,310,311,312,313,314,314,
	202,203,204,205,206,207,208,209,210,211,212,213,214,
	102,103,104,105,106,107,108,109,110,111,112,113,114
};
const int cardorder[] = {
	414,314,214,114,413,313,213,113,412,312,212,112,
	411,311,211,111,410,310,210,110,409,309,209,109,
	408,308,208,108,407,307,207,107,406,306,206,106,
	405,305,205,105,404,304,204,104,403,303,203,103,402,302,202,102
};

int streval[11][7];
int fleval[11][7];
int eveval[11][7];
int hands = 0;
int ard = 0;
float tiex = 0;
float winx = 0;
float equity = 0;

//-----------------------------------------------------------
//static int returner[7];

int dealtsize = 0;
int dealtsize2 = 0;
int dealt[29] = { 0 };
int card[25] = { 0 };
int flop[5] = { 0 };
//static int* current = { 0 };
//int current[7] = { 0 };
//int straight[7] = { 0 };
//int flush[7] = { 0 };
int handv[11] = { 0 };
int handvcompare[11] = { 0 };

/*

int fast_mod(const int input) {
	//return input % 100;

	if (((input - 100) > 0) && ((input - 100) < 15)) {
		return input - 100;
	}
	else if (((input - 200) > 0) && ((input - 200) < 15)) {
		return input - 200;
	}
	else if (((input - 300) > 0) && ((input - 300) < 15)) {
		return input - 300;
	}
	else if (((input - 400) > 0) && ((input - 400) < 15)) {
		return input - 400;
	}

}


void comparearrays(int arr1[], int arr2[]) {
	int i = 0;
	while (i < 7) {
		//cout << "comparing " << arr1[i] << " to " << arr2[i] << endl;
		if (arr1[i] != arr2[i]) {
			cout << "NO MATCH FOR YOU" << endl;
		}
		i++;
	}
}

*/
int getpoz(int arry[], int num, int num2) {
	int j = -1;
	for (int i = 0; i < num2; i++) {
		if (arry[i] == num) {
			j = num;
		}
	}
	return j;

}

/*
int soa(int arrz[])
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (arrz[i] == -1)
		{
			return i;
		}
		if (arrz[i] == 0)
		{
			return i;
		}

	}
	return 0;
}
*/

//move(returned, poopy, i, 0)

int* move(const int arrz[], const int mvalue, const int rlocation, const int mlocation) {
	static int uselessarray[7] = { 0 };
	uselessarray[0] = arrz[0];
	uselessarray[1] = arrz[1];
	uselessarray[2] = arrz[2];
	uselessarray[3] = arrz[3];
	uselessarray[4] = arrz[4];
	uselessarray[5] = arrz[5];
	uselessarray[6] = arrz[6];

	static int returnarray[7];
	//returnarray[0] = 1;
	int i = 0; int j = 0;

	
	
	for (i = 0; i < 7; i++) {
		if (i == mlocation) {
			j++;
			returnarray[mlocation] = mvalue;
		}
		if (i == rlocation) {
		}
		else {
			returnarray[j] = uselessarray[i];
			//returnarray[j] = arrz[i];
			j++;
		}
		
	}
	return returnarray;
}
/*
void move(int arrz[], const int mvalue, const int rlocation, const int mlocation)
{
	// Get a copy of the value to "move"
	int value = arrz[mlocation];

	// Move (part) of the array one step to the right
	memmove(&arrz[rlocation + 1], &arrz[rlocation], (mlocation - rlocation) * sizeof(int));

	// And copy the value to its destination place
	arrz[rlocation] = value;
}

int* remove(int arrz[], const int a)
{
	static int returner[7];
	//int returner[7];
	int j = 0;
	for (int i = 0; i < 7; i++)
	{
		if (i == a)
		{
			j++;
		}
		returner[i] = arrz[j];
		j++;

	}

	//int* pointer;
	//pointer = returner;
	return returner;
}
*/
/*
int* insert(int arrz[], const int a, const int b)
{
	static int returner[7];
	//int returner[7];
	int j = 0;
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		if (i == b)
		{
			returner[i] = a;
		}
		else
		{
			returner[i] = arrz[j];
			j++;
		}
	}
	//int* pointer;
	//pointer = returner;
	return returner;
}
*/

int* Order4(int returned[]) {
	int i = 0; int j = 0; int k = 0;
	int returner[7] = { 0 };

	while (i < 52) {
		j = 0;
		while (j < 7) {
			//cout << "returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;

			cout << "comparing " << returned[j] << " with " << cardorder[i] << endl;
			if (returned[j] == cardorder[i]) {
				cout << "found a match with " << returned[j] << endl;
				returner[k] = cardorder[i];
				k++;
				j = 7;
			}
			j++;
		}
		i++;
	}
	//cout << " returner is: " << returner[0] << " " << returner[1] << " " << returner[2] << " " << returner[3] << " " << returner[4] << " " << returner[5] << " " << returner[6] << endl;

	return returner;
}

int* Order3(int returned[]) {
	int maskless[7] = { 0 };
	int* masklesspointer = 0;

	int i = 0; int masker; int j = 0;
	int poopy; int poopy1;
	while (i < 7) {
		masker = returned[i] % 100;
		maskless[i] = masker;
		i++;
	}
	masklesspointer = maskless;
	i = 0;
	while (i < 6) {
		//cout << "iteration number "<<i<<" returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
		poopy = masklesspointer[i];
		poopy1 = masklesspointer[i + 1];
		if (poopy < poopy1) {
			//masklesspointer = remove(masklesspointer, i);
			//masklesspointer = insert(masklesspointer, poopy, i + 1);
			i = -1;
		}
		i++;
	}

	//combine maskless with returned
	//cout << " MASKLESSpoINTER is: " << masklesspointer[0] << " " << masklesspointer[1] << " " << masklesspointer[2] << " " << masklesspointer[3] << " " << masklesspointer[4] << " " << masklesspointer[5] << " " << masklesspointer[6] << endl;
	//cout << "----------" << endl;
	int returner[7] = { 0 };
	i = 0;
	while (i < 7) {
		poopy = masklesspointer[i];
		j = 0;
		while (j < 7) {
			//cout << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
			if ((poopy + 400 == returned[j]) || (poopy + 100 == returned[j]) || (poopy + 200 == returned[j]) || (poopy + 300 == returned[j])) {
				//cout << "poopy " << poopy << " found returned[j]" << returned[j] << endl;
				returner[i] = returned[j];
				returned[j] = 0;
				j = 7;
			}
			j++;
		}
		i++;

	}
	//cout << " returner is: " << returner[0] << " " << returner[1] << " " << returner[2] << " " << returner[3] << " " << returner[4] << " " << returner[5] << " " << returner[6] << endl;
	return returner;
}

int* Order2(int returned[]) {
	//static int returned[7];
	int i = 0;
	int poopy = 0; int poopy1 = 0;
	int subpoopy = 0; int subpoopy1 = 0;
	int temp = 0;
	while (i < 6) {
		//cout << "iteration number "<<i<<" returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
		poopy = returned[i];
		poopy1 = returned[i + 1];
		subpoopy = poopy % 100;
		//subpoopy = fast_mod(poopy);
		subpoopy1 = poopy1 % 100;
		//subpoopy1 = fast_mod(poopy1);
		if (subpoopy < subpoopy1) {

			temp = returned[i];
			returned[i] = returned[i + 1];
			returned[i + 1] = temp;

			//returned = remove(returned, i);


			//returned = insert(returned, poopy, i + 1);

			i = -1;
		}
		i++;
	}
	//cout <<" returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
	return returned;
}

int* Order(int cards[])
{

	static int returned[7];
	int i = 14; int j = 0; int pos = 0;
	int poopy; int subpoopy;
	while (i != 1)
	{
		j = 0;
		while (j < 7)
		{
			poopy = cards[j];
			//subpoopy = poopy % 100;
			if ((poopy - 100 == i) || (poopy - 200 == i) || (poopy - 300 == i) || (poopy - 400 == i))
				//if (subpoopy == i)
			{
				returned[pos] = poopy;
				pos++;
			}
			j++;
		}
		i--;
	}
	return returned;
}

int* Pairme2(int returned[]) {
	int i = 0; int temp = 0;
	bool trips = false; bool quads = false; bool pair = false; bool twopair = false; bool house = false;
	int poopy = 0; int poopy1 = 0; int poopy2 = 0; int poopy3 = 0;
	int subpoopy = 0; int subpoopy1 = 0; int subpoopy2 = 0; int subpoopy3 = 0;
	while (i < 6) {
		//cout << "iteration number "<<i<<" returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
		poopy = returned[i];
		poopy1 = returned[i + 1];
		subpoopy = poopy % 100;
		subpoopy1 = poopy1 % 100;

		if (i < 5)
		{
			poopy2 = returned[i + 2];
			subpoopy2 = poopy2 % 100;
		}
		else {
			poopy2 = 0;
			subpoopy2 = 0;
		}
		if (i < 4)
		{
			poopy3 = returned[i + 3];
			subpoopy3 = poopy3 % 100;
		}
		else {
			poopy3 = 0;
			subpoopy3 = 0;
		}
		if (subpoopy == subpoopy1) {
			//cout << poopy << " has a pair" << endl;
			if (subpoopy == subpoopy2) {
				//cout << poopy << " trip" << endl;
				if (subpoopy == subpoopy3) {
					//cout << poopy << " has a quad" << endl;
					//returned = remove(returned, i);
					//returned = insert(returned, poopy, 0);
					returned = move(returned, poopy, i, 0);
					returned = move(returned, poopy1, i + 1, 1);
					returned = move(returned, poopy2, i + 2, 2);
					returned = move(returned, poopy3, i + 3, 3);
					//move(returned,poopy,i,0)
					//returned = remove(returned, i + 1);
					//returned = insert(returned, poopy1, 1);
					//returned = remove(returned, i + 2);
					//returned = insert(returned, poopy2, 2);
					//returned = remove(returned, i + 3);
					//returned = insert(returned, poopy3, 3);
					i = 7;
				}
				else {
					if (trips == false) {
						//cout << poopy << " has a trips and no previous trips" << endl;
						//returned = remove(returned, i);
						//returned = insert(returned, poopy, 0);
						//returned = remove(returned, i + 1);
						//returned = insert(returned, poopy1, 1);
						//returned = remove(returned, i + 2);
						//returned = insert(returned, poopy2, 2);
						returned = move(returned, poopy, i, 0);
						returned = move(returned, poopy1, i + 1, 1);
						returned = move(returned, poopy2, i + 2, 2);
						if (pair == true) { house = true; }
						trips = true;
						i++;
					}
					else if (trips == true) {
						//cout << poopy << " has a second trip oooooo" << endl;
						//returned = remove(returned, i);
						//returned = insert(returned, poopy, 3);
						//returned = remove(returned, i + 1);
						//returned = insert(returned, poopy1, 4);
						returned = move(returned, poopy, i, 3);
						returned = move(returned, poopy1, i + 1, 4);
						i = 7;
					}

				}
			}
			else if ((pair == false) && (twopair == false) && (trips == false)) {
				//cout << pair << " has pair" << endl;
				//returned = remove(returned, i);
				//returned = insert(returned, poopy, 0);
				//returned = remove(returned, i + 1);
				//returned = insert(returned, poopy1, 1);
				//cout << "before move 1 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				returned = move(returned, poopy, i, 0);
				//cout << "before move 2 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				returned = move(returned, poopy1, i + 1, 1);
				//cout << "after both moves " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				pair = true;

			}
			else if ((pair == true) && (twopair == false) && (trips == false)) {
				//cout << "two pair processing" << endl;
				//cout << "before removed 1 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				//returned = remove(returned, i);
				//cout << "before insert 1 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				//returned = insert(returned, poopy, 2);
				//cout << "before remove 2 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				//returned = remove(returned, i + 1);
				//cout << "before insert 2 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				//returned = insert(returned, poopy1, 3);
				//cout << "before move 1 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				returned = move(returned, poopy, i, 2);
				//cout << "before move 2 " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				returned = move(returned, poopy1, i + 1, 3);
				twopair = true;

			}
			else if (trips == true && house == false) {
				//returned = remove(returned, i);
				//returned = insert(returned, poopy, 3);
				//returned = remove(returned, i + 1);
				//returned = insert(returned, poopy1, 4);

				returned = move(returned, poopy, i, 3);
				returned = move(returned, poopy1, i + 1, 4);
				house = true;
				//cout << "full house " << i << " returned is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
				//i = 7;

			}



		}

		i++;
	}
	//cout <<" returned2 is: " << returned[0] << " " << returned[1] << " " << returned[2] << " " << returned[3] << " " << returned[4] << " " << returned[5] << " " << returned[6] << endl;
	return returned;
}



int* Flushme(int cards[])
{
	int i = 0;
	int order[7] = { -1,-1,-1,-1,-2,-1,-1 };
	for (i = 0; i < 7; i++)
	{
		order[i] = cards[i];
	}
	int eval = 0;
	int poopy;
	int intpoopy = 0;
	int subpoopy;
	int so;
	static int flarr[6];
	int n = 0;
	while (n != 6) {
		flarr[n] = 0;
		n++;
	}
	//int plopy;
	int lhearts[] = { 0,0,0,0,0,0,0,0 };
	int* rhearts = lhearts;
	int lspades[] = { 0,0,0,0,0,0,0,0 };
	int* rspades = lspades;
	int lclubs[] = { 0,0,0,0,0,0,0,0 };
	int* rclubs = lclubs;
	int ldiamonds[] = { 0,0,0,0,0,0,0,0 };
	int* rdiamonds = ldiamonds;
	int fh = 69; int fs = 69; int fc = 69; int fd = 69;
	int hearts = 0; int spades = 0; int clubs = 0; int diamonds = 0;
	for (i = 0; i < 7; i++)
	{
		poopy = order[i];
		subpoopy = poopy / 100;
		//plopy = poopy % 100;
		//plopy = fast_mod(poopy);
		if (subpoopy == 1)
		{
			hearts++;
			//so = soa(lhearts);
			lhearts[hearts - 1] = poopy;
		}
		if (subpoopy == 2)
		{
			spades++;
			//so = soa(lspades);
			lspades[spades - 1] = poopy;
		}
		if (subpoopy == 3)
		{
			clubs++;
			//so = soa(lclubs);
			lclubs[clubs - 1] = poopy;
		}
		if (subpoopy == 4)
		{
			diamonds++;
			//so = soa(ldiamonds);
			ldiamonds[diamonds - 1] = poopy;
		}


	}
	if (hearts >= 5)
	{
		eval = 5; // flu
		flarr[0] = eval;
		flarr[1] = rhearts[0];
		flarr[2] = rhearts[1];
		flarr[3] = rhearts[2];
		flarr[4] = rhearts[3];
		flarr[5] = rhearts[4];
		i = 7;
		//flusz++;
		for (i = 0; i < hearts - 4; i++)
		{
			if (rhearts[i] == 114)
			{
				//so = soa(lhearts);
				lhearts[hearts] = 101;
				hearts++;
			}
			if (rhearts[i] - 1 == rhearts[i + 1] && rhearts[i] - 2 == rhearts[i + 2] && rhearts[i] - 3 == rhearts[i + 3] && rhearts[i] - 4 == rhearts[i + 4])
			{

				eval = 8; //str flu
				flarr[0] = eval;
				flarr[1] = rhearts[i];
				flarr[2] = rhearts[i + 1];
				flarr[3] = rhearts[i + 2];
				flarr[4] = rhearts[i + 3];
				flarr[5] = rhearts[i + 4];
				i = 7;

			}
		}

	}
	if (diamonds >= 5)
	{
		eval = 5; // flu
		flarr[0] = eval;
		flarr[1] = rdiamonds[0];
		flarr[2] = rdiamonds[1];
		flarr[3] = rdiamonds[2];
		flarr[4] = rdiamonds[3];
		flarr[5] = rdiamonds[4];
		i = 7;
		//flusz++;
		for (i = 0; i < diamonds - 4; i++)
		{
			if (rdiamonds[i] == 414)
			{
				//so = soa(ldiamonds);
				ldiamonds[diamonds] = 401;
				diamonds++;
			}
			if (rdiamonds[i] - 1 == rdiamonds[i + 1] && rdiamonds[i] - 2 == rdiamonds[i + 2] && rdiamonds[i] - 3 == rdiamonds[i + 3] && rdiamonds[i] - 4 == rdiamonds[i + 4])
			{

				eval = 8; //str flu
				flarr[0] = eval;
				flarr[1] = rdiamonds[i];
				flarr[2] = rdiamonds[i + 1];
				flarr[3] = rdiamonds[i + 2];
				flarr[4] = rdiamonds[i + 3];
				flarr[5] = rdiamonds[i + 4];
				i = 7;
				//strflushz++;
			}
		}

	}
	if (spades >= 5)
	{
		eval = 5; // flu
		flarr[0] = eval;
		flarr[1] = rspades[0];
		flarr[2] = rspades[1];
		flarr[3] = rspades[2];
		flarr[4] = rspades[3];
		flarr[5] = rspades[4];
		i = 7;
		//flusz++;
		for (i = 0; i < spades - 4; i++)
		{
			if (rspades[i] == 214)
			{
				//so = soa(lspades);
				lspades[spades] = 201;
				spades++;
			}
			if (rspades[i] - 1 == rspades[i + 1] && rspades[i] - 2 == rspades[i + 2] && rspades[i] - 3 == rspades[i + 3] && rspades[i] - 4 == rspades[i + 4])
			{

				eval = 8; //str flu
				flarr[0] = eval;
				flarr[1] = rspades[i];
				flarr[2] = rspades[i + 1];
				flarr[3] = rspades[i + 2];
				flarr[4] = rspades[i + 3];
				flarr[5] = rspades[i + 4];
				i = 7;
				//strflushz++;
			}
		}

	}
	if (clubs >= 5)
	{
		eval = 5; // flu
		flarr[0] = eval;
		flarr[1] = rclubs[0];
		flarr[2] = rclubs[1];
		flarr[3] = rclubs[2];
		flarr[4] = rclubs[3];
		flarr[5] = rclubs[4];
		i = 7;
		//flusz++;
		for (i = 0; i < clubs - 4; i++)
		{
			if (rclubs[i] == 314)
			{
				//so = soa(lclubs);
				lclubs[clubs] = 301;
				clubs++;
			}
			if (rclubs[i] - 1 == rclubs[i + 1] && rclubs[i] - 2 == rclubs[i + 2] && rclubs[i] - 3 == rclubs[i + 3] && rclubs[i] - 4 == rclubs[i + 4])
			{

				eval = 8; //str flu
				flarr[0] = eval;
				flarr[1] = rclubs[i];
				flarr[2] = rclubs[i + 1];
				flarr[3] = rclubs[i + 2];
				flarr[4] = rclubs[i + 3];
				flarr[5] = rclubs[i + 4];
				i = 7;
				//strflushz++;
			}
		}

	}

	return flarr;
}
int* Straightme(int cards[])
{

	int i = 0; int l = 6; int eval = 0; int so = 7;
	int checka; int checkb;
	int poopy; int poopy1; int poopy2; int poopy3; int poopy4; int poopy5;
	int subpoopy; int subpoopy1; int subpoopy2; int subpoopy3; int subpoopy4; int subpoopy5;
	int order[9] = { 0,0,0,0,0,0,0,0,0 };
	for (i = 0; i < 7; i++)
	{
		order[i] = NULL;
		order[i] = cards[i];
	}

	int* returner;
	static int strarr[6] = { 0,0,0,0,0,0 };
	int n = 0;
	while (n != 6) {
		strarr[n] = 0;
		n++;
	}
	returner = order;

	//removes duplicate cards. we dont need them to check straights
	for (i = 0; i < l; i++)
	{
		poopy = returner[i];
		poopy1 = returner[i + 1];
		if (poopy > poopy1) {
			checka = poopy1;
			checkb = poopy;
		}
		else {
			checka = poopy;
			checkb = poopy1;
		}

		//subpoopy = poopy % 100;
		//subpoopy = fast_mod(poopy);
		/*
		int* remove(int arrz[], const int a)
		{
			static int returner[7];
			//int returner[7];
			int j = 0;
			for (int i = 0; i < 7; i++)
			{
			if (i == a)
				{
				j++;
				}
			returner[i] = arrz[j];
			j++;

		}

		//int* pointer;
		//pointer = returner;
		return returner;
}
		*/
		//subpoopy1 = poopy1 % 100;
		//subpoopy1 = fast_mod(poopy1);
		if ((checka + 100 == checkb) || (checka + 200 == checkb) || (checka + 300 == checkb))
		{
			//returner = remove(returner, i + 1);
			//cout << " returner is before: " << returner[0] << " " << returner[1] << " " << returner[2] << " " << returner[3] << " " << returner[4] << " " << returner[5] << " " << returner[6] << " " << returner[7] << " " << returner[8] << endl;

			int zj = 0;
		    static int zzarray[7];
			for (int zz = 0; zz < 7; zz++) {
				if (zz == i + 1) {
					zj++;
				}
				//returner[zz] = returner[zj];
				zzarray[zz] = returner[zj];
				zj++;
			}
			returner[zj] = 0;
			//cout << " returner is before: " << returner[0] << " " << returner[1] << " " << returner[2] << " " << returner[3] << " " << returner[4] << " " << returner[5] << " " << returner[6] << " " << returner[7] << " " << returner[8] << endl;
			returner = zzarray;

			so--;
			l--;
			i--;
		}

	}

	for (i = 0; i < 7; i++)
	{
		order[i] = cards[i];
	}
	int str = 0; int two = 1; int mcase; int mvalue;
	poopy = returner[str];
	//mvalue = poopy % 100;
	//mvalue = fast_mod(poopy);
	//mcase = poopy / 100;
	if ((poopy - 100 == 14) || (poopy - 200 == 14) || (poopy - 300 == 14) || (poopy - 400 == 14))
	{
		//two += mcase * 100;
		//so = soa(returner);
		//cout << "so is " << so << endl;
		returner[so] = 101;
		returner[so + 1] = 0;
		so++;
		//cout << "so is " << so << "after so++"<< endl;


	}

	//so = soa(returner);
	//cout << "so is " << so << "after soa" << endl;

	for (str = 0; str < so - 4; str++)
	{
		poopy = returner[str];
		subpoopy = poopy % 100;
		//subpoopy = fast_mod(poopy);
		poopy2 = returner[str + 1];
		subpoopy2 = poopy2 % 100;
		//subpoopy2 = fast_mod(poopy2);
		poopy3 = returner[str + 2];
		subpoopy3 = poopy3 % 100;
		//subpoopy3 = fast_mod(poopy3);
		poopy4 = returner[str + 3];
		subpoopy4 = poopy4 % 100;
		//subpoopy4 = fast_mod(poopy4);
		poopy5 = returner[str + 4];
		subpoopy5 = poopy5 % 100;
		//subpoopy5 = fast_mod(poopy5);
		if (subpoopy - 1 == subpoopy2 && subpoopy - 2 == subpoopy3 && subpoopy - 3 == subpoopy4 && subpoopy - 4 == subpoopy5)
		{
			eval = 4; // str
			strarr[0] = eval;
			strarr[1] = subpoopy;
			strarr[2] = subpoopy2;
			strarr[3] = subpoopy3;
			strarr[4] = subpoopy4;
			strarr[5] = subpoopy5;
			str = 7;
			//straz++;
		}

	}
	//cout << "THIS iS WHAT IT RETURNS is before: " << returner[0] << " " << returner[1] << " " << returner[2] << " " << returner[3] << " " << returner[4] << " " << returner[5] << " " << returner[6] << " " << returner[7] << " " << returner[8] << endl;
	return strarr;
}
int* Evaluate(int order[])
{
	//ofstream myfile;
	//myfile.open ("s72bent.txt", ios::out | ios::app ); 
	int i = 0;
	int eval = 0;
	static int evarr[6];
	int poopy; int poopy1; int poopy2; int poopy3; int poopy4; int poopy5;  int poopy6;
	int subpoopy; int subpoopy1; int subpoopy2; int subpoopy3; int subpoopy4; int subpoopy5; int subpoopy6;
	poopy = order[0];
	poopy1 = order[1];
	poopy2 = order[2];
	poopy3 = order[3];
	poopy4 = order[4];
	poopy5 = order[5];
	poopy6 = order[6];
	subpoopy = poopy % 100;
	subpoopy1 = poopy1 % 100;
	subpoopy2 = poopy2 % 100;
	subpoopy3 = poopy3 % 100;
	subpoopy4 = poopy4 % 100;
	subpoopy5 = poopy5 % 100;
	subpoopy6 = poopy6 % 100;

	if (subpoopy == subpoopy1)
	{
		if (subpoopy == subpoopy2)
		{
			if (subpoopy3 == subpoopy4)
			{
				eval = 6; // house
				evarr[0] = eval;
				evarr[1] = subpoopy;
				evarr[2] = subpoopy1;
				evarr[3] = subpoopy2;
				evarr[4] = subpoopy3;
				evarr[5] = subpoopy4;
				i = 5;
				//fhousez++;
			}
			else
			{
				if (subpoopy == subpoopy3)
				{
					eval = 7; //quads
					evarr[0] = eval;
					evarr[1] = subpoopy;
					evarr[2] = subpoopy1;
					evarr[3] = subpoopy2;
					evarr[4] = subpoopy3;
					evarr[5] = subpoopy4;
					if (order[4] == order[5]) {
						if (subpoopy5 < subpoopy6) {
							evarr[5] = subpoopy6;
						}
					}
					i = 5;
					//quadz++;
				}
				else
				{
					eval = 3; // trips
					evarr[0] = eval;
					evarr[1] = subpoopy;
					evarr[2] = subpoopy1;
					evarr[3] = subpoopy2;
					evarr[4] = subpoopy3;
					evarr[5] = subpoopy4;
					i = 5;
					//tripz++;
				}
			}
		}
		else
		{
			if (subpoopy2 == subpoopy3)
			{
				eval = 2; // two pair
				evarr[0] = eval;
				evarr[1] = subpoopy;
				evarr[2] = subpoopy1;
				evarr[3] = subpoopy2;
				evarr[4] = subpoopy3;
				evarr[5] = subpoopy4;
				if (order[4] == order[5]) {
					if (subpoopy5 < subpoopy6) {
						evarr[5] = subpoopy6;
					}
				}
				i = 5;
				//twopairz++;
			}
			else
			{
				eval = 1; // pair
				evarr[0] = eval;
				evarr[1] = subpoopy;
				evarr[2] = subpoopy1;
				evarr[3] = subpoopy2;
				evarr[4] = subpoopy3;
				evarr[5] = subpoopy4;
				i = 5;
				//pairz++;
			}
		}
	}
	else
	{
		eval = 0; // no pair
		evarr[0] = eval;
		evarr[1] = subpoopy;
		evarr[2] = subpoopy1;
		evarr[3] = subpoopy2;
		evarr[4] = subpoopy3;
		evarr[5] = subpoopy4;
		i = 5;
		//nopairz++;
	}
	return evarr;

}


int getposition(int arr[], int value)
{
	int j = -1;
	for (int i = 0; i < 28; i++)
	{
		if (arr[i] == value)
		{
			j = value;
		}

	}
	return j;
}
void loop(int handnumber, int one, int two, int three, int four, int five, int six, int seven)
//void loop()
{
#ifdef DEBUG
	ofstream myfile;
	myfile.open("s72bent.txt", ios::out | ios::app);
#endif

	//int handnumber = 2;
	int ordered[7];
	//int cards[52];
	//int handnumber = 2;
	dealtsize = (handnumber * 2) + 5;
	dealtsize2 = handnumber * 2;
	//int dealt[29] = { 0 };
	//int card[25];
	//int flop[5] = { 0 };
	//int current[7];
	//int straight[7];
	int afterpairme[7];
	//int handv[11];
	//int handvcompare[11];
	int i; int rander = 0;
	int k = 0; int j;
	int index = 0;
	/*
	for (i = 1; i < 5; i++)
	{
		for (j = 2; j < 15; j++)
		{
			cards[k] = (i * 100) + j;
			k++;
		}

	}
	*/
	dealt[0] = one;
	dealt[1] = two;
	i = 2;
	int poop;
	int johnsucks;
	//poop = rand() % 52 + 0;
	flop[0] = 0; flop[1] = 0; flop[2] = 0; flop[3] = 0; flop[4] = 0;
	if (three != 0) {
		flop[0] = three;
		dealtsize--;
	}
	if (four != 0) {
		flop[1] = four;
		dealtsize--;

	}
	if (five != 0) {
		flop[2] = five;
		dealtsize--;
	}
	if (six != 0) {
		flop[3] = six;
		dealtsize--;
	}
	if (seven != 0) {
		flop[4] = seven;
		dealtsize--;
	}
	int assigned = 0;
	/*
	while (i < dealtsize)
	{
		rander = rand() % 52;
		index = getpoz(dealt, cards[rander], 28);
		johnsucks = getpoz(flop, cards[rander], 5);
		if ((index == -1) && (johnsucks == -1))
		{
			dealt[i] = cards[rander];

			i++;
		}


	}
	j = handnumber * 2; k = 0;
	for (i = 0; i < j; i++)
	{
		card[i] = dealt[k];
		k++;
	}
	for (i = 0; i < 5; i++)
	{
		if (flop[i] == 0) {
			flop[i] = dealt[k];
			k++;
		}
		// flop[i] = cardz[combination[i]];
	}
	*/
	card[0] = 114;
	card[1] = 214;
	card[2] = 307;
	card[3] = 402;

#ifdef DEBUG
	int debugint = 0;
	while (debugint < dealtsize2) {
		myfile << "hand " << debugint << " is " << card[debugint] << " " << card[debugint + 1] << endl;
		debugint++;
		debugint++;
	}
	myfile << "FLOP: " << flop[0] << " " << flop[1] << " " << flop[2] << " " << flop[3] << " " << flop[4] << endl;

#endif



	int cardnumber = 0;
	//int streval[11][7];
	//int fleval[11][7];
	//int eveval[11][7];
	for (i = 0; i < handnumber; i++)
	{
		int test[7] = { card[cardnumber], card[cardnumber + 1], flop[0], flop[1], flop[2], flop[3], flop[4] };
		cardnumber++; cardnumber++;
		static int* arraypointer;
		int* another;
		int zz;
		arraypointer = Order2(test);
		//arraypointer = test;
		//for (zz = 0; zz < 7; zz++)
		//{
		//	flush[zz] = arraypointer[zz];
		//	straight[zz] = arraypointer[zz];
		//	current[zz] = arraypointer[zz];
		//}
		memcpy(afterpairme, arraypointer, 7 * sizeof(int));
		//memcpy(straight, arraypointer, 7 * sizeof(int));
		//memcpy(current, arraypointer, 7 * sizeof(int));


#ifdef DEBUG
		myfile << "Current: " << arraypointer[0] << "-"
			<< arraypointer[1] << "-"
			<< arraypointer[2] << "-"
			<< arraypointer[3] << "-"
			<< arraypointer[4] << "-"
			<< arraypointer[5] << "-"
			<< arraypointer[6] << endl;
#endif	
		arraypointer = Pairme2(afterpairme);
		//another = Pairme(afterpairme);

		//comparearrays(arraypointer, another);
		 //use afterpairme here because of current because functionally there's no difference. flush has the same data as current and its not being written to. 
		/*
		for (zz = 0; zz < 7; zz++)
		{
			ordered[zz] = arraypointer[zz];
		}*/
		//memcpy(ordered, arraypointer, 7 * sizeof(int));

#ifdef DEBUG
		myfile << "Ordered: " << arraypointer[0] << "-" <<
			arraypointer[1] << "-" <<
			arraypointer[2] << "-" <<
			arraypointer[3] << "-" <<
			arraypointer[4] << "-" <<
			arraypointer[5] << "-" <<
			arraypointer[6] << endl;
#endif	
		arraypointer = Evaluate(arraypointer);


		for (zz = 0; zz < 6; zz++)
		{
			eveval[i][zz] = arraypointer[zz];
		}

		handv[i] = eveval[i][0];


#ifdef DEBUG
		myfile << "Eveval: " << eveval[i][0] << "-" <<
			eveval[i][1] << "-" <<
			eveval[i][2] << "-" <<
			eveval[i][3] << "-" <<
			eveval[i][4] << "-" <<
			eveval[i][5]
			<< endl;
#endif			
		arraypointer = Straightme(afterpairme);
		for (zz = 0; zz < 7; zz++)
		{
			streval[i][zz] = arraypointer[zz];
		}

#ifdef DEBUG
		myfile << "STREVAL: " << streval[i][0] << "-" <<
			streval[i][1] << "-" <<
			streval[i][2] << "-" <<
			streval[i][3] << "-" <<
			streval[i][4] << "-" <<
			streval[i][5]
			<< endl;
#endif	


		handvcompare[i] = streval[i][0];
		if (handvcompare[i] > handv[i])
		{
			handv[i] = handvcompare[i];
		}


		arraypointer = Flushme(afterpairme);
		for (zz = 0; zz < 7; zz++)
		{
			fleval[i][zz] = arraypointer[zz];
		}

#ifdef DEBUG
		myfile << "Fleval: " << fleval[i][0] << "-" <<
			fleval[i][1] << "-" <<
			fleval[i][2] << "-" <<
			fleval[i][3] << "-" <<
			fleval[i][4] << "-" <<
			fleval[i][5] << endl;
#endif
		handvcompare[i] = fleval[i][0];
		if (handvcompare[i] > handv[i])
		{
			handv[i] = handvcompare[i];
		}
#ifdef DEBUG
		myfile << "Hand value of hand " << i << " is " << handv[i] << endl;
#endif

	}
	int percent = 0;
	bool checker = false;
	int divider = 0;
	for (i = 1; i < handnumber; i++)
	{
		if (handv[i] > handv[0])
		{
			checker = true;
			i = handnumber;
		}
		else if (handv[i] == handv[0])
		{
			switch (handv[0])
			{
			case 0:
				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 1:
				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 2:
				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 3:
				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 4:
				for (int j = 1; j < 6; j++)
				{
					if (streval[i][j] > streval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (streval[i][j] < streval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (streval[i][j] == streval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 5:
				for (int j = 1; j < 6; j++)
				{
					if (fleval[i][j] > fleval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (fleval[i][j] < fleval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (fleval[i][j] == fleval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 6:

				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 7:
				for (int j = 1; j < 6; j++)
				{
					if (eveval[i][j] > eveval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (eveval[i][j] < eveval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (eveval[i][j] == eveval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			case 8:
				for (int j = 1; j < 6; j++)
				{
					if (fleval[i][j] > fleval[0][j])
					{
						checker = true;
						j = 7;
						break;
					}
					else if (fleval[i][j] < fleval[0][j])
					{
						//checker = false;
						j = 7;
						break;
					}
					else if (fleval[i][j] == fleval[0][j])
					{
						if (j == 5)
						{
							divider++;
						}
					}
				}
				break;
			}
		}
	}


	if (checker == false)
	{
		if (divider == 0)
		{
			percent = 100;
		}
		else
		{
			//tiez++;
			divider++;
			percent = 100 / divider;
		}
	}
	else
	{
		percent = 0;
	}
#ifdef DEBUG
	myfile << "percent is " << percent << endl;
#endif
	if (percent != 0 && percent < 100) tiex++; else if (percent == 100) winx++;
	//return percent;


}

int calculate(int numhands, int hand1, int hand2) {
	//srand(time(NULL));
	//cin >> hand1;
	//cin >> hand2;
	cout << "hand1 set to " << hand1 << " hand2 set to " << hand2 << endl;
	cout << "Calculating..." << endl;
	//system("pause");
	clock_t t;
	t = clock();
	int l = 2; // = AMOUNT of hands	
	int times = 0;
	while (times < 1) {
		tiex = 0;
		winx = 0;
		for (int i = 0; i < 100000; i++)
		{
			//ard = loop(numhands, hand1, hand2, 0, 0, 0, 0, 0);
			//ard = loop(numhands,hand1, hand2,0,0,0,0,0);
			if (ard != 0 && ard < 100) { tiex++; }
			if (ard == 100) { winx++; }
		}
		t = clock() - t;

		cout << "won " << winx;
		cout << " tied " << tiex << " against" << l << endl;
		times++;
	}
	cout << "t is " << t << endl;
	//system("pause");
	return 0;
}


int mainup(int argc, char* argv[])
{
	int pooper;
	int arg1 = strtol(argv[1], NULL, 10);
	int arg2 = strtol(argv[2], NULL, 10);
	int arg3 = strtol(argv[3], NULL, 10);
	cout << "Hello World!\n";
	pooper = calculate(arg1, arg2, arg3);
	return 0;
}

int mainupper()
{
	//srand(time(NULL));
	//clock_t t;
	//t = clock();
	int l = 0;
	int k = 302;
	int m = 402; int mb = 401;
	int n = 302; int nb = 301;
	int huh = 0;
	int couter = 0;
	int zixx;
	for (k = 302; k < 315; k++)
	{
		mb++; nb++;
		cout << k << endl;
		for (m = mb; m < 415; m++)
		{
			cout << k << m << endl;
			for (zixx = 2; zixx < 11; zixx++)
			{
				//tmn(zixx, k, m);
			}
		}
		for (n = nb; n < 315; n++)
		{
			if (k != n) {
				cout << k << n << endl;
				for (zixx = 2; zixx < 11; zixx++)
				{

					//tmn(zixx, k, n);
				}
			}
		}
	}
	system("pause");
	return 0;
}

void printfuck() {
	cout << "fuck" << endl;
}

void tmn(int one, int two, int three)
{
	//ofstream myfile;
	int fard;
	//myfile.open("ssss.txt", ios::out | ios::app);
	int iz = 0;
	tiex = 0;
	winx = 0;
	while (iz < 100000)
	{
		//fard = loop(one, two, three, 0, 0, 0, 0, 0);
		//if (fard != 0 && fard < 100) { tiex++; }
		//if (fard == 100) { winx++; }
		iz++;
	}
	//myfile << two << "," << three;
	//myfile << "," << winx << ",";
	//myfile << tiex << endl;
	//myfile.close();
}

int counz = 0;
int threadzz = 1;
vector<int> people;
vector<int> combination;
int peoplea[5];
int combinationa[5];
int filly = 0;
future<void> fn1;
future<void> fn2;
future<void> fn3;
future<void> fn4;
//std::vector <std::thread> threads;

void go(int offset, int k) {

	if (k == 0) {
		//loop(2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
		loop(2, 114, 214, cardz[combinationa[0]], cardz[combinationa[1]], cardz[combinationa[2]], cardz[combinationa[3]], cardz[combinationa[4]]);
		//std::thread t(loop, 2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
		//std::thread t(loop, 2, 114, 214, 314, 414, 205, 306, 407);
		//std::thread t(printfuck);
		/*
		switch(threadzz) {
		case 1:

			fn1 = async(launch::async, loop, 2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
			fn1.get();
			//threadzz++;
			break;
		case 2:

			fn2 = async(launch::async, loop, 2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
			fn2.get();
			threadzz++;
			break;
		case 3:

			fn3 = async(launch::async, loop, 2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
			fn3.get();
			threadzz++;
			break;
		case 4:

			fn4 = async(launch::async, loop, 2, 114, 214, cardz[combination[0]], cardz[combination[1]], cardz[combination[2]], cardz[combination[3]], cardz[combination[4]]);
			fn4.get();
			threadzz = 1;




			break;

		}*/

		//threads.push_back(std::move(t));
		//cout << cardz[combinationa[0]] <<" "<< cardz[combinationa[1]] <<" "<< cardz[combinationa[2]]<<" "<< cardz[combinationa[3]] <<" "<< cardz[combinationa[4]] <<endl;
		//cout << cardz[combination[0]] << " " << cardz[combination[1]] << endl;
		//if (ard != 0 && ard < 100) { tiex++; }
		//if (ard == 100) { winx++; }
		//counz++;
		//filly--;
		return;
	}
	for (int i = offset; i <= 48 - k; i++) {
		//combination.push_back(people[i]);
		//cout << "combination[" << filly << "] = " << peoplea[i] << ";"<<"and i is "<<i << endl;
		combinationa[filly] = i;
		filly++;
		//cout << "go(" << i << " + 1, " << k << " - 1);" << endl;
		go(i + 1, k - 1);
		filly--;
		//combination.pop_back();
	}
}

int main() {
	int n = 48, k = 5;

	//for (int i = 0; i < n; ++i) {
	//	peoplea[i] = i;
		//cout << "people[" << i << " = " << i << endl;
		//people.push_back(i);

	//}
	//srand(time(NULL));
	clock_t t;
	t = clock();
	go(0, k);
	//loop(2, 114, 214, 403, 404, 405, 406, 304);
	//for (auto& t : threads) {
	//	t.join();
	//}
	cout.precision(17);
	cout << "count is " << counz;
	cout << " you won " << winx << " percent of the time";
	cout << " you tied " << tiex << " percent of the time" << endl;
	t = clock() - t;
	cout << "t is " << t << endl;
	//system("pause");
	return 0;
}

//404-304-204-403-203

