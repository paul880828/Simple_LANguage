// Name : Wenjie Yang    Course: cse 109

#include "parse.h"

int Parse::genCode(int a){
  if (flag==true){
  out<<"["<<codeLine<<"]:"<<' '<<a<<endl;
  code[codeLine]=a;}
  codeLine++;
  return a;
}

Parse:: Parse(){
  STKPNT=999;

  count[0]=0;
}

void Parse::fullparse(){                              //parse it twice
  openFile();                                         //open the file

  in.clear();in.seekg(0,ios::beg);              //clear the
  codeLine=0;      				        //stream, and
					        //set the
					        //pointer to the
						//begin of file
  
  flag=false;                              //false is for the first
					   //time parse
    
  parse();
  count[1]=codeLine;
  //  cout<<count[1]<<endl;
  flag=true;
  codeLine=0;                                 //set it true for the 2nd parse
  in.clear(); in.seekg(0,ios::beg);
     parse();
     cout<<codeLine<<endl;
     printVar();                            //write the var table

         
     out.close();
     out.open(filename3);
     for (int i=0; i<codeLine; i++)
     out<<code[i]<<endl;
    
     out<<"END"<<endl;

}

void Parse::expect(int tok, const char * mess){        
  check(token==tok, mess);
  token=lex.next();
}

void Parse::check(bool b, const char * mess){
  if (!b){
    cerr<<"Error:" <<mess<<endl;
    cerr<<"AT Line: "<<lineNum<<endl;
    exit(1);
  }
}

void Parse::readLine(){                     //read line method
  //Word temp;                      
  if (!in.eof()){               
    in.getline(b,200);                      //get the 100 charater
					    //from the line
    check(b,"fail to getline"); 
    lex.set(b);
    lineNum++;
    out<<lineNum<<'\t'<<lex.string<<'\n';   // write the line into
    // output file
  }
}



void Parse::printVar(){                    //print the var tale in output file
  out<<"----------------------------"<<'\n';
  out<<"Symbol Table"<<'\n';
  out<<"---------------------------"<<'\n';
  out<<"adress   | symbol"<<'\n';
    for (int i=0; i<101; i++)
   {if (var.Table[i]->getKey()!="")
     {out<<count[1]+var.Table[i]->data<<"    "<<var.Table[i]->getKey()<<'\n';
    }
   }
}



/* parse() first determind if it is in the first parse, then read
   line, process declaration(); then process the line(); and if it
   reach EOF return */

void Parse::parse(){                       
  if (flag==false)                           //write it in output 
   out<<"------------------This is the first parse: -----------------------"<<'\n';
  else
   out<<"------------------This is the second parse: ----------------------"<<'\n';
  
  lineNum=0;                               //set the line number to be 0
  
  //b=new char;
  readLine();                              //read a line from file,
					   //store it with lex.set(a)
  
  declaration();                           //process the declaration
  
  token=lex.next();
  
  while (token!=Lex::END&&!in.eof()){
    if (token==Lex::NUMBER){               //if  token is number
					   //means it is the number of
					   //that line, a 'goto' exit
      
      if (flag==false)                     //if it is the first parse
	                                   
	
	{check(!gotoExit.inTable(lex.token), "Error: Goto exit redifine"); 
	gotoExit.add(lex.token,codeLine);}        // store the line number in
					   // the table, used for
					   // second parse
      
      token=lex.next();}
    
    // else
      { line();                           // if the line is not begin
      
        expect(Lex::EOLN, " EOLN expected");  
        readLine();
        token=lex.next();}
  }
  expect(Lex::END, "END expected");      //should be end of the
					 //program
  
  if (flag==false)
    cout<<"-----------------First parse success!------------------ "<<endl;
  else
    cout<<"----------------------Second parse success!-------------"<<endl;
  
}


void Parse::openFile(){         //open the file;
  in.open(filename1,ios::in);
  if(!in.good())
    exit(1);
  out.open(filename2,ios::out);
  if(!out.good())
    exit(1);  
}

/*
void Parse::secondParse(){
  cout<<"hello"<<endl;
   lineNum=0;
   b=new char;
   check(!b, "heapover flow");
   //in.clear();in.seekg(0);
   //in.open("p9.err");
   
   readLine();
   declaration();
   token=lex.next();
   while (token!=Lex::END){
   
   if (token==Lex::NUMBER){
   token=lex.next();}
   else
    {line();
    cerr<<b<<endl;
   expect(Lex::EOLN, " EOLN expected");
   readLine();
   token=lex.next();}
   }
   
   expect(Lex::END, "END expected");
   cout<<"sucessfully  second parse! "<<endl;
 }
*/
/*Parse::Parse(){
   lineNum=0;
   b=new char;
   in.open("p1.txt");
   readLine();
   declaration();
	      token=lex.next();
	        while (token!=Lex::END){

		    if (token==Lex::NUMBER){
		          var.add(lex.token,0);
			        token=lex.next();}
				    else {line();
				        expect(Lex::EOLN, " EOLN
		          expected");
			      readLine();
			      token=lex.next();}

			        }
				  expect(Lex::END, "END expected");
				    cout<<"sucessfully parse! "<<endl;
				    }
*/


/* precondition : current line is at the begin of file */
void Parse::declaration(){                      
  token=lex.next();
  switch (token){                   //swich the token, and follow the
				    //diagram you gave us
  case Lex::BEGIN:                    
    token=lex.next();
    expect( Lex::EOLN, " should be end of line");
    readLine();
    break;
  case Lex::IDENT:                  //if it is ident, call declaration() again;                           
    if (flag!=true)
      {check (!var.inTable(lex.token),"  redefinition of Ident"); 
      					  
      var.add(lex.token.wd, count[0]);
      count[0]++;
      
       }
    token=lex.next();
    expect(Lex::EOLN, " should be end of line ");
    readLine();           
    declaration();                 // call it again and put it in the
				   // stack
    break;
  case Lex::EOLN:                  //if EOLN, read next line    
    readLine();
    declaration();
    cout<<token<<endl;
    break;
  default:                         //default means the program can not
				   //find "begin", so output error 
    //cout<<token<<endl;
    expect(Lex::BEGIN, "begin expected");
    break;
  }
}



/*precondition: only can run after declaration */
void Parse::line(){               
  Word temp1;
  Word tempSymbol;
  switch (token){               //follow the diagram, there are 6 kind
				//of way it can process, so swicth
				//them
    
  case Lex::IDENT :            // ident must be followed by '='
    temp1=lex.str();
    token=lex.next();
    expect(Lex::SETEQ, " '=' expected ");
    expression();
    genCode(SLOAD+STKPNT);               //load the number into acc
    
    genCode(SSTORE+var[temp1]+count[1]); //count[1] store the total number
					 //of line of code, var[temp1]
					 //return the data of temp1,
					 //which is the location of
					 //variance. add them together
					 // add them together should
					 // be the absolute location
					 // of the variance
    
    // readLine();
    break;
    
  case Lex::IF :                //if must follow by expression(), then
				//bool operator, then expression, then
         			//goto   
    token=lex.next();
    expression();
    
    if (token==Lex::LT || token==Lex::LTE || token==Lex::GT||token==Lex::GTE||token==Lex::EQU ||token==Lex::NEQ)
      { tempSymbol=token;
	token=lex.next();
	STKPNT--;             //stkpnt should be 998 now
      expression();                   // after the expression, should
      genCode(SLOAD+STKPNT+1);                 // expect for goto         
      genCode(SSUB+STKPNT);                // do (st998)- (st999)
      STKPNT++;
       expect(Lex::GOTO, " GOTO expected");
      if (token==Lex::NUMBER)
	if (flag==true)
	  check(gotoExit.inTable(lex.token), "undefine exit of JUMP"); //check the line number valid or not
      if (tempSymbol==Lex::LT)
	genCode(SJUMPN+ gotoExit[lex.token]);  //jump if  a-b<0;
      if (tempSymbol==Lex::GT)
	{genCode(SJUMPN+codeLine+3);
        genCode(SJUMPZ+codeLine+2);
	genCode(SJUMP+gotoExit[lex.token]);}
      if (tempSymbol==Lex::LTE)
	{genCode(SJUMPN+gotoExit[lex.token]);
        genCode(SJUMPZ+gotoExit[lex.token]);}  
      if (tempSymbol==Lex::GTE)
	{genCode(SJUMPN+codeLine+3);
        genCode(SJUMPZ+gotoExit[lex.token]);
        genCode(SJUMP+gotoExit[lex.token]);}
      if (tempSymbol==Lex::EQU)
	genCode(SJUMPZ+gotoExit[lex.token]);
      if (tempSymbol==Lex::NEQ)
	{genCode(SJUMPZ+codeLine+1);
        genCode(SJUMP+gotoExit[lex.token]);}
		
      expect(Lex::NUMBER, " number expected");
      
      }
    else cerr<<"Error:  bool operator expected"<<endl;
    break;
    
  case Lex::GOTO:           //is similar  the goto above
    token=lex.next();
    if (token==Lex::NUMBER)
      if (flag==true)
	check(gotoExit.inTable(lex.token), "undefine exit of JUMP");
    genCode(SJUMP+gotoExit[lex.token]);
    expect(Lex::NUMBER, "number expected");
    // readLine();
    break;
    
  case Lex::HALT:          // if token==halt, expect nothing, but EOLN
    token=lex.next();
    expect(Lex::EOLN, " should be eoln");
    genCode(SHALT);
    break;
    
  case Lex::READ :         // if read, expect an ident
    token=lex.next();
    check(var.inTable(lex.token), "Ident not define");
    genCode(SREAD+var[lex.token]+count[1]);
    expect(Lex::IDENT, " IDENT expected");
    
    break;
    
  case Lex::WRITE :       //if write, expect expression;
    token=lex.next();     // and call expression() for recursion
    //  cout<<lex.token<<endl;
    expression();
    genCode(SWRITE+STKPNT);
    //cout<<token<<endl;
    //cout<<lex.token<<endl;
    expect(Lex::EOLN, "EOLN expected");
    break;
    
  case Lex::EOLN:
    break;
    
  default:
    cerr<<" Error: " <<" Junk input"<<endl;
    cerr<<" At Line:"<<lineNum<<endl;
    exit(1);
    break;
  }
}

void Parse::expression(){                  //it either meet a "+" or a "-"
  term();
  //STKPNT--;
  //cout<<lex.token<<endl;
  while (token==Lex::PLUS|| token==Lex::MINUS)
    {STKPNT--;
    switch (token) {
    case Lex::PLUS :
      token=lex.next();
      term();
      genCode(SLOAD+STKPNT+1);                    //load from the stk
      genCode(SADD+STKPNT);                       //add them together
      STKPNT++;                                  //when finish the
						 //operation, then stk
						 //pointer should +1  
      genCode(SSTORE+STKPNT);
      break;
      
    case Lex::MINUS:
      token=lex.next();
      term();
      genCode(SLOAD+STKPNT+1);
      genCode(SSUB+STKPNT);
      STKPNT++;
      genCode(SSTORE+STKPNT);
      break;
    default :
      break;
    }

    }
  // STKPNT++;
}

void Parse::term(){                // if it meets a "*" or '/', call
				   // the the factor(); do the
				   // recursion 
  factor();
  //STKPNT--;
  while (token==Lex::TIMES ||token==Lex::DIVIDE)
    {STKPNT--;
      switch (token){
    case Lex::TIMES:
      token=lex.next();              
      factor();
      genCode(SLOAD+STKPNT+1);
      genCode(SMUL+STKPNT);
      STKPNT++;                // after finishing the operation the
			       // stk pnt  should +1;
      genCode(SSTORE+STKPNT);
      break;
    case Lex::DIVIDE:
      token=lex.next();
      factor();
      out<<"DIV operation"<<endl;
      genCode(SLOAD+STKPNT+1);
      genCode(SDIV+STKPNT);
      STKPNT++;
      genCode(SSTORE+STKPNT);
      break;
    default:
      break;
    }

    }
  
}

void Parse::factor(){           //there is 3 ways to process  factor
  switch (token) {
  case Lex::LPAREN:             //the first way -----'(' expression ' )'
    token=lex.next();
    expression();
    expect(Lex::RPAREN, " ' ) ' expected");
    break;
  case Lex::IDENT:              //the second way ----- ident , x, y
    check(var.inTable(lex.token), "IDENT NOT DEFINE");
    genCode(SLOAD+var[lex.token]+count[1]);
    genCode(SSTORE+STKPNT);
    token=lex.next();
    break;
  case Lex::NUMBER:             // the third way ----- numbers 
    if (flag==false&&!var.inTable(lex.token))
      {var.add(lex.token,count[0]);
   
      count[0]++;}                             //count[0] is the place
					       //that store the
					       //number, count[0]+
					       //codeLine(PC)  is the
					       //absolute location
    
    // varNum++;
      genCode(SLOAD+var[lex.token]+count[1]);
      genCode(SSTORE+STKPNT);
      // genCode(SLOAD+STKPNT);
      //STKPNT--;
    token=lex.next();
    break;
    
  default:
       {cerr<<"Error: 'factor' junk input AT line:"<<lineNum<<endl; exit(1);}
  }
	    
   }
