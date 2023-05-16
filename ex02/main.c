#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "This Program needs at least a argument" << std::endl;
		exit (1);
	}
	try{
		PmergeMe sorter;
		sorter.loadList(argc - 1, &argv[1]);
		sorter.sort();
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
	}
}