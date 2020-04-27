.default: all

all: assign2

clean:
	rm -f APT_A02 *.o

assign2: azul.o Bag.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
