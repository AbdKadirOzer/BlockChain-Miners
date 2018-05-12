#include "Miner.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "Utilizer.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
/*
     * Constructor.
     *
     * @param name Name of the miner.
     */
Miner::Miner(std::string name){
        this->name = name;
        this->countid = 0;

    }
Miner::~Miner(){
       int i=0;


        while(i < countid)
        {
            delete blocks[i];
            i++;
        }

    }


    /**
     * Create a new blockchain with the next available ID.
     */
void Miner::createNewBlockchain(){
        Blockchain* nw= new Blockchain(countid);
        this->blocks.push_back(nw);
        countid++;

    }

    /**
     * Start mining with the given count.
     * For every count, a single Koin will be produced in each blockchain.
     *
     * Operations must be ordered according to the blockchainIDs.
     *
     * @param cycleCount The count which the blockchains will be run for.
     */
void Miner::mineUntil(int cycleCount){
        int i=0;
        Blockchain* tmp;
        while(cycleCount)
            {
            while(i<countid)
            {
                tmp = blocks[i];
                ++(*tmp);
                i++;
            }
            i=0;
            cycleCount--;
            }
    }

    /**
     * Start de-mining with the given count.
     * For every count, the last Koin in the blockchain must be destroyed.
     * no-op for Blockchain if it doesn't have any (left).
     *
     * Operations must be ordered according to the blockchainIDs.
     *
     * @param cycleCount The count which the blockchains will be run for.
     */
void Miner::demineUntil(int cycleCount){
        int i=0;
        Blockchain* tmp;
        while(cycleCount){
            while(i<countid)
            {
                tmp = blocks[i];
                --(*tmp);
                i++;
            }
            i=0;
            cycleCount--;}
    }

    /**
     * Calculate the value of the miner, which is the sum of the blockchains' value.
     *
     * Soft-forks DO NOT constitute for the total value of the miner.
     *
     * @return Total value of the miner.
     */
double Miner::getTotalValue() const{
        double sum =0;
        int i=0;
        Blockchain* tmp;
        while(i<countid)
        {
            tmp = blocks[i];
            if(tmp->sofistik == 1)
                sum += 0;
            else
                sum += tmp->getTotalValue();
            
            i++;
        } 

        return sum ;
    
    }

    /**
     * Return the count of the blockchains.
     *
     * @return Total count of the blockchains.
     */
long Miner::getBlockchainCount() const{
        if(this->blocks[0] == NULL)
            return 0;
        else
            return (countid);
    }

    /**
     * Indexing.
     *
     * Find the blockchain with the given id.
     *
     * @return The blockchain with the given id. nullptr if not exists.
     */
Blockchain* Miner::operator[](int id) const{
        if(id >= countid)
            return NULL;
        return this->blocks[id];

    }

    /**
     *  Shallow-copy the blockchain with given ID.
     *
     *  How-To:
     *  1) Fetch the blockchain in the miner with given ID.
     *  2) If not exists, no-op.
     *  3) Fetch the next available ID for the blockchain.
     *  4) Create a new blockchain with the new ID, and with the head as the original of the last Koin of the blockchain.
     *  5) Hence, a modification to the newly created blockchain will also affect the old blockchain, but only ...
     *  6) ... after the head (head included). And vice versa.
     *  7) Save the newly created blockchain in the miner.
     *
     *  @param blockchainID The blockchain ID to be forked.
     *
     *  @return true if the blockchain with given ID exists, otherwise false.
    */
bool Miner::softFork(int blockchainID)
    {
    if(blockchainID >= countid)
        return false;
    Blockchain* tmp = this->blocks[blockchainID];
    Koin* tmp2;
    if(tmp == NULL  )
        return false;

    tmp2 = tmp->getHead();
    while(tmp2->getNext() != NULL)
    {
        
        tmp2= tmp2->getNext();
    }
    tmp2->yumos =1;
    Blockchain* nw = new Blockchain(this->countid, tmp2);
    nw->sofistik = 1;
    this->blocks.push_back(nw);

    countid++;




    return true;
    }

    /**
     *  Deep-copy the blockchain with given ID.
     *
     *  How-To:
     *  1) Fetch the blockchain in the miner with given ID.
     *  2) If not exists, no-op.
     *  3) Else, fetch the next available ID for the blockchain.
     *  4) Create a new blockchain with the new ID, and with the head as a copy of the last Koin of the blockchain.
     *  5) Any changes made in the new blockchain will NOT affect the old blockchain. And vice versa.
     *  6) Save the newly created blockchain in the miner.
     *
     *  @param blockchainID The blockchain ID to be forked.
     *
     *  @return true if the blockchain with given ID exists, otherwise false.
    */
bool Miner::hardFork(int blockchainID)
    {
    if(blockchainID >= countid)
        return false;
    Blockchain* tmp = this->blocks[blockchainID];
    Koin* tmp2;
    if(tmp == NULL )
        return false;
    
    tmp2 = tmp->getHead();
    while(tmp2->getNext() != NULL)
    {
        tmp2= tmp2->getNext();
    }
    Koin* nw2 = new Koin(tmp2->getValue());
    Blockchain* nw = new Blockchain(this->countid,nw2);
    this->blocks.push_back(nw);
    countid++;

    return true;
    }

    /**
     * Stream overload.
     *
     * What to stream:
     *
     * -- BEGIN MINER --
     * Miner name: -minerName-
     * Blockchain count: -getBlockchainCount()-
     * Total value: -getTotalValue()-
     *
     * Block -blockchainID-: headKoin (see Blockchain for stream example)
     * .
     * .
     * .
     * Block -lastBlockchainID-: headKoin (see Blockchain for stream example)
     *
     * -- END MINER --
     *
     * Example:
     *
     * -- BEGIN MINER --
     * Miner name: BTCMiner
     * Blockchain count: 5
     * Total value: 2.519
     *
     * Block 0: 0.491--0.103--0.529--|(1.123)
     * Block 1: Empty.
     * Block 2: Empty.
     * Block 3: Empty.
     * Block 4: 0.400--0.924--0.072--|(1.396)
     *
     * -- END MINER --
     *
     * @param os Stream to be used.
     * @param miner Miner to be streamed.
     * @return The current stream.
     */
std::ostream& operator<<(std::ostream& os, const Miner& miner){
    int pres=Utilizer::koinPrintPrecision();
    int i=0;
    os<< std::fixed <<std::setprecision(pres)<< "-- BEGIN MINER --\n" << "Miner name: " << miner.name ; 
    os << "\nBlockchain count: " <<miner.getBlockchainCount();
    os << "\n" << "Total value: " << miner.getTotalValue() << "\n" << "\n";
    while(i < miner.countid)
    {
        os<<(*miner.blocks[i]) << "\n";
        i++;

    }

    os<< "\n"<< "-- END MINER --\n" ;
 
    return os;
   }

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES BELOW