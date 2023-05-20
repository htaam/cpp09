#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe( void ): _vectorTime(0), _listTime(0) {
    LOG("Default constructor");
}

PmergeMe::PmergeMe( PmergeMe const& src ) {
	*this = src;
}

PmergeMe::~PmergeMe( void ) {
    LOG("Default destructor");
}

PmergeMe&	PmergeMe::operator=( PmergeMe const& rhs ) {
	this->_vector = rhs._vector;
	this->_list = rhs._list;
	this->_vectorTime = rhs._vectorTime;
	this->_listTime = rhs._listTime;
	return (*this);
}


void	PmergeMe::fillSTLs( std::string const& str ) {
	this->_vector.push_back(std::atoi(str.c_str()));
	this->_list.push_back(std::atoi(str.c_str()));
}

void	PmergeMe::printSTLs( void ) {
	LOG("Vector:");
	for (std::vector<int>::iterator it = this->_vector.begin(); it != this->_vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	LOG("List:");
	for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}


void	PmergeMe::sort( void ) {
	clock_t	start = clock();
	this->sortVector(0, this->_vector.size() - 1);
	clock_t	end = clock();
	this->_vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	start = clock();
	this->sortList(this->_list.begin(), this->_list.end());
	end = clock();
	this->_listTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
}


void	PmergeMe::sortVector( int left, int right ) {
    if (left >= right)
		return ;
	if ((right - left + 1) <= 10) {
		this->vectorInsertSort(left, right);
		return ;
	}
	// merge sort
	int mid = (left + right) / 2;
	sortVector(left, mid);
	sortVector(mid + 1, right);
	std::vector<int> temp(right - left + 1);
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right) {
		if (this->_vector[i] <= this->_vector[j])
			temp[k++] = this->_vector[i++];
		else
			temp[k++] = this->_vector[j++];
	}
	while (i <= mid)
		temp[k++] = this->_vector[i++];
	while (j <= right)
		temp[k++] = this->_vector[j++];
	for (int i = 0; i < k; ++i)
		this->_vector[left + i] = temp[i];
}

void	PmergeMe::vectorInsertSort(int left, int right) {
	for (int i = left + 1; i <= right; ++i) {
		int temp = this->_vector[i];
		int j = i - 1;
		while (j >= left && this->_vector[j] > temp) {
			this->_vector[j + 1] = this->_vector[j];
			j--;
		}
		this->_vector[j + 1] = temp;
	}
	return ;
}

void	PmergeMe::sortList( std::list<int>::iterator begin, std::list<int>::iterator end) {
	if (std::distance(begin, end) <= 0)
		return ;
	if (std::distance(begin, end) <= 10) {
		this->listInsertSort(begin, end);
		return ;
	}
	//merge sort
	std::list<int>::iterator mid = begin;
	std::advance(mid, std::distance(begin, end) / 2);
	sortList(begin, mid);
	sortList(mid, end);
	std::list<int> temp;
	std::list<int>::iterator i = begin;
	std::list<int>::iterator j = mid;
	while (i != mid && j != end) {
		if (*i <= *j) {
			temp.push_back(*i);
			i++;
		}
		else {
			temp.push_back(*j);
			j++;
		}
	}
	while (i != mid) {
		temp.push_back(*i);
		i++;
	}
	while (j != end) {
		temp.push_back(*j);
		j++;
	}
	i = begin;
	j = temp.begin();
	while (i != end) {
		*i = *j;
		i++;
		j++;
	}
	return ;
}

void	PmergeMe::listInsertSort(std::list<int>::iterator begin, std::list<int>::iterator end) {
	std::list<int>::iterator temp, temp2;
	
	temp2 = begin;
	for (std::list<int>::iterator i = ++temp2; i != end; i++) {
		int key = *i;
		std::list<int>::iterator j = i;
		while (j != begin && *(--j) > key) {
			temp = j;
			temp++;
			*temp = *j;
			temp = j;
			*temp = key;
		}
	}
}

double	PmergeMe::getVectorTime( void ) const {
	return (this->_vectorTime);
}

double	PmergeMe::getListTime( void ) const {
	return (this->_listTime);
}