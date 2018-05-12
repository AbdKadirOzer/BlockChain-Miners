#include "Blockchain.h"
#include "Utilizer.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
    /**
     * Constructor.
     *
     * @param id The ID of the Blockchain.
     */
Blockchain::Blockchain(int id):id(id)
{this->head = NULL;
}
    /**
     * Secondary Constructor.
     *
     * Important: Blockchain "owns" this Koin.
     *
     * @param id The ID of the Blockchain.
     * @param head The starting point of the Blockchain.
     */
Blockchain::Blockchain(int id, Koin *head):id(id)
{  this->head = head; }
    /**
     * Copy Constructor.
     *
     * The head should be deep copied.
     *
     * @param rhs The blockchain to be copied.
     */
Blockchain::Blockchain(const Blockchain& rhs):id(rhs.id){
	Koin * temp =  rhs.head;
	if(temp == NULL)return;
	this->head = new Koin( rhs.head->getValue() );
	temp = temp->getNext();
	Koin * temp2 = this->head;
	while(temp != NULL){
		Koin * koko  = new Koin(temp->getValue());
		temp2->setNext(koko);
		temp2 = temp2->getNext();
		temp = temp->getNext();
	}

}
    /**
     * Move Operator.
     *
     * RHS will relinquish the rights of the headKoin to LHS.
     * LHS's ID will not (cannot) be changed.
     *
     * Careful about memory-leaks!
     *
     * @param rhs The blockchain to be moved into this blockchain.
     * @return The modified blockchain.
     */
Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept {

//    Blockchain temp(rhs);
//    std::swap(this->head,rhs.head);
    Koin * tmp= this->head;
  while(tmp != NULL)
  {
    head = head->getNext();
    delete tmp;
    tmp = head;

  }
  Koin* tmp4 = rhs.getHead();
  this->head = new Koin(tmp4->getValue());
  tmp = head;
  while(tmp4->getNext() != NULL)
  {
    tmp4= tmp4->getNext();
    tmp->setNext( new Koin(tmp4->getValue()));
    tmp = tmp->getNext();
    
  }

    if(rhs.getHead() == NULL) return *this;
    Koin* temp3 = rhs.getHead()->getNext();
    Koin* temp2 = rhs.getHead()->getNext();
    while(temp3 != NULL ){
        temp2 = temp2->getNext();
        delete temp3;
        temp3 = temp2;
    }
    

    return *this;
}
    /**
     * No assignment with const rhs.
     *
     * @param rhs -noNeed-
     * @return -noNeed-
     */
Blockchain::~Blockchain(){
  Koin *tmp= this->head;
  Koin *tmp2 = this->head;
  if(sofistik == 1) return;
  while(tmp != NULL)
  {
    head = head->getNext();
    delete tmp;
    tmp = head;

}
}

int Blockchain::getID() const{return this->id;}
Koin* Blockchain::getHead() const{return this->head;}

    /**
     * Calculate the value of the blockchain.
     *
     * @return Total value of the Koins in the blockchain.
     */
double Blockchain::getTotalValue() const{
	Koin * tep = this->head;
	double sum=0;
	while( tep  != NULL){
		sum +=  tep->getValue();
		tep = tep->getNext();
    }

	return sum;}

    /**
     * Calculate the length of the koins end-to-end.
     *
     * @return The length of the blockchain.
     */
long Blockchain::getChainLength() const{
	Koin *tmp = this->head;
	long a=0;
	while(tmp != NULL){
		a=a+1;
		tmp = tmp->getNext();
	}
	return a;}

    /**
     * Prefix addition.
     *
     * Mine and insert the mined Koin at the end of the chain.
     */
void Blockchain::operator++(){
   Koin * tmp = this->head;
    Koin *minedKoin = new Koin(Utilizer::fetchRandomValue());
    if(tmp  == NULL)
    {   this->head = minedKoin;

    }
    else{

        while( tmp->getNext() != NULL)
        {
           tmp = tmp->getNext();
        }

        tmp->setNext(minedKoin);
    }  
    minedKoin->setNext(NULL);

}

    /**
     * Prefix decrement.
     *
     * Remove/destroy the last inserted Koin to the chain.
     * no-op if the head is nullptr.
     *
     * Important note:
     *
     * If a blockchain is created by a soft fork, its head cannot be deleted.
     */
void Blockchain::operator--(){
    Koin* tmp = this->head;
    Koin* tmp2 = this->head;
    if(tmp == NULL)
        return;
    else
    {   if(this->head->getNext() == NULL){
        if(head->yumos == 1) return;
        tmp->setNext(NULL);
        delete tmp;
        this->head=NULL;
              
        return;
    }

        while(tmp->getNext() != NULL)
        {   
            tmp=tmp->getNext();
            
        }
        while(tmp2->getNext() != tmp )
        {
            tmp2= tmp2->getNext();
        }
        if(tmp->yumos == 1)
            return;

        delete tmp;
        tmp2->setNext(NULL);
    }
}

    /**
     * Multiplication overload.
     *
     * Multiply the value of every Koin in the blockchain.
     *
     * @param multiplier The value to be multiplied with the values of the Koins.
     * @return The current blockchain.
     */
Blockchain& Blockchain::operator*=(int multiplier){
	Koin * tmp = this->head;
	while(tmp != NULL)
	{
		(*tmp) *= multiplier;
		tmp = tmp->getNext();
	}
	return *this;
}

    /**
     * Division.
     *
     * Divide the value of every Koin in the blockchain.
     *
     * @param divisor The value to divide the values of the Koins.
     * @return The current blockchain.
     */
Blockchain& Blockchain::operator/=(int divisor){
	Koin * tmp = this->head;
	while(tmp != NULL)
	{
		(*tmp) /= divisor;
		tmp = tmp->getNext();
	}
	return *this;
}
    /**
     * Stream overload.
     *
     * What to stream:
     *
     * Block -blockchainID-: headKoinStream (see Koin for stream example) (-totalValue-)
     *
     * Example:
     *
     * Block 6: 0.707--0.390--0.984--|(2.080)
     *
     * Edge case : Blockchain without head
     *
     * Block -blockchainID-: Empty.
     *
     * @param os Stream to be used.
     * @param blockchain Blockchain to be streamed.
     * @return The current stream.
     */
std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain){
	Koin * tempo =  blockchain.head;

	os<< "Block " <<  blockchain.id << ": ";

	int tmpint = Utilizer::koinPrintPrecision();
    
    if(tempo == NULL)
        os<<"Empty.";
	
    else{
        for(;tempo != NULL ; )
	{
		os << std::setprecision(tmpint)<< std::fixed << tempo->getValue() << "--";
		tempo = tempo->getNext();
	}
	os << "|";
	os << "(" << std::setprecision(tmpint) << std::fixed << blockchain.getTotalValue() << ")" ;
    }

}

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW
