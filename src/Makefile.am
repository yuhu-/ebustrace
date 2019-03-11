AM_CXXFLAGS = -fpic \
	      -Wall \
	      -Wextra \
	      -Wpedantic \
	      -std=c++17 \
	      $(LIBEBUSFSM_CFLAGS)

bin_PROGRAMS = ebustrace \
	       demo_datatypes

ebustrace_SOURCES = logger.cpp \
		    datatypes.cpp \
		    ebustrace.cpp
ebustrace_LDADD = $(LIBEBUSFSM_LIBS)

demo_datatypes_SOURCES = datatypes.cpp \
			 demo_datatypes.cpp
demo_datatypes_LDADD = $(LIBEBUSFSM_LIBS)
