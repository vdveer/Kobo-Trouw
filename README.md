Kobo-Trouw
==========

Download dutch daily newspaper called 'Trouw', this is based on QT Embedded 4.8.0 but with a few patches
you can also run it on other platforms. I focused on the eink reader Kobo Glo, it doesn't support flash so
it was not possible to directly visist http://krant.trouw.nl to read it. I used information from the Android application 
and created my own QT app.

If you want to build it from source, please compile the whole Kobo reader enviroment, can be found here: https://github.com/kobolabs/Kobo-Reader

Do not compile QT embedded 4.6.2, but unzip the new QT tar.gz delivered by Kobo labs, and apply patch first.
Use this command to compile QT embedded 4.8.0:

`
/home/user/Development/kobo/tmp/qt-everywhere-opensource-src-4.8.0/configure -I/home/user/Development/kobo/fs/include -I/home/user/Development/kobo/fs/usr/include -L/home/user/Development/kobo/fs/lib -L/home/user/Development/kobo/fs/usr/lib -release -no-accessibility -system-libmng -no-nis -no-cups -no-xshape -no-xrandr -no-xkb -no-xinerama -no-xcursor -no-sm -system-libpng -system-libjpeg -no-libpng -qt-zlib -embedded arm -xplatform qws/linux-arm-g++ -no-qt3support -exceptions -opensource -no-pch -qt-freetype -qt-gfx-qvfb -confirm-license -dbus -ldbus-1 -nomake examples -nomake docs -nomake translations -nomake examples -nomake docs -nomake demos -scripttools -xmlpatterns -no-opengl -depths all -qt-gfx-transformed -no-armfpa -no-neon -openssl -lrt -I/home/user/Development/kobo/fs/include/dbus-1.0 -I/home/user/Development/kobo/fs/lib/dbus-1.0/include -D QT_NO_QWS_CURSOR -DQT_NO_QWS_QPF2
`

**change path right!

---------------
You need to change some other paths first to compile Kobo Trouw, 
the following files, maybe more:

-Trouw_Kobo_QT.pro

-settings.ini


