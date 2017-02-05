#-- GAUDI jobOptions generated on Wed Jan 11 21:22:08 2017
#-- Contains event types : 
#--   13104025 - 82 files - 1055864 events - 239.88 GBytes


#--  Extra information about the data processing phases:


#--  Processing Pass Step-129669 

#--  StepId : 129669 
#--  StepName : Stripping21-NoPrescalingFlagged for Sim09 (I/O DST) 
#--  ApplicationName : DaVinci 
#--  ApplicationVersion : v36r1p3 
#--  OptionFiles : $APPCONFIGOPTS/DaVinci/DV-Stripping21-Stripping-MC-NoPrescaling.py;$APPCONFIGOPTS/DaVinci/DV-RedoCaloPID-Stripping21.py;$APPCONFIGOPTS/DaVinci/DataType-2012.py;$APPCONFIGOPTS/DaVinci/InputType-DST.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r277 
#--  Visible : Y 


#--  Processing Pass Step-130245 

#--  StepId : 130245 
#--  StepName : Reco14c for MC - 2012 - to be used with Sim09 
#--  ApplicationName : Brunel 
#--  ApplicationVersion : v43r2p11 
#--  OptionFiles : $APPCONFIGOPTS/Brunel/DataType-2012.py;$APPCONFIGOPTS/Brunel/MC-WithTruth.py;$APPCONFIGOPTS/Brunel/Sim09-Run1.py;$APPCONFIGOPTS/Persistency/DST-multipleTCK-2012.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : fromPreviousStep 
#--  CONDDB : fromPreviousStep 
#--  ExtraPackages : AppConfig.v3r302 
#--  Visible : Y 

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000001_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000002_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000003_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000004_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000005_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000006_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000007_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000008_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000010_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000011_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000012_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000013_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000014_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000015_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000017_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000018_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000019_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000020_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000021_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000022_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000023_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000024_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000025_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000026_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000027_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000029_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000030_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000031_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000032_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000033_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000034_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000035_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000036_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000037_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000038_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000039_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000040_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000041_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000042_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000043_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000044_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000045_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000046_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000047_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000048_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000049_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000050_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000051_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000052_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000053_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000054_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000055_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000056_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000057_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000058_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000059_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000060_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000061_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000062_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000063_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000064_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000065_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000066_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000067_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000068_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000069_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000070_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000071_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000072_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000073_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000074_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000075_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000076_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000077_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000078_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000079_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000081_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000082_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000083_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000084_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000085_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00056475/0000/00056475_00000086_2.AllStreams.dst'
], clear=True)