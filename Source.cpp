#include<iostream>
#include<ctime>
#include<cmath>
#include<iomanip>
#include "Individual.h"
#include "Fitness.h"
#include "Population.h"
#include <string>
#include <stdio.h>
//#include <limits>

using namespace std;

int main()
{
	srand(unsigned(time(0)));
	
	int count=0;
	int terminationCount=8;

	Population p;
	p.initialize();
	p.print();
	
	//do
	//{
	//count++;

	p.select_parents();
	p.generate_offspring();
	p.gen_nextpopulation();

	//}while(count<terminationCount);
	
	p.print();

	getchar();
	return 0;
}