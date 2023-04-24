CC= gcc
CFLAGS=-g -Werror -Wextra -std=c11
SOURSES=main.c s21_matrix.c test.c
OBJECTS=$(SOURSES:.c=.o)
TEST_FLAGS=-lcheck $(shell pkg-config --cflags --libs check)
LIB=s21_matrix.a

ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit
endif

all: clean $(LIB)

$(LIB): s21_matrix.o
	ar rc $(LIB) s21_matrix.o
	ranlib $(LIB)
	rm *.o

debug: $(LIB) main.o
	$(CC) $(CFLAGS) main.o $(LIB) -lm -o debug

test: $(LIB)
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	./test

# $(CC) $(CFLAGS) test.o $(LIB) $(TEST_FLAGS) -o test
# ./test

add_coverage_flag: 
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag test
	./test
	rm test.g*
	lcov -t “gcov_test” -o test.info --rc lcov_branch_coverage=1 --no-external -c -d .
	genhtml -o report/ test.info --rc lcov_branch_coverage=1
	open ./report/index.html

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov \
	*.html *.css *.info report main/*.o s21_math debug

rebuild: clean all
