# Makefile.in generated by automake 1.6a from Makefile.am.
# lib/autotest/Makefile.  Generated from Makefile.in by configure.

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
top_srcdir = ../..

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
top_builddir = ../..

ACLOCAL = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run aclocal-1.6a
AUTOCONF = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run autoconf
AUTOMAKE = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run automake-1.6a
AUTOHEADER = ${SHELL} /opt/freeware/src/packages/BUILD/autoconf-2.53/config/missing --run autoheader

am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = ../../config/install-sh -c
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

autotestlibdir = $(pkgdatadir)/autotest
dist_autotestlib_DATA = autotest.m4 general.m4
nodist_autotestlib_DATA = autotest.m4f
CLEANFILES = $(nodist_autotestlib_DATA)

TAGS_FILES = $(dist_autotestlib_DATA)

ETAGS_ARGS = --lang=none \
  --regex='/\(A[CU]_DEFUN\|m4_\(defun\|define\)\|define\)(\[\([^]]*\)\]/\3/'


SUFFIXES = .m4 .m4f

# Do not use AUTOM4TE here, since Makefile.maint (my-distcheck)
# checks if we are independant of Autoconf by defining AUTOM4TE (and
# others) to `false'.  But we _ship_ tests/autom4te, so it doesn't
# apply to us.
MY_AUTOM4TE = $(top_builddir)/tests/autom4te

AUTOM4TE_CFG = $(top_builddir)/lib/autom4te.cfg

# Factor the dependencies between all the frozen files.
# Some day we should explain to Automake how to use autom4te to compute
# the dependencies...
src_libdir = $(top_srcdir)/lib
build_libdir = $(top_builddir)/lib

m4f_dependencies = $(MY_AUTOM4TE) $(AUTOM4TE_CFG)

m4sugar_m4f_dependencies = \
	$(m4f_dependencies)			\
	$(src_libdir)/m4sugar/m4sugar.m4	\
	$(build_libdir)/m4sugar/version.m4


m4sh_m4f_dependencies = \
	$(m4sugar_m4f_dependencies)		\
	$(src_libdir)/m4sugar/m4sh.m4


autotest_m4f_dependencies = \
	$(m4sh_m4f_dependencies)		\
	$(src_libdir)/autotest/autotest.m4	\
	$(src_libdir)/autotest/general.m4


autoconf_m4f_dependencies = \
	$(m4sh_m4f_dependencies)		\
	$(src_libdir)/autoconf/general.m4	\
	$(src_libdir)/autoconf/autoheader.m4	\
	$(src_libdir)/autoconf/autoupdate.m4	\
	$(src_libdir)/autoconf/autotest.m4	\
	$(src_libdir)/autoconf/status.m4	\
	$(src_libdir)/autoconf/oldnames.m4	\
	$(src_libdir)/autoconf/specific.m4	\
	$(src_libdir)/autoconf/lang.m4		\
	$(src_libdir)/autoconf/c.m4		\
	$(src_libdir)/autoconf/fortran.m4	\
	$(src_libdir)/autoconf/functions.m4	\
	$(src_libdir)/autoconf/headers.m4	\
	$(src_libdir)/autoconf/types.m4		\
	$(src_libdir)/autoconf/libs.m4		\
	$(src_libdir)/autoconf/programs.m4	\
	$(src_libdir)/autoconf/autoconf.m4

subdir = lib/autotest
mkinstalldirs = $(SHELL) $(top_srcdir)/config/mkinstalldirs
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DATA = $(dist_autotestlib_DATA) $(nodist_autotestlib_DATA)

DIST_COMMON = $(dist_autotestlib_DATA) Makefile.am Makefile.in
all: all-am

.SUFFIXES:
.SUFFIXES: .m4 .m4f
$(srcdir)/Makefile.in:  Makefile.am $(srcdir)/../freeze.mk $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  lib/autotest/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)
uninstall-info-am:
dist_autotestlibDATA_INSTALL = $(INSTALL_DATA)
install-dist_autotestlibDATA: $(dist_autotestlib_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(autotestlibdir)
	@list='$(dist_autotestlib_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(dist_autotestlibDATA_INSTALL) $$d$$p $(DESTDIR)$(autotestlibdir)/$$f"; \
	  $(dist_autotestlibDATA_INSTALL) $$d$$p $(DESTDIR)$(autotestlibdir)/$$f; \
	done

uninstall-dist_autotestlibDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_autotestlib_DATA)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(autotestlibdir)/$$f"; \
	  rm -f $(DESTDIR)$(autotestlibdir)/$$f; \
	done
nodist_autotestlibDATA_INSTALL = $(INSTALL_DATA)
install-nodist_autotestlibDATA: $(nodist_autotestlib_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(autotestlibdir)
	@list='$(nodist_autotestlib_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(nodist_autotestlibDATA_INSTALL) $$d$$p $(DESTDIR)$(autotestlibdir)/$$f"; \
	  $(nodist_autotestlibDATA_INSTALL) $$d$$p $(DESTDIR)$(autotestlibdir)/$$f; \
	done

uninstall-nodist_autotestlibDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(nodist_autotestlib_DATA)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(autotestlibdir)/$$f"; \
	  rm -f $(DESTDIR)$(autotestlibdir)/$$f; \
	done

ETAGS = etags
ETAGSFLAGS =

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$tags$$unique" \
	  || $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	     $$tags $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../..
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
	$(MAKE) $(AM_MAKEFLAGS) check-local
check: check-am
all-am: Makefile $(DATA)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(autotestlibdir) $(DESTDIR)$(autotestlibdir)

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

distclean-am: clean-am distclean-generic distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am: install-dist_autotestlibDATA \
	install-nodist_autotestlibDATA

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic

uninstall-am: uninstall-dist_autotestlibDATA uninstall-info-am \
	uninstall-nodist_autotestlibDATA

.PHONY: GTAGS all all-am check check-am check-local clean clean-generic \
	distclean distclean-generic distclean-tags distdir dvi dvi-am \
	info info-am install install-am install-data install-data-am \
	install-dist_autotestlibDATA install-exec install-exec-am \
	install-info install-info-am install-man \
	install-nodist_autotestlibDATA install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic tags \
	uninstall uninstall-am uninstall-dist_autotestlibDATA \
	uninstall-info-am uninstall-nodist_autotestlibDATA


check-local:
	if (cd $(srcdir) && \
	    egrep '^_?EOF' $(dist_autotestlib_DATA)) >eof.log; then \
	  echo "ERROR: user EOF tags were used:" >&2; \
	  sed "s,^,$*.m4: ," <eof.log >&2; \
	  echo >&2; \
	  exit 1; \
	else \
	  rm -f eof.log; \
	fi

autotest.m4f: $(autotest_m4f_dependencies)
$(MY_AUTOM4TE):
	cd $(top_builddir)/tests && $(MAKE) $(AM_MAKEFLAGS) autom4te
$(AUTOM4TE_CFG):
	cd $(top_builddir)/lib && $(MAKE) $(AM_MAKEFLAGS) autom4te.cfg

# When processing the file with diversion disabled, there must be no
# output but comments and empty lines.
# If freezing produces output, something went wrong: a bad `divert',
# or an improper paren etc.
# It may happen that the output does not end with a end of line, hence
# force an end of line when reporting errors.
.m4.m4f:
	$(MY_AUTOM4TE)				\
		--language=$*			\
		--freeze			\
		--include=$(srcdir)/..		\
		--include=..			\
		--output=$@

# For parallel builds.
$(build_libdir)/m4sugar/version.m4:
	cd $(build_libdir)/m4sugar && $(MAKE) $(AM_MAKEFLAGS) version.m4
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
