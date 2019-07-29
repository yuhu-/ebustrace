AM_CXXFLAGS = -fpic \
	      -Wall \
	      -Wextra \
	      -Wpedantic \
	      -std=c++17 \
	      $(LIBEBUS_CFLAGS)

bin_PROGRAMS = ebustrace

ebustrace_SOURCES = datatypes.cpp \
		    ebustrace.cpp
ebustrace_LDADD = $(LIBEBUS_LIBS)

EXTRA_DIST = datatypes.h \
	     Average.h

distclean-local:
	-rm -f Makefile.in
	-rm -rf .deps
