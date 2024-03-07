#!/bin/bash

if [ "$#" -ne 1 ];then
	echo "usage: process <script>"
	
	
	
else
    ./wrapper $1 temp.cpp
    g++ -o temp temp.cpp -w
    ./temp

   # rm temp.cpp #commenter cette ligne pour garder le fichier c++ généré
    rm temp

fi