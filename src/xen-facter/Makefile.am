## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = xen-facter
xen_facter_LDADD = @GMODULE_STATIC_LIBS@ @JSON_STATIC_LIBS@
xen_facter_LDFLAGS = -Wl,-rpath=$(pkglibdir),--enable-new-dtags
xen_facter_CFLAGS = -std=gnu11
xen_facter_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" -DPKGLIBDIR=\"$(pkglibdir)\" @GMODULE_STATIC_CFLAGS@ @JSON_STATIC_CFLAGS@ @XENLIGHT_CFLAGS@
xen_facter_SOURCES = main.c \
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
