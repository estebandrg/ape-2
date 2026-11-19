CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -std=c11
TARGET  := billetera
SRCS    := main.c tBilletera.c tOperacion.c tFecha.c
OBJS    := $(SRCS:.c=.o)
HDRS    := tBilletera.h tOperacion.h tFecha.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

out: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) out $(OBJS)
