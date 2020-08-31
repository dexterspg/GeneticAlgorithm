
#ifndef INDIVIDUAL_H
#define	INDIVIDUAL_H

#include "Fitness.h"
#include<string>

using namespace std;

class Individual:public Fitness
{
	friend ostream &operator<<( ostream &, const Individual &);
	static const int MAX_GENOTYPE=2;
	
public:
	Individual(float=0.0,float=0.0);
	~Individual();

	Individual(const Individual&);
	const Individual& operator=(const Individual&); //assignment operator
	Individual operator+(Individual&);//add operator
	Individual operator-(Individual&);//subtract operator
	Individual operator*(Individual&);//multiply operator
	bool operator!=(Individual&);//not equal conditional operator
	void mutate();//mutate genotype
	bool operator>(Individual&);//greater than operator
	//bool operator||(Individual&);
	void reset();//set a new genotype value for an individual
	void setIndividual(float,float); //set Individual genotype
	//float getFitness() const;
	virtual void print() const; //print

protected:
	
	float *genotypePtr;
	
};

#endif // !INDIVIDUAL_H

