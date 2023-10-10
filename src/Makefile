CC = -Wall -Werror -Wextra -std=c11
FLAGS = -lcheck -lpthread -fprofile-arcs
FLAGS += -ftest-coverage

all: clean install open

install: clean
	mkdir -p build
	cd frontend && qmake && make && make clean
	mv frontend/3DViewer.app build 
	
uninstall:
	cd frontend && rm -rf Makefile 3DViewer.app 3DViewer.pro.user .qmake.stash .qtc_clangd .tmp .qm
	rm -rf build/3DViewer.app

open:
	./build/3DViewer.app/Contents/MacOS/3DViewer

dvi:
	open ./readme/readme.md

# test: clean
# 	gcc $(CC) ./tests/test.c ./backend/s21_smart_calc.c -lcheck -o ./build/test.out
# 	./build/test.out

# gcov_report: clean
# 	gcc $(CC) tests/test.c backend/s21_smart_calc.c $(FLAGS) -o ./build/test.out
# 	./build/test.out
# 	lcov -t "./test"  -o report.info --no-external -c -d .
# 	genhtml -o report report.info
# 	open ./report/index.html
# 	rm -rf *.gcno *gcda *.gco

rebuild: clean install open

clean: uninstall
	rm -rf frontend/*.o *.a ./build/test.out
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf smart_new.tar.gz

check:
	clear
	@cp ../materials/linters/.clang-format .
	cd backend/ && clang-format -n *.c *.h *.cpp
	cd frontend/ && clang-format -n *.cpp *.h
	cd tests/ && clang-format -n *.c *.h
	@rm .clang-format 
