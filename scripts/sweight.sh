#!/bin/bash
table=../scripts/tables/mKKcutResults.csv
cd ../ntuples/
modes=(BsphiKK_data BsphiKK_MC)
fitrange="--xmin 5250 --xmax 5500"
for mode in ${modes[@]}; do
  cutapplier ${mode}_mvaVars_vetoes.root DecayTree "TMath::Abs(BCON_KK_M-1019.461)<15" ${mode}_phi_mvaVars_vetoes.root 2>&1| tee log_${mode}_phi.tmp &
  cutapplier ${mode}_mvaVars_vetoes.root DecayTree "BCON_KK_M>1050" ${mode}_1050_mvaVars_vetoes.root 2>&1| tee log_${mode}_1050.tmp &
  cutapplier ${mode}_mvaVars_vetoes.root DecayTree "BCON_KK_M<1800" ${mode}_1800_mvaVars_vetoes.root 2>&1| tee log_${mode}_1800.tmp &
  cutapplier ${mode}_mvaVars_vetoes.root DecayTree "BCON_KK_M>1050&&BCON_KK_M<1800" ${mode}_1050_1800_mvaVars_vetoes.root 2>&1| tee log_${mode}_1050_1800.tmp &
done
wait
for mode in ${modes[@]}; do
  for label in phi 1050 1800 1050_1800; do
    line=$(grep "accepted" log_${mode}_${label}.tmp)
    value=$(echo $line | sed -r 's/^accepted:\s*?(.*?)\s*\+\/-.*$/\1/')
    error=$(echo $line | sed -r 's/^accepted:.*?\+\/-\s*(.*?)\s*$/\1/')
    ../bin/UpdateResults ${table} ${mode}_mKKcut$(echo ${label} | sed 's/1050/A/' | sed 's/1800/B/')_evts yield ${value} ${error}
  done
  rm -v log_${mode}*.tmp
done
../bin/ExportResults ${table} ../latex/results/mKKcutResults.tex
cd ../fits/
table=../scripts/tables/MassFits.csv
../bin/BsMassFit \
    -M ../ntuples/BsphiKK_MC_mvaVars_vetoes.root \
    -R ../ntuples/BsphiKK_data_mvaVars_vetoes.root \
    -O ../latex/figs/initialmassfit \
    -N B_s0_LOKI_Mass \
    --sweight $fitrange \
    --pulls \
    --save-results initialmassfit \
    --output-file ${table}
../bin/BsMassFit \
    -M ../ntuples/Bsphiphi_MC_mvaVars_vetoes.root \
    -R ../ntuples/BsphiKK_data_phi_mvaVars_vetoes.root \
    -O ../latex/figs/initialmassfitphi \
    -N B_s0_LOKI_Mass \
    --sweight $fitrange \
    --pulls \
    --output-file ${table}
../bin/BsMassFit \
    -M ../ntuples/BsphiKK_MC_1050_mvaVars_vetoes.root \
    -R ../ntuples/BsphiKK_data_1050_mvaVars_vetoes.root \
    -O ../latex/figs/initialmassfit1050 \
    -N B_s0_LOKI_Mass \
    --sweight $fitrange \
    --pulls \
    --save-results initialmassfitA \
    --output-file ${table}
../bin/BsMassFit \
    -M ../ntuples/BsphiKK_MC_1800_mvaVars_vetoes.root \
    -R ../ntuples/BsphiKK_data_1800_mvaVars_vetoes.root \
    -O ../latex/figs/initialmassfit1800 \
    -N B_s0_LOKI_Mass \
    --sweight $fitrange \
    --pulls \
    --save-results initialmassfitB \
    --output-file ${table}
../bin/BsMassFit \
    -M ../ntuples/BsphiKK_MC_1050_1800_mvaVars_vetoes.root \
    -R ../ntuples/BsphiKK_data_1050_1800_mvaVars_vetoes.root \
    -O ../latex/figs/initialmassfit10501800 \
    -N B_s0_LOKI_Mass \
    --sweight $fitrange \
    --draw-region 3 \
    --pulls \
    --save-results initialmassfitAB \
    --output-file ${table}
../bin/ExportResults ${table} ../latex/results/MassFits.tex
for mode in ${modes[@]}; do
  for label in phi 1050 1800 1050_1800; do
    rm -v ../ntuples/${mode}_${label}_mvaVars_vetoes.root
  done
done


