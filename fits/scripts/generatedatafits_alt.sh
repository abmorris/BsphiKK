#!/bin/bash
CWD=$(pwd)
#  protect against empty string
if [ -z "${CWD}" ]
then
	exit 1
fi
bindir="${CWD}/../bin"
srcdir="${CWD}/src/datafits/alt"
best=(nonres fzero980 phi1020 fzero1500LHCb ftwop1525 phi1680)
mkdir -p ${srcdir}
for extra in "altbarrier" "altflatte" "floatflatte" "conspeaking" "nopeaking" "notminLb" "conssigfrac" "altresolution" "alttrigger" "altlifetime" "PIDcalib" #"splitbyyear" "splitbytrigger" "splitbymagnet"
do
	cd ${srcdir}
	${bindir}/PrintSource ${best[@]} ${extra}
	cd ${CWD}
done
cd ${srcdir}
${bindir}/PrintSource ${best[@]} "conspeaking" "conssigfrac"
${bindir}/PrintSource ${best[@]} "conspeaking" "conssigfrac" "floatflatte"
${bindir}/PrintSource nonres fzero980 phi1020 fzero1500LHCb ftwop1525 phi1680 alt1680
${bindir}/PrintSource nonres fzero980 phi1020 fzero1500 ftwop1525 phi1680
cd ${CWD}

