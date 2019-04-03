CC = gcc
TARGET = shell
obj = shell.o parse.o builtin.o run_command.o is_background.o

all :$(obj)
	$(CC) -o $(TARGET) $(obj)
$(obj) :$(TARGET).h

.PONEY:clean
clean:
	rm -r $(TARGET) $(obj)

