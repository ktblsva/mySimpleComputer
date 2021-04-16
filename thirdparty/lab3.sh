#!/bin/bash
echo -e "\E[H\E[2J"
echo -e "\E(0"
echo -e -n "\E[5;10H"
echo -n "l"
for number in 1 2 3 4 5 6
do
	echo -n "q"
done
echo -n "k"


for number in 1 2 3 4 5 6
do
	rows=5
	columns=10
	let "rows+=number"
	echo -e -n "\E[${rows};${columns}H"
	echo -n "x"
	# echo -n $rows
	let "columns+=7"
	echo -e -n "\E[${rows};${columns}H"
	echo -n "x"
	
	#echo -e -n "x"
done
echo -e -n "\E[12;10H"
echo -n "m"
for number in 1 2 3 4 5 6
do
	echo -n "q"
done
echo -n "j"

echo -e -n "\E[6;10H"
columns=10
for i in 1 2 3 4 5 6
do
	let "columns+=1"
	echo -e -n "\E[6;${columns}H"
	echo -n "a"
done

echo -e -n "\E[7;15H"
echo "aa"
columns=10
for i in 1 2 3 4 5 6
do
	let "columns+=1"
	echo -e -n "\E[8;${columns}H"
	echo -n "a"
done
echo -e -n "\E[9;11H"
echo "aa"
columns=10
for i in 1 2 3 4 5 6
do
	let "columns+=1"
	echo -e -n "\E[10;${columns}H"
	echo -n "a"
done

echo -e "\E(B"
echo -e -n "\E[15;1H"
