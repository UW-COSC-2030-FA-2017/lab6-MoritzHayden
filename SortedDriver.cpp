// SortedDriver.cpp

// Hayden Moritz
// COSC 2030 - Lab 06
// October 27, 2017

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double dist1 = 0;
	double dist2 = 0;
	double dist3 = 0;
	double mostIso = 0;
	double xCurr = 0;
	double xDown = 0;
	double xUp = 0;

	for (int h = 0; h < number.size(); h++) {

		// Check special case of first value
		if (h == 0) {
			xCurr = number[h];
			xUp = number[h+1];
			dist3 = xUp - xCurr;
			mostIso = xCurr;
		}
		// Check special case of last value
		else if (h == (number.size()-1)){
			xCurr = number[h];
			xDown = number[h - 1];
			dist1 = xCurr - xDown;
			if (dist1 > dist3) {
				mostIso = xCurr;
			}
		}
		else {
			// Get distances between neighbors of current position
			xCurr = number[h];
			xDown = number[h - 1];
			xUp = number[h + 1];
			dist1 = xCurr - xDown;
			dist2 = xUp - xCurr;
			// Test each side for the bigger of the two distances
			if (dist1 < dist2 && dist1 >= dist3) {
				dist3 = dist1;
				mostIso = xCurr;
			}
			else if (dist2 < dist1 && dist2 >= dist3) {
				dist3 = dist2;
				mostIso = xCurr;
			}
		}
	}
	// Return the most isolated value
	return mostIso;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	// Create counter
	int total = 0;
	// Create two iterators (one for each list)
	// Also my attempt at humor
	list<string>::iterator iterAtor = A.begin();
	list<string>::iterator iterBtor = B.begin();

	// Iterate through list a
	for (iterAtor; iterAtor != A.end(); ++iterAtor) {
		// Iterate through list b simultaneously
		while ((*iterAtor > *iterBtor) && (iterBtor != B.end())) {
			iterBtor++;
		}
		// If a value doesnt match, add one to the number of unmatched values
		if (*iterAtor != *iterBtor) {
			total++;
		}
	}
	return total;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}