#include <iostream>
#include "PmergeMe.hpp"
#include <iomanip>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe [number] [number] ..." << std::endl;
		return (1);
	}
	PmergeMe pm;

	for (int i = 1; i < argc; ++i) {
		pm.fillSTLs(std::string(argv[i]));
	}
	LOG("Before merge");
	pm.printSTLs();
	pm.sort();
	LOG("After merge:");
	pm.printSTLs();
	int i = argc - 1;
	LOG("Time to merge " << i << " elements with vector:");
	LOG(std::setprecision(6) << std::fixed << pm.getVectorTime());
	LOG("Time to merge " << i << " elements with list:");
	LOG(std::setprecision(6) << std::fixed << pm.getListTime());
	return (0);
}