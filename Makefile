# USAGE:
#
# // to compile:
# make
#
# // to compile tests and run tests:
# make test
#
# // remove compilation output files:
# make clean
#

# make variables let us avoid pasting these options in multiple places
CC = g++ 
#CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O         # for final build
 CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O0 -g   # for debugging

bin: SkipBoMain
	./SkipBoMain

test: SkipBo
	./SkipBo

Board.o: Board.cpp Board.h
	$(CC) $(CXXFLAGS) -c Board.cpp

Player.o: Player.cpp Player.h
	$(CC) $(CXXFLAGS) -c Player.cpp

Computer.o: Computer.cpp Computer.h
	$(CC) $(CXXFLAGS) -c Computer.cpp

Human.o: Human.cpp Human.h
	$(CC) $(CXXFLAGS) -c Human.cpp

Game.o: Game.cpp Board.h Player.h Human.h Computer.h
	$(CC) $(CXXFLAGS) -c Game.cpp

SkipBo.o: SkipBo.cpp Player.h Computer.h Human.h
	$(CC) $(CXXFLAGS) -c SkipBo.cpp

SkipBoMain.o: SkipBoMain.cpp Game.h Player.h Computer.h Human.h Board.h
	$(CC) $(CXXFLAGS) -c SkipBoMain.cpp

SkipBo: SkipBo.o Board.o Player.o Computer.o Human.o
	$(CC) $(CXXFLAGS) -O -o SkipBo SkipBo.o Board.o Player.o Computer.o Human.o

SkipBoMain: SkipBoMain.o Game.o Player.o Computer.o Human.o Board.o
	$(CC) $(CXXFLAGS) -O -o SkipBoMain SkipBoMain.o Game.o Board.o Player.o Computer.o Human.o

clean:
	rm -f *.o SkipBo SkipBoMain
