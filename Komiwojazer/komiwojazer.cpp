#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime> 
#include <cstdio>
#include <cmath>
#include <algorithm>

class City
{
	private:
	double x;
	double y;
	bool visited;
	
	public:
	City(double x, double y)
	{
		this->visited = false;
		this->x = x;
		this->y = y;
	}
	double getX() const {return this->x;}
	double getY() const {return this->y;}
	double operator-(const City& c) const
	{
		return sqrt( (this->x - c.getX())*(this->x - c.getX()) + (this->y - c.getY())*(this->y - c.getY()));
	}
	void setVisited() { this->visited = true; }
	bool getVisited() const { return this->visited; }
	
	bool operator<(const City & c)
	{
		return this->x < c.getX();
	}
	
};

void cities(std::vector<City> const & c)
{
	for (int i = 0; i < c.size(); i++)
	{
		std::cout << "City: N#" << i << " x: " << c[i].getX() << " y: " << c[i].getY() << std::endl;
	}
}

double distance(std::vector<City> const c)
{
	double result = 0.0;
	
	for (int i = 0; i < (c.size() -1); i++)
	{
		result += c[i + 1] - c[i];
	}
	return result;
}

void nearestNeighbor(std::vector<City> c)
{
	City actual = c[0];
	c.erase(c.begin());
	std::vector<City> result;
	result.push_back(actual);
	
	std::clock_t t = std::clock();
	
	while(!c.empty())
	{
		int min = 0;
		for (int i = 1; i < c.size(); i++)
		{
			if ( (actual - c[i]) < (actual - c[min]) )
			{
				min = i;
			}
		}
		result.push_back( c[min] );
		actual = c[min];
		c.erase(c.begin() + min);
	}
	
	t = std::clock() - t;
	
	std::cout << "Nearest Neighbor Distance: " << distance(result) << " Time: " << ((double)t)/CLOCKS_PER_SEC << "s" << std::endl;
}

void bruteForce(std::vector<City> c)
{
	std::vector<City> result = c;
	double minDistance = distance(c);
	
	std::clock_t t = std::clock();
	
	while(std::next_permutation(c.begin(), c.end()) )
	{
		double dist = distance(c);
		if (dist < minDistance )
		{
			minDistance = dist;
			result = c;
		}
	}
	
	t = std::clock() - t;
	
	std::cout << "Brute Force Distance: " << distance(result) << " Time: " << ((double)t)/CLOCKS_PER_SEC << "s" << std::endl;
}

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cerr << "search.exe [Num of nodes]" << std::endl;
		return -1;
	}
	
	srand (time(NULL));
	int n = atoi(argv[1]);
	std::vector<City> c;
	
	for (int i = 0; i < n; i++)
	{
		c.push_back(City(rand() % 100, rand() % 100));
	}
	
	std::cout << "Nodes: " << c.size() << std::endl;
	bruteForce(c);
	nearestNeighbor(c);		
	std::cout << std::endl;
	
	return 0;
}