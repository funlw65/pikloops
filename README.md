Basic Build and Installation
============================

Note: In order to build pikloops, you need to install the Qt5  
development package. This package comes with Qt Creator, but can 
be generally installed separately.

Manual build:
-------------

    1. Unpack the archive (tar xzvf pikloops-0.2.5-qt5.tar.gz)
    2. Go to the pikloops sub directory (cd pikloops/)
    3. Generate the Makefile (qmake -o Makefile pikloops.pro)
    4. Build the application (make)
    5. Become root (su root)
    6. Install in /usr/bin (make install)

Note: "make install" just copy the pikloops executable to /usr/bin.
However, pikloops doesn't need to be "installed" to work properly:
You can use it from anywhere. If you use it from pikdev, do not forget 
to configure pikdev properly.

Build from Qt Creator:
----------------------

    1. Enter the pikloops directory with you file browser
    2. Go to the pikloops sub directory (cd pikloops/)
    3. Just click on the pikloops.pro file

Use Qt Creator as usual. If you don't know how to use it, 
use the manual procedure above.


Enjoy
