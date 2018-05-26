#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace SHAPE 
{
	const double SQUARE = 1.0;
	const double CIRCLE = 0.0;
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
	
	// tag::learn[]
	void learn(std::vector<Point> vPoints, std::vector<unsigned int> vTargetFunction)
	{
		for (int i = 0; i < vPoints.size(); i++)
		{
			unsigned int yi = activationFunction(vPoints[i]);
			int e = vTargetFunction[i] - yi;
			if (e != 0)	// <1> 
			{
				double x = vPoints[i].getX();
				double y = vPoints[i].getY();
				vWeight[0] += e * x;
				vWeight[1] += e * y;
				vWeight[2] += e;
			}
		}
	}
	// end::learn[]
	
	// tag::test[]
	unsigned int test(std::vector<Point> vPoints, std::vector<unsigned int> vTargetFunction)
	{
		unsigned int result = 0;
		for (int i = 0; i < vPoints.size(); i++)
		{
			unsigned int yi = activationFunction(vPoints[i]);
			int e = vTargetFunction[i] - yi;
			if (e != 0) result++;
			std::cout << e;
		}
		return result;
	}
	// end::test[]
	
	std::vector<double> getWeights()
	{
		return this->vWeight;
	}
	
private:
	
	std::vector<double> vWeight;
	
	// tag::activationFunction[]
	unsigned int activationFunction(Point const & p)
	{
		double a = vWeight[0] * p.getX() + vWeight[1] * p.getY() + vWeight[2];
		return a > 0 ? SHAPE::SQUARE : SHAPE::CIRCLE;
	}
	// end::activationFunction[]
	
};

std::vector<Point> vPoints;
std::vector<unsigned int> vTargetFunction;

void generatePoints(int n)
{
	srand(time(NULL));
	vPoints.clear();
	
	unsigned int p = 0;
	int x = n; 
	for ( int x = n; (x /= 10) != 0; p++);
	
	for (int i = 0; i < n; i++)
	{
		vPoints.push_back(Point( (rand() % (n * (int)pow(10, p))) / pow(10, p - 1), (rand() % (n * (int)pow(10, p))) / pow(10, p - 1)));
	}
}


//Funkcja F(X) = 1.2x + 3
void generateTargetFunction()
{
	for (Point p : vPoints)
	{
		double y = 1.2 * p.getX() + 3.0;
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
	
	int N = atoi(argv[1]);
	
	srand(time(NULL));
	
	generatePoints(N);
	generateTargetFunction();
	Perceptron perceptron(3);
	
	perceptron.learn(std::vector<Point>(vPoints.begin(), vPoints.begin() + N * 0.8), vTargetFunction);
	unsigned int result = perceptron.test(std::vector<Point>(vPoints.begin() + N * 0.8, vPoints.end() ), std::vector<unsigned int>(vTargetFunction.begin() + N * 0.8, vTargetFunction.end()));
	
	std::cout << "\nTarget function: F(x) = 1.2x + 3" << std::endl;
	std::vector<double> vp = perceptron.getWeights();
	std::cout << "Perceptron function: F(x) = " << vp[0]/-vp[1] << "x + " << vp[2] << std::endl;
	std::cout << "Size of learn set: " << N * 0.8 << std::endl;
	std::cout << "Size of test set: " << N - N * 0.8 << std::endl;
	std::cout << "Mistakes: " << result << std::endl;

	return 0;
}
