@echo off
set path=%path%;../util/bin/
bison -d gram.y
flex -o lex.yy.cc lex.l