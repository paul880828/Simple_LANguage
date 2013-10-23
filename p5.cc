//Name: Wenjie Yang   Couse : cse 109


//In the program, I found that my lex.cc do not perform well,
//because it run p13.prog, it can not tell 'iff' and 'if', 'begin' and
//'beginn',  but my parse.cc is fine I think.

#include <iostream>
#include <fstream>
#include "parse.h"
using namespace std;

int main(int argv, char * argc[]){             //use the command line 
  // ifstream i;
  // ofstream o;
  // i.open("p10.txt");
  //o.open("result.txt");
  //cout<<argv[1]<<argv[2];
  
  cout<<"------------------Initialize the table-------------------"<<endl;
  Parse p;
  p.filename1=argc[1];                         //use command line as a parameter
  p.filename2=argc[2];
  p.filename3=argc[3];
  cout<<endl;
  cout<<endl;
  
  cout<<"-----------------Now parsing the program-----------------"<<endl;
  p.fullparse();
  // i.close();
  // o.close();
  return 0;
}
