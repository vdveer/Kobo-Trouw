#!/bin/sh
##This script is for Kobo Devices only using firmware 2x##
##Please put libquazip.so.1.0.0 in the same dir as this script, change the paths if they are different.###

#export QT_PLUGIN_PATH=/mnt/onboard/checkers/qt_plugins
export LD_LIBRARY_PATH=/usr/local/Trolltech/QtEmbedded-4.8.0-arm/lib:/home/admin/kobo_trouw
export QWS_MOUSE_PROTO=KindleTS
export QWS_DISPLAY=Transformed:kindlefb:Rot90
export QT_QWS_FONTDIR=/mnt/onboard/checker/fonts
killall nickel

/home/admin/kobo_trouw/Trouw_Kobo_QT -qws

