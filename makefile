driver.exe: XMLParse2.o driver.o
	g++ XMLParse2.o driver.o -o driver.exe -std=c++03

XMLParse.o: XMLParse2.cpp
	g++ -c XMLParse2.cpp -o XMLParse2.o -std=c++03

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o -std=c++03

clean:
	rm *.o driver.exe
