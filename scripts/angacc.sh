#!/bin/bash
source eos.sh
cd ../fits/results
make -C ../modules -j
trigger=Gen
fitting -f acceptance$trigger.xml --calculateAcceptanceCoefficients
mv -v LegendreMoments_1.root LegendreMoments_Acceptance_$trigger.root
mv -v sampled_LegendreMomentShape_1.root sampled_LegendreMomentShape_$trigger.root
xrdcp --verbose --force LegendreMoments_Acceptance_*.root ${nTuples_dir}
rename LegendreMomentShape acceptance sampled_LegendreMomentShape_*.root

for trigger in TIS TOS TOS_PIDcalib TOS_14ps TOS_17ps
do
  fitting -f acceptance$trigger.xml --calculateAcceptanceCoefficients
  mv -v LegendreMoments_1.root LegendreMoments_Acceptance_not$trigger.root
  mv -v LegendreMoments_2.root LegendreMoments_Acceptance_$trigger.root
  mv -v sampled_LegendreMomentShape_1.root sampled_LegendreMomentShape_not$trigger.root
  mv -v sampled_LegendreMomentShape_2.root sampled_LegendreMomentShape_$trigger.root
  xrdcp --verbose --force LegendreMoments_Acceptance_*.root ${nTuples_dir}
  rename LegendreMomentShape acceptance sampled_LegendreMomentShape_*.root
done
for file in $(ls sampled_acceptance_*.root)
do
  ../../bin/PlotAngAcc $file $(echo $file | sed 's/sampled_acceptance_//g' | sed 's/\.root//g')
done
mv -v acceptance_*pdf ../../latex/figs/

