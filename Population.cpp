#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include "Population.h"

using namespace std;


Population::Population()/*:populationPtr()/*,fitnessPtr()*/ {

	populationPtr=NULL;
	
}


void Population::initialize() {

	populationPtr = new Individual[POPULATION_SIZE]; //initialize population
}
int Population::tournament_selection()
{
	
	const int number_of_individuals=3;
	int ind[number_of_individuals]={};

	do{//pick random three numbers corresponding the index from values 1 to population size

	for(int choice=0;choice<number_of_individuals;++choice)
		 ind[choice]=rand()% (POPULATION_SIZE-1)+1;
			
	}while(ind[0]==ind[1]||ind[0]==ind[2]); //three index should not be equal

	//cout<<endl;
	/*
	//****************print Individuals
	for(int choice=0;choice<number_of_individuals;++choice)
		cout<<"choice "<<choice+1<<" is "<<ind[choice]+1<<endl;
	
	//print Individuals respective fitness
	for(int choice=0;choice<number_of_individuals;++choice)
	cout<<"Fitness level "<<choice+1<<" is "<<fixed<<setprecision(2)<<populationPtr[ind[choice]].getFitness()<<endl;
	*/
	cout<<endl;

	Individual minFitness; //store the lowest fitness
	int best_out_of_three=0; //the index of the lowest fitness

	minFitness.setFitness(1.0); //set minimum to 1

	for(int choice=0;choice<number_of_individuals;++choice)
	{
		
	if(populationPtr[ind[choice]]<minFitness)  
	{
		minFitness=populationPtr[ind[choice]]; //lowest fitness value
		best_out_of_three=ind[choice];   //store the index of lowest fitness
		}
	}

	//**********Print best fitness
	//cout<<"best fitness: "<<fixed<<setprecision(2)<<populationPtr[best_out_of_three].getFitness()<<endl; 
	//cout<<"corresponding genotype: "<<populationPtr[best_out_of_three]<<endl;
	
	return best_out_of_three; //return index of winner of tournament selection

}

void Population::select_parents()
{
		
	parentPtr=new Individual[PARENT_POOL_SIZE]; //declare for parent candidate
	
	//cout<<endl;

	for(int parentCount=0;parentCount<PARENT_POOL_SIZE;++parentCount)
	{
		//cout<<"Number: "<<parentCount+1<<endl;
		int parentPool=tournament_selection(); //store value of winner of tournament selection to parent pool
		parentPtr[parentCount]=populationPtr[parentPool]; //copy the value of genotype from population to parent
					}
	/*
	//***********Print parents
	cout<<endl<<endl<<endl;
		for(int parentCount=0;parentCount<PARENT_POOL_SIZE;++parentCount)
	{
		cout<<"Parent"<<parentCount+1<<": "<<parentPtr[parentCount]<<endl;
		cout<<"Fitness: "<<parentPtr[parentCount].getFitness()<<endl;
		cout<<endl;
			}*/
			
		}

void Population::generate_offspring()
{
	
	const int number_of_parents=2; //mother and father
	int parent[number_of_parents]={};
	
	//crossover
	Individual scale1; 
	Individual scale2;
	
	scale1.setIndividual(0.5,0.1);//set crossover scale for parent 1
	scale2.setIndividual(0.1,0.5);//set crossover scale for parent 2

	offspring1=new Individual[OFFSPRING_POOL_SIZE/2]; //declare arrary of offsprings1
	offspring2=new Individual[OFFSPRING_POOL_SIZE/2];//declare array of offsprings2

	for(int choice=0;choice<OFFSPRING_POOL_SIZE/2;++choice){

	do{ //pick random 2 numbers corresponding the index from values 1 to parent pool size

	for(int count=0;count<number_of_parents;++count)
		 parent[count]=rand()% PARENT_POOL_SIZE;
				
	}while(parent[0]==parent[1]);  //parent 1 and parent 2 should be different
	

	//offspring genotype formula : offspring = parent 1 -scale *(parent 2-parent 1)
	offspring1[choice]=parentPtr[parent[0]]+scale1*(parentPtr[parent[1]]-parentPtr[parent[0]]);
	offspring2[choice]=parentPtr[parent[0]]+scale2*(parentPtr[parent[1]]-parentPtr[parent[0]]);
	
	/*
	//*************print crossover
	cout<<endl<<endl;
	cout<<"Number :"<<choice+1 <<endl;
	cout<<"Parent 1: "<<parent[0]+1<<" Parent 2: "<<parent[1]+1<<endl;
	cout << "Parent 1 genotype: " << parentPtr[parent[0]] << "Fitness: " << parentPtr[parent[0]].getFitness()<<endl
		<< "Parent 2 genotype: " << parentPtr[parent[1]] << "Fitness: " << parentPtr[parent[1]].getFitness()<<endl;
	cout << "offspring 1: " << offspring1[choice] << "Fitness: " << offspring1[choice].getFitness()<<endl;
	cout << "offspring 2: " << offspring2[choice] << "Fitness: " << offspring2[choice].getFitness() << endl;
	*/	
	}

	//mutate

	for(int choice=0;choice<OFFSPRING_POOL_SIZE/2;++choice)
	{
	offspring1[choice].mutate();
	offspring2[choice].mutate();
	
	/*
	//*************print mutation
	cout<<endl<<endl<<"Mutation"<<endl;
	cout<<"Number :"<<choice+1 <<endl;
	cout << "offspring 1: " << offspring1[choice] << "Fitness: " << offspring1[choice].getFitness()<<endl;
	cout << "offspring 2: " << offspring2[choice] << "Fitness: " << offspring2[choice].getFitness() << endl;
	*/
	}


	
}

void Population::gen_nextpopulation()
{
	
	vector <Individual> jointPool(PARENT_POOL_SIZE+OFFSPRING_POOL_SIZE);
	
	int count=0;

	for( size_t i=0;i<PARENT_POOL_SIZE; ++i)
			jointPool[i]=parentPtr[i];
					
	for( size_t i=PARENT_POOL_SIZE;i<(PARENT_POOL_SIZE+OFFSPRING_POOL_SIZE/2); ++i)
			jointPool[i]=offspring1[count++];	

	count=0;

	for( size_t i=(PARENT_POOL_SIZE+OFFSPRING_POOL_SIZE/2);i<jointPool.size(); ++i)
			jointPool[i]=offspring2[count++];	

	
	//**************print joint pool
	cout<<endl<<endl<<"Joint Pool"<<endl;
	for( size_t i=0;i<jointPool.size(); ++i)
		cout<<"Number :"<<i+1<<" "<<fixed<<setprecision(2)<<jointPool[i]<<endl;
	
	for(int populationCount=0;populationCount<POPULATION_SIZE;++populationCount)
	{
		int newPopulation=tournament_selection(); //store value of winner of tournament selection to new population pool
		populationPtr[populationCount]=jointPool[newPopulation]; //copy the value of genotype from joint to new population
			}

}

void Population::print() const {

	for(int i=0;i<POPULATION_SIZE;++i)   
		{
		cout<<"Person "<<i+1<<" "<<"Genotype: [ "<<populationPtr[i]<<"] Fitness value: ";
		cout << fixed << setprecision(2)<< populationPtr[i].getFitness();
		cout<<endl;
	}
	cout<<endl;
		
}
/*
void printBestFitness() const {

	for(int populationCount=0;populationCount<POPULATION_SIZE;++populationCount)


}*/


Population::~Population(){

	delete [] populationPtr;
	delete [] parentPtr;
	delete [] offspring1;
	delete [] offspring2;
}





/*for(int i=0;i<POPULATION_SIZE;++i)
	{
		
	for(int j=i+1;j<POPULATION_SIZE;++j)
	   {	
		
			for(int k=0;k!=i && k<i;++k)
			{
				if((populationPtr[i]==populationPtr[j])||(populationPtr[i]==populationPtr[k])) //if two genotypes are the same
				populationPtr[i].reset();  //set a new value for the current individual
			}
	   }
	}*/