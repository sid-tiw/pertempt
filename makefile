objects = main.o operations.o person.o

pertempt: $(objects)
			$(CXX) -o pertempt $(objects) -lcurl -std=c++17
main.o: main.cpp operations.h person.h
			$(CXX) -c main.cpp -std=c++17
operations.o: operations.cpp operations.h
			$(CXX) -c operations.cpp -std=c++17
person.o: person.cpp person.h
			$(CXX) -c person.cpp -std=c++17