# Makefile.in generated by automake 1.6a from Makefile.am.
# doc/Makefile.  Generated from Makefile.in by configure.

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

MAKEINFO = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run makeinfo --no-split
TEXI2HTML = texi2html
TEXI2HTML_FLAGS = -split_chapter

info_TEXINFOS = autoconf.texi standards.texi
autoconf_TEXINFOS = fdl.texi install.texi
standards_TEXINFOS = make-stds.texi

# Files from texi2dvi that should be removed, but which Automake does
# not know.
CLEANFILES = autoconf.acs  autoconf.cvs  autoconf.mss  autoconf.prs \
	     autoconf.ats  autoconf.evs  autoconf.fns  autoconf.ovs \
             autoconf.tmp \
	     autoconf*.html standards*.html \
	     autoconf*.pdf standards*.pdf

subdir = doc
mkinstalldirs = $(SHELL) $(top_srcdir)/config/mkinstalldirs
CONFIG_CLEAN_FILES =
DIST_SOURCES =
TEXINFO_TEX = $(top_srcdir)/config/texinfo.tex
INFO_DEPS = autoconf.info standards.info
DVIS = autoconf.dvi standards.dvi
TEXINFOS = autoconf.texi standards.texi
DIST_COMMON = $(autoconf_TEXINFOS) $(standards_TEXINFOS) Makefile.am \
	Makefile.in stamp-vti version.texi
all: all-am

.SUFFIXES:
.SUFFIXES: .dvi .info .ps .texi
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  doc/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)

$(srcdir)/version.texi:  $(srcdir)/stamp-vti
	@:
$(srcdir)/stamp-vti: autoconf.texi $(top_srcdir)/configure.ac
	@(set `$(SHELL) $(top_srcdir)/config/mdate-sh $(srcdir)/autoconf.texi`; \
	echo "@set UPDATED $$1 $$2 $$3"; \
	echo "@set UPDATED-MONTH $$2 $$3"; \
	echo "@set EDITION $(VERSION)"; \
	echo "@set VERSION $(VERSION)") > vti.tmp
	@cmp -s vti.tmp $(srcdir)/version.texi \
	  || (echo "Updating $(srcdir)/version.texi"; \
	      cp vti.tmp $(srcdir)/version.texi)
	-@rm -f vti.tmp
	@cp $(srcdir)/version.texi $@

mostlyclean-vti:
	-rm -f vti.tmp

maintainer-clean-vti:
	-rm -f $(srcdir)/stamp-vti $(srcdir)/version.texi

autoconf.info: autoconf.texi $(srcdir)/version.texi $(autoconf_TEXINFOS)
autoconf.dvi: autoconf.texi $(srcdir)/version.texi $(autoconf_TEXINFOS)

standards.info: standards.texi $(standards_TEXINFOS)
standards.dvi: standards.texi $(standards_TEXINFOS)

.texi.info:
	@cd $(srcdir) && rm -f $@ $@-[0-9] $@-[0-9][0-9]
	cd $(srcdir) \
	  && $(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) \
	       `echo $< | sed 's,.*/,,'`

.texi.dvi:
	TEXINPUTS="$(top_srcdir)/config$(PATH_SEPARATOR)$$TEXINPUTS" \
	MAKEINFO='$(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) -I $(srcdir)' \
	$(TEXI2DVI) $<

.texi:
	@cd $(srcdir) && rm -f $@ $@-[0-9] $@-[0-9][0-9]
	cd $(srcdir) \
	  && $(MAKEINFO) $(AM_MAKEINFOFLAGS) $(MAKEINFOFLAGS) \
	       `echo $< | sed 's,.*/,,'`
TEXI2DVI = texi2dvi
DVIPS = dvips
.dvi.ps:
	$(DVIPS) $< -o $@

uninstall-info-am:
	$(PRE_UNINSTALL)
	@if (install-info --version && \
	     install-info --version | fgrep -i -v debian) >/dev/null 2>&1; then \
	  list='$(INFO_DEPS)'; \
	  for file in $$list; do \
	    echo " install-info --info-dir=$(DESTDIR)$(infodir) --remove $(DESTDIR)$(infodir)/$$file"; \
	    install-info --info-dir=$(DESTDIR)$(infodir) --remove $(DESTDIR)$(infodir)/$$file; \
	  done; \
	else :; fi
	@$(NORMAL_UNINSTALL)
	@list='$(INFO_DEPS)'; \
	for file in $$list; do \
	  (if cd $(DESTDIR)$(infodir); then \
	     echo " rm -f $$file $$file-[0-9] $$file-[0-9][0-9])"; \
	     rm -f $$file $$file-[0-9] $$file-[0-9][0-9]; \
	   else :; fi); \
	done

dist-info: $(INFO_DEPS)
	list='$(INFO_DEPS)'; \
	for base in $$list; do \
	  d=$(srcdir); \
	  for file in $$d/$$base*; do \
	    relfile=`expr "$$file" : "$$d/\(.*\)"`; \
	    test -f $(distdir)/$$relfile || \
	      cp -p $$file $(distdir)/$$relfile; \
	  done; \
	done

mostlyclean-aminfo:
	-rm -f autoconf.ac autoconf.at autoconf.aux autoconf.cp autoconf.cps \
	  autoconf.cv autoconf.dvi autoconf.ev autoconf.fn autoconf.ky \
	  autoconf.log autoconf.ms autoconf.ov autoconf.pg autoconf.pr \
	  autoconf.ps autoconf.toc autoconf.tp autoconf.vr autoconf.vrs \
	  standards.aux standards.cp standards.cps standards.dvi \
	  standards.fn standards.ky standards.log standards.pg \
	  standards.ps standards.toc standards.tp standards.vr

maintainer-clean-aminfo:
	cd $(srcdir) && \
	for i in $(INFO_DEPS); do \
	  rm -f $$i; \
	  if test "`echo $$i-[0-9]*`" != "$$i-[0-9]*"; then \
	    rm -f $$i-[0-9]*; \
	  fi; \
	done
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
	$(MAKE) $(AM_MAKEFLAGS) \
	  top_distdir="${top_distdir}" distdir="$(distdir)" \
	  dist-info
check-am: all-am
check: check-am
all-am: Makefile $(INFO_DEPS)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(infodir)

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
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic

dvi: dvi-am

dvi-am: $(DVIS)

info: info-am

info-am: $(INFO_DEPS)

install-data-am: install-info-am

install-exec-am:

install-info: install-info-am

install-info-am: $(INFO_DEPS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(infodir)
	@list='$(INFO_DEPS)'; \
	for file in $$list; do \
	  d=$(srcdir); \
	  for ifile in echo $$d/$$file $$d/$$file-[0-9] $$d/$$file-[0-9][0-9]; do \
	    if test -f $$ifile; then \
	      relfile=`expr "$$ifile" : "$$d/\(.*\)"`; \
	      echo " $(INSTALL_DATA) $$ifile $(DESTDIR)$(infodir)/$$relfile"; \
	      $(INSTALL_DATA) $$ifile $(DESTDIR)$(infodir)/$$relfile; \
	    else : ; fi; \
	  done; \
	done
	@$(POST_INSTALL)
	@if (install-info --version && \
	     install-info --version | fgrep -i -v debian) >/dev/null 2>&1; then \
	  list='$(INFO_DEPS)'; \
	  for file in $$list; do \
	    echo " install-info --info-dir=$(DESTDIR)$(infodir) $(DESTDIR)$(infodir)/$$file";\
	    install-info --info-dir=$(DESTDIR)$(infodir) $(DESTDIR)$(infodir)/$$file || :;\
	  done; \
	else : ; fi
install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-aminfo \
	maintainer-clean-generic maintainer-clean-vti

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-aminfo mostlyclean-generic mostlyclean-vti

uninstall-am: uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic dist-info \
	distclean distclean-generic distdir dvi dvi-am info info-am \
	install install-am install-data install-data-am install-exec \
	install-exec-am install-info install-info-am install-man \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-aminfo \
	maintainer-clean-generic maintainer-clean-vti mostlyclean \
	mostlyclean-aminfo mostlyclean-generic mostlyclean-vti \
	uninstall uninstall-am uninstall-info-am


html: autoconf_1.html standards_1.html

autoconf_1.html: autoconf.texi install.texi
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) $(srcdir)/autoconf.texi

standards_1.html: standards.texi make-stds.texi
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) $(srcdir)/standards.texi

pdf: autoconf.pdf standards.pdf

autoconf.pdf: autoconf.texi install.texi
	$(TEXI2DVI) --pdf --batch $(srcdir)/autoconf.texi

standards.pdf: standards.texi make-stds.texi
	$(TEXI2DVI) --pdf --batch $(srcdir)/standards.texi

.PHONY: html pdf
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
