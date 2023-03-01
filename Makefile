# Template Makefile
EXECUTABLE=ThinkgearSimple

CXX=g++
CXXFLAGS=
CC=gcc
CFLAGS=

SOURCES=$(wildcard *.cpp) $(wildcard *.c)
OBJECTS=$(filter %.o, $(SOURCES:.cpp=.o) $(SOURCES:.c=.o))

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	@echo Building $@
	@$(CXX) $^ -o $@
	@echo
	@echo Type $@ to run.
	
.c.o: 
	@echo Building object: $@
	@$(CC) $(CFLAGS) -c $< -o $@

.cpp.o: 
	@echo Building object: $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	

clean:
	@rm -Rfv *.o $(EXECUTABLE)
