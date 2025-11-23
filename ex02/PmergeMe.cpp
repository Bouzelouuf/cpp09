#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_vec = other._vec;
	_deq = other._deq;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

void PmergeMe::sort(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		int val = atoi(av[i]);
		if (val <= 0)
		{
			std::cerr << "Error" << std::endl;
			return;

		}
		_vec.push_back(val);
		_deq.push_back(val);
	}
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++)
		{
			std::cout << _vec[i];
			if (i < _vec.size() - 1)
				std::cout << " ";
		}
	std::cout << std::endl;

	clock_t start1 = clock();
	_sortVector(_vec);
	clock_t end1 = clock();
	double time_vec = (double)(end1 - start1) / CLOCKS_PER_SEC * 1000000;

	clock_t start2 = clock();
	_sortDeque(_deq);
	clock_t end2 = clock();
	double time_deq = (double) (end2- start2) / CLOCKS_PER_SEC * 1000000;
	std::cout << "After: ";

	for (size_t i = 0; i < _vec.size(); i++)
	{
		std::cout << _vec[i];
		if (i < _vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vec.size() 
				<< " elements with std::vector : " << time_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() 
				<< " elements with std::deque  : " << time_deq << " us" << std::endl;
}

void PmergeMe::_sortVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    int straggler = -1;
    bool has_straggler = (arr.size() % 2 != 0);
    if (has_straggler)
        straggler = arr[arr.size() - 1];
    
    size_t limit = has_straggler ? arr.size() - 1 : arr.size();
    
    for (size_t i = 0; i + 1 < limit; i += 2)
    {
        if (arr[i] < arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }
    
    std::vector<int> main_chain;
    std::vector<int> pend_chain;
    
    for (size_t i = 0; i < limit; i += 2)  // ✅ i < limit
    {
        main_chain.push_back(arr[i]);
        pend_chain.push_back(arr[i + 1]);  // ✅ Pas de if
    }
    
    _sortVector(main_chain);
    
    for (size_t i = 0; i < pend_chain.size(); i++)  // ✅ pend_chain.size()
    {
        std::vector<int>::iterator pos = std::lower_bound(
            main_chain.begin(),
            main_chain.end(),
            pend_chain[i]
        );
        main_chain.insert(pos, pend_chain[i]);
    }
    
    if (has_straggler)
    {
        std::vector<int>::iterator pos = std::lower_bound(
            main_chain.begin(),
            main_chain.end(),
            straggler
        );
        main_chain.insert(pos, straggler);
    }
    
    arr = main_chain;
}


void PmergeMe::_sortDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    int straggler = -1;
    bool has_straggler = (arr.size() % 2 != 0);
    if (has_straggler)
        straggler = arr[arr.size() - 1];
    
    size_t limit = has_straggler ? arr.size() - 1 : arr.size();
    
    for (size_t i = 0; i + 1 < limit; i += 2)
    {
        if (arr[i] < arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }
    
    std::deque<int> main_chain;
    std::deque<int> pend_chain;
    
    for (size_t i = 0; i < limit; i += 2)  // ✅ i < limit
    {
        main_chain.push_back(arr[i]);
        pend_chain.push_back(arr[i + 1]);  // ✅ Pas de if
    }
    
    _sortDeque(main_chain);
    
    for (size_t i = 0; i < pend_chain.size(); i++)  // ✅ pend_chain.size()
    {
        std::deque<int>::iterator pos = std::lower_bound(
            main_chain.begin(),
            main_chain.end(),
            pend_chain[i]
        );
        main_chain.insert(pos, pend_chain[i]);
    }
    
    if (has_straggler)
    {
        std::deque<int>::iterator pos = std::lower_bound(
            main_chain.begin(),
            main_chain.end(),
            straggler
        );
        main_chain.insert(pos, straggler);
    }
    
    arr = main_chain;
}
