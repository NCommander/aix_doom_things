# Makefile.in generated by automake 1.6a from Makefile.am.
# config/Makefile.  Generated from Makefile.in by configure.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /opt/freeware
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/autoconf
pkglibdir = $(libdir)/autoconf
pkgincludedir = $(includedir)/autoconf
top_builddir = ..

ACLOCAL = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run aclocal-1.6a
AUTOCONF = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run autoconf
AUTOMAKE = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run automake-1.6a
AUTOHEADER = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run autoheader

am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = ../config/install-sh -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :

EXEEXT = @EXEEXT@
OBJEXT = @OBJEXT@
PATH_SEPARATOR = :
AMTAR = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run tar
AWK = nawk
DEPDIR = @DEPDIR@
EMACS = no
EXPR = /usr/bin/expr
HELP2MAN = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run help2man
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
M4 = /opt/freeware/bin/m4
PACKAGE = autoconf
PACKAGE_NAME = GNU Autoconf
PERL = /usr/bin/perl
STRIP = 
VERSION = 2.53
am__include = @am__include@
am__quote = @am__quote@
install_sh = /opt/freeware/src/packages/BUILD/autoconf-2.53/config/install-sh
lispdir = 

EXTRA_DIST = $(SPECIFIC_MACROS) $(SPECIFIC_TOOLS) \
              prev-version.txt

MAINTAINERCLEANFILES = $(GENERIC_TOOLS)

SPECIFIC_MACROS = \
m4.m4


GENERIC_TOOLS = \
config.guess					\
config.sub					\
emacs-comp					\
install-sh					\
mdate-sh					\
missing						\
mkinstalldirs					\
texinfo.tex


SPECIFIC_TOOLS = move-if-change
subdir = config
mkinstalldirs = $(SHELL) $(top_srcdir)/config/mkinstalldirs
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DIST_COMMON = Makefile.am Makefile.in config.guess config.sub \
	elisp-comp install-sh mdate-sh missing mkinstalldirs \
	texinfo.tex
all: all-am

.SUFFIXES:
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  config/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)
uninstall-info-am:
tags: TAGS
TAGS:

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkinstalldirs) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir)$$dir \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
clean: clean-am

clean-am: clean-generic mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic

uninstall-am: uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic distclean \
	distclean-generic distdir dvi dvi-am info info-am install \
	install-am install-data install-data-am install-exec \
	install-exec-am install-info install-info-am install-man \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-generic uninstall uninstall-am uninstall-info-am

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
