#ifndef WORD_H
#define WORD_H

#include <iostream>
using namespace std;

/* It reloaded different operator of  class Word, icluding ostearm<<
   istream
   >>, +=, >= etc*/

class Word{
private:

  int space;
public:
  char *wd;
  static const int BLOCK=10;
  Word(const char *c=NULL);

  //postconditions: wd=={c,'\0'};
  //                space=2
  Word(char c);                     //
  Word(const Word &w);              //

  ~Word();                      //
  friend ostream & operator<<(ostream & out,const Word &w);//
  friend Word operator+(const Word &a, const Word & b); //
  int length()const;//
  friend bool operator<(const Word &a, const Word &b);//
  friend bool operator<=(const Word &a, const Word &b);
  friend bool operator>(const Word &a, const Word &b);
  friend bool operator>=(const Word &a, const Word &b);
  friend bool operator==(const Word &a, const Word &b);
  friend bool operator!=(const Word &a, const Word &b);
  Word & operator+=(char c);  //
  Word & operator+=(const Word &w);//
  char operator[](int index)const;//
  friend istream & operator>>(istream & in,Word &a);
  const char * str()const{ return wd;};//
  int hash()const;//
  const Word & operator=(const Word &w);//
  static void test();//
  void makeSpace();
private:
  void build(const char * st);
  static void check(bool b, const char * mess);
};

#endif
