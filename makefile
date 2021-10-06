C=gcc
CFLAGS = -g 
SOURCES = scanner.c testScanner.c
OBJECTS = scanner.o testScanner.o
DEP = scanner.h
TARGET = P1
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS)-o $@ $^
scanner.o : scanner.c scanner.h
	$(CC) $(CFLAGS) -c -o $@ $<
testScanner.o : testScanner.c scanner.h
	$(CC) $(CFLAGS) -c -o $@ $< 
clean:
	rm -f *.o  