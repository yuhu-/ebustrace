AC_PREREQ([2.69])
AC_INIT([ebustrace],[0.0.0],[roland.jax@liwest.at],[ebusfsm],[https://github.com/yuhu-/ebusfsm])

AC_CONFIG_AUX_DIR([build])

AM_INIT_AUTOMAKE([1.11 -Wall -Werror foreign subdir-objects])

if test -z $CXXFLAGS;
	then CXXFLAGS='-g -O2'
fi

AC_PROG_CXX

PKG_CHECK_MODULES([LIBEBUSFSM], [ebusfsm >= 0.0])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_SRCDIR([src/ebustrace.cpp])

AC_CONFIG_FILES([Makefile
		 src/Makefile])

AC_OUTPUT
