#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int N = 100000;

namespace SHAPE 
{
	const int SQUARE = 1;
	const int CIRCLE = 0;
}

class Point
{
private:
	
	double x; 
	double y;

public:
	Point(double x, double y)
	{
		this->x = x; 
		this->y = y;
	}
	
	inline double getX() const
	{ 
		return this->x; 
	}
	
	inline double getY() const
	{ 
		return this->y; 
	}
};

class Perceptron
{
public:
	
	Perceptron(const int count_of_weight)
	{
		for (int i = 0; i < count_of_weight; i++)
		{
			vWeight.push_back( double(rand() % 100) / 100.0 );
		}
	}
	
	void learn(std::vector<Point> vPoints, std::vector<unsigned int> vTargetFunction)
	{
		for (int i = 0; i < vPoints.size(); i++)
		{
			unsigned int yi = activationFunction(vPoints[i]);
			int e = vTargetFunction[i] - yi;
	
			if (e != 0)
			{
				double x = vPoints[i].getX();
				double y = vPoints[i].getY();
				
				vWeight[0] += e * x;
				vWeight[1] += e * y;
				vWeight[2] += e;
			}
		}
	}

	void test(std::vector<Point> vPoints, std::vector<unsigned int> vTargetFunction)
	{
		for (int i = 0; i < vPoints.size(); i++)
		{
			unsigned int yi = activationFunction(vPoints[i]);
			int e = vTargetFunction[i] - yi;
			
			std::cout << e;
		}
	}
	
private:
	
	std::vector<double> vWeight;
	
	unsigned int activationFunction(Point const & p)
	{
		double a = vWeight[0] * p.getX() + vWeight[1] * p.getY() + vWeight[2];
		return a > 0 ? SHAPE::SQUARE : SHAPE::CIRCLE;
	}
	
};

std::vector<Point> vPoints;
std::vector<unsigned int> vTargetFunction;

void generatePoints(int n)
{
	srand(time(NULL));
	vPoints.clear();
	
	for (int i = 0; i < n; i++)
	{
		vPoints.push_back(Point(rand(), rand()));
	}
}


//Funkcja F(X) = 1.2x + 3
void generateTargetFunction()
{
	for (Point p : vPoints)
	{
		double y = 1.2 * p.getX() + 3;
		if ( y < p.getY() )
		{
			vTargetFunction.push_back(SHAPE::CIRCLE);
		}
		else 
		{
			vTargetFunction.push_back(SHAPE::SQUARE);
		}
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " [Number of points]" << std::endl;
		return -1;
	}
	
	N = atoi(argv[1]);
	
	srand(time(NULL));
	
	generatePoints(N);
	generateTargetFunction();
	Perceptron perceptron(3);
	
	perceptron.learn(std::vector<Point>(vPoints.begin(), vPoints.begin() + N * 0.8), vTargetFunction);
	perceptron.test(std::vector<Point>(vPoints.begin() + N * 0.8 + 1, vPoints.end() ), std::vector<unsigned int>(vTargetFunction.begin() + N * 0.8 + 1, vTargetFunction.end()));

	return 0;
}
