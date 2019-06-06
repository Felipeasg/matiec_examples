CC=gcc
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-std=gnu99 -I ./lib/C -c 
LDFLAGS=-lrt
EXECUTABLE=softplc


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(LDFLAGS) -o $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)


