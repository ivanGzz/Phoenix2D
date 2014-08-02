AM_CPPFLAGS = -Ibase/include -Itests/include -Iai/include -Iutils/include
AM_LDFLAGS = -lboost_regex -lpthread
SUBDIRS = utils base tests ai .
bin_PROGRAMS = agent
agent_SOURCES = main.cpp
agent_LDADD = \
	$(top_builddir)/utils/libPhoenixUtils-2.1.la \
	$(top_builddir)/base/libPhoenixBase-2.1.la \
	$(top_builddir)/tests/libPhoenixTests-2.1.la \
	$(top_builddir)/ai/libPhoenixAI-2.1.la \
	$(AM_LDFLAGS)
