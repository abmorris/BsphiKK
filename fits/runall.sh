#!/bin/bash
make -C modules -j
currentdir=$(pwd)
rapidfit=/scratch/adam/RapidFit/bin/fitting
if [ "$1" == "" ]
then
	fitfolders=(toystudies mcfits/phasespace mcfits/pwave datafits)
else
	fitfolders=($1)
fi
for folder in ${fitfolders[@]}
do
	cd $currentdir/$folder
	for file in $(ls *.xml)
		do $rapidfit -f $file
		/scratch/adam/BsphiKK/fits/output/mergeprojections.sh
		/scratch/adam/BsphiKK/fits/output/compareresult.sh
		mkdir -p FitResult_$(echo $file | sed 's/\.xml//g')
		mv -v RapidFitOutput* FitResult_$(echo $file | sed 's/\.xml//g')
	done
done
