#!/bin/bash
# Usage: submitall.sh [<folder>] [<pattern to match>] [<extra RapidFit options>]
make -C modules -j
currentdir=$(pwd)
if [ "$1" == "" ]
then
	fitfolders=(toystudies mcfits/phasespace mcfits/pwave datafits)
else
	fitfolders=($1)
fi
for folder in ${fitfolders[@]}
do
	cd $currentdir/$folder
	for file in $(ls *$2*xml)
	do
		submission_script=$(echo "submit_$file" | sed 's/xml/sh/')
		cat <<-EOF > ${submission_script}
		#!/bin/bash
		#$ -N "$(echo $file | sed 's/.xml//')"
		#$ -l h_rt=00:05:00 
		#$ -l h_vmem=1G
		#$ -pe mpi 32
		#$ -cwd
		export PATH=\$PATH:~/RapidFit/bin
		. /etc/profile.d/modules.sh
		module load root
		module load igmm/apps/texlive
		mkdir -p FitResult_$(echo $file | sed 's/\.xml//g')
		cd FitResult_$(echo $file | sed 's/\.xml//g')
		fitting -f ../$file $3 | tee RapidFitOutput-\$(date +"%Y%m%d_%H%M%S").log
		$currentdir/output/mergeprojections.sh
		$currentdir/output/compareresult.sh
		EOF
		qsub ${submission_script}
		rm ${submission_script}
	done
done