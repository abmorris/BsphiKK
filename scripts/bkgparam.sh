#!/bin/bash
cd ../fits
fitting -f background.xml --calculateBackgroundCoefficients ## Angular part only
mv LegendreMoments.root LegendreMoments_Background.root
../bin/PlotAngAcc sampled_background.root background.root
mv background_*pdf ../latex/figs/
cd ../ntuples
## Fit for the mass-dependent part
../bin/FitBranch -F BsphiKK_data_mvacut.root \
                 -M Threshold \
                 -B KK_M \
                 -T "#it{m}(#it{K^{#plus}K^{#minus}})" \
                 -U "MeV/#it{c}^{2})" \
                 -C "TMath::Abs(B_s0_LOKI_Mass-5366.77)>50" \
                 -l 900 \
                 -u 1800 \
                 -b 20 \
                 -O ../latex/figs/BackgroundFit \
                 --pulls

