#!/bin/bash
set -e
trap "rm -rf bin" EXIT
if [[ ! -d bin ]]
then
    mkdir bin
fi
g++ -std=c++17 -O2 src/io.cpp src/graph.cpp src/max_flow.cpp src/bipartite_matching.cpp src/bipartite_matching_main.cpp -Wl,--stack,268435456 -o bin/bipartite_matching
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
    fno="output/${bsnm}.bm.out.txt"
    sed /^#/d < $fn > $fnc
    echo -e "-----------------------------------------"
    bin/bipartite_matching < $fnc > $fno
    printf "\033[0;33m"
    echo $fno
    printf "\033[0m"
    cat $fno
    echo
    rm $fnc
done
unset fn fnc fno
