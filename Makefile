# compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Wc++11-extensions -O2
# enables common warnings, enables extra warnings, compiles using cpp17 standard, turns on compiler optimization level 2

# final exe file name
TARGET = main

# default target when running make
all: $(TARGET)

# Source files
SRCS = main.cpp

# Object files
OBJECTS = $(SRCS:.cpp=.o)

# Link object files to target exe
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
# $@ = automatic variable for target name
# $^ = automatic variable for all prerequisites (.o files)

# pattern rule tells make how to compile any source file (.cpp) into object (.o)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
# $< = first prerequisite file (i.e. matrices.cpp)

# remove .o file and executable
clean:
	rm -f *.o $(TARGET)
