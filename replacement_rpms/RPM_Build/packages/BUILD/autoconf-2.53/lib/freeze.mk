## Freeze M4 files.

## Copyright 2002 Free Software Foundation, Inc.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

SUFFIXES = .m4 .m4f

# Do not use AUTOM4TE here, since Makefile.maint (my-distcheck)
# checks if we are independant of Autoconf by defining AUTOM4TE (and
# others) to `false'.  But we _ship_ tests/autom4te, so it doesn't
# apply to us.
MY_AUTOM4TE = $(top_builddir)/tests/autom4te
$(MY_AUTOM4TE):
	cd $(top_builddir)/tests && $(MAKE) $(AM_MAKEFLAGS) autom4te

AUTOM4TE_CFG = $(top_builddir)/lib/autom4te.cfg
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

# Factor the dependencies between all the frozen files.
# Some day we should explain to Automake how to use autom4te to compute
# the dependencies...
src_libdir   = $(top_srcdir)/lib
build_libdir = $(top_builddir)/lib

m4f_dependencies = $(MY_AUTOM4TE) $(AUTOM4TE_CFG)

# For parallel builds.
$(build_libdir)/m4sugar/version.m4:
	cd $(build_libdir)/m4sugar && $(MAKE) $(AM_MAKEFLAGS) version.m4

m4sugar_m4f_dependencies =			\
	$(m4f_dependencies)			\
	$(src_libdir)/m4sugar/m4sugar.m4	\
	$(build_libdir)/m4sugar/version.m4

m4sh_m4f_dependencies =				\
	$(m4sugar_m4f_dependencies)		\
	$(src_libdir)/m4sugar/m4sh.m4

autotest_m4f_dependencies = 			\
	$(m4sh_m4f_dependencies)		\
	$(src_libdir)/autotest/autotest.m4	\
	$(src_libdir)/autotest/general.m4

autoconf_m4f_dependencies =			\
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
