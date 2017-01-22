CXXFLAGS="-I/usr/local/include/OGRE/Overlay"
#LDFLAGS="$LDFLAGS -lboost_system"
LIBS += -lOgreOverlay
#-lboost_system

noinst_HEADERS= OgreFramework.hpp PWTViewer.hpp

ACLOCAL_AMFLAGS = -I m4

if DEBUG
AM_CFLAGS = -g3 -O0
AM_CXXFLAGS = -g3 -O0
else
AM_CFLAGS = -O2
AM_CXXFLAGS = -O2
endif

bin_PROGRAMS= PWTViewer
 PWTViewer_CPPFLAGS= -I$(top_srcdir)
 PWTViewer_SOURCES= OgreFramework.cpp PWTViewer.cpp main.cpp
 PWTViewer_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS)
 PWTViewer_LDADD= $(OGRE_LIBS) $(OIS_LIBS)

 EXTRA_DIST = bootstrap
 AUTOMAKE_OPTIONS = foreign
