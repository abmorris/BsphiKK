# file /nightlies/jenkins/workspace/nightly-slot-checkout/tmp/checkout/DBASE/Gen/DecFiles/v27r55/options/13104024.py generated: Tue, 13 Oct 2015 17:19:57
#
# Event Type: 13104024
#
# ASCII decay Descriptor: [B_s0 -> (phi(1020) -> K+ K-) K+ K-]cc
#
from Configurables import Generation
Generation().EventType = 13104024
Generation().SampleGenerationTool = "SignalRepeatedHadronization"
from Configurables import SignalRepeatedHadronization
Generation().addTool( SignalRepeatedHadronization )
Generation().SignalRepeatedHadronization.ProductionTool = "PythiaProduction"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "$DECFILESROOT/dkfiles/Bs_phiK+K-=DecProdCut,hpt400.dec"
#Generation().SignalRepeatedHadronization.CutTool = "DaughtersInLHCbAndWithDaughAndBCuts"
Generation().SignalRepeatedHadronization.SignalPIDList = [ 531,-531 ]

# Ad-hoc particle gun code

#from Configurables import ParticleGun
#pgun = ParticleGun("ParticleGun")
#pgun.SignalPdgCode = 531
#pgun.DecayTool = "EvtGenDecay"
#pgun.GenCutTool = "DaughtersInLHCbAndWithDaughAndBCuts"

#pgun.addTool( Generation().SignalRepeatedHadronization.DaughtersInLHCbAndWithDaughAndBCuts.clone() )

#from Configurables import FlatNParticles
#pgun.NumberOfParticlesTool = "FlatNParticles"
#pgun.addTool( FlatNParticles , name = "FlatNParticles" )

#from Configurables import MomentumSpectrum
#pgun.ParticleGunTool = "MomentumSpectrum"
#pgun.addTool( MomentumSpectrum , name = "MomentumSpectrum" )
#pgun.MomentumSpectrum.PdgCodes = [ 531,-531 ]
#pgun.MomentumSpectrum.InputFile = "$PGUNSDATAROOT/data/Ebeam4000GeV/MomentumSpectrum_531.root"
#pgun.MomentumSpectrum.BinningVariables = "pteta"
#pgun.MomentumSpectrum.HistogramPath = "h_pteta"

#from Configurables import BeamSpotSmearVertex
#pgun.addTool(BeamSpotSmearVertex, name="BeamSpotSmearVertex")
#pgun.VertexSmearingTool = "BeamSpotSmearVertex"
#pgun.EventType = 13104024
