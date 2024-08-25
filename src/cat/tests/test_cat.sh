# !/bin/bash

cd tests

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

RED='\033[0;31m'
GREEN='\033[0;32m'
NOCOLOR='\033[0m'

declare -a tests=(
"VAR test_case_cat.txt"
)

declare -a extra=(
# "no_file.txt"  FAILS (as intended)
"-s test_1_cat.txt"
"-b -e -n -s -t -v test_1_cat.txt"
"-t test_3_cat.txt"
"-n test_2_cat.txt"
"-n -b test_1_cat.txt"
"-s -n -e test_4_cat.txt"
"-n test_1_cat.txt"
"-n test_1_cat.txt test_2_cat.txt"
"-v test_5_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    # valgrind --leak-check=full --show-leak-kinds=all ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++  ))
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++  ))
        echo -e "${RED}${FAIL}${NOCOLOR}/${GREEN}${SUCCESS}${NOCOLOR}/${COUNTER} ${GREEN}success${NOCOLOR} cat $t"
    else
      (( FAIL++  ))
        echo -e "${RED}${FAIL}${NOCOLOR}/${GREEN}${SUCCESS}${NOCOLOR}/${COUNTER} ${RED}fail${NOCOLOR} cat $t"
    fi

}


# specifics
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 param
for var1 in b e n s t v
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 params
for var1 in b e n s t v
do
    for var2 in b e n s t v
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
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
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


./s21_cat sample_1_cat.txt

# 4 params
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            for var4 in b e n s t v
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

./s21_cat sample_2_cat.txt

#  5 params
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            for var4 in b e n s t v
            do
                for var5 in b e n s t v
                do
                    if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                    && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                    && [ $var2 != $var4 ] && [ $var3 != $var4 ] \
                    && [ $var1 != $var5 ] && [ $var2 != $var5 ] \
                    && [ $var3 != $var5 ] && [ $var4 != $var5 ]
                    then
                        for i in "${tests[@]}"
                        do
                            var="-$var1 -$var2 -$var3 -$var4 -$var5"
                            testing $i
                        done
                    fi
                done
            done
        done
    done
done

# Output the results
echo
echo -e "${RED}FAIL: $FAIL${NOCOLOR}"
echo -e "${GREEN}SUCCESS: $SUCCESS${NOCOLOR}"
echo "ALL: $COUNTER"