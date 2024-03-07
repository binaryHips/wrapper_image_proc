#!/bin/bash

OPTSTRING=":s" #option to keep the generated source

if [ "$#" -ne 1 ];then
	echo "usage: process <script>"
	
	
	
else

    getopts ${OPTSTRING} opt



    ./wrapper $1 temp.cpp
    g++ -o temp temp.cpp
    ./temp

    rm temp

    if [${opt} -ne "s"]; then
        rm temp.cpp
    fi
fi