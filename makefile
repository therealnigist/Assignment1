driver.exe: XMLParse2.o driver2.o
	g++ XMLParse2.o driver.o -o driver.exe -std=c++2a

XMLParse.o: XMLParse2.cpp
	g++ -c XMLParse2.cpp -o XMLParse2.o -std=c++2a

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o -std=c++2a

clean:
	rm *.o driver.exe
