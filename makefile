all:
	g++ main.cpp Fish.cpp -o freefish -std=c++11

clean:
	rm freefish
