#!/bin/zsh

run_meson() {
  	meson setup build --native-file=../../release.ini --wipe
  	cd build
  	meson configure -Dprefix=$GLIBRARY
  	meson install
  	meson test
  	cd ..
}

projects='      gtranslationTable gdata gtouchable'

for s in $=projects
do
  echo " "
  echo " Running Meson for "$s
  cd "subprojects/$s" || exit
  run_meson
  echo " --------------------------------  "
  echo
  cd ../../
done
