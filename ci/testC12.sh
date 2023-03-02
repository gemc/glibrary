#!/usr/bin/env zsh

# Purpose: Runs the CLAS12 test in clas12-system

# Container run:
# docker run -it --rm jeffersonlab/gemc3:1.0c12s sh
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# git clone http://github.com/maureeungaro/glibrary /root/glibrary && cd /root/glibrary
# ./ci/testC12.sh -s ft

# if we are in the docker container, we need to load the modules
if [[ -z "${DISTTAG}" ]]; then
    echo "\nNot in container"
else
    echo "\nIn container: ${DISTTAG}"
    source  /app/localSetup.sh
fi

Help()
{
	# Display Help
	echo
	echo "Syntax: runExamples.sh [-h|s]"
	echo
	echo "Options:"
	echo
	echo "-h: Print this Help."
	echo "-s <system>: test CLAS12 system"
	echo
}

if [ $# -eq 0 ]; then
	Help
	exit 1
fi

while getopts ":hs:" option; do
   case $option in
      h)
         Help
         exit
         ;;
      s)
         detector=$OPTARG
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

# using the checked out GLIBRARY
export GLIBRARY=`pwd`
export GPLUGIN_PATH=$GLIBRARY/plugins
echo
echo "TESTC12.SH: GLIBRARY is $GLIBRARY, GPLUGIN_PATH is $GPLUGIN_PATH"

# for some reason DYLD_LIBRARY_PATH is not passed to this script
export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLIBRARY}/lib

# using the just compiled gemc and the container clas12-system
cd $CLAS12_SYSTEMS
./ci/tests.sh -s $detector -t
