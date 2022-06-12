#ifndef QS_H_
#define QS_H_
#include <string>
#include "QSInterface.h"
using namespace std;

#define DEFAULT_SIZE 0			//using default size 0 for size, indexCounter, and capacity 

template<typename T>
class QS : public QSInterface<T> {
private:
	T* qsData; 
	size_t qsCapacity;
	size_t qsSize;
	int indexCounter;
	int comparisons;
	int exchanges;

public:
	QS() : qsSize(DEFAULT_SIZE), comparisons(DEFAULT_SIZE), exchanges(DEFAULT_SIZE), indexCounter(DEFAULT_SIZE), 
		qsCapacity(DEFAULT_SIZE), qsData(new T[DEFAULT_SIZE]) {}
	~QS() {
		delete[] qsData;		//deallocate the dynamic memory
	}

	void modifyArray(size_t newCapacity) {		//modify the array by moving the current array into a new one twice as large in capacity
		size_t oldCapacity = qsCapacity;
		qsCapacity = newCapacity;
		T* tempData = new T[qsCapacity];
		for (int i = 0; i < oldCapacity; ++i) {
			tempData[i] = qsData[i];
		}
		delete[] qsData;
		qsData = tempData;
		return;
	}

	void newArray(size_t newCapacity) {		//make a new array by changing the current qsData into an array twice as large 
		qsCapacity = newCapacity;
		T* tempData = new T[qsCapacity];
		delete[] qsData;
		qsData = tempData;
		qsSize = DEFAULT_SIZE;
		indexCounter = DEFAULT_SIZE;
		return;
	}

	virtual bool addElement(T element) {	//add an element to the array by using an index counter as the location and incrementing it each time
		if (qsSize == qsCapacity) {			//check first for if size is equal to capacity to know when to increase the array size
			modifyArray(qsCapacity * 2);
		}
		qsData[indexCounter] = element;
		++qsSize;
		++indexCounter;
		return true;
	}

	virtual bool sort(size_t left, size_t right) {		//sort function which takes certain parameters of where to sort in the list
		comparisons = DEFAULT_SIZE;
		exchanges = DEFAULT_SIZE;
		quickSort(left,right);
		return true;
	}

	virtual bool sortAll() {			//recursive starter sort all function which calls the recursive quickSort function to sort the array
		comparisons = DEFAULT_SIZE;
		exchanges = DEFAULT_SIZE;
		int zero = 0;
		int end = qsSize;
		quickSort(zero, end);
		return true;
	}

	void quickSort(int start, int end) {		//recursive quick sort function which calls itself on each side of the pivot to sort the array
		int index;
		int p;
		if (end - start > 1) {
			index = medianOfThree(start, end);
			p = partition(start, end, index);
			quickSort(start, p);											
			quickSort(p + 1, end);
			++exchanges;
		}
		return;
	}

	virtual bool clear() {			//clear function which sets all the values of the array equal to 0 to know that it is empty
		for (int i = 0; i < qsCapacity; ++i) {
			qsData[i] = 0;
		}
		qsSize = DEFAULT_SIZE;			//set private data members of size and index counter back to 0
		indexCounter = DEFAULT_SIZE;
		return true;
	}

	virtual size_t capacity() const {		//return the current capacity of the array
		return qsCapacity;
	}

	virtual size_t size() const {			//return the current size of the array
		return qsSize;
	}

	virtual int medianOfThree(size_t left, size_t right) {		//medianOfThree function which takes the left and right indexes and returns the pivotIndex
		size_t index;
		index = (right - left) / 2;
		index += left;
		++comparisons;
		if (qsData[left] > qsData[right - 1]) {			//bubble sort function of three numbers which compares each one and moves as needed
			int temp = qsData[left];
			qsData[left] = qsData[right - 1];
			qsData[right - 1] = temp;
			++exchanges;
		}
		++comparisons;
		if (qsData[left] > qsData[index]) {
			int temp = qsData[left];
			qsData[left] = qsData[index];
			qsData[index] = temp;
			++exchanges;
		}
		++comparisons;
		if (qsData[index] > qsData[right - 1]) {
			int temp = qsData[index];
			qsData[index] = qsData[right - 1];
			qsData[right - 1] = temp;
			++exchanges;
		}
		return index;
	}

	virtual int partition(size_t left, size_t right, size_t pivotIndex) {		//partition function which takes a pivot and partitions out the array
		int temp = qsData[left];												//so that all values to the left are less than and to the right are greater than
		qsData[left] = qsData[pivotIndex];
		qsData[pivotIndex] = temp;
		int up = left + 1;
		int down = right - 1;
		do {
			while ((up != right) && (qsData[left] >= qsData[up])) {			
				++up;														//increment the up index
				++comparisons;
			}
			while (qsData[left] < qsData[down]) {
				--down;														//decrement the down index
				++comparisons;
			}
			if (up < down) {
				int tempData = qsData[up];
				qsData[up] = qsData[down];
				qsData[down] = tempData;
				++exchanges;
				++comparisons;
			}
			++comparisons;
		} while (up < down);
		int tempData = qsData[left];
		qsData[left] = qsData[down];
		qsData[down] = tempData;
		++exchanges;
		++exchanges;
		return down;
	}

	int getComparisons() {			//return the current number of comparisons done
		return comparisons;
	}

	int getExchanges() {			//return the current number of exchanges done
		return exchanges;
	}

	virtual string toString() const {				//toString function which takes each element of the array and puts it into a strinstream 
		stringstream ss;	
		for (int i = 0; i < qsSize; ++i) {
			ss << qsData[i] << ",";
		}
		string line = ss.str();
		return line.substr(0, line.size() - 1);
	}

	friend ostream& operator<<(ostream& os, QS<T>& qs) {		//freind insertion that calls toString function 
		return os << qs.toString();
	}
};

#endif //QS_H_ 
