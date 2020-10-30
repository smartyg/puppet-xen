dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([puppet-xen], [0.1], [goedhart.martijn@gmail.com])
AC_CONFIG_SRCDIR([src/xen-facter/main.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

AH_BOTTOM([#include <features.h>])

AC_CANONICAL_BUILD
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 foreign -Wall -Werror silent-rules])
AM_GNU_GETTEXT_VERSION([0.18.3])
AM_GNU_GETTEXT([external])

# AX_DEFINE_SUBST(NAME, VALUE, DESCRIPTION)
# -----------------------------------------
AC_DEFUN([AX_DEFINE_SUBST], [
	AC_DEFINE([$1], ["$2"], [$3])
	AC_SUBST([$1], ['$2'])
])

# AX_CHECK_LIB(NAME, FUNC, NAME2)
# -----------------------------------------
AC_DEFUN([AX_CHECK_LIB], [
	AC_CHECK_LIB([$1], [$2], [AC_SUBST([$3_LIBS], ["-l$1"])
	AC_DEFINE([HAVE_LIB$3], [1], [Define if you have lib$1])])
])

# some other package constants
AX_DEFINE_SUBST([PROGRAM_NAME], [puppet-xen], [program name])
AX_DEFINE_SUBST([PROGRAM_SUMMARY], [], [program summary])
AX_DEFINE_SUBST([PROGRAM_DESCRIPTION], [], [program description])
AX_DEFINE_SUBST([LAST_CHANGE], [24-10-2020], [Day of last change])
AX_DEFINE_SUBST([AUTHOR], [Martijn Goedhart], [Author])
AX_DEFINE_SUBST([COPYRIGHT], [Copyright (c) 2020 Martijn Goedhart], [Copyright])
AX_DEFINE_SUBST([LICENSE], [GNU General Public License], [License name])
AX_DEFINE_SUBST([LICENSE_SHORT], [GPLv2+], [License shorthand])
AX_DEFINE_SUBST([LICENSE_SHORT_RPM], [GPL-2.0+], [SPDX License code])
AX_DEFINE_SUBST([LICENSE_LONG], [GNU GPL version 2 or later <http://www.gnu.org/licenses/gpl-2.0.html>], [Long license description])
AX_DEFINE_SUBST([PACKAGE_HOMEPAGE], [http://www.martijn-goedhart.nl/puppet-xen/], [package home page])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR

# Initialize Libtool
LT_INIT([static dlopen])

# Check which option are enabled and disabled
AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug], [Turn on debugging @<:@default=disabled@:>@])],
	[case "${enableval}" in
		yes) debug=true ;;
		no)  debug=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac],
	[debug=false])

#compile manpage?
AC_ARG_ENABLE([man],
	[AS_HELP_STRING([--disable-man], [generate documentation @<:@default=enabled@:>@])],
	[case "${enableval}" in
		yes) man=true ;;
		no)  man=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --disable-man]) ;;
	esac],
	[man=true])

#compile documentation (doxygen)?
AC_ARG_ENABLE([docs],
	[AS_HELP_STRING([--enable-docs], [generate documentation @<:@default=disabled@:>@])],
	[case "${enableval}" in
		yes) docs=true ;;
		no)  docs=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-docs]) ;;
	esac],
	[docs=false])

# Checks for packages.
PKG_CHECK_MODULES([GMODULE], [gmodule-2.0])
PKG_CHECK_MODULES([XENLIGHT], [xenlight >= 4.0])

PKG_CHECK_MODULES_STATIC([JSON_STATIC], [json-c >= 0.13])
PKG_CHECK_MODULES_STATIC([GMODULE_STATIC], [gmodule-2.0])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h stdio.h libxl.h gmodule.h json.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_DEFINE([_GNU_SOURCE], [], [use gnu extensions])
AC_DEFINE([_(s)], [gettext(s)], [use gnu extensions])

if test "x$debug" == xtrue; then
	AC_DEFINE([DEBUG], [], [debug flag])
	CFLAGS+=" -g -Wall"
else
	AM_SILENT_RULES
fi

AC_SUBST(have_dot, "NO")
if test "x$docs" == xtrue; then
	AC_CHECK_PROGS([DOXYGEN], [doxygen])

	if test -z "$DOXYGEN"
	then
		AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
		docs=false
	else
		AC_CHECK_PROGS([DOT], [dot])
		if test -z "$DOT"
		then
			AC_MSG_WARN([Dot not found - continuing without Dot support])
		else
			AC_SUBST(have_dot, "YES")
		fi
	fi
fi

if test "x$man" == xtrue; then
	AC_CHECK_PROGS([HELP2MAN], [help2man])

	if test -z "$HELP2MAN"
	then
		AC_MSG_WARN([help2man not found - continuing without man-page support])
		man=false
	fi
fi

AM_CONDITIONAL([DOCS], [test x$docs = xtrue])
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_CONDITIONAL([HAVE_DOT], [test -n "$DOT"])

AM_CONDITIONAL([MAN], [test x$man = xtrue])
AM_CONDITIONAL([HAVE_HELP2MAN], [test -n "$HELP2MAN"])

AC_CONFIG_FILES([Makefile src/xen-facter/Makefile src/xen-facter/po/Makefile.in src/xen-facter/docs/Doxyfile src/xen-facter/docs/Makefile src/libxl-ruby/Makefile src/libxl-ruby/po/Makefile.in src/libxl-ruby/docs/Doxyfile src/libxl-ruby/docs/Makefile])
AC_OUTPUT
