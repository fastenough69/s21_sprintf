GCC= gcc -std=c11
FLAGS= -Wall -Wextra -Werror
MAIN_FILE= s21_sprintf.c
VALGRIND= valgrind --tool=memcheck --leak-check=yes
TARGET= s21_sprintf

all: $(TARGET)

$(TARGET): 
	$(GCC) $(FLAGS) $(MAIN_FILE) -o $(TARGET)

test:
	$(VALGRIND) ./$(TARGET)

clean:
	rm -rf s21_sprintf
	rm -rf *.a *.out *.o

rebuild:
	make clean
	make all