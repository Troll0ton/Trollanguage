CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp differentiator.cpp frontend.cpp middleend.cpp tree.cpp lines_handle.cpp input_output.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=diff

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@