#!/usr/bin/env zsh

# Purpose: Runs the example in sci-g

# Container run:
# docker run -it --rm jeffersonlab/gemc3:1.0 sh
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# git clone http://github.com/maureeungaro/glibrary /root/glibrary && cd /root/glibrary
# ./ci/testSciG.sh -e examples/dosimeter

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

Help()
{
	# Display Help
	echo
	echo "Syntax: runExamples.sh [-h|e]"
	echo
	echo "Options:"
	echo
	echo "-h: Print this Help."
	echo "-e <example>: runs sci-g examples"
	echo
}

if [ $# -eq 0 ]; then
	Help
	exit 1
fi

while getopts ":he:" option; do
   case $option in
      h)
         Help
         exit
         ;;
      e)
         example=$OPTARG
         ;;
     \?) # Invalid option
         echo "Error: Invalid option"
         exit 1
         ;;
   esac
done

# build glibrary / gemc
# notice the gemc version is the one in the container, here we are
# recompiling it using the checked out glibrary
./ci/build.sh

# using the checked out GLIBRARY - notice we need to set these here again
export GLIBRARY=`pwd`
export GPLUGIN_PATH=$GLIBRARY/plugins
echo
echo "TESTSCIG.SH: GLIBRARY is $GLIBRARY, GPLUGIN_PATH is $GPLUGIN_PATH"

# for some reason DYLD_LIBRARY_PATH is not passed to this script
export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLIBRARY}/lib

# using the just compiled gemc and the container sci-g
cd $SCIG
./ci/tests.sh -e $example -t
