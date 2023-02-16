from Gaudi.Configuration import *

# Data service
from Configurables import k4DataSvc
datasvc = k4DataSvc("EventDataSvc")
datasvc.input = "megat_tut.root"

# Fetch the collection into TES
from Configurables import PodioInput
inp = PodioInput()
inp.collections = ["CztHits"] # branch name

# Add algorithm
from Configurables import MgTut_AddNoise
addnoise = MgTut_AddNoise("Add_Noise")
addnoise.InHits.Path = "CztHits"
addnoise.OutHits.Path = "NoisyCztHits"
addnoise.Mean = 3
addnoise.Sigma = 1

from Configurables import MgTut_DrawCaloEnergy
drawcalo = MgTut_DrawCaloEnergy("DrawCaloEnergy")
drawcalo.InHits.Path = "NoisyCztHits"
drawcalo.HistName = "hCaloE"
drawcalo.HistDir = "/noise"

drawcalo2 = MgTut_DrawCaloEnergy("DrawCaloEnergyNoise")
drawcalo2.InHits.Path = "CztHits"
drawcalo2.HistName = "hCaloE"

# Hist service: 'tutorial' is the top level dir in registry
histsvc = THistSvc()
histsvc.Output = ["tutorial DATAFILE='tut_addnoise.root' TYP='ROOT' OPT='RECREATE'"]
histsvc.PrintAll=True
histsvc.AutoSave=True
histsvc.AutoFlush=True
histsvc.OutputLevel=INFO

# ApplicationMgr
from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = [inp, addnoise, drawcalo, drawcalo2],
                EvtSel = 'NONE',
                EvtMax   = -1,
                ExtSvc = [datasvc, histsvc],
                OutputLevel=INFO
 )

