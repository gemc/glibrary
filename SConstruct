import os
import sys

from init_env import init_environment

# load needed environment for all glibraries
env = init_environment('glibrary clhep geant4 qt5')

gdata                = SConscript('gdata/SConscript',                exports='env')
textProgressBar      = SConscript('textProgressBar/SConscript',      exports='env')
guts                 = SConscript('guts/SConscript',                 exports='env')
goptions             = SConscript('goptions/SConscript',             exports='env')
gsplash              = SConscript('gsplash/SConscript',              exports='env')
gtouchable           = SConscript('gtouchable/SConscript',           exports='env')
ghit                 = SConscript('ghit/SConscript',                 exports='env')
gsystem              = SConscript('gsystem/SConscript',              exports='env')
g4system             = SConscript('g4system/SConscript',             exports='env')
gstreamer            = SConscript('gstreamer/SConscript',            exports='env')
eventDispenser       = SConscript('eventDispenser/SConscript',       exports='env')
gQtButtonsWidget     = SConscript('gQtButtonsWidget/SConscript',     exports='env')
g4display            = SConscript('g4display/SConscript',            exports='env')
gparticle            = SConscript('gparticle/SConscript',            exports='env')
gdynamicDigitization = SConscript('gdynamicDigitization/SConscript', exports='env')
gtranslationTable    = SConscript('gtranslationTable/SConscript',    exports='env')
gphysics             = SConscript('gphysics/SConscript',             exports='env')


# output plugins
# notice dependencies are taken care of in the SConscript below
BINROOT =  os.popen('root-config --bindir').readline()

if BINROOT:
    libsRootDLL    = SConscript('gstreamer/SConscriptROOTDLL')
    Requires(libsRootDLL, textProgressBar)
    Depends(libsRootDLL, textProgressBar)
else:
    print("Warning: root-config not found. Skipping ROOT output gstreamer plugins ")


libsTextDLL    = SConscript('gstreamer/SConscriptTEXTDLL')
libsJlabSRODLL = SConscript('gstreamer/SConscriptJLABSRODLL')
