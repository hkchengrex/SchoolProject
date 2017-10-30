#!/bin/bash

bison -d matfunc.y
flex -o matfunc.lex.yy.c matfunc.lex
gcc *.c -o test -lm
./test testcase.txt
