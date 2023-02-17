from Gaudi.Configuration import *

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr(
                EvtSel = 'NONE',
                EvtMax   = -1,
                OutputLevel=INFO,
                StopOnSignal=True,
 )

# Hist service: 'tutorial' is the top level dir in registry
from Configurables import THistSvc
histsvc = THistSvc()
histsvc.Output = ["tutorial DATAFILE='hist_chain.root' TYP='ROOT' OPT='RECREATE'"]
histsvc.PrintAll=True
histsvc.AutoSave=True
histsvc.AutoFlush=True
histsvc.OutputLevel=INFO
ApplicationMgr().ExtSvc += [histsvc]

# Data service
from Configurables import k4DataSvc
datasvc = k4DataSvc("EventDataSvc")
datasvc.input = "megat_tut.root"
datasvc.ForceLeaves= True
ApplicationMgr().ExtSvc += [datasvc]

# Fetch the collection into TES
from Configurables import PodioInput
inp = PodioInput()
inp.collections = ["CztHits"] # branch name
ApplicationMgr().TopAlg += [inp]

# Add algorithm
from Configurables import MgTut_AddNoise
addnoise1 = MgTut_AddNoise("Add_Mean1")
addnoise1.InHits.Path = "CztHits"
addnoise1.OutHits.Path = "noise/Mean1"
addnoise1.Mean = 1
addnoise1.Sigma = 0
ApplicationMgr().TopAlg += [addnoise1]

addnoise2 = MgTut_AddNoise("Add_Mean2")
addnoise2.InHits.Path = "CztHits"
addnoise2.OutHits.Path = "noise/Mean2"
addnoise2.Mean = 2
addnoise2.Sigma = 0
ApplicationMgr().TopAlg += [addnoise2]

addnoise3 = MgTut_AddNoise("Add_Sigma1")
addnoise3.InHits.Path = "noise/Mean1"
addnoise3.OutHits.Path = "noise/Mean1_Sigma1"
addnoise3.Mean = 0
addnoise3.Sigma = 1
ApplicationMgr().TopAlg += [addnoise3]

addnoise4 = MgTut_AddNoise("Add_Sigma2")
addnoise4.InHits.Path = "noise/Mean2"
addnoise4.OutHits.Path = "noise/Mean2_Sigma2"
addnoise4.Mean = 0
addnoise4.Sigma = 2
ApplicationMgr().TopAlg += [addnoise4]

from Configurables import MgTut_DrawCaloEnergy
drawcalo1 = MgTut_DrawCaloEnergy("DrawCaloEnergy1")
drawcalo1.InHits.Path = "noise/Mean1"
drawcalo1.HistName = "hCaloE_Mean1"
drawcalo1.HistDir = "/noise"
ApplicationMgr().TopAlg += [drawcalo1]

drawcalo2 = MgTut_DrawCaloEnergy("DrawCaloEnergy2")
drawcalo2.InHits.Path = "noise/Mean2"
drawcalo2.HistName = "hCaloE_Mean2"
drawcalo2.HistDir = "/noise"
ApplicationMgr().TopAlg += [drawcalo2]

drawcalo3 = MgTut_DrawCaloEnergy("DrawCaloEnergy3")
drawcalo3.InHits.Path = "noise/Mean1_Sigma1"
drawcalo3.HistName = "hCaloE_Mean1_Sigma1"
drawcalo3.HistDir = "/noise"
ApplicationMgr().TopAlg += [drawcalo3]

drawcalo4 = MgTut_DrawCaloEnergy("DrawCaloEnergy4")
drawcalo4.InHits.Path = "noise/Mean2_Sigma2"
drawcalo4.HistName = "hCaloE_Mean2_Sigma2"
drawcalo4.HistDir = "/noise"
ApplicationMgr().TopAlg += [drawcalo4]

# Select & Write the collections to disk ROOT file
from Configurables import PodioOutput
out = PodioOutput('out')
#### caveat: the filename must be different from HistSvc output file
out.filename = 'chain_megat_tut.root'
#### drop all but keep the offset collection
out.outputCommands = ['keep *', 'drop CztHits']
ApplicationMgr().TopAlg += [out]

