# Works with Ganga v601r18 but later versions complain:
# ERROR    global name 'lfn' is not defined

#JobName  = 'BsPhiPhiGen'
#LFNsFile = 'PwaveLFNs.txt'
JobName  = 'BsPhiKKGen'
LFNsFile = 'PhaseSpaceLFNs.txt'
Application = DaVinci()
Application.version = 'v37r0'

debug = False

Splitter = SplitByFiles(ignoremissing = True, bulksubmit=True)
Output   = [ DiracFile('DVntuple.root'), LocalFile('histo.root'), LocalFile('summary.xml') ]
Backend  = Dirac()
Input    = []
LFNs = [line.rstrip('\n') for line in open(LFNsFile)]
if not debug:
  for line in LFNs:
    Input.append(DiracFile(lfn=line))
else:
  Input.append(DiracFile(lfn=LFNs[0]))
Options  = [ File ( './tupleResult.py' ) ]
Application.optsfile = Options
j = Job ()
j.name         = JobName
j.application  = Application
j.splitter     = Splitter
j.backend      = Backend
j.outputfiles  = Output
j.inputdata    = Input
j.do_auto_resubmit = True
j.prepare()
j.submit()
