MAINTAINERCLEANFILES = Makefile.in libbuddy.pc
pkgconfigdir = $(libdir)/pkgconfig/
pkgconfig_DATA = libbuddy.pc
EXTRA_DIST = libbuddy.pc.in
CLEANFILES = libbuddy.pc

libbuddy.pc : libbuddy.pc.in Makefile
	sed \
		-e "s:[@]LIBBUDDY_PC_PREFIX@:$(prefix):" \
		-e "s:[@]LIBBUDDY_PC_LIBDIR@:$(libdir):" \
		-e "s:[@]LIBBUDDY_PC_INCLUDEDIR@:$(includedir)/libbuddy-$(LIBBUDDY_PC_SLOT):" \
		-e "s:[@]LIBBUDDY_PC_VERSION@:$(LIBBUDDY_PC_VERSION):" \
		-e "s:[@]LIBBUDDY_PC_LIBS@:$(LIBBUDDY_PC_LIBS):" \
		-e "s:[@]LIBBUDDY_PC_CFLAGS@:$(LIBBUDDY_PC_CFLAGS):" \
		< $(srcdir)/libbuddy.pc.in > libbuddy.pc
