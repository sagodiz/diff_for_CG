#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m'

if [ $# -eq 1 ]; then
  if [ "$1" == "c" ]; then
    clear
  elif [ "$1" == "clear" ]; then
    clear
  fi
fi

g++ main.cpp src/Loader.cpp src/Loader_soot.cpp src/Record.cpp src/Switch.cpp src/Loader_callerhierarchy.cpp src/common.cpp src/Loader_sourcemeter.cpp src/Factory.cpp src/Loader_spoon.cpp src/Option.cpp src/OptionMethods.cpp src/Labels.cpp src/Loader_gousiosg.cpp src/Loader_wala.cpp src/Loader_trace.cpp src/GraphDBCommon.cpp -o main -std=c++11 -Wall -Werror

if [ $? -eq 0 ]; then
  echo -e "${GREEN}Sikeres fordítás: egyesítő${NC}"
else
  echo -e "${RED}Sikertelen fordítás: egyesítő${NC}"
fi

g++ commonTSV.cpp -std=c++11 -Wall -Werror -o commonTSV

if [ $? -eq 0 ]; then
  echo -e "${GREEN}Sikeres fordítás: táblázatos${NC}"
else
  echo -e "${RED}Sikertelen fordítás: táblázatos${NC}"
fi