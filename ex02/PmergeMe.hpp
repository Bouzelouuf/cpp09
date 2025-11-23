#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <ctime>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int>  _deq;

	void _sortVector(std::vector<int>& arr);
	void _sortDeque(std::deque<int>& arr);
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	void sort(int argc, char **argv);
};

#endif
