#!/bin/bash
# Usage: submitall.sh [<folder>] [<pattern to match>] [<extra RapidFit options>]
source RFjobconfig.sh
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
#		runtimeoption=$(grep -h --color=never "\-l h_rt=" $file)
#		if [ "$runtimeoption" == "" ]
#		then
			runtimeoption=" #$ -l h_rt=04:00:00"
#		fi
		cat <<-EOF > ${submission_script}
		#!/bin/bash
		#$ -N "j_$(echo $file | sed 's/.xml//')"
		$runtimeoption
		#$ -l h_vmem=1G
		$ParallelEnv
		#$ -cwd
		#$ -hold_jid buildRapidFit
		# Re-make the XML file to pick up the number of threads this machine has
		rm $file && make -C $currentdir/modules ../$folder/$file
		# Set up the environment
		source $currentdir/RFjobconfig.sh
		EOF
		echo -e "$SetupEnvironment" >> ${submission_script}
		cat <<-EOF >> ${submission_script}
		export PATH=\$PATH:\$RapidFitDir/bin
		# Move to the right folder
		mkdir -p FitResult_$(echo $file | sed 's/\.xml//g')
		cd FitResult_$(echo $file | sed 's/\.xml//g')
		# Perform the fit
		fitting -f ../${file} $3 | tee RapidFitOutput-\$(date +"%Y%m%d_%H%M%S").log
		# Deal with the output
		$currentdir/output/mergeprojections.sh
		$currentdir/output/compareresult.sh
		EOF
		# Submit the jobs
		qsub ${submission_script}
		rm ${submission_script}
	done
done

