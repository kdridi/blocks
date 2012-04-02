CFLAGS	= -O2 -g -Wall -fmessage-length=0 -Iinclude -std=c99
OBJS	= blocks.o
LIBS	= 
TARGET	= blocks

$(TARGET): blocks.cc $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f blocks.cc $(OBJS) $(TARGET)

%.cc: %.c
	$(CC) $(CFLAGS) -E $< > $@

test:
	clear
	$(MAKE) clean all
	./$(TARGET) && echo "Success"'!'
	