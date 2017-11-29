AM_CXXFLAGS = -fpic \
	      -Wall \
	      -Wextra \
	      -std=c++14 \
	      $(LIBEBUSFSM_CFLAGS)

bin_PROGRAMS = ebustrace

ebustrace_SOURCES = ebustrace.cpp \
		    logger.cpp logger.h

ebustrace_LDADD = $(LIBEBUSFSM_LIBS)
