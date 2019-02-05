COMPILER = g++ -std=c++11
FLAGS = -Wall
ONAME = out
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(OBJ) 
	$(COMPILER) $(OBJ) $(FLAGS) -o $(ONAME)
	./$(ONAME)

%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

.PHONY: clean g
clean:
	rm -f *.o out

g:
	./out
