#-- GAUDI jobOptions generated on Wed Apr 22 13:29:18 2015
#-- Contains event types : 
#--   13104081 - 217 files - 4004542 events - 815.12 GBytes


#--  Extra information about the data processing phases:


#--  Processing Pass Step-124834 

#--  StepId : 124834 
#--  StepName : Reco14a for MC 
#--  ApplicationName : Brunel 
#--  ApplicationVersion : v43r2p7 
#--  OptionFiles : $APPCONFIGOPTS/Brunel/DataType-2012.py;$APPCONFIGOPTS/Brunel/MC-WithTruth.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : Y 


#--  Processing Pass Step-124620 

#--  StepId : 124620 
#--  StepName : Digi13 with G4 dE/dx 
#--  ApplicationName : Boole 
#--  ApplicationVersion : v26r3 
#--  OptionFiles : $APPCONFIGOPTS/Boole/Default.py;$APPCONFIGOPTS/Boole/DataType-2012.py;$APPCONFIGOPTS/Boole/Boole-SiG4EnergyDeposit.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : Y 


#--  Processing Pass Step-124632 

#--  StepId : 124632 
#--  StepName : TCK-0x409f0045 Flagged for Sim08 2012 
#--  ApplicationName : Moore 
#--  ApplicationVersion : v14r8p1 
#--  OptionFiles : $APPCONFIGOPTS/Moore/MooreSimProductionWithL0Emulation.py;$APPCONFIGOPTS/Conditions/TCK-0x409f0045.py;$APPCONFIGOPTS/Moore/DataType-2012.py;$APPCONFIGOPTS/L0/L0TCK-0x0045.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : Y 


#--  Processing Pass Step-126434 

#--  StepId : 126434 
#--  StepName : Sim08e - 2012 - MD - Pythia8 
#--  ApplicationName : Gauss 
#--  ApplicationVersion : v45r7 
#--  OptionFiles : $APPCONFIGOPTS/Gauss/Sim08-Beam4000GeV-md100-2012-nu2.5.py;$DECFILESROOT/options/@{eventType}.py;$LBPYTHIA8ROOT/options/Pythia8.py;$APPCONFIGOPTS/Gauss/G4PL_FTFP_BERT_EmNoCuts.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : dddb-20130929-1 
#--  CONDDB : sim-20130522-1-vc-md100 
#--  ExtraPackages : AppConfig.v3r193;DecFiles.v27r22 
#--  Visible : Y 


#--  Processing Pass Step-124630 

#--  StepId : 124630 
#--  StepName : Stripping20-NoPrescalingFlagged for Sim08 
#--  ApplicationName : DaVinci 
#--  ApplicationVersion : v32r2p1 
#--  OptionFiles : $APPCONFIGOPTS/DaVinci/DV-Stripping20-Stripping-MC-NoPrescaling.py;$APPCONFIGOPTS/DaVinci/DataType-2012.py;$APPCONFIGOPTS/DaVinci/InputType-DST.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : Y 

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000002_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000005_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000006_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000007_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000008_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000009_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000010_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000011_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000012_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000013_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000014_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000015_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000016_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000017_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000018_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000019_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000020_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000021_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000022_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000023_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000024_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000025_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000026_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000028_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000029_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000030_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000031_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000032_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000033_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000034_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000035_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000036_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000037_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000038_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000039_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000040_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000041_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000042_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000043_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000044_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000045_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000046_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000047_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000048_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000049_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000050_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000051_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000052_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000053_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000055_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000056_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000057_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000058_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000060_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000061_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000062_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000063_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000064_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000065_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000066_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000067_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000068_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000069_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000070_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000071_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000072_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000073_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000074_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000075_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000076_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000077_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000078_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000079_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000080_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000081_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000082_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000083_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000084_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000085_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000086_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000087_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000088_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000089_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000090_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000091_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000092_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000093_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000094_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000095_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000096_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000097_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000098_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000099_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000100_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000101_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000102_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000103_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000104_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000105_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000106_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000107_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000108_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000109_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000110_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000111_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000112_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000113_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000114_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000115_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000116_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000117_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000118_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000119_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000120_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000121_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000122_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000123_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000124_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000125_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000126_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000127_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000128_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000129_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000130_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000131_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000132_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000133_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000134_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000135_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000136_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000137_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000138_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000139_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000140_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000141_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000142_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000143_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000144_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000145_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000146_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000147_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000148_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000149_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000150_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000151_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000152_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000153_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000154_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000155_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000156_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000157_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000158_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000159_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000160_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000161_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000162_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000163_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000164_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000165_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000166_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000167_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000168_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000169_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000170_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000171_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000172_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000173_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000174_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000175_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000176_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000177_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000178_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000179_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000180_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000181_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000182_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000183_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000184_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000185_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000186_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000187_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000188_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000189_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000190_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000191_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000192_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000193_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000194_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000195_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000197_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000198_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000199_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000200_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000201_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000202_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000203_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000204_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000205_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000206_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000207_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000208_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000209_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000210_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000211_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000212_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000213_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000214_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000215_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000216_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000217_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000218_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000219_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000220_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00035942/0000/00035942_00000221_1.allstreams.dst'
], clear=True)