/***************************************************************
  Alexander Phan
  simulation.cpp
  Project 3

  This file contains the function definitions for Simulation class.
 ***************************************************************/

#include "simulation.hpp"

Simulation::Simulation()
{
}

void Simulation::LoadMatrix()
{
	std::vector<std::vector<double>> adjMatrix(20, std::vector<double>(20, 0));
	std::ifstream infile("distances.txt");
	if (!infile) 
	{
		std::cerr << "Error: unable to open input file\n";
		return;
	}

	double value;
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (i == j)
			{
				adjMatrix[i][j] = 0;
			}
			else 
			{
				infile >> value;
				adjMatrix[i][j] = value;
			}
		}
	}

	this->adjMatrix = adjMatrix;

}

void Simulation::BruteRun()
{
	long i;
	struct timeval * t;
	t = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(t,NULL);
	time_t startSec = t->tv_sec;
	
	bf.Algorithm(this->adjMatrix);
	std::cout << "Optimal Cost: " << bf.GetCost() << std::endl;
	
	gettimeofday(t,NULL);
	std::cout << "Time for brute force: ";
	printf("%ld Seconds %d Microseconds\n",t->tv_sec - startSec,t->tv_usec);
	
	return;
}

void Simulation::GeneticRun()
{
	long i;
	struct timeval * t;
	t = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(t,NULL);
	time_t startSec = t->tv_sec;

	g.Run();


	gettimeofday(t,NULL);
	std::cout << "Time for genetic: ";
	printf("%ld Seconds %d Microseconds\n",t->tv_sec - startSec,t->tv_usec);

	return;
}

void Simulation::Run()
{
	LoadMatrix();

	int numCities, populationSize, numGenerations, mutationRate;
	
	std::cout << "Enter the number of cities: ";
	std::cin >> numCities;

	std::cout << "Enter the number of individual tours in a given generation: ";
	std::cin >> populationSize;

	std::cout << "Enter the number of generations to run: ";
	std::cin >> numGenerations;

	std::cout << "Enter the mutation rate percentage: ";
	std::cin >> mutationRate;
	
	g.SetValues(numCities, populationSize, numGenerations, mutationRate);
	
	std::cout << std::endl;
	std::cout << "Number of Cities Ran: " << numCities << std::endl;

	NewMatrix(numCities);	
	g.SetMatrix(adjMatrix);

	BruteRun();

	GeneticRun();

	double bfcost = bf.GetCost(), gcost = g.GetCost();
	percentage = (((gcost - bfcost)/bfcost) * 100) + 100;
	std::cout << "Percent of Optimal Produced: " << percentage << std::endl;

}

void Simulation::NewMatrix(int numCities)
{
	std::vector<std::vector<double>> temp(numCities, std::vector<double>(numCities, 0));
	
	int value;
	for (int i = 0; i < numCities; ++i)
	{
		for (int j = 0; j < numCities; ++j)
		{
			temp[i][j] = this->adjMatrix[i][j];
		}
	}
	
	this->adjMatrix = temp;

}

