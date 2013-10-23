#ifndef HTABLE_H
#define HTABLE_H

#include "rek.h"
#include "word.h"
using namespace std;     
                  
class HTable{
private:
  // Rek *Table[101];// set a array of pointers to point to Rek Ojects
  
public:
  HTable();
  ~HTable(){};
  int add(Word  k, int d);    
  bool inTable(Word k);                       // return a bool value
  Rek * Table[101];				      // to check  if it is in the Htable
  int operator [] (Word k) const;       //reload the operator []
  int at(Word k);						                                              
};
  
#endif
