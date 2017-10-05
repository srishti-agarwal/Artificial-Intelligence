CXX=g++
CXXFLAGS= -std=c++11
BIN=prog

SRC=$(main *.cpp)
OBJ=$(SRC:%.cpp=%.o)
all:	compile

compile:	main.cpp
			$(CXX) $(CXXFLAGS) main.cpp

clean:	rm -f *.o
		rm $(BIN)