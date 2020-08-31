#ifndef FITNESS_H
#define	FITNESS_H



class Fitness
{
	
public:
	Fitness(float=0.0,float=0.0);
	~Fitness();
	
	float evaluateFitness(float,float); //evaluate fitness of Individual 
	virtual void setFitness(float);//set fitness with one argument
	virtual void setFitness(float,float);//set fitness with two argument
	virtual float getFitness() const;
	bool operator<(Fitness&);//check if one is less than the other fitness
	void print()const;
protected:
	float fitness;
	float input1;
	float input2;
		
};

#endif // !FITNESS_H