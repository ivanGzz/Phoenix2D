AM_CPPFLAGS = -Ibase/include -Itests/include -Iai/include -Iutils/include
AM_LDFLAGS = -lboost_regex
SUBDIRS = base tests ai .
bin_PROGRAMS = agent
agent_SOURCES = main.cpp
agent_LDADD = \
	$(top_builddir)/base/libPhoenixBase-1.0.la \
	$(top_builddir)/tests/libPhoenixTests-1.0.la \
	$(top_builddir)/ai/libPhoenixAI-1.0.la \
	$(AM_LDFLAGS)