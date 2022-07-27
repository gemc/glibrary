#!/usr/bin/env zsh

# Purpose: Runs the example in sci-g

# Container run:
# docker run -it --rm jeffersonlab/gemc:3.0 sh
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# ./ci/testSciG.sh -e examples/geometry/dosimeter

if [[ -z "${G3CLAS12_VERSION}" ]]; then
	# load environment if we're on the container
	# notice the extra argument to the source command
	TERM=xterm # source script use tput for colors, TERM needs to be specified
	FILE=/etc/profile.d/jlab.sh
	test -f $FILE && source $FILE keepmine
else
  echo environment already defined
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



# using the checked out GLIBRARY
export GLIBRARY=`pwd`
# for some reason DYLD_LIBRARY_PATH is not passed to this script
echo GLIBRARY is $GLIBRARY, GPLUGIN_PATH is $GPLUGIN_PATH
export DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLIBRARY}/lib

./ci/build.sh # build glibrary / gemc and install plugins to $GPLUGIN_PATH
if [ $? -ne 0 ]; then
	echo building gemc / glibrary failed
	exit 1
fi

cd $JLAB_ROOT/$JLAB_VERSION/noarch/sci-g/$SCIG_VERSION

./ci/tests.sh -e $example -t
