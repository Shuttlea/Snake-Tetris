CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
GTFLAG = $(shell pkg-config --cflags --libs gtest) -pthread
CSLDIR = gui/cli/
DESDIR = gui/desctop/view/
TETDIR = brick_game/tetris/
SNKDIR = brick_game/snake/
GCOV_EX = --gcov-executable gcov-13 -r . --exclude-throw-branches --html --html-details
#GCOV_EX = --exclude-throw-branches --html --html-details


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	TESTRUN = ./googletest
else
	TESTRUN = leaks --atExit -- ./googletest
endif

all: tests

install: desk cons
	mkdir $(HOME)/Desktop/Brick_game2/
	cp $(PWD)/gui/desctop/View/build/View.app/Contents/MacOS/View $(HOME)/Desktop/Brick_game2/desktop
	rm -rf gui/desctop/View/build
	cp game $(HOME)/Desktop/Brick_game2/console
	rm -rf *.o game


uninstall:
	rm -rf $(HOME)/Desktop/Brick_game2 $(HOME)/tetrisHighScore $(HOME)/snakeHighScore

dist: desk cons
	mkdir Brick_game2
	cp $(PWD)/gui/desctop/View/build/View.app/Contents/MacOS/View Brick_game2/desctop
	rm -rf gui/desctop/View/build
	cp game Brick_game2/console
	rm -rf *.o game
	tar -cf Brick_game.tar Brick_game2

dvi:
	doxygen brick_config
	open html/index.html

tests:
	$(CC) $(CFLAGS) --coverage -c $(SNKDIR)snake.cpp 
	$(CC) $(CFLAGS) -c test/googletest.cpp $(GTFLAG)
	$(CC) $(CFLAGS) --coverage googletest.o snake.o -o googletest $(GTFLAG)
	$(TESTRUN)
	rm -rf report
	mkdir report
	gcovr $(GCOV_EX) -o report/vector__report.html
	rm -rf *.o *.gcda *.gcno snakeHighScore

clean: uninstall
	rm -rf *.o *.gcda *.gcno game snakeHighScore tetrisHighScore game report googletest html latex

desk:
	cd gui/desctop/View && mkdir build && cmake -B build
	cd gui/desctop/View/build && make

cons:
	$(CC) $(CFLAGS) -c $(CSLDIR)main.cpp  $(CSLDIR)view.cpp  $(TETDIR)controller.cpp $(SNKDIR)snake.cpp $(TETDIR)tetris.cpp -lncurses
	$(CC) $(CFLAGS) tetris.o snake.o controller.o view.o main.o -o game -lncurses	

clang: 
	clang-format -i gui/cli/*.h gui/cli/*.cpp $(TETDIR)*.h $(TETDIR)*.cpp $(SNKDIR)*.h $(SNKDIR)*.cpp $(DESDIR)*.h $(DESDIR)*.cpp \
	\test/*.h test/*.cpp