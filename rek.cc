#include "rek.h"
/*Hash table exercise */
Rek::Rek(){}

Rek::~Rek(){//cerr<<"deleting '"<<key<<"'\n";
}

Rek::Rek(const Word &k,int d):key(k),data(d){}

int Rek::hash()const{
  return key.hash();
}

const Word & Rek::getKey()const{
  return key;
}


ostream&operator<<(ostream&out,const Rek&r){
  return out<<"("<<r.key<<", "<<r.data<<")";
}
