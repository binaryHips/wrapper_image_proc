#!/bin/bash

suppr_source=1

#options
while getopts "s" option; do
    case "${option}" in
        s)
            suppr_source=0
            ;;
        *)
            echo "usage: $0 [-s] <script>"
	        exit 1
            ;;
    esac
done
shift $((OPTIND-1)) # I hate bash



#usage
if [ "$#" -ne 1 ];then
	echo "usage: $0 [-s] <script>"
	exit 1
	
	
else


    ./wrapper $1 temp.cpp
    g++ -o temp temp.cpp
    ./temp

    rm temp
    if [ "${suppr_source}" == 1 ]; then
        rm temp.cpp #keep generated source only if we put the option
    fi
fi