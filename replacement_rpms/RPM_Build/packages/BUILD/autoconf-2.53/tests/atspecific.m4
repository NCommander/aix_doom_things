# M4 macros used in building Autoconf test suites.        -*- Autotest -*-

# Copyright 2000, 2001 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.


## ----------------- ##
## Testing M4sugar.  ##
## ----------------- ##


# AT_DATA_M4SUGAR(FILENAME, CONTENTS)
# -----------------------------------
# Escape the invalid tokens with @&t@.
m4_define([AT_DATA_M4SUGAR],
[AT_DATA([$1],
[m4_bpatsubsts([$2],
               [@&t@],    [@&@&t@t@],
               [\(m4\)_], [\1@&t@_],
               [dnl],     [d@&t@nl])])])


# AT_CHECK_M4SUGAR(FLAGS, [EXIT-STATUS = 0], STDOUT, STDERR)
# ----------------------------------------------------------
m4_define([AT_CHECK_M4SUGAR],
[AT_CHECK([autom4te --language=m4sugar script.4s -o script $1],
          m4_default([$2], [0]), [$3], [$4])])



## -------------- ##
## Testing M4sh.  ##
## -------------- ##


# AT_DATA_M4SH(FILENAME, CONTENTS)
# --------------------------------
# Escape the invalid tokens with @&t@.
m4_define([AT_DATA_M4SH],
[AT_DATA([$1],
[m4_bpatsubsts([$2],
               [@&t@],        [@&@&t@t@],
               [\(m4\|AS\)_], [\1@&t@_],
               [dnl],         [d@&t@nl])])])


# AT_CHECK_M4SH(FLAGS, [EXIT-STATUS = 0], STDOUT, STDERR)
# -------------------------------------------------------
m4_define([AT_CHECK_M4SH],
[AT_CHECK([autom4te --language=m4sh script.as -o script $1],
          m4_default([$2], [0]), [$3], [$4])])



## ------------------ ##
## Testing Autoconf.  ##
## ------------------ ##


# AT_DATA_AUTOCONF(FILENAME, CONTENTS)
# ------------------------------------
# Escape the invalid tokens with @&t@.
m4_define([AT_DATA_AUTOCONF],
[AT_DATA([$1],
[m4_bpatsubsts([$2],
               [@&t@],            [@&@&t@t@],
               [\(m4\|AS\|AC\)_], [\1@&t@_],
               [dnl],             [d@&t@nl])])])



# AT_CONFIGURE_AC(BODY)
# ---------------------
# Create a full configure.ac running BODY, with a config header set up,
# AC_OUTPUT, and environment checking hooks.
#
# Here are the exceptions to AC_STATE_SAVE:
#
# - ^ac_
#   Autoconf's shell name space.
# - prefix and exec_prefix
#   are kept undefined (NONE) until AC_OUTPUT which then sets them to
#   `/usr/local' and `${prefix}' for make.
# - CONFIG_STATUS and DEFS
#   Set by AC_OUTPUT.
# - F77_DUMMY_MAIN
#   Set by AC_F77_DUMMY_MAIN.
# - ALLOCA|NEED_SETGID|KMEM_GROUP
#   AC_FUNCs from acspecific.
# - AWK|LEX|LEXLIB|LEX_OUTPUT_ROOT|LN_S|M4|RANLIB|SET_MAKE|YACC
#   AC_PROGs from acspecific
# - _|@|.[*#?].|LINENO|OLDPWD|PIPESTATUS|RANDOM|SECONDS
#   Some variables some shells use and change.
#   `.[*#?].' catches `$#' etc. which are displayed like this:
#      | '!'=18186
#      | '#'=0
#      | '$'=6908
# - POW_LIB
#   From acfunctions.m4.
#
m4_define([AT_CONFIGURE_AC],
[AT_DATA_AUTOCONF([aclocal.m4],
[[
# AC_STATE_SAVE(FILE)
# ------------------
# Save the environment, except for those variables we are allowed to touch.
# This is to check no test touches the user name space.
# FIXME: There are surely better ways.  Explore for instance if
# we can ask help from AC_SUBST.  We have the right to touch what
# is AC_SUBST'ed.
#
# Some `egrep' choke on such a big regex (e.g., SunOS 4.1.3).  In this
# case just don't pay attention to the env.  It would be great
# to keep the error message but we can't: that would break AT_CHECK.
m4_defun([AC_STATE_SAVE],
[(set) 2>&1 |
  egrep -v -e 'm4_join([|],
      [^a[cs]_],
      [^((exec_)?prefix|DEFS|CONFIG_STATUS)=],
      [^(CC|CFLAGS|CPP|GCC|CXX|CXXFLAGS|CXXCPP|GXX|F77|FFLAGS|FLIBS|G77)=],
      [^(LIBS|LIB@&t@OBJS|LDFLAGS)=],
      [^INSTALL(_(DATA|PROGRAM|SCRIPT))?=],
      [^(CYGWIN|ISC|MINGW32|MINIX|EMXOS2|XENIX|EXEEXT|OBJEXT)=],
      [^(X_(CFLAGS|(EXTRA_|PRE_)?LIBS)|x_(includes|libraries)|(have|no)_x)=],
      [^(host|build|target)(_(alias|cpu|vendor|os))?=],
      [^(cross_compiling)=],
      [^(interpval|PATH_SEPARATOR)=],
      [^(F77_DUMMY_MAIN|f77_(case|underscore))=],
      [^(ALLOCA|GETLOADAVG_LIBS|KMEM_GROUP|NEED_SETGID|POW_LIB)=],
      [^(AWK|LEX|LEXLIB|LEX_OUTPUT_ROOT|LN_S|M4|RANLIB|SET_MAKE|YACC)=],
      [^(_|@|.[*#?].|LINENO|OLDPWD|PIPESTATUS|RANDOM|SECONDS)=])' 2>/dev/null |
  # There maybe variables spread on several lines, eg IFS, remove the dead
  # lines.
  grep '^m4_defn([m4_re_word])=' >state-env.$[@]&t@1
test $? = 0 || rm -f state-env.$[@]&t@1

ls -1 | egrep -v '^(at-|state-|config\.)' | sort >state-ls.$[@]&t@1
])# AC_STATE_SAVE
]])

AT_DATA([configure.ac],
[[AC_INIT
AC_CONFIG_AUX_DIR($top_srcdir/config)
AC_CONFIG_HEADER(config.h:config.hin)
AC_STATE_SAVE(before)]
$1
[AC_OUTPUT
AC_STATE_SAVE(after)
]])
])# AT_CONFIGURE_AC


# AT_CHECK_AUTOCONF(ARGS, [EXIT-STATUS = 0], STDOUT, STDERR)
# ----------------------------------------------------------
m4_define([AT_CHECK_AUTOCONF],
[AT_CHECK([autoconf $1],
          [$2], [$3], [$4])])


# AT_CHECK_AUTOHEADER(ARGS, [EXIT-STATUS = 0],
#                     STDOUT, [STDERR = `autoheader: `config.hin' is created'])
# -----------------------------------------------------------------------------
m4_define([AT_CHECK_AUTOHEADER],
[AT_CHECK([autoheader $1], [$2],
          [$3],
          m4_default([$4], [[autoheader: `config.hin' is created
]]))])


# AT_CHECK_CONFIGURE(END-COMMAND,
#                    [EXIT-STATUS = 0],
#                    [SDOUT = IGNORE], STDERR)
# --------------------------------------------
# `abs_top_srcdir' is needed so that `./configure' finds install-sh.
# Using --srcdir is more expensive.
m4_define([AT_CHECK_CONFIGURE],
[AT_CHECK([top_srcdir=$abs_top_srcdir ./configure $1],
          [$2],
          m4_default([$3], [ignore]), [$4],
          [test $at_verbose = echo && echo "$srcdir/AT_LINE: config.log" && cat config.log])])


# AT_CHECK_ENV
# ------------
# Check that the full configure run remained in its variable name space,
# and cleaned up tmp files.
# me tests might exit prematurely when they find a problem, in
# which case `env-after' is probably missing.  Don't check it then.
m4_define([AT_CHECK_ENV],
[if test -f state-env.before -a -f state-env.after; then
  mv -f state-env.before expout
  AT_CHECK([cat state-env.after], 0, expout)
fi
if test -f state-ls.before -a -f state-ls.after; then
  mv -f state-ls.before expout
  AT_CHECK([cat state-ls.after], 0, expout)
fi
])


# AT_CHECK_DEFINES(CONTENT)
# -------------------------
# Verify that config.h, once stripped, is CONTENT.
# Stripping consists of keeping CPP lines (i.e. containing a hash),
# but those of automatically checked features (STDC_HEADERS etc.)
# and symbols (PACKAGE_...).
# AT_CHECK_HEADER is a better name, but too close from AC_CHECK_HEADER.
m4_define([AT_CHECK_DEFINES],
[AT_CHECK([[fgrep '#' config.h |
 egrep -v 'STDC_HEADERS|STD(INT|LIB)|INTTYPES|MEMORY|PACKAGE_|STRING|SYS_(TYPES|STAT)|UNISTD']],,
          [$1])])


# AT_CHECK_AUTOUPDATE
# -------------------
m4_define([AT_CHECK_AUTOUPDATE],
[AT_CHECK([autoupdate], 0,
          [], [autoupdate: `configure.ac' is updated
])])


# _AT_CHECK_AC_MACRO(AC-BODY, PRE-TESTS)
# --------------------------------------
# Create a minimalist configure.ac running the macro named
# NAME-OF-THE-MACRO, check that autoconf runs on that script,
# and that the shell runs correctly the configure.
m4_define([_AT_CHECK_AC_MACRO],
[AT_CONFIGURE_AC([$1])
$2
AT_CHECK_AUTOCONF
AT_CHECK_AUTOHEADER
AT_CHECK_CONFIGURE
AT_CHECK_ENV
])# _AT_CHECK_AC_MACRO


# AT_CHECK_MACRO(MACRO, [MACRO-USE], [ADDITIONAL-CMDS],
#                [AUTOCONF-FLAGS = -W obsolete])
# -----------------------------------------------------
# Create a minimalist configure.ac running the macro named
# NAME-OF-THE-MACRO, check that autoconf runs on that script,
# and that the shell runs correctly the configure.
#
# New macros are not expected to depend upon obsolete macros.
m4_define([AT_CHECK_MACRO],
[AT_SETUP([$1])

AT_CONFIGURE_AC([m4_default([$2], [$1])])

AT_CHECK_AUTOCONF([m4_default([$4], [-W obsolete])])
AT_CHECK_AUTOHEADER
AT_CHECK_CONFIGURE
AT_CHECK_ENV
$3
AT_CLEANUP()dnl
])# AT_CHECK_MACRO


# AT_CHECK_AU_MACRO(MACRO)
# ------------------------
# Create a minimalist configure.ac running the macro named
# NAME-OF-THE-MACRO, autoupdate this script, check that autoconf runs
# on that script, and that the shell runs correctly the configure.
#
# Updated configure.ac shall not depend upon obsolete macros, which votes
# in favor of `-W obsolete', but since many of these macros leave a message
# to be removed by the user once her code ajusted, let's not check.
#
# Remove config.hin to avoid `autoheader: config.hin is unchanged'.
m4_define([AT_CHECK_AU_MACRO],
[AT_SETUP([$1])
AT_KEYWORDS([autoupdate])

AT_CONFIGURE_AC([$1])

AT_CHECK_AUTOCONF
AT_CHECK_AUTOHEADER
AT_CHECK_CONFIGURE
AT_CHECK_ENV

rm config.hin
AT_CHECK_AUTOUPDATE

AT_CHECK_AUTOCONF
AT_CHECK_AUTOHEADER
AT_CHECK_CONFIGURE
AT_CHECK_ENV

AT_CLEANUP()dnl
])# AT_CHECK_UPDATE
