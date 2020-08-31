#include<iostream>
#include<iomanip>
#include<cmath>
#include<ctime>
#include "Fitness.h"

using namespace std;


Fitness::Fitness(float x,float y):input1(x),input2(y){

	fitness=evaluateFitness(x,y);
}

void Fitness::setFitness(float f)
{
fitness=f;
}

void Fitness::setFitness(float x,float y) 
{
input1=x;
input2=y;
evaluateFitness(input1,input2);
}


float Fitness::getFitness() const{
	return fitness;
}

float Fitness::evaluateFitness(float x,float y){
	//Langermann function
	float fxy=0.0;
	float exp1;
	float exp2;
	const int m=5;
	const float a[5]={3.0,5.0,2.0,1.0,7.0};
	const float b[5]={5.0,2.0,1.0,4.0,9.0};
	const float c[5]={1.0,2.0,5.0,2.0,3.0};
	const float PI = 3.1415927;

	
	for (int i = 0; i<m; ++i)
	{
		exp1 = c[i] * exp(-pow(x - a[i], 2) / PI - pow(y - b[i], 2) / PI);
		exp2 = cos(PI*(pow(x - a[i], 2)) + PI*(pow(y - b[i], 2)));

		fxy += exp1*exp2;

		}
	return abs(fxy);
	
	
}


bool Fitness::operator<(Fitness& right)//check whether fitness is leser than the right.fitness
{
		
	if( fitness<right.fitness)
		return true;
	return false;
}

void Fitness::print() const {
	
	cout<<setprecision(2)<<fixed<<fitness;
	
	}

	
	

Fitness::~Fitness(){
	
}