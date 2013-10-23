#ifndef REK_H
#define REK_H
#include "word.h"
class Rek{
private:
  Word key;
  Rek();
public:
  int data;
  Rek(const Word &k,int d);
  int hash()const;
  const Word & getKey()const;
  ~Rek();
  friend ostream&operator<<(ostream&out,const Rek&r);
};
#endif
