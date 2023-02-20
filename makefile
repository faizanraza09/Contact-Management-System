output:	main.o myvector.o contact.o contactbst.o
	g++ main.o myvector.o contact.o contactbst.o -o output
main.o: main.cpp
	g++ -c main.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
clean:
	rm output main.o myvector.o contact.o contactbst.o