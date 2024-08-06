debug = -g

p3_402: p3_402.o SBGame.o Date.o
	g++ -std=c++0x -o p3_402 p3_402.o SBGame.o Date.o $(debug)

p3_402.o: SBGame.cpp SBGame.h Date.h
	g++ -std=c++0x -c p3_402.cpp $(debug)
	
SBGame.o: SBGame.cpp SBGame.h 
	g++ -std=c++0x -c SBGame.cpp $(debug)
	
Date.o: Date.cpp Date.h
	g++ -std=c++0x -c Date.cpp $(debug)

clean:
	\rm -f *.o run