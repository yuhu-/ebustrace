AC_PREREQ([2.69])

# Given a version number MAJOR.MINOR.PATCH, increment the:
# MAJOR version when you make incompatible API changes,
# MINOR version when you add functionality in a backwards-compatible manner, and
# PATCH version when you make backwards-compatible bug fixes.
AC_INIT([ebustrace],[0.0.0],[roland.jax@liwest.at],[ebustrace],[https://github.com/yuhu-/ebustrace])

AC_CONFIG_AUX_DIR([build])

AM_INIT_AUTOMAKE([1.11 -Wall -Werror foreign subdir-objects])

if test -z $CXXFLAGS;
	then CXXFLAGS='-g -O2'
fi

AC_PROG_CXX

PKG_CHECK_MODULES([LIBEBUS], [ebus >= 0.0])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_SRCDIR([src/ebustrace.cpp])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 test/Makefile])

AC_OUTPUT
