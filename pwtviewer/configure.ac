AC_INIT(PWTViewer, 0.1)
 AM_INIT_AUTOMAKE
 AM_CONFIG_HEADER(config.h)

 AC_LANG_CPLUSPLUS
 AC_PROG_CXX
 AM_PROG_LIBTOOL

 AC_CONFIG_MACRO_DIRS([m4])

 PKG_CHECK_MODULES(OGRE, [OGRE >= 1.2])
 AC_SUBST(OGRE_CFLAGS)
 AC_SUBST(OGRE_LIBS)

 PKG_CHECK_MODULES(OIS, [OIS >= 1.0])
 AC_SUBST(OIS_CFLAGS)
 AC_SUBST(OIS_LIBS)

 AC_CONFIG_FILES(Makefile)
 AC_OUTPUT

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
