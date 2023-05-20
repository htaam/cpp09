#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <string>
# include <cstdlib>
# include <ctime>

# define LOG(x) std::cout << x << std::endl

class PmergeMe {

private:
	std::vector<int>	_vector;
	std::list<int>		_list;
	double				_vectorTime;
	double				_listTime;

	
public:
	PmergeMe( void ); /* Default constructor */
	PmergeMe( PmergeMe const& src ); /* Copy constructor */
	~PmergeMe( void ); /* Destructor */

	PmergeMe	&operator=( PmergeMe const& rhs ); /* Copy assignment operator */

	void	printSTLs( void );
	void	fillSTLs( std::string const& str );
	void	sort( void );
	//Vector sorting
	void	sortVector( int left, int right );
	void	vectorInsertSort( int left, int right );
	//List sorting
	void	sortList( std::list<int>::iterator begin, std::list<int>::iterator end );
	void	listInsertSort( std::list<int>::iterator begin, std::list<int>::iterator end );

	double	getVectorTime( void ) const;
	double	getListTime( void ) const;
	std::vector<int> const&	getVector( void ) const;
	std::list<int> const&	getList( void ) const;
};

#endif /* PMERGE_ME_HPP */