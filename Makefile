all: clean test

test: loadbalancer.o request.o main.o webserver.o firewall.o
	g++ -g loadbalancer.o request.o webserver.o firewall.o main.o -o test

loadbalancer.o: loadbalancer.h loadbalancer.cpp
	g++ -c -g loadbalancer.cpp

webserver.o: webserver.h webserver.cpp
	g++ -c -g webserver.cpp

request.o: request.h request.cpp
	g++ -c -g request.cpp

firewall.o: firewall.cpp
	g++ -c -g firewall.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean:
	rm -f *.o test.exe test.out test

run: test
	./test