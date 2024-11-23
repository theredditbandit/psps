CC=zig cc
CFLAGS=-std=c99 -Wall
LIBS=-ledit -lm
TARGET=parsing

$(TARGET): parsing.c
	$(CC) $(CFLAGS) parsing.c mpc.c $(LIBS) -o $(TARGET)

clean:
	rm  $(TARGET)

run: $(TARGET)
	-./$(TARGET)
   
.PHONY: clean run
