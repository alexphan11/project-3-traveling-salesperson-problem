/***************************************************************
  Alexander Phan
  genetic.hpp
  Project 3

  This file will run a genetic algorithm to find the optimal cost.
***************************************************************/

#ifndef GENETIC_HPP
#define GENETIC_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

const double INFI = 1e9;
const double ELITE_RATE = 0.1;

class Genetic
{
	public:
		Genetic();
		double GetCost();
		void SetMatrix(std::vector<std::vector<double>> adjMatrix);
		void SetValues(int numCities, int populationSize, int numGenerations, double mutationRate);
		std::vector<int> GenerateRandomPath(int n);
		double CalculatePathDistance(const std::vector<int>& path, const std::vector<std::vector<double>>& adjMatrix);
		std::vector<std::vector<int>> GeneratePopulation(int n, int populationSize);
		std::vector<int> Crossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
		void Mutate(std::vector<int>& path);
		std::vector<std::vector<int>> Elitism(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix);
		std::vector<std::vector<int>> GenerateNextGeneration(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix);
		std::vector<int> FindBestPath(const std::vector<std::vector<int>>& population, const std::vector<std::vector<double>>& adjMatrix);
		void Run();

	private:
		int populationSize;
		int numCities;
		int numGenerations;
		double mutationRate;
		double bestCost;
		std::vector<std::vector<double>> adjMatrix;

};

#endif
