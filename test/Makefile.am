AM_CXXFLAGS = -fpic \
	      -Wall \
	      -Wextra \
	      -Wpedantic \
	      -std=c++17 \
	      -isystem$(top_srcdir)/src \
	      $(LIBEBUS_CFLAGS)

noinst_PROGRAMS = test_datatypes

test_datatypes_SOURCES = ../src/datatypes.cpp \
			 test_datatypes.cpp
test_datatypes_LDADD = $(LIBEBUS_LIBS)

distclean-local:
	-rm -f Makefile.in
	-rm -rf .deps
