## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

pkglib_LTLIBRARIES = libxl-ruby.la
libxl_ruby_la_LIBADD = @GMODULE_STATIC_LIBS@
libxl_ruby_la_LDFLAGS = -shared -module -avoid-version
libxl_ruby_la_CFLAGS = -std=gnu11
libxl_ruby_la_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" -DPKGLIBDIR=\"$(pkglibdir)\" -fPIC @GMODULE_STATIC_CFLAGS@ @XENLIGHT_CFLAGS@
libxl_ruby_la_SOURCES = main.c \
../common/libxl_loader.c

noinst_HEADERS = main.h \
../common/libxl_loader.h

SUBDIRS = po

if DOCS
SUBDIRS += docs
endif

if MAN
dist_man_MANS=backup.1
$(dist_man_MANS): $(bin_PROGRAMS)
	-$(HELP2MAN) --no-info --output=$@ ./$(@:%.1=%)
clean-local:
	rm -f $(dist_man_MANS)
endif
