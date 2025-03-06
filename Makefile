GCC= gcc -std=c11
FLAGS= -Wall -Wextra -Werror
MAIN_FILE= s21_sprintf.c
VALGRIND= valgrind --tool=memcheck --leak-check=yes
TARGET= s21_sprintf
LIBS_TEST= -lcheck -lpthread -lm -lrt -lsubunit

all: $(TARGET)

$(TARGET): 
	$(GCC) $(FLAGS) $(MAIN_FILE) -o $(TARGET)

test: test_compile
	./test.o >> test.md

test_compile: obj
	$(GCC) test/test.c $(TARGET).o -o test.o $(LIBS_TEST)

obj:
	$(GCC) $(FLAGS) -c s21_sprintf.c -o $(TARGET).o

clear_test:
	rm -rf test.*
	rm -rf *.o

clean:
	rm -rf s21_sprintf
	rm -rf *.a *.out *.o

rebuild:
	make clean
	make all