CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@ @libusb_CFLAGS@ -std=c99 -D_XOPEN_SOURCE=600

SUBDIRS = .

lib_LTLIBRARIES = libbuddy.la

libbuddy_la_SOURCES = buddy.c buddy.h protocol.c protocol.h
libbuddy_la_LDFLAGS = -version-info @VERSION_LIB_CURRENT@:@VERSION_LIB_REVISION@:0

libbuddy_includedir = $(includedir)/libbuddy-@VERSION_MAJOR@.@VERSION_MINOR@/libbuddy
libbuddy_include_HEADERS = buddy.h
