#Wenjie Yang
#cse 411
#wey311

OPT= -c -Wall -Werror

p5 : p5.o word.o lex.o parse.o htable.o rek.o 
	g++ -o p5 p5.o word.o lex.o parse.o htable.o rek.o

p5.o : p5.cc lex.h parse.h 
	g++ $(OPT) p5.cc parse.cc

parse.o : parse.cc parse.h lex.h htable.h word.h 
	g++ $(OPT) parse.cc lex.cc

lex.o : lex.cc lex.h htable.h word.h
	g++ $(OPT) lex.cc

rek.o : rek.cc rek.h word.h
	g++ $(OPT) rek.cc 

htable.o : htable.cc htable.h rek.h word.h
	g++ $(OPT) htable.cc

word.o : word.cc word.h  
	g++ $(OPT) word.cc

clean:
	rm -f p4 *.o *~
