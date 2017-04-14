#!/bin/bash
source eos.sh
cd ../fits
for trigger in $(echo "TIS TOS")
do
  fitting -f acceptance$trigger.xml --calculateAcceptanceCoefficients
  mv -v LegendreMoments_1.root LegendreMoments_Acceptance_not$trigger.root
  mv -v LegendreMoments_2.root LegendreMoments_Acceptance_$trigger.root
  mv -v sampled_LegendreMomentShape_1.root sampled_LegendreMomentShape_not$trigger.root
  mv -v sampled_LegendreMomentShape_2.root sampled_LegendreMomentShape_$trigger.root
  cp -v LegendreMoments_Acceptance_*.root ${nTuples_dir}
  rename LegendreMomentShape acceptance sampled_LegendreMomentShape_*.root
  for file in $(ls sampled_acceptance_*.root)
  do
    ../bin/PlotAngAcc $file $(echo $file | sed 's/sampled_acceptance_//g' | sed 's/\.root//g')
  done
done
mv -v acceptance_*pdf ../latex/figs/
exit 0
ls

