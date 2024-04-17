#!/bin/zsh

run_meson() {
  	meson setup build --native-file=../../release.ini --wipe
  	cd build
  	meson configure -Dprefix=$GLIBRARY
  	meson install
  	meson test
  	cd ..
}

sprojects='guts goptions gfactory'


echo " "
for s in $=sprojects
do
  echo " Running Meson for "$s
  cd "subprojects/$s" || exit
  run_meson
  echo " --------------------------------  "
  echo
  cd ../../
done
