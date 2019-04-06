SOURCES = main.c
OBJECTS = $(SOURCES:%.c=%.o)

TARGET = PiZiGate_test

$(TARGET): $(OBJECTS)
	gcc $^ -o $@ -lwiringPi

%.o: %.c
	gcc -c $< -o $@
