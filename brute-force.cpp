/***************************************************************
  Alexander Phan
  brute-force.cpp
  Project 3
  This file contains the function definitons for the BruteForce class.
***************************************************************/

#include "brute-force.hpp"

void BruteForce::GenerateRoutes(int current, int n, std::vector<int>& path, std::vector<bool>& visited, double cost, const std::vector<std::vector<double>> adjMatrix, double& minCost, std::vector<int>& bestPath)
{
	// Base case: all nodes have been visited
	if (path.size() == n) 
	{
		if (cost + adjMatrix[current][0] < minCost) 
		{
			// Update best path and cost
			bestPath = path;
			bestPath.push_back(0);
			minCost = cost + adjMatrix[current][0];
		}
		return;
	}

	// Recursive case: generate all possible paths from current node
	for (int i = 1; i < n; i++) 
	{
		if (!visited[i]) 
		{
			visited[i] = true;
			path.push_back(i);
			GenerateRoutes(i, n, path, visited, cost + adjMatrix[current][i], adjMatrix, minCost, bestPath);
			path.pop_back();
			visited[i] = false;
		}
	}
}

void BruteForce::Algorithm(std::vector<std::vector<double>> adjMatrix)
{
	int n = adjMatrix.size();
	double minCost = INF;
	std::vector<int> bestPath;
	std::vector<bool> visited(n, false);
	visited[0] = true;
	std::vector<int> path;
	path.push_back(0);
	GenerateRoutes(0, n, path, visited, 0.0, adjMatrix, minCost, bestPath);
	optimalCost = minCost;	 
}
