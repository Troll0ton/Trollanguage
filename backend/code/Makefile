CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -D_DEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS=-I../../
SOURCES=main.cpp backend.cpp tree.cpp lines_handle.cpp input_output.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../../run_backend

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(IFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(IFLAGS) $(CFLAGS) $< -o $@