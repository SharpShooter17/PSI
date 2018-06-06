/**
 * f(x) = 2(x2+1), gdzie x ? <1...127>
 */
 
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

union population_t
{
	unsigned char x;
	struct 
	{
		unsigned char x1 : 1;
		unsigned char x2 : 1;
		unsigned char x3 : 1;
		unsigned char x4 : 1;
		unsigned char x5 : 1;
		unsigned char x6 : 1;
		unsigned char x7 : 1;
		unsigned char x8 : 1;
	};
};

void show_population(const population_t & p)
{
	std::cout << (int)p.x << "\t" << (int)p.x1 << (int)p.x2 << (int)p.x3 << (int)p.x4 << (int)p.x5 <<(int)p.x6 << (int)p.x7 <<(int)p.x8 << std::endl;
}

population_t cross( population_t p1, population_t p2, int locus )
{
	p1.x = p1.x << 8 - locus;
	p1.x = p1.x >> 8 - locus;
	p2.x = p2.x >> locus;
	p2.x = p2.x << locus;		
	p1.x = p1.x | p2.x;
	return p1;
}

population_t mutation(const population_t & population, int locus)
{
	population_t p = population;
	p.x = p.x >> locus - 1;
    p.x = p.x << locus - 1;
    p.x = p.x << 8 - locus;
    p.x = p.x >> 8 - locus;
    if (p.x == 0) 
    {
        p.x = 1;
        p.x = p.x << locus -1;
    }
    p.x = p.x ^ population.x;
	return p;
}

int adaptation(const population_t & p)
{
	return 2 * ( (int)p.x * (int)p.x + 1);
}

int main()
{
	const int N = 10;
	const int era = 100;
	const int crossing_probability = 85;
	const int mutation_probability = 20;
	
	std::vector<population_t> population;
	//Generowanie populacji pocz¹tkowej
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		population_t p;
		p.x = rand() % 128;
		population.push_back(p);
		show_population(population[i]);
	}	
	
	for (int e = 0; e < era; e++)
	{
		//Selekcja
		int adapt[N];
		int sumOfAdaptaion = 0;
		for (int i = 0; i < N; i++)
		{
			adapt[i] = adaptation(population[i]);
			sumOfAdaptaion += adapt[i];
		}
		//prawdopodobieñstwo selekcji
		double probability[N];
		for(int i = 0; i < N; i++)
		{
			probability[i] = (double)adapt[i] / (double)sumOfAdaptaion * 100.0;
		}
		//kolo ruletki 
		std::vector<population_t> next_population;
		for (int i = 0; i < N; i++)
		{
			double r = (rand() % 10000) / 100.0;
			double sum = 0.0;
			for (int j = 0; j < N; j++)
			{
				sum += probability[j];
				if ( sum >= r )
				{
					next_population.push_back(population[j]);
					break;
				}
			}
		}
		//krzy¿owanie
		for (int i = 0; i < N; i += 2)
		{		
			int index = rand() % next_population.size();
			population_t p1 = next_population[index];
			next_population.erase(next_population.begin() + index);
			index = rand() % next_population.size();
			population_t p2 = next_population[index];
			next_population.erase(next_population.begin() + index);
			
			if ( rand() % 101 > crossing_probability)
			{
				population[i] = p1;	
				population[i + 1] = p2;
			} else 
			{			
				int locus = (rand() % 8) + 1;
				population[i] = cross(p1, p2, locus);			
				population[i + 1] = cross(p2, p1, locus);
			}
		}
		//mutacja
		for ( int i = 0; i < N; i++ )
		{
			if (rand() % 101 <= mutation_probability)
			{
				mutation(population[i], (rand() % 8) + 1);
			}
		}
	}
	
	std::cout << "-----------------------\n";
	
	for (int i = 0; i < N; i++)
	{
		show_population(population[i]);
	}	
	
	return 0;
}