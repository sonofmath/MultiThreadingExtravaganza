CC      	= gcc
CFLAGS  	= -Wall -g -Werror
LDFLAGS		= -pthread
OBJFILES 	= threadGlobalVar.o
TARGET		= thread1

default: all

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~