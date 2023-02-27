#!/usr/bin/env zsh

# Purpose: compiles the Cadmesh, glibrary libraries and gemc

# Container run:
# docker run -it --rm jeffersonlab/gemc3:1.0 sh
# git clone http://github.com/gemc/glibrary         /root/glibrary && cd /root/glibrary
# git clone http://github.com/maureeungaro/glibrary /root/glibrary && cd /root/glibrary
# ./ci/build.sh

# if we are in the docker container, we need to load the modules
if [[ -z "${DISTTAG}" ]]; then
    echo "\nNot in container"
else
    echo "\nIn container: ${DISTTAG}"
    TERM=xterm # source script use tput for colors, TERM needs to be specified
    source /usr/share/Modules/init/sh
    source /work/ceInstall/setup.sh
	module load gemc3/1.0
    if [[ $? != 0 ]]; then
        echo "Error loading gemc3 module"
	    exit 1
    fi
fi

function compileGLibrary {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling Glibrary with options: "$copt"
	scons $copt
	if [ $? -ne 0 ]; then
    	echo building glibrary failed
    	exit 1
    fi
	echo
	echo Compilation completed, content of lib:
	ls -ltrh lib/
}

function checkLibsExistence {
	echo
	echo Checking libraries existence

	# shared (dynamic) library extension is different on linux/darwin
	libExtension=".so"
	[[ $OSTYPE == 'darwin'* ]] && libExtension=".dylib"

	# plugins
	libExtension=".gplugin"
	for lib in gstreamerJLABSROFactory gstreamerROOTFactory gstreamerTEXTFactory
	do
		ls lib/$lib$libExtension
		if [ $? -ne 0 ]; then
			echo $lib not present
			exit 1
		fi
	done
}


function compileGEMC {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling GEMC with options: "$copt"
	cd $GEMC
	scons $copt
	if [ $? -ne 0 ]; then
    	echo building gemc failed
    	exit 1
    fi
	echo
	echo Compilation completed. Content of gemc/src:
	ls -ltrh ./

}

# using the checked out GLIBRARY
export GLIBRARY=`pwd`
export GPLUGIN_PATH=$GLIBRARY/plugin
echo
echo GLIBRARY is $GLIBRARY, GPLUGIN_PATH is $GPLUGIN_PATH

# for some reason DYLD_LIBRARY_PATH is not passed to this script
export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLIBRARY}/lib

compileGLibrary
checkLibsExistence
compileGEMC

