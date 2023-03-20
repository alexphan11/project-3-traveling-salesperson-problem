/***************************************************************
	Alexander Phan
	genetic.cpp
	Project 3
  	   	 		
	This file contains the function definitions of Genetic class.
***************************************************************/

#include "genetic.hpp"

Genetic::Genetic()
{
	this->populationSize = 0;
	this->numCities = 0;
	this->numGenerations = 0;
	this->mutationRate = 0;
	this->bestCost = 0;
}

double Genetic::GetCost()
{
	return bestCost;
}

void Genetic::SetMatrix(std::vector<std::vector<double>> adjMatrix)
{
	this->adjMatrix = adjMatrix;
}

void Genetic::SetValues(int numCities, int populationSize, int numGenerations, double mutationRate)
{
	this->numCities = numCities;
	this->populationSize = populationSize;
	this->numGenerations = numGenerations;
	this->mutationRate = mutationRate;
}

// Generate a random permutation of integers from 0 to n-1
std::vector<int> Genetic::GenerateRandomPath(int n) 
{
	std::vector<int> path(n);
	for (int i = 0; i < n; i++) 
	{
		path[i] = i;
	}
	random_shuffle(path.begin(), path.end());
	return path;
}

// Calculate the total distance of a path given an adjacency matrix
double Genetic::CalculatePathDistance(const std::vector<int>& path, const std::vector<std::vector<double>>& adjMatrix)
{
	double distance = 0.0;
	int n = path.size();
	for (int i = 0; i < n - 1; i++) 
	{
		distance += adjMatrix[path[i]][path[i+1]];
	}
	distance += adjMatrix[path[n-1]][path[0]];
	return distance;
}

// Generate a population of random paths
std::vector<std::vector<int>> Genetic::GeneratePopulation(int n, int populationSize) 
{
	std::vector<std::vector<int>> population(populationSize);
	for (int i = 0; i < populationSize; i++) 
	{
		population[i] = GenerateRandomPath(n);
	}
	return population;
}

// Perform crossover operation on two parent paths to produce a child path
std::vector<int> Genetic::Crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) 
{
	int n = parent1.size();
	std::vector<int> child(n, -1);
	int startIndex = rand() % n;
	int endIndex = rand() % n;
	if (startIndex > endIndex) 
	{
		std::swap(startIndex, endIndex);
	}
	for (int i = startIndex; i <= endIndex; i++) 
	{
		child[i] = parent1[i];
	}
	int j = 0;
	for (int i = 0; i < n; i++) 
	{
		if (child[i] == -1) 
		{
			while (find(child.begin(), child.end(), parent2[j]) != child.end()) 
			{
				j++;
			}
			child[i] = parent2[j];
		}
	}
	return child;
}

// Perform mutation operation on a path
void Genetic::Mutate(std::vector<int>& path) 
{
	int n = path.size();
	for (int i = 0; i < n; i++) 
	{
		if (rand() / (double)RAND_MAX < mutationRate) 
		{
			int j = rand() % n;
			std::swap(path[i], path[j]);
		}
	}
}

// Perform elitism operation by selecting the best paths from a population
std::vector<std::vector<int>> Genetic::Elitism(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix) 
{
	int populationSize = population.size();
	int eliteSize = round(ELITE_RATE * populationSize);
	std::vector<std::pair<double, std::vector<int>>> fitnessPairs(populationSize);
	for (int i = 0; i < populationSize; i++) 
	{
		double fitness = CalculatePathDistance(population[i], adjMatrix);
		fitnessPairs[i] = make_pair(fitness, population[i]);
	}
	sort(fitnessPairs.begin(), fitnessPairs.end());
	std::vector<std::vector<int>> elitePaths(eliteSize);
	for (int i = 0; i < eliteSize; i++) 
	{
		elitePaths[i] = fitnessPairs[i].second;
	}
	return elitePaths;
}
// Generate the next generation of paths by performing crossover and mutation operations
std::vector<std::vector<int>> Genetic::GenerateNextGeneration(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix) 
{
	int populationSize = population.size();
	std::vector<std::vector<int>> nextGeneration(populationSize);
	std::vector<std::vector<int>> elitePaths = Elitism(population, adjMatrix);
	int eliteSize = elitePaths.size();
	for (int i = 0; i < eliteSize; i++) 
	{
		nextGeneration[i] = elitePaths[i];
	}
	for (int i = eliteSize; i < populationSize; i++) 
	{
		int parentIndex1 = rand() % (populationSize - eliteSize);
		int parentIndex2 = rand() % (populationSize - eliteSize);
		std::vector<int> child = Crossover(population[parentIndex1], population[parentIndex2]);
		Mutate(child);
		nextGeneration[i] = child;
	}
	return nextGeneration;
}

// Find the path with the minimum total distance in a population
std::vector<int> Genetic::FindBestPath(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix) 
{
	int populationSize = population.size();
	int bestIndex = 0;
	double bestDistance = INFI;
	for (int i = 0; i < populationSize; i++) 
	{
		double distance = CalculatePathDistance(population[i], adjMatrix);
		if (distance < bestDistance) 
		{
			bestIndex = i;
			bestDistance = distance;
		}
	}
	return population[bestIndex];
}

void Genetic::Run()
{
	srand(time(NULL));
	
	std::vector<std::vector<int>> population = GeneratePopulation(numCities, this->populationSize);
	for (int i = 0; i < this->numGenerations; i++) 
	{
		population = GenerateNextGeneration(population, this->adjMatrix);
		CalculatePathDistance(FindBestPath(population, this->adjMatrix), this->adjMatrix);
	}

	std::vector<int> bestPath = FindBestPath(population, this->adjMatrix);
	bestCost = CalculatePathDistance(bestPath, this->adjMatrix);
	std::cout << "Genetic Cost: " << bestCost << std::endl;
}
