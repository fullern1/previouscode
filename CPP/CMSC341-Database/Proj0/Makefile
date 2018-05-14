driver.out: joke.o driver.o
	g++ -Wall -ansi joke.cpp driver.cpp -o driver.out

joke.o: joke.cpp joke.h
	g++ -Wall -ansi -c joke.cpp

driver.o: driver.cpp joke.h
	g++ -Wall -ansi -c driver.cpp

clean:
	rm *.o *.out

run: driver.out
	./driver.out