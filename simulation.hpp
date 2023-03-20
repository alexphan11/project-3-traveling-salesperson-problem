/***************************************************************
  Alexander Phan
  simulation.hpp
  Project 3

  This file will runs both algorithms to find the optimal cost.
 ***************************************************************/

#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "brute-force.hpp"
#include "genetic.hpp"
#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> /* for malloc */

class Simulation
{
	public:
		Simulation();
		void LoadMatrix();
		void BruteRun();
		void GeneticRun();
		void Run();
		void NewMatrix(int numCities);

	private:
		std::vector<std::vector<double>> adjMatrix;
		BruteForce bf;
		Genetic g;
		double percentage;
		

};

#endif
