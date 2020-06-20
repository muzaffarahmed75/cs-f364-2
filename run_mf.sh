#!/bin/bash
set -e
trap "rm -rf bin" EXIT
if [[ ! -d bin ]]
then
    mkdir bin
fi
g++ -std=c++17 -O2 src/io.cpp src/graph.cpp src/max_flow.cpp src/maxflow_main.cpp -Wl,--stack,268435456 -o bin/max_flow
if [[ ! -d output ]]
then
    mkdir output
fi
set +e
for fn in $@
do
    if [[ ! -f $fn ]]
    then
        continue
    fi
    bsnm=$(basename $fn .txt)
    fnc="${bsnm}_clean.txt"
    fno="output/${bsnm}.mf.out.txt"
    sed /^#/d < $fn > $fnc
    echo -e "---------------------------------"
    bin/max_flow < $fnc > $fno
    printf "\033[0;33m"
    echo $fno
    printf "\033[0m"
    cat $fno
    echo
    rm $fnc
done
unset fn fnc fno
