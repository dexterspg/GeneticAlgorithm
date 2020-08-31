#ifndef POPULATION_H
#define	POPULATION_H

//#include "Fitness.h"
#include "Individual.h"

static const int POPULATION_SIZE=50;
static const int PARENT_POOL_SIZE=5;
static const int OFFSPRING_POOL_SIZE=10*PARENT_POOL_SIZE;

class Population
{
	
public:
	Population();
	~Population();

	void initialize(); //initialize population
	int tournament_selection(); //get the winner out of three for the lowest fitness
	void select_parents(); //select randomly parents from winners of tournament selection
	void generate_offspring();//generate offspring from selected parents
	void gen_nextpopulation();
	void print()const;
	//void printBestFitness() const;


private:
	Individual *populationPtr;
	Individual *parentPtr;
	Individual *offspring1;
	Individual *offspring2;
};

#endif // !POPULATION_H
