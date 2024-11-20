CC=zig cc
CFLAGS=-std=c99 -Wall
LIBS=-ledit
TARGET=prompt

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c $(LIBS) -o $(TARGET)

clean:
	rm  $(TARGET)

run: $(TARGET)
	-./$(TARGET)
   
.PHONY: clean run
