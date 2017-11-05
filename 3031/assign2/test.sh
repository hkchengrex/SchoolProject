#!/bin/bash

bison -d matfunc.y
flex -d matfunc.lex
gcc *.c 
./a.out testcase.txt
