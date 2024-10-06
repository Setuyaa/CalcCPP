CC=gcc 
NAME = s21_smart_calc.a
CFLAGS=-Wall -Wextra -Werror  -std=c11
FILES = *.c
TEST_SRC= tests/*.c 
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
TEST_FLAGS=-lcheck 
ADDRESSFLAGS=-fsanitize=address

all: install

${NAME}:
	$(CC) $(CFLAGS) -c ${FILES}
	ar rc ${NAME} *.o
	ranlib ${NAME}
	rm *.o

tests: gcov_report

gcov_report: ${NAME}
	$(CC) ${GCOV_FLAGS} -c $(FILES)
	$(CC) $(CFLAGS) -c ${TEST_SRC} 
	$(CC) $(GCOV_FLAGS) *.o ${NAME} ${TEST_FLAGS} -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html


test: ${NAME}
	$(CC) $(CFLAGS) -c ${TEST_SRC} 
	$(CC) *.o ${NAME} ${TEST_FLAGS} -o test
	./test

dvi:
	open README.md

dist: install
	tar -czf c23.tar.gz --directory=build/ .

install: uninstall
	mkdir build
	cd build && qmake ../c23.pro
	make -C ./build/

uninstall:
	rm -Rf build/
	rm -rf C23.tar.gz

style:
	clang-format -style=google -i *.c *.cpp *.h

check_style:
	clang-format -style=google -n *.c *.cpp *.h

clean: uninstall
	rm -rf report
	rm -rf obj *.a test test.info ./gcov_report program *.o *.gch *.gcno *.gcda c23.tar.gz c23 exec ./a.out main_coverage.info
