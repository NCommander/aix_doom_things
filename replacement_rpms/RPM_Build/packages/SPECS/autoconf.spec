Summary: A GNU tool for automatically configuring source code.
Name: autoconf
Version: 2.57
Release: 3
Copyright: GPL
Group: Development/Tools
Source: ftp://prep.ai.mit.edu/pub/gnu/autoconf/autoconf-%{version}.tar.bz2
URL: http://www.gnu.org/software/autoconf/
Patch1: autoconf-2.52-wait3.patch
#Patch2: autoconf-2.53-autoheader-warn.patch
Prereq(post,preun): /sbin/install-info
BuildRequires: sed, m4, emacs
Requires: gawk, m4, mktemp, perl, textutils
BuildArchitectures: noarch
BuildRoot: %{_tmppath}/%{name}-root

# run "make check" by default
%{?_without_check: %define _without_check 1}
%{!?_without_check: %define _without_check 0}

%description
GNU's Autoconf is a tool for configuring source code and Makefiles.
Using Autoconf, programmers can create portable and configurable
packages, since the person building the package is allowed to 
specify various configuration options.

You should install Autoconf if you are developing software and
would like to create shell scripts that configure your source code
packages. If you are installing Autoconf, you will also need to
install the GNU m4 package.

Note that the Autoconf package is not required for the end-user who
may be configuring software with an Autoconf-generated script;
Autoconf is only required for the generation of the scripts, not
their use.

%prep
%setup -q -n autoconf-%{version}
#%patch2 -p1 -b .warn

%build
#%configure --program-suffix=-%{version}
%configure
make
%if ! %{_without_check}
  make check
%endif

%install
rm -rf ${RPM_BUILD_ROOT}
%makeinstall

#ln -s autoconf-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autoconf
#ln -s autoheader-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autoheader
#ln -s autom4te-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autom4te
#ln -s autoreconf-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autoreconf
#ln -s autoscan-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autoscan
#ln -s autoupdate-%{version} ${RPM_BUILD_ROOT}%{_bindir}/autoupdate
#ln -s ifnames-%{version} ${RPM_BUILD_ROOT}%{_bindir}/ifnames

#gzip -9nf ${RPM_BUILD_ROOT}%{_infodir}/autoconf.info*

rm -f $RPM_BUILD_ROOT%{_infodir}/dir

%clean
rm -rf ${RPM_BUILD_ROOT}

%post
/sbin/install-info %{_infodir}/autoconf.info.gz %{_infodir}/dir

%preun
if [ "$1" = 0 ]; then
    /sbin/install-info --del %{_infodir}/autoconf.info.gz %{_infodir}/dir
fi

%files
%defattr(-,root,root)
%{_bindir}/*
%{_infodir}/autoconf.info*
# don't include standards.info, because it comes from binutils...
%exclude %{_infodir}/standards*
%{_datadir}/autoconf
%{_datadir}/emacs/site-lisp
%{_mandir}/man1/*
%doc AUTHORS COPYING ChangeLog NEWS README THANKS TODO

%changelog
* Wed Jan 22 2003 Tim Powers <timp@redhat.com>
- rebuilt

* Thu Dec 12 2002 Elliot Lee <sopwith@redhat.com> 2.57-2
- Fix missing/unpackaged file

* Thu Dec  5 2002 Jens Petersen <petersen@redhat.com> 2.57-1
- update to 2.57 bugfix release
- buildrequire emacs (#79031), sed and m4

* Sat Nov 23 2002 Jens Petersen <petersen@redhat.com> 2.56-2
- add --without check build option to control whether "make check" run
- don't gzip info files explicitly
- use exclude for unwanted info files

* Thu Nov 21 2002 Jens Petersen <petersen@redhat.com>
- no longer obsolete autoconf253

* Mon Nov 18 2002 Jens Petersen <petersen@redhat.com> 2.56-1
- update to 2.56
- obsolete autoheader-warn patch
- no longer provide autoconf253
- include site-lisp and man files
- remove info dir which is not in the manifest
- do not version suffix bin files for now

* Mon Aug 19 2002 Jens Petersen <petersen@redhat.com> 2.53-8
- make check

* Fri Jun 28 2002 Jens Petersen <petersen@redhat.com> 2.53-7
- update url (#66840)
- added doc files

* Fri Jun 21 2002 Tim Powers <timp@redhat.com> 2.53-6
- automated rebuild

* Sun May 26 2002 Tim Powers <timp@redhat.com> 2.53-5
- automated rebuild

* Mon May 20 2002 Bill Nottingham <notting@redhat.com> 2.53-4
- provide autoconf253

* Thu May 16 2002 Bill Nottingham <notting@redhat.com> 2.53-3
- obsolete autoconf253

* Wed May  8 2002 Jens Petersen <petersen@redhat.com> 2.53-2
- patch autoheader so that --warnings=CATEGORY works (#64566)
  [reported with fix by hjl@gnu.org]

* Tue Apr 23 2002 Jens Petersen <petersen@redhat.com> 2.53-1
- update to autoconf-2.53
- drop mawk patch again
- version suffix bindir files and add symlinks to unversioned names

* Fri Feb  1 2002 Jens Petersen <petersen@redhat.com> 2.52-7
- revert to 2.52 (also fixes #58210!)
- remove relversion variable
- bring back mawk -> gawk patch

* Wed Jan 09 2002 Tim Powers <timp@redhat.com> 2.52-6
- automated rebuild

* Thu Dec 20 2001 Jens Petersen <petersen@redhat.com> 2.52-5
- update to 2.52f
- add URL
- minor description improvements
- define relversion to carry version number
- mawk.patch no longer needed

* Sat Nov 17 2001 Florian La Roche <Florian.LaRoche@redhat.de> 2.52-4
- rebuild

* Wed Sep 19 2001 Jens Petersen <petersen@redhat.com> 2.52-3
- restore patch to prefer gawk to mawk

* Tue Sep 18 2001 Florian La Roche <Florian.LaRoche@redhat.de> 2.52-2
- update to 2.52d

* Mon Sep 17 2001 Jens Petersen <petersen@redhat.com> 2.52-1
- update to 2.52
- remove obsolete patches, since already new version
- dont install install-sh

* Tue Jul 10 2001 Jens Petersen <petersen@redhat.com>
- add patch to include various standard C headers as needed
  by various autoconf tests (#19114)
- add patch to autoscan.pl to get a better choice of init
  file (#42071), to test for CPP after CC (#42072) and to
  detect C++ source and g++ (#42073).

* Tue Jun 26 2001 Jens Petersen <petersen@redhat.com>
- Add a back-port of _AC_PROG_CXX_EXIT_DECLARATION
  from version 2.50 to make detection of C++ exit()
  declaration prototype platform independent.  The check is
  done in AC_PROG_CXX with the result stored in "confdefs.h".
  The exit() prototype in AC_TRY_RUN_NATIVE is no longer needed.
  (fixes #18829)

* Wed Nov 29 2000 Bernhard Rosenkraenzer <bero@redhat.com>
- Fix up interoperability with glibc 2.2 and gcc 2.96:
  AC_TRY_RUN_NATIVE in C++ mode added a prototype for exit() to
  the test code without throwing an exception, causing a conflict
  with stdlib.h --> AC_TRY_RUN_NATIVE for C++ code including stdlib.h
  always failed, returning wrong results

* Fri Jul 21 2000 Nalin Dahyabhai <nalin@redhat.com>
- add textutils as a dependency (#14439)

* Wed Jul 12 2000 Prospector <bugzilla@redhat.com>
- automatic rebuild

* Mon Jun  5 2000 Jeff Johnson <jbj@redhat.com>
- FHS packaging.

* Sun Mar 26 2000 Florian La Roche <Florian.LaRoche@redhat.com>
- fix preun

* Fri Mar 26 1999 Cristian Gafton <gafton@redhat.com>
- add patch to help autoconf clean after itself and not leave /tmp clobbered
  with acin.* and acout.* files (can you say annoying?)

* Sun Mar 21 1999 Cristian Gafton <gafton@redhat.com> 
- auto rebuild in the new build environment (release 4)
- use gawk, not mawk

* Thu Mar 18 1999 Preston Brown <pbrown@redhat.com>
- moved /usr/lib/autoconf to /usr/share/autoconf (with automake)

* Wed Feb 24 1999 Preston Brown <pbrown@redhat.com>
- Injected new description and group.

* Tue Jan 12 1999 Jeff Johnson <jbj@redhat.com>
- update to 2.13.

* Fri Dec 18 1998 Cristian Gafton <gafton@redhat.com>
- build against glibc 2.1

* Mon Oct 05 1998 Cristian Gafton <gafton@redhat.com>
- requires perl

* Thu Aug 27 1998 Cristian Gafton <gafton@redhat.com>
- patch for fixing /tmp race conditions

* Sun Oct 19 1997 Erik Troan <ewt@redhat.com>
- spec file cleanups
- made a noarch package
- uses autoconf
- uses install-info

* Thu Jul 17 1997 Erik Troan <ewt@redhat.com>
- built with glibc

