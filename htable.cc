
#include <iostream>
#include "htable.h"
#include "word.h"
#include "rek.h"
using namespace std;
 

HTable::HTable(){                  //to initialize the Htable, giving all
				   //the oject a value (NULL,0)
  for (int i=0; i<101 ;i++)

    Table[i]=new Rek("",0);
}

int HTable::at(Word k){
  for(int i = 0;i < 101;i++)
    {
      if(Table[i]!=NULL)
	{
	  if (Table[i]->getKey()==k)
	    {
	      // cout<<k<<"    "<<i<<endl;
	      return i;
	    }
	}
    }
  return 0;
}

bool HTable::inTable(Word k){        //to find if it is in the table
  for (int i=0; i<101; i++){
    if (Table[i]->getKey()==k.str()) // when it is in the htable
				     // return true
                                     
     { 
     return true;}
  }
  return false;
}

int HTable::add(Word k, int d){
  int shift=0;             //shift is the postion shift when collsions happened
  int oldPosition =k.hash() % 101; // using % 101 to hash the ssn
  //  cout<<k.hash()<<"hash"<<endl;
  int newPosition=oldPosition;     // using the newPosition in case of
			 	   // oldPostion is occupied already.
  while (Table[newPosition]->hash()!=NULL){
    shift++;
    if (Table[newPosition]->hash()==k){
      return 0;
    }
    else
      newPosition = (oldPosition+shift*shift)%101;  //Given that
						       //newPosition
						       //may exceed
						       //101, so % 101

    // if the shift>=50, stop trying add the entry into
    // HashTable. stop this entry.
    if (shift>=50){
      cout<<"entry "<<"("<<k<<","<<d<<")"<<"can not be added to Hashtable after 50 probes, carsh!"<<endl;
      return 0;
    }
  }
  cout<<"It took "<<shift+1<<"probe(s) to add "<<"("<<k<<","<<d<<")"<<endl;
  Table[newPosition]= new Rek(k,d);
  /*cout<<newPosition<<endl;*/
  return 1;
}


 int HTable:: operator [] (Word k) const{  // given K then search
						// Htable for its
						// value  and then return 
  for (int i=0; i<101; i++){
    if (k.str()==Table[i]->getKey())  
      return Table[i]->data;
  }
  return 0;
}
  
