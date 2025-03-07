# директории
OUT := ./out/

# параметры компиляции
CC := gcc
CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -Wfloat-conversion -Wfloat-equal -g
LIBFLAGS :=
CLEAN := $(RM) -r $(OUT) *.exe ./*.gcov *.info *.lastbuildstate
CREATE_OUT := mkdir -p $(OUT)

unit_tests.exe : LIBFLAGS += -lcheck -lpthread -lrt
unit_tests.exe : $(OUT)check_main.o $(OUT)associative_array_impl_2.o $(OUT)check_func_1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

$(OUT)check_main.o : check_main.c check_func_1.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)check_func_1.o : check_func_1.c check_func_1.h associative_array.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)associative_array_impl_2.o : associative_array_impl_2.c associative_array.h
	$(CREATE_OUT)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY : unit clean %.lastbuildstate

%.lastbuildstate:
	$(CLEAN)
	touch $@

unit : unit_tests.exe
	./unit_tests.exe

clean :
	$(CLEAN)
