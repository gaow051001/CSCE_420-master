# all: dpll2

# dpll2: dpll2.cpp 
# 	g++ -o dpll2 -std=c++11 dpll2.cpp parser2.h

# clean:
# 	rm -rf *.o
# 	rm -f *.out
# 	rm -f *~ *.h.gch *#

all: DPLL

DPLL: DPLL.cpp parser.o
	g++ -o dpll -Wall -std=c++11 DPLL.cpp parser.o

parser.o: parser.cpp parser.h
	g++ -c -Wall -std=c++11 parser.cpp


clean:
	rm dpll
	rm *.o