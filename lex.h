//Name Wenjie Yang   Course CSE411
#ifndef LEX_H
#define LEX_H
#include "word.h"
#include "htable.h"
/*This is class Lex, it is used for tokenize the string and identify
  their type. It begins with 3 function 1)readChar() 2) readSym()
  #3)readNum(). These 3 function are mainly to tokenize different
  string.*/

class Lex{
public:
  Lex();
  ~Lex(){};
  void set(char * a);
  Word str();          //to return the token which  has been tokenized
  int count();         // I don't use much of count(), "int position"
		       // instead
  int next();          // next() return the value of a token which
  Word readNum();      //read numbers and then return it as a token
  Word readSym();      //read symbol and then return, but there are 2
  //type of symbol should be classified such as < and <=
  Word readChar();     //read chars and decide whether it is IDENT or
		       //instruction
  //such as "index" and "read"

  static const int IF=0, HALT=1, READ=2, WRITE=3, BEGIN=4, END=5, EOLN=6,
    LT=7, LTE=8, GT=9, GTE=10, EQU=11, NEQ=12, GOTO=13, SETEQ=14,
    PLUS=15, MINUS=16, TIMES=17, DIVIDE=18, LPAREN=19, RPAREN=20,
    JUNK=21, IDENT=22, NUMBER=23;
  Word token;
  Word string;
private:
  // Word string;
  // Word token;
  HTable  Table;
  int position;
};

#endif
