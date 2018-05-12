#!/bin/bash
# Script creado por Francisco Calleja Vazquez

echo "Desea lanzar el programa despues de instalarlo? [s/N]="
read respuesta

sudo apt-get install git qt5-default qtbase5-dev qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5

cd M_A_C/
qmake M_A_C.pro
make
sudo make install

if [ $respuesta = "s" ] || [ $respuesta = "S"]; then
  ./M_A_C
fi
