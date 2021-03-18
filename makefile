all:
	g++ main.cpp Fish.cpp -o freefish -std=c++11

install:
	mkdir ~/.freefish
	cp -r ./sample/* ~/.freefish

clean:
	rm freefish
