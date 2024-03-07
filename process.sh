#!/bin/bash

if [ "$#" -ne 1 ];then
	echo "usage: process <script>"
	
	
	
else
    ./wrapper $1 temp.cpp
    g++ -o temp temp.cpp
    ./temp

    rm temp.cpp
    rm temp

fi