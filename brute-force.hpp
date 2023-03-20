/***************************************************************
	Alexander Phan
   brute-force.hpp
	Project 3
 		
	This file will run a brute force algorithm to find the optimal cost.
 ***************************************************************/

#ifndef BRUTEFORCE_HPP
#define BRUTEFORCE_HPP
#include <vector>
#include <algorithm>

const double INF = 1e9;

class BruteForce
{
	public:
		BruteForce() {this->optimalCost = 0;};
		void GenerateRoutes(int current, int n, std::vector<int>& path, std::vector<bool>& visited, double cost, const std::vector<std::vector<double>> adjMatrix, double& minCost, std::vector<int>& bestPath);
		void Algorithm(const std::vector<std::vector<double>> adjMatrix);
		double GetCost() {return this->optimalCost;};

	private:
		double optimalCost;

};

#endif
