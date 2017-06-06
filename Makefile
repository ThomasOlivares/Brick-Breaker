FLAG=-lsfml-graphics \
	 -lsfml-window \
	 -lsfml-system

CLASSES=application.o \
		ball.o \
		brick.o \
		main.o \
		neuralNetwork.o \
		platform.o \
		textNode.o \
		utility.o \
		world.o

COMPILER=g++

LDFLAGS=-g

RDFLAGS=-std=c++14

all : main

main : $(CLASSES)
	$(COMPILER) $(LDFLAGS) $(CLASSES) -o BrickBreaker $(RDFLAGS) $(FLAG)

main.o : main.cpp
	$(COMPILER) $(LDFLAGS) -c main.cpp $(RDFLAGS)

application.o : application.cpp application.hpp
	$(COMPILER) $(LDFLAGS) -c application.cpp $(RDFLAGS)

ball.o : ball.cpp ball.hpp
	$(COMPILER) $(LDFLAGS) -c ball.cpp $(RDFLAGS)

brick.o : brick.cpp brick.hpp
	$(COMPILER) $(LDFLAGS) -c brick.cpp $(RDFLAGS)

neuralNetwork.o : neuralNetwork.cpp neuralNetwork.hpp
	$(COMPILER) $(LDFLAGS) -c neuralNetwork.cpp $(RDFLAGS)

platform.o : platform.cpp platform.hpp
	$(COMPILER) $(LDFLAGS) -c platform.cpp $(RDFLAGS)

textNode.o : textNode.cpp textNode.hpp
	$(COMPILER) $(LDFLAGS) -c textNode.cpp $(RDFLAGS)

utility.o : utility.cpp utility.hpp
	$(COMPILER) $(LDFLAGS) -c utility.cpp $(RDFLAGS)

world.o : world.cpp world.hpp
	$(COMPILER) $(LDFLAGS) -c world.cpp $(RDFLAGS)

clean : 
	rm *.o BrickBreaker