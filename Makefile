out: clean compile execute

compile: main.cpp
	g++ -g -Wall -std=c++14 main.cpp -o mainexe

execute: mainexe
	./mainexe

clean:
	rm -f mainexe testexe

# Test executable
test_compile: test.cpp
	g++ -g -Wall -std=c++14 test.cpp -o testexe

test_execute: testexe
	./testexe

test: clean test_compile test_execute