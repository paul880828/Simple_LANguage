//Name Wenjie Yang  Course CSE 411
#include <iostream>
#include "lex.h"
Lex::Lex(){                   //initialize the hash table
  position=0;
  Table.add("if",0);
  Table.add("halt",1);
  Table.add("read",2);
  Table.add("write",3);
  Table.add("begin",4);
  Table.add("end",5);
  Table.add("eoln",6);
  Table.add("<",7);
  Table.add("<=",8);
  Table.add(">",9);
  Table.add(">=",10);
  Table.add("==",11);
  Table.add("!=",12);
  Table.add("goto",13);
  Table.add("=",14);
  Table.add("+",15);
  Table.add("-",16);
  Table.add("*",17);
  Table.add("/",18);
  Table.add("(",19);
  Table.add(")",20);
  Table.add("JUNK",21);
  Table.add("IDENT",22);
  Table.add("NUMBER",23);
 
  
}

void Lex:: set(char *a){    
  string.wd=new char;
  string=a;              //set Word string equal to the line we should read         
  token.wd=new char;     // give Word token.wd a new space, so that it
			 // change its content while the line changes
  position=0;            // while line change, position the same as count() should
			 // reset to Zero
}



int Lex::count(){       

  return position;
}

Word Lex::str(){         //return the token which is just tokenized
  return token;
}

/*precondition: the first charater read is in the hash table, like =,
+.  and some charater like "!", which is not in the table , but != is in
htable, so "!" should  be included.*/

Word Lex::readSym(){      // tokenize a symbol  
  Word tempToken;         // tempToken store the token currently get 
  Word nextToken;         // nextToken store the next character 
  Word symbol_2;          // symbol_2 is used for storing the symble
			  // which has 2 character, like "<=" "=="
  symbol_2=string[position];
  tempToken=string[position];
  nextToken=string[position+1];

  symbol_2+=nextToken;  
  if (symbol_2=="//")     // if it equal to "//", ignore the rest of line
    {position++; return "\0";}  // the symbol of end of line
  else {
    
    if (Table.inTable(symbol_2)) //the symbol_2 is in table, return it
      {position=position+2;      
      return symbol_2;}
    
    else                        //it means it is not a combine symbol
				//like <=, so just return tempToken 
      {position++; return tempToken;}
  }
}
/* precondistion:the first character  is digit */
Word Lex::readNum(){   
  Word tempToken;                 //tempToken store the token, and
				  //it will be updated in while 
  Word nextToken;
  tempToken=string[position]; 
  nextToken=string[position+1];
  position++;
  while(nextToken.wd[0]>='0' &&nextToken.wd[0]<='9') // if next char is digit
    {tempToken+=nextToken;                         // combine it as
						   // new tempToken      
    position=position+1;
    nextToken=string[position];}
  return tempToken;
}

/*precondition: the first charactor is letter, in this function I have
  to decide whether it is a IDENT or a instruction like "read"*/
Word Lex::readChar(){

  Word tempToken;                                     
  Word nextToken;
  tempToken=string[position];
  nextToken=string[position+1];
  position++;
  while(!Table.inTable(tempToken) &&nextToken.wd[0]!=' ' &&!Table.inTable(nextToken)&&nextToken.wd[0]!='\0'&&nextToken.wd[0]!='!')
    // if the token is in table, than it must be an instruction
    // or if next char is in table, the token is a IDENT,
    {tempToken+=nextToken;
    position=position+1;
    nextToken=string[position];}
  return tempToken;

}
/* next is used for returning the type of a token, a int value*/
int Lex::next(){
  if (token.wd[0]=='\0')  //if it is end of line, dont read any more
    return EOLN;

  while (string[count()]==' '||string[count()]=='\t')   //skip the space 
    position++;
  
  Word ch=string[position];

  /*to decide if we should call readSym*/
  if (Table.inTable(ch)||ch.wd[0]=='!')   // take '!' into
					  // consideration, because
					  // '!=' is in htable
    {token=readSym();
    if (token=="!") return JUNK;
    else if (token=="\0") return EOLN;   
    else
      return Table[token];}
  /* to decide if it should call readNum*/
  else if (ch.wd[0]>='0' &&ch.wd[0]<='9')
    {token=readNum();
    return NUMBER;}
  /* to decide if it should call readChar*/
  else if (ch.wd[0]>='a' &&ch.wd[0]<='z')   
    {token=readChar();                      // read the letters
    if (Table.inTable(token))
      return Table[token];
    else /*if (token=="if")
      return 0;
    else if (token=="goto")
      return 13;
    else if (token=="halt")
      return 1;
    else if (token=="end")
      return 5;
    else if (token=="read")
      return 2;
    else if (token=="write")
      return 3;
      else */
      return IDENT;}
  else if (ch.wd[0]=='\0')
    {/*position=0;*/ return EOLN;}
  else
    {position++; token=ch; return JUNK;}
}

