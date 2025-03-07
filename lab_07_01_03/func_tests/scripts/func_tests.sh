#!/bin/bash

GREEN=$'\e[0;32m'
RED=$'\e[0;31m'
NC=$'\e[0m'

errors=0

echo -e '\n----------------------------------\n'

echo -e 'pos_case:\n'

FILES="../data/pos_??_in.txt"
for in_test in $FILES
do
	num=$(echo "$in_test" | sed 's/.*pos_\(..\)_in.txt/\1/')
    if ! [[ $num =~ ^[0-9]{2}$ ]]; then
        break
    fi
    out_test=../data/pos_"$num"_out.txt
    args_test=../data/pos_"$num"_args.txt

    
    if bash ./pos_case.sh "$in_test" "$out_test" "$args_test"; then
        echo -n "POS TEST pos_${num}_in.txt: ${GREEN}PASS${NC}"

    else
        echo -n "POS TEST pos_${num}_in.txt: ${RED}FAIL${NC}"   
        errors=$((errors + 1))
    fi

    if bash ./valgrind_check.sh "$in_test"; then
        echo " VALGRIND ${GREEN}PASS${NC}"
    else
        echo " VALGRIND ${RED}FAIL${NC}"
    fi
done

echo -e '\nneg_case:\n'

FILES="../data/neg_??_in.txt"   
for in_test in $FILES
do
	num=$(echo "$in_test" | sed 's/.*neg_\(..\)_in.txt/\1/')
    if ! [[ $num =~ ^[0-9]{2}$ ]]; then
        break
    fi

    args_test=../data/neg_"$num"_args.txt

    if bash ./neg_case.sh "$in_test" "$args_test"; then
        echo -n "NEG TEST neg_${num}_in.txt: ${GREEN}PASS${NC}" 

    else
        echo -n "NEG TEST neg_${num}_in.txt: ${RED}FAIL${NC}" 
        errors=$((errors + 1))
    fi

    if bash ./valgrind_check.sh "$in_test"; then
        echo " VALGRIND ${GREEN}PASS${NC}"
    else
        echo " VALGRIND ${RED}FAIL${NC}"
    fi
done

echo -e '\n----------------------------------\n'

exit $errors