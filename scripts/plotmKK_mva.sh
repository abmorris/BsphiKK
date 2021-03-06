#!/bin/bash
cd ../ntuples
../bin/AnnotateBranch \
    -F BsphiKK_data_mvacut.root \
    -B BCON_KK_M \
    -O ../latex/figs/mKKmvacut \
    -l 900 \
    -u 4100 \
    -b 64
../bin/AnnotateBranch \
    -F BsphiKK_data_mvacut.root \
    -B BCON_KK_M \
    -C "BCON_KK_M>1050" \
    -O ../latex/figs/mKKmvacut_1050 \
    -l 1050 \
    -u 4100 \
    -b 61
../bin/PlotBranch \
    -F BsphiKK_data_mvacut.root \
    -B BCON_KK_M \
    -C "BCON_KK_M<1800" \
    -T "#it{m}(#it{K}^{#plus}#it{K}^{#minus})" \
    -O ../latex/figs/mKKmvacut_1800 \
    -l 900 \
    -u 1800 \
    -b 18
../bin/PlotBranch \
    -F BsphiKK_data_mvacut.root \
    -B BCON_KK_M \
    -C "BCON_KK_M>1050&&BCON_KK_M<1800" \
    -T "#it{m}(#it{K}^{#plus}#it{K}^{#minus})" \
    -O ../latex/figs/mKKmvacut_1050_1800 \
    -l 1050 \
    -u 1800 \
    -b 15


