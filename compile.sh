#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'

DEF=""

if [ $# -gt 0 ]; then
  for var in "$@"
  do
    if [ "$var" == "c" ]; then
      clear
    elif [ "$var" == "clear" ]; then
      clear
    fi
    
    if [[ $var == D* ]]; then
      DEF+=" -"$var
      echo "Definition was added: $DEF"
    fi
  done
fi

g++ $DEF \
main.cpp \
src/Loader.cpp \
src/Loader_soot.cpp \
src/Record.cpp \
src/Switch.cpp \
src/common.cpp \
src/Loader_osa.cpp \
src/Factory.cpp \
src/Loader_spoon.cpp \
src/Option.cpp \
src/OptionMethods.cpp \
src/Labels.cpp \
src/Loader_jcg.cpp \
src/Loader_wala.cpp \
src/Loader_trace.cpp \
src/Loader_jdt.cpp \
src/GraphDBCommon.cpp \
src/StatMethods.cpp \
src/StaticIteration.cpp \
-o main \
-std=c++11 -Wall -Werror

if [ $? -eq 0 ]; then
  echo -e "${GREEN}Compilation success: comparer${NC}"
else
  echo -e "${RED}Compilation failed: comparer${NC}"
fi

g++ commonTSV.cpp -std=c++11 -Wall -Werror -o commonTSV

if [ $? -eq 0 ]; then
  echo -e "${GREEN}Compilation success: table-generator${NC}"
else
  echo -e "${RED}Compilation failed: table-generator${NC}"
fi

g++ traceValami.cpp -std=c++11 -Wall -Werror -o traceValami

if [ $? -eq 0 ]; then
  echo -e "${GREEN}Compilation success: traceValami${NC}"
else
  echo -e "${RED}Compilation failed: traceValami${NC}"
fi