CC:= gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g -O0
DEPFLAGS := -MMD -MP

TARGET := kyber
SAN_TARGET := kyber-san

SOURCES := main.c poly.c polyvec.c prng.c indcpa.c
OBJECTS := $(SOURCES:.c=.o)
DEPS := $(OBJECTS:.o=.d)

# .d saved the dependency of the file

.PHONY: all run sanitize clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@  
# $< is the dependency (on the right of ":")

run: $(TARGET)
	./$(TARGET)

sanitize:
	$(CC) $(CFLAGS) -fsanitize=address,undefined $(SOURCES) -o $(SAN_TARGET)
	./$(SAN_TARGET)

clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET) $(SAN_TARGET)

-include $(DEPS)

