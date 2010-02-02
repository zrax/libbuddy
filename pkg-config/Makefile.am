MAINTAINERCLEANFILES = Makefile.in lib-buddy.pc
pkgconfigdir = $(libdir)/pkgconfig/
pkgconfig_DATA = lib-buddy.pc
EXTRA_DIST = lib-buddy.pc.in
CLEANFILES = lib-buddy.pc

lib-buddy.pc : lib-buddy.pc.in Makefile
	sed \
		-e "s:[@]LIB_BUDDY_PC_PREFIX@:$(prefix):" \
		-e "s:[@]LIB_BUDDY_PC_LIBDIR@:$(libdir):" \
		-e "s:[@]LIB_BUDDY_PC_INCLUDEDIR@:$(includedir)/lib-buddy-$(LIB_BUDDY_PC_SLOT):" \
		-e "s:[@]LIB_BUDDY_PC_VERSION@:$(LIB_BUDDY_PC_VERSION):" \
		-e "s:[@]LIB_BUDDY_PC_LIBS@:$(LIB_BUDDY_PC_LIBS):" \
		-e "s:[@]LIB_BUDDY_PC_CFLAGS@:$(LIB_BUDDY_PC_CFLAGS):" \
		< $(srcdir)/lib-buddy.pc.in > lib-buddy.pc
