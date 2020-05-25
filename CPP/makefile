objects = main.o operations.o person.o
DELETE	:=
ifeq ($(OS),Windows_NT)
	DELETE = del
else
	DELETE = rm
endif

pertempt: $(objects)
			$(CXX) -o pertempt $(objects)  -std=c++17 -lcurl 
main.o: main.cpp operations.h person.h
			$(CXX) -c main.cpp -std=c++17
operations.o: operations.cpp operations.h
			$(CXX) -c operations.cpp -std=c++17
person.o: person.cpp person.h
			$(CXX) -c person.cpp -std=c++17
clean: operations.o main.o person.o
			$(DELETE) operations.o main.o person.o