#include "Koin.h"
#include "Utilizer.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
   /**
     * Constructor.
     *
     * @param value The Koin's value.
     */
Koin::Koin(double value){

	this->value=value;
	this->next=NULL;
}

  
Koin::Koin(const Koin& rhs){
    this->value = rhs.value;
    this->next = rhs.next;
    }

Koin& Koin::operator=(const Koin& rhs){
    this->value = rhs.value;
    this->next= rhs.next;
    return *this;	
    }
Koin::~Koin(){
    	this->value=0;
    	this->next=NULL;
    }

double Koin::getValue() const{ return this->value;}

Koin* Koin::getNext() const{ return this->next;}
 
void Koin::setNext(Koin *next){
	this->next=next;
    }

bool Koin::operator==(const Koin& rhs) const{
	if(this->value - rhs.getValue()  < Utilizer::doubleSensitivity())
	{
		if (this->next == rhs.next)return true;
		else return false;

	}
    return false;
    }

bool Koin::operator!=(const Koin& rhs) const{
    if(this->value - rhs.getValue() >= Utilizer::doubleSensitivity())
    	return true;
    else
    	if(this->next != rhs.next)return true;
    return false;
    }

 
Koin& Koin::operator*=(int multiplier){
	this->value = (this->getValue() * multiplier);
}

Koin& Koin::operator/=(int divisor){
	this->value = (this->getValue() / divisor);
}

 
std::ostream& operator<<(std::ostream& os, const Koin& koin){
	Koin * tempo =  koin.next;

	int tmpint = Utilizer::koinPrintPrecision();
	os<< std::setprecision(tmpint) << koin.value << "--" ;
	for(;tempo != NULL ; )
	{
		os << std::setprecision(tmpint) << tempo->getValue() << "--";
		tempo = tempo->next;
	}
	os << "|";
}
