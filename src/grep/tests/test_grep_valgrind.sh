#!/bin/bash

cd tests

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

RED='\033[0;31m'
GREEN='\033[0;32m'
NOCOLOR='\033[0m'

declare -a tests=(
"flags test_0_grep.txt VAR"
)

declare -a extra=(
"-n for test_1_grep.txt test_2_grep.txt"
"-n for test_1_grep.txt"
"-n -e ^\} test_1_grep.txt"
"-ce ^int test_1_grep.txt test_2_grep.txt"
"-e ^int test_1_grep.txt"
"-nivh test_1_grep.txt test_2_grep.txt"
"-e"
"-e INT test_5_grep.txt"
"-e char test_1_grep.txt test_2_grep.txt"
"-ne -e out test_5_grep.txt"
"-iv int test_5_grep.txt"
"-in int test_5_grep.txt"
"-c -l aboba test_1_grep.txt test_5_grep.txt"
"-v test_1_grep.txt -e ank"
"-ne ) test_5_grep.txt"
"-l for test_1_grep.txt test_2_grep.txt"
"-e int test_4_grep.txt"
"-e -e out test_5_grep.txt"
"-f test_3_grep.txt test_5_grep.txt"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    valgrind --leak-check=full --show-leak-kinds=all ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++  ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++  ))
        echo -e "${RED}${FAIL}${NOCOLOR}/${GREEN}${SUCCESS}${NOCOLOR}/${COUNTER} ${GREEN}success${NOCOLOR} grep $t"
    else
      (( FAIL++  ))
        echo -e "${RED}${FAIL}${NOCOLOR}/${GREEN}${SUCCESS}${NOCOLOR}/${COUNTER} ${RED}fail${NOCOLOR} grep $t"
    fi
}



# specifics
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

cat test.txt

# 1 param
for var1 in v c l n h i o f s e
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 params
for var1 in v c l n h i o f s e
do
    for var2 in v c l n h 
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 params
for var1 in v c l n h i 
do
    for var2 in v c l n h i 
    do
        for var3 in v c l n h i 
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 2 joined params
for var1 in v c l n h i 
do
    for var2 in v c l n h i 
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                testing $i
            done
        fi
    done
done

# 3 joined params
for var1 in v c l n h i 
do
    for var2 in v c l n h i 
    do
        for var3 in v c l n h i 
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    testing $i
                done
            fi
        done
    done
done

# Output the results
echo
echo -e "${RED}FAIL: $FAIL${NOCOLOR}"
echo -e "${GREEN}SUCCESS: $SUCCESS${NOCOLOR}"
echo "ALL: $COUNTER"