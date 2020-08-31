#include<iostream>
#include <ctime>
#include<cmath>
#include<iomanip>
#include "Individual.h"

using namespace std;

Individual::Individual(float x, float y) :Fitness(x,y)
{

	genotypePtr=new float[MAX_GENOTYPE];//create genotype for an Individual..
	
	for(int i=0;i<MAX_GENOTYPE;++i)
		genotypePtr[i]=rand()% 9 +static_cast<float>(rand()% 9)/100; //..using random values with from 0 to 99.9
	
	fitness=evaluateFitness(genotypePtr[0],genotypePtr[1]);
			}



ostream &operator<<( ostream &output, const Individual& h) {

	for(int i=0;i<Individual::MAX_GENOTYPE;++i)
	output<<h.genotypePtr[i]<<" ";
	
return output;
}

Individual::Individual(const Individual &genotypeToCopy)
{
	 genotypePtr=new float[MAX_GENOTYPE];
	 for(int i=0;i<MAX_GENOTYPE;++i)
	 genotypePtr[i]=genotypeToCopy.genotypePtr[i]; //copy values
}

const Individual& Individual::operator=(const Individual& right)
{
	if(&right!=this) //avoid self-assignment
	{
	if(MAX_GENOTYPE!=right.MAX_GENOTYPE) //for array of different size
		{
	delete []genotypePtr; //deallocate original or release space
		genotypePtr=new float[MAX_GENOTYPE]; //space for copy
		}
	 for(int i=0;i<MAX_GENOTYPE;++i)
	 genotypePtr[i]=right.genotypePtr[i]; //copy array into object
	}
	fitness=evaluateFitness(genotypePtr[0],genotypePtr[1]);
	return *this;
}
	
Individual Individual::operator+(Individual& add) //adding genoype of two Individual
{
	Individual sum(add);
	for(int i=0;i<MAX_GENOTYPE;++i)
		sum.genotypePtr[i]=genotypePtr[i]+add.genotypePtr[i];
		
	return sum;
	
	}

Individual Individual::operator-(Individual& subtract) //subract genotype of two Individual
{
	Individual difference(subtract);
	for(int i=0;i<MAX_GENOTYPE;++i)
		difference.genotypePtr[i]=genotypePtr[i]-subtract.genotypePtr[i];
	
	return difference;
	
	}

Individual Individual::operator*(Individual& multiply) //multiply genoype of two Individual
{
	Individual multiplication(multiply);
	for(int i=0;i<MAX_GENOTYPE;++i)
		multiplication.genotypePtr[i]=genotypePtr[i]*multiply.genotypePtr[i];
	
return multiplication;
	
	}

void Individual::setIndividual(float xgene,float ygene)//set genes of an Individual
{
	genotypePtr[0]=xgene;
	genotypePtr[1]=ygene;
}

bool Individual::operator>(Individual& right)//check whether individual value is greater than the right.Individual
{

	if (genotypePtr[0] > right.genotypePtr[0] && genotypePtr[1] > right.genotypePtr[1])
			return true;
	return false;
}

void Individual::reset(){
	//reset the Individual and create a new random Individual genotype
	delete []genotypePtr; 

	genotypePtr=new float[MAX_GENOTYPE];

	for(int i=0;i<MAX_GENOTYPE;++i)
		genotypePtr[i]=rand()% 100 +static_cast<float>(rand()% 99)/100;
}

bool Individual::operator!=(Individual& right)//compare genoype of two Individual
{

	{
		for (int i = 0; i<MAX_GENOTYPE; ++i)
			if (genotypePtr[i] != right.genotypePtr[i])
				return true; //two genotype are not equal
	}
	return false;//otherwise
}

void Individual::mutate()
{
	for(int i=0;i<MAX_GENOTYPE;++i){
	float mutationPrecision=static_cast<float>(rand()%17+4); //[4,20]
	float mutationRange=0.10; //standard: 0.1
	float signNumber=static_cast<float>(rand()%1); //(-1,1)
	float u=static_cast<float>(rand()%2);//[0,1]
	
	if(signNumber==0)
		signNumber=-1;

	genotypePtr[i]=genotypePtr[i]+signNumber*mutationRange*pow(2,(-u*mutationPrecision));
	}
	
	
}
void Individual::print() const {
	
	cout<<"Genotype is: ";
	for(int i=0;i<MAX_GENOTYPE;++i)
	cout<<genotypePtr[i]<<" ";
	cout<<"Fitness: ";
	Fitness::print();
	cout<<endl;
	}

Individual::~Individual(){
	delete []genotypePtr;
}








/*

bool Individual::operator==(Individual& right)
{
	
	{
	for(int i=0;i<MAX_GENOTYPE;++i)
	if( genotypePtr[i]==right.genotypePtr[i])
		return true;
	}
	return false;
}


bool Individual::operator||(Individual& right)
{
	
	{
	for(int i=0;i<MAX_GENOTYPE;++i)
	if( genotypePtr[i]||right.genotypePtr[i])
		return true;
	}
	return false;
}


}*/