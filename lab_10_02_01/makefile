# директории
SRC := ./src/
INC := ./inc/
OUT := ./out/
UNIT := ./unit_tests/
SCRIPTS := ./func_tests/scripts/

# параметры компиляции
CC := gcc
CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-conversion -Wfloat-equal
LIBFLAGS := -lm
CLEAN := $(RM) -r $(OUT) *.exe $(SCRIPTS)*.txt ./*.gcov *.info *.lastbuildstate
CREATE_OUT := mkdir -p $(OUT)

app.exe : $(OUT)main.o $(OUT)node.o $(OUT)list.o $(OUT)polynomial_funtcions.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

unit_tests.exe : LIBFLAGS += -lcheck -lpthread -lrt
unit_tests.exe : $(OUT)check_main.o $(OUT)list.o $(OUT)node.o $(OUT)polynomial_funtcions.o $(OUT)check_polynomial_functions.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

$(OUT)check_main.o : $(UNIT)check_main.c $(INC)func_check.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)check_polynomial_functions.o : $(UNIT)check_polynomial_functions.c $(INC)polynomial_funtcions.h $(INC)list.h $(INC)func_check.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)main.o : $(SRC)main.c $(INC)list.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)list.o : $(SRC)list.c $(INC)list.h $(INC)node.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)node.o : $(SRC)node.c $(INC)node.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(OUT)polynomial_funtcions.o : $(SRC)polynomial_funtcions.c $(INC)polynomial_funtcions.h $(INC)list.h $(INC)node.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@


.PHONY : unit release func debug clean %.lastbuildstate

debug : debug.lastbuildstate
debug : CFLAGS += -fprofile-arcs -ftest-coverage -g
debug : app.exe

release : release.lastbuildstate
release : app.exe

%.lastbuildstate:
	$(CLEAN)
	touch $@

func : debug
	./full_testing.sh

unit : unit_tests.exe
	./unit_tests.exe

clean :
	$(CLEAN)
