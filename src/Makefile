CC = -Wall -Werror -Wextra -std=c11
FLAGS = -lcheck -lpthread -fprofile-arcs
FLAGS += -ftest-coverage
CHECK = -i


all: clean install dvi open

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
	open readme.html

dist: clean install
	cd .. && tar -czvf src/3DViewer.tar.gz src

obj: 
	open -a safari https://github.com/belkamydog/obj/raw/main/obj.zip

test: clean
	gcc $(CC) ./tests/test.c ./backend/*.c  ./backend/matrix/*.c -lcheck -o ./build/test.out
	./build/test.out

gcov_report: clean
	gcc $(CC) ./tests/test.c ./backend/*.c ./backend/matrix/*.c $(FLAGS) -o ./build/test.out
	./build/test.out
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gco

rebuild: clean install open

clean: uninstall
	rm -rf frontend/*.o *.a ./build/test.out
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf smart_new.tar.gz

check:
	clear
	@cp ../materials/linters/.clang-format .
	cd backend/ && clang-format $(CHECK) *.c *.h
	cd backend/matrix/ clang-format $(CHECK) *.c *.h *.cpp
	cd frontend/ && clang-format $(CHECK) *.cpp *.h
	cd tests/ && clang-format $(CHECK) *.c *.h
	@rm .clang-format 
