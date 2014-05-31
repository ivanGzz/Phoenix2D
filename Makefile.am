AM_CPPFLAGS = -Ibase/include -Ilibs/include
AM_LDFLAGS = -lboost_regex
SUBDIRS = base libs .
bin_PROGRAMS = agent
agent_SOURCES = main.cpp
agent_LDADD = $(top_builddir)/base/libPhoenixBase-1.0.la $(top_builddir)/libs/libPhoenixLibs-1.0.la $(AM_LDFLAGS)