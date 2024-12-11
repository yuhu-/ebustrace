AM_CXXFLAGS = -fpic \
	      -Wall \
	      -Wextra \
	      -Wpedantic \
	      -std=c++20 \
	      $(LIBEBUS_CFLAGS)

bin_PROGRAMS = ebustrace

ebustrace_SOURCES = Datatypes.cpp \
		    ebustrace.cpp
ebustrace_LDADD = $(LIBEBUS_LIBS)

EXTRA_DIST = Datatypes.h \
	     Average.h

distclean-local:
	-rm -f Makefile.in
	-rm -rf .deps
