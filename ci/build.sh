#!/usr/bin/env zsh

# Purpose: compiles the Cadmesh, glibrary libraries and gemc

# Container run:
# docker run -it --rm jeffersonlab/gemc:3.0 sh
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# ./ci/build.sh

# load environment if we're on the container
# notice the extra argument to the source command
TERM=xterm # source script use tput for colors, TERM needs to be specified
FILE=/etc/profile.d/jlab.sh
test -f $FILE && source $FILE keepmine

function compileGLibrary {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling Glibrary with options: "$copt"
	scons $copt
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

	# cadmesh
	for lib in assimp cadmesh
	do
		ls lib/lib$lib$libExtension
		if [ $? -ne 0 ]; then
			echo $lib not present
			exit 1
		fi
	done

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
	echo
	echo Compilation completed
	ls -ltrh ./

}

# using the checked out GLIBRARY
# for some reason DYLD_LIBRARY_PATH is not passed to this script
export GLIBRARY=`pwd`
echo GLIBRARY is $GLIBRARY, GPLUGIN_PATH is $GPLUGIN_PATH
export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLIBRARY}/lib

./compileCmesh
compileGLibrary
if [ $? -ne 0 ]; then
	echo building glibrary failed
	exit 1
fi

checkLibsExistence
compileGEMC
if [ $? -ne 0 ]; then
	echo building gemc failed
	exit 1
fi

cp $GLIBRARY/lib/gstreamer*.gplugin $GPLUGIN_PATH
