#!/bin/bash

if [ $# -ne 2 ]
  then
    echo "Niepoprawna ilość parametrów."
    exit 1;
fi

PROG="$(realpath "$1")"
DIR="$(realpath "$2")"

for f in $DIR/*.in
do
  filename=${f%.in}
  printf "Testuję działanie programu dla pliku $(basename "$f").\n"
  printf "Output: "
  $PROG < "$f" 1> output.out 2> output.err

  if diff output.out "$filename.out" >/dev/null
    then
      if diff output.err "$filename.err" >/dev/null
        then
          printf "poprawny.\n"
        else
          printf "niepoprawny.\n"
      fi
    else
      printf "niepoprawny.\n"
  fi

  printf "Zarządzanie pamięcią:\n"
  valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all $PROG < "$f"

  if [ $? -eq 123 ]
    then
      printf "Wykryto problemy z pamięcią.\n"
    else
      printf "Nie wykryto problemów z pamięcią.\n"
  fi
  printf "\n"

done
rm -f output.out output.err


