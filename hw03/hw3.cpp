/*
	Author:			Dillon VanBuskirk
	Date:			09-18-16
	Description:	Given k-sorted arrays, produce a sorted k*n master array using min-heaps
*/

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


void Push(vector<pair<int, int> > &heap, int key, int arr);
pair<int, int> Pop(vector<pair<int, int> > &heap);
struct pairCompare {
	bool operator()(pair<int, int> p1, pair<int, int> p2) {
		return p1.first > p2.first;
	}
};

int main(int argc, char** argv) {
	int k;
	cout << "Waiting for k: ";
	cin >> k;
	vector<pair<int, int> > heap;
	vector<vector<int> > input(k);

	/* Input */
	for (int i = 0; i < k; i++) {
		string file = "input" + to_string(i) + ".txt";
		ifstream infile;
		infile.open(file.c_str());
		int key;
		while (infile >> key)
			input[i].push_back(key);
		infile.close();
	}
	
	/* Begin k-way Merge Algorithm */
	vector<int> kWay;
	for (int i = 0; i < k; i++) {
		Push(heap, input[i][0], i); // push first elements from k lists, a constant k time
		input[i].erase(input[i].begin());
	}
	while (heap.size() > 0) {
		pair<int, int> p = Pop(heap); // extract min
		kWay.push_back(p.first);
		if (input[p.second].size() > 0) {
			Push(heap, input[p.second][0], p.second); // push next element from extracted min's list
			input[p.second].erase(input[p.second].begin());
		}
	}
	/* End k-way Merge Algorithm */
	
	/* Output */
	ofstream outfile;
	outfile.open("output.txt");
	for (int i = 0; i < kWay.size(); i++) {
		outfile << kWay[i] << " ";
	}
	outfile.close();
	
	return 0;
}

/* Pushes the pair into the heap using the defined algorithm package */
void Push(vector<pair<int, int> > &heap, int key, int arr) {
	pair<int, int> p(key, arr);
	heap.push_back(p);
	push_heap(heap.begin(), heap.end(), pairCompare());
}

/* Pops the pair from the front of the heap using the defined algorithm package */
pair<int, int> Pop(vector<pair<int, int> > &heap) {
	pair<int,int> p = heap.front();
	pop_heap(heap.begin(), heap.end(), pairCompare());
	heap.pop_back();
	return p;
}