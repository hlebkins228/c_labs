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

app.exe : $(OUT)main.o $(OUT)matrix_alloc_functions.o $(OUT)matrix_io_functions.o $(OUT)matrix_calc_functions.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

unit_tests.exe : LIBFLAGS += -lcheck -lpthread -lrt
unit_tests.exe : $(OUT)check_main.o $(OUT)matrix_alloc_functions.o $(OUT)matrix_io_functions.o $(OUT)matrix_calc_functions.o $(OUT)check_unit_tests.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

$(OUT)check_main.o : $(UNIT)check_main.c $(INC)func_check.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)check_main.o

$(OUT)check_unit_tests.o : $(UNIT)check_unit_tests.c $(INC)func_check.h $(INC)matrix_alloc_functions.h $(INC)matrix_calc_functions.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)check_unit_tests.o

$(OUT)main.o : $(SRC)main.c $(INC)matrix_alloc_functions.h $(INC)matrix_io_functions.h $(INC)matrix_calc_functions.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)main.o

$(OUT)matrix_alloc_functions.o : $(SRC)matrix_alloc_functions.c $(INC)matrix_alloc_functions.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)matrix_alloc_functions.o

$(OUT)matrix_io_functions.o : $(SRC)matrix_io_functions.c $(INC)matrix_alloc_functions.h $(INC)matrix_io_functions.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)matrix_io_functions.o

$(OUT)matrix_calc_functions.o : $(SRC)matrix_calc_functions.c $(INC)matrix_calc_functions.h $(INC)exitcodes.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $(OUT)matrix_calc_functions.o


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
