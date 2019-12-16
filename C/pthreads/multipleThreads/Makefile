CC      	= gcc
CFLAGS  	= -Wall -g -Werror
LDFLAGS		= -pthread
OBJFILES 	= multThreads.o
TARGET		= multThreads

default: all

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~