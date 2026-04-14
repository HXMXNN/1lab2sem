CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = main.o int.o double.o matrix.o errors.o io.o

TARGET = run.exe

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@del /Q *.o $(TARGET) 2>nul || echo Очистка завершена.

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run