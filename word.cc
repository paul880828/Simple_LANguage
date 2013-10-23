#include "word.h"
#include <iostream>
using namespace std;
/* A wrapper class for strings of char (arrays of char
         to avoid the problems of calling strlen(), strcat(),
	          strcpy(), and strcmp() with null pointers.

		              Never save a null pointer. If we get a
		              null pointer
			                     store "".  {'\0'}
					                       char
		              *cc;
			                           Word  a, b("a
		              word"),c(cc),d(b);
			                              cout<<b<<endl;
						                                 cout<<b.length()<<b[2]<<(b+d)<<(b+"more
										                strng")
												                  <<("more string "+d)<<(a=b)<<(a<"one")<<(a==b)
														                       <<a.hash()<<endl;

																                               cin>>a;
																                               //stop
																                               at
																                               \n
																			                                  a+=b;
*/

/*precondition   strlen(w.wd)<100 */
istream & operator>>(istream & in,  Word &w){
  in.getline(w.wd, 100);
  return in;
}
/*reload operator" <<", then return a string   */
ostream &operator <<(ostream & out, const Word &w){
  out<<w.wd;
  return out;
}

/*reload operator +=, then the content of sting a=a+b */
Word & Word::operator += (const Word &w){
  makeSpace();             //make space  for a longer string a+b
  /*int locA;
          int locB;
	          locA=strlen(wd);
		            locB=strlen(w.wd);
			                for (int i=0; i<locB;i++){
					                wd[locA+i]=w.wd[i];
							                  }
									                      wd[locA+locB]='\0';
  */
  strcat(wd,w.wd);
  return *this ;
}

/* to check the length of * wd */
int Word::length()const{
  return strlen(wd);
}

/* hash function, add all the ASKII value of the string as
   the hash value */
int Word::hash()const{
  int temp=0;
  int len=strlen(wd);
  for (int i=0; i<len; i++){
    temp=temp+(int) wd[i];
  }
  return temp*10;
}  //to make a sparse disturbution of the hash value
char Word::operator[](int index)const{
  return wd[index];
}

Word::Word(const char * st){     //constructor for char *
  if(st==NULL)
    build("");
  else
    build(st);
}

void Word::check(bool b,const char *mess)
{
  if(!b){
    cerr<<"ERROR[Word]: "<<mess<<endl;
    exit(1);
  }
}

Word::Word(char ch){ //contructor for char
  // char temp[]={ch,'\0'};
  char temp[2];
  temp[0]=ch;
  temp[1]='\0';

  build(temp);
}

Word::Word(const Word &w){ //constructor for Word
  build(w.wd);
}
const Word & Word::operator=(const Word&w){
  if(this!=&w){
    delete []wd;
    build(w.wd);
  }
  return *this;
}
Word::~Word(){
  delete [] wd;
}

//compare stirng
bool operator<(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)<0;
}

bool operator<=(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)<=0;
}

bool operator>(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)>0;
}

bool operator>=(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)>=0;
}
bool operator==(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)==0;
}

bool operator!=(const Word &a, const Word &b){
  return strcmp(a.wd,b.wd)!=0;
}

Word & Word::operator+=(char c){
  makeSpace();
  int loc;
  loc=strlen(wd);
  wd[loc]=c;
  wd[loc+1]='\0';
  return *this;
}
//preconditions: ch!=NULL
//postcondtions: wd has the string
void Word::build(const char *ch){
  int n;
  n=strlen(ch);
  wd=new char[n+1];
  check(wd!=NULL,"(build()) heap overflow");
  strcpy(wd,ch);
  /* int loc;
               loc=0;
	                      while(ch[loc]!='\0'){
			                             wd[loc]=ch[loc];
						                                    loc++;
										                                           }
															                                                wd[loc]='\0';
  */
  space=n+1;
}

/*to make more space for wd  */
void Word::makeSpace(){
  if((int)strlen(wd)>=space-1){
    char *temp;
    temp=new char[length()+BLOCK+1]; //space stores the new lenth of
				     //wd
    space=length()+1+BLOCK;
    check(temp!=NULL,"(makeSpace()) heap overflow");
    strcpy(temp,wd);
    delete [] wd;     //release wd
    wd=temp;
  }
}
void Word::test(){
  char *t;
  t=NULL;
  Word a, b(t), c("one"), d(c);
  cout<<"'"<<a<<"' '"<<b<<"' '"<<c<<"' '"<<d<<"' '"<<endl;
  a=c;
  cout<<"'"<<a<<"'"<<endl;

  Word e("a"),f("b"),g(e),h('a');
  cout<<"I expect 'a': '"<<h<<"'\n";
  cout<<"        "<<(e<f)<<(e>f)<<(e==f)<<(e!=f)<<(e<=f)<<(e>=f)<<endl;
  cout<<"Match?  100110\n";
  cout<<"        "<<(e<g)<<(e>g)<<(e==g)<<(e!=g)<<(e<=g)<<(e>=g)<<endl;
  cout<<"Match?  001011\n";
  cout<<"        "<<(e<'a')<<(e>'a')<<(e=='a')<<
    (e!='a')<<(e<='a')<<(e>='a')<<endl;
  cout<<"Match?  001011\n";
  cout<<"        "<<('a'<f)<<('a'>f)<<('a'==f)
      <<('a'!=f)<<('a'<=f)<<('a'>=f)<<endl;
  cout<<"Match?  100110\n";
  cout<<"        "<<("two"<c)<<("two">c)<<("one"==c)
      <<("one"!=c)<<("one"<=c)<<("one">=c)<<endl;
  cout<<"Match?  011011\n";
  Word y("hello");
  for(int j=0;j<20;j++)
    y+=(char)('a'+j);
  cout<<y<<endl;
  for(int j=2;j<24;j++)
    cout<<y[j];
  cout<<endl;
  Word p("one time");
  cout<<(p+=" I had a friend who took me to a party")<<endl;
  cout<<"Again: '"<<p.str()<<"'\n";

}
