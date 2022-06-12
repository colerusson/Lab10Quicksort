#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "QS.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	QS<int> quickSort;			//insantiation of QS object of int
	
	for (string line; getline(in, line);) {		//parse through the file until the end
		string item1;
		int item2;
		int left, right, pivotIndex;		//multiple strings and ints that will be needed throghout parsing the file
		if (line.size() == 0) continue;
		istringstream iss(line);
		iss >> item1;
		if (item1 == "AddToArray") {			//special output with commas for AddToArray
			out << endl << "AddToArray ";
		}
		else if (item1 == "MedianOfThree") {	//special output with commas for MedianOfThree
			out << endl << "MedianOfThree ";
		}
		else if (item1 == "Partition") {		//special output with commas for Partition
			out << endl << "Partition ";
		}
		else if (item1 == "Sort") {				//special output with commas for Sort
			out << endl << "Sort ";
		}
		else {
			out << endl << line;
		}

		if (item1 == "QuickSort") {			//check for call to QuickSort, then call newArray and modify the QS object
			iss >> item2;
			quickSort.newArray(item2);
			out << " OK";
		}
		else if (item1 == "AddToArray") {		//check for call to AddToArray adn take in the elements one by one, calling addElement
			stringstream ss;
			while (!iss.eof()) {
				iss >> item2;
				quickSort.addElement(item2);
				ss << item2 << ",";
			}
			string line = ss.str();				//special output of the parsed line now with commas
			out << line.substr(0, line.size() - 1);
			out << " OK";
		}
		else if (item1 == "PrintArray") {		//check for call to PrintArray and ouput empty if size is 0, else call the friend and toString
			if (quickSort.size() == 0) {
				out << " Empty";
			}
			else {
				out << " " << quickSort;
			}
		}
		else if (item1 == "Size") {			//check for call to Size and output the current size of the array
			out << " " << quickSort.size();
		}
		else if (item1 == "Capacity") {		//check for call to Capacity and output the current capacity of the array
			out << " " << quickSort.capacity();
		}
		else if (item1 == "Clear") {		//check for call to Clear and call the clear function for the quickSort object
			quickSort.clear();
			out << " OK";
		}
		else if (item1 == "MedianOfThree") {		//check for call to MedianOfThree and take in the ints, set as size_t and call medianOfThree
			iss >> left;
			iss >> right;
			int error = -1;
			out << left << "," << right << " = ";

			if (left < 0 || right < 0 || right - left <= 0) {
				out << error;
			}
			else {
				out << quickSort.medianOfThree(left, right);
			}
		}
		else if (item1 == "Partition") {			//check for call to Partition, take in the ints, and call partition
			iss >> left;
			iss >> right;
			iss >> pivotIndex;
			int error = -1;
			out << left << "," << right << "," << pivotIndex << " = ";
			if (left < 0 || right < 0 || pivotIndex < 0 || right - left <= 0 || right < pivotIndex) {
				out << error;
			}
			else {
				out << quickSort.partition(left, right, pivotIndex);
			}
		}
		else if (item1 == "Sort") {			//check for call to Sort, take in the values needed, and call the specific sort function
			iss >> left;
			iss >> right;
			quickSort.sort(left, right);
			out << left << "," << right << " OK";
		}
		else if (item1 == "SortAll") {			//check for call to SortAll and call the function to sort the entire array
			quickSort.sortAll();
			out << " OK";
		}
		else if (item1 == "Stats") {			//check for call to Stats and calculate and output the stats
			out << " " << quickSort.getComparisons() << "," << quickSort.getExchanges();
		}
	}

	in.close();
	return 0;
}
