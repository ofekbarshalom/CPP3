# ofekbarshalom@gmail.com

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -I./src -I./GUI
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = main.cpp $(wildcard src/*.cpp) $(wildcard GUI/*.cpp)
TEST_SRC = test.cpp $(filter-out main.cpp, $(SRC))  # All but main.cpp

# Executables
MAIN_EXE = Main
TEST_EXE = Test

# Build the main GUI program
Main: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXE) $(SRC) $(LDFLAGS)

# Build and run tests
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXE) $(TEST_SRC) $(LDFLAGS)
	./$(TEST_EXE)

# Run valgrind on the GUI binary
valgrind: Main
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_EXE)

# Clean build files
clean:
	rm -f $(MAIN_EXE) $(TEST_EXE) *.o
