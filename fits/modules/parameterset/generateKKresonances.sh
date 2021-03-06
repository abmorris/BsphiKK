#!/bin/bash
function newKK()
{
	name=$1
	echo "Building ${name}"
	spin=$2
	mass=$3
	muperr=$4
	mloerr=$5
	width=$6
	wuperr=$7
	wloerr=$8
	./newresonance.sh ${name} ${mass} ${width} > resonances/${name}_float.xml
	cp resonances/${name}_float.xml resonances/${name}_fixed.xml
	sed -i "s/Float/Fixed/" resonances/${name}_fixed.xml
	./newamplitude.sh ${name} ${spin} 0.0 > amplitudes/${name}_float.xml
	cp amplitudes/${name}_float.xml amplitudes/${name}_float_fixdeltazero.xml
	cp amplitudes/${name}_float.xml amplitudes/${name}_float_fixdeltaminus.xml
	cp amplitudes/${name}_float.xml amplitudes/${name}_float_fixdeltazero_fixdeltaminus.xml
	for polarisation in "zero" "minus"
	do
		sed -i "s/<Type>Float<\/Type> #delta${polarisation}/<Type>Fixed<\/Type> #delta${polarisation}/" amplitudes/${name}_float_fix*delta${polarisation}*.xml
	done
	if [[ ${name} == *"ftwop1525"* ]]
	then
		sed -i "s/<Value>.*<\/Value> #Azero/<Value>0.9<\/Value> #Azero/" amplitudes/${name}_float.xml
		sed -i "s/<Value>.*<\/Value> #Aplus/<Value>0.3<\/Value> #Aplus/" amplitudes/${name}_float.xml
		sed -i "s/<Value>.*<\/Value> #deltaminus/<Value>1.4<\/Value> #deltaminus/" amplitudes/${name}_float.xml
		sed -i "s/<Value>.*<\/Value> #deltaplus/<Value>2.0<\/Value> #deltaplus/" amplitudes/${name}_float.xml
		sed -i "s/<Value>.*<\/Value> #deltazero/<Value>-0.4<\/Value> #deltazero/" amplitudes/${name}_float.xml
	fi
	if [ ${spin} -gt 0 ]
	then
		cp amplitudes/${name}_float.xml amplitudes/${name}_float_longitudinal.xml
		sed -i "s/<Type>Float<\/Type> #Azero/<Type>Fixed<\/Type> #Azero/" amplitudes/${name}_float_longitudinal.xml
		sed -i "s/<Value>.*<\/Value> #Azero/<Value>1.0<\/Value> #Azero/" amplitudes/${name}_float_longitudinal.xml
		sed -i "s/<Value>.*<\/Value> #Aplus/<Value>0.0<\/Value> #Aplus/" amplitudes/${name}_float_longitudinal.xml
		for polarisation in "plus" "minus"
		do
			sed -i "s/<Type>Float<\/Type> #A${polarisation}/<Type>Fixed<\/Type> #A${polarisation}/" amplitudes/${name}_float_longitudinal.xml
			sed -i "s/<Type>Float<\/Type> #delta${polarisation}/<Type>Fixed<\/Type> #delta${polarisation}/" amplitudes/${name}_float_longitudinal.xml
		done
		cp amplitudes/${name}_float.xml amplitudes/${name}_float_transverse.xml
		sed -i "s/<Type>Float<\/Type> #Azero/<Type>Fixed<\/Type> #Azero/" amplitudes/${name}_float_transverse.xml
		sed -i "s/<Type>Float<\/Type> #deltazero/<Type>Fixed<\/Type> #Adeltazero/" amplitudes/${name}_float_transverse.xml
		sed -i "s/<Value>.*<\/Value> #Azero/<Value>0.0<\/Value> #Azero/" amplitudes/${name}_float_transverse.xml
		sed -i "s/<Value>.*<\/Value> #Aplus/<Value>0.707<\/Value> #Aplus/" amplitudes/${name}_float_transverse.xml
	fi
	./newfraction.sh ${name} ${spin} "BW" > fractions/${name}_float.xml
	cp fractions/${name}_float.xml fractions/${name}_fixed.xml
	sed -i "s/<Type>Float<\/Type>/<Type>Fixed<\/Type>/" fractions/${name}_fixed.xml
	if [ "${spin}" == "0" ]
	then
		./newfraction.sh ${name} ${spin} "SP" > fractions/${name}_spline_float.xml
	fi
	./newconstraint.sh ${name} ${mass} ${mloerr} ${muperr} ${width} ${wloerr} ${wuperr} > ../constraintfunction/${name}_constraint.xml
}
# Note: f0(980) added by hand because Flatte
#     Name          J mass     +        −        width    +        −
newKK phi1020       1 1.019461 0.000019 0.000019 0.004266 0.000031 0.000031
newKK ftwo1270      2 1.2755   0.0008   0.0008   0.1867   0.0022   0.0025
newKK fzero1370     0 1.350    0.150    0.150    0.350    0.150    0.150
newKK fzero1370LHCb 0 1.475    0.006    0.006    0.113    0.011    0.011
newKK fzero1500     0 1.504    0.006    0.006    0.109    0.007    0.007
newKK fzero1500LHCb 0 1.461    0.003    0.003    0.124    0.007    0.007
newKK ftwop1525     2 1.525    0.005    0.005    0.073    0.006    0.005
newKK ftwop1525LHCb 2 1.522    0.006    0.003    0.084    0.012    0.008
newKK ftwo1565      2 1.562    0.013    0.013    0.134    0.008    0.008
newKK ftwo1640      2 1.639    0.006    0.006    0.099    0.060    0.040
newKK phi1680       1 1.680    0.020    0.020    0.159    0.050    0.050
newKK fzero1710     0 1.723    0.006    0.005    0.139    0.008    0.008
newKK ftwo1750      2 1.737    0.009    0.009    0.151    0.033    0.033
newKK ftwo1810      2 1.815    0.012    0.012    0.197    0.022    0.022
# Custom styles for the phi and f2"
for file in $(ls fractions/phi1020* fractions/ftwop1525*)
do
	sed -i "s/style: 1/style: 9/" $file
	sed -i "s/width: 1/width: 2/" $file
	sed -i "s/colour: 1/colour: 28/" $file
done
for file in $(ls fractions/phi1020*)
do
	sed -i "s/colour: [0-9]*/colour: 6/" $file
	sed -i "s/<Value>0.01<\/Value>/<Value>1.0<\/Value>/" $file
done
for file in $(ls fractions/ftwop1525*)
do
	sed -i "s/<Value>0.01<\/Value>/<Value>2.5<\/Value>/" $file
done
exit 0

