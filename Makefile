CXX = g++

# compiler flags:
# #  -g    adds debugging information to the executable file
# #  -Wall turns on most, but not all, compiler warnings
# CXXFLAGS = -std=c++14 -g -Wall

OBJECTS = brute-force.o genetic.o simulation.o

main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* main
