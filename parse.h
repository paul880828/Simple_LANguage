//Name: Wenjie Yang   Couse: CSE109  P6 
#ifndef PARSE_H
#define PARSE_H

#include "lex.h"
#include "htable.h"
#include <fstream>
#include <iostream>
using namespace std;
/*This is a class parse. It is used for checking syntax or other error in EASY
  language. */

class Parse{
private:
  Lex lex;                 //creat a object lex, used for tokenizing the code
  int token;               //store the number of the current token
  HTable  var;             //use for storing the var such as x, y, x1, 1
  HTable  gotoExit;        //use for storing the line number of the  exit
			   //of goto
  int code[200];
  // char *varTab[20];
  // int varNum;
   Word tempVar[20];
  int count[20];         //count[1] store the total number of line of code.
public:                     
  Parse();                     
  // Parse(ifstream & in, ostream & out); 
  void parse();
  ~Parse(){};
  void fullparse();                             //parse for twice
  
  void expect(int tok, const char * mess);      //expect() is the same
						//fuction  you use in
						//the class
  void check(bool b, const char * mess);        

  /* Expression---->Term-------------------->
                      |   |- + ----|
		    Term--|        |
			  |- - ----|
  */
  void expression();                            //expression() is
						//written to follow
                                                //the diagram 



  void factor();            //term is the same as expresstion, it
			    //calls fact()  and get nex token ,if it
			    //is * or / call fact()  again;
  
  void term();              
  
  void declaration();       //declaration is follow the diagram. but
			    //it  also store the Ident in the table.
  
  void line();              //line() is complicate, it call all the
			    //fuction  above to process the line.
  
  void readLine();          //read a line for the file, store it, and
			    //prepare to use for tokenize;
  
  bool flag;                // to detemine whether it is in the first
			    // parse or in the second parse;
  
  //void secondParse();
  void printVar();          // print the Var table and write it in the
			    // output file
  
  void openFile();          // open the input and output file 
  
  ifstream in;
  ofstream out;
  char *b;                  //to temporary store the line
  
  char *filename1;          //intput file name;
  char *filename2;          //outout file name;
  char *filename3;
  int lineNum;              // record the numbers of line

  static const int SREAD=10000, SWRITE=11000, SLOAD=20000,SSTORE=21000,
    SADD=30000, SSUB=31000,SDIV=32000,SMUL=33000,SJUMP=40000,SJUMPN=41000,
    SJUMPZ=42000, SHALT=43000;

  int STKPNT;                    // stack pointer
  int genCode(int a);           
  int codeLine;           //it stores the number of current line of code  

}; 

#endif
