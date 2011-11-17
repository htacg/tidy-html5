# Makefile - for tidy - HTML parser and pretty printer
#
#  CVS Info :
#
#     $Author: arnaud02 $ 
#     $Date: 2008/03/22 21:13:38 $ 
#     $Revision: 1.37 $ 
#
#  Copyright (c) 1998-2008 World Wide Web Consortium
#  (Massachusetts Institute of Technology, European Research 
#  Consortium for Informatics and Mathematics, Keio University).
#  All Rights Reserved.
#
#  Contributing Author(s):
#
#     Dave Raggett <dsr@w3.org>
#     Terry Teague <terry_teague@users.sourceforge.net>
#     Pradeep Padala<ppadala@users.sourceforge.net>
#
#  The contributing author(s) would like to thank all those who
#  helped with testing, bug fixes, and patience.  This wouldn't
#  have been possible without all of you.
#
#  COPYRIGHT NOTICE:
#
#  This software and documentation is provided "as is," and
#  the copyright holders and contributing author(s) make no
#  representations or warranties, express or implied, including
#  but not limited to, warranties of merchantability or fitness
#  for any particular purpose or that the use of the software or
#  documentation will not infringe any third party patents,
#  copyrights, trademarks or other rights. 
#
#  The copyright holders and contributing author(s) will not be
#  liable for any direct, indirect, special or consequential damages
#  arising out of any use of the software or documentation, even if
#  advised of the possibility of such damage.
#
#  Permission is hereby granted to use, copy, modify, and distribute
#  this source code, or portions hereof, documentation and executables,
#  for any purpose, without fee, subject to the following restrictions:
#
#  1. The origin of this source code must not be misrepresented.
#  2. Altered versions must be plainly marked as such and must
#     not be misrepresented as being the original source.
#  3. This Copyright notice may not be removed or altered from any
#     source or altered source distribution.
# 
#  The copyright holders and contributing author(s) specifically
#  permit, without fee, and encourage the use of this source code
#  as a component for supporting the Hypertext Markup Language in
#  commercial products. If you use this source code in a product,
#  acknowledgment is not required but would be appreciated.
#

SHELL=/bin/sh

PROJECT=tidy

# Installation variables.  Spaces OK, only dir create and file copy operations.
runinst_prefix=/usr/local
devinst_prefix=/usr/local

bininst = ${runinst_prefix}/bin
libinst = ${devinst_prefix}/lib
incinst = ${devinst_prefix}/include/$(PROJECT)
maninst = ${devinst_prefix}/man

# Internal variables. - No spaces allowed: libtool chokes on spaces in directory names.
TOPDIR = ../..
INCDIR = ${TOPDIR}/include
APPDIR = ${TOPDIR}/console
SRCDIR = ${TOPDIR}/src
OBJDIR = ./obj
LIBDIR = ${TOPDIR}/lib
BINDIR = ${TOPDIR}/bin
DOCDIR = ${TOPDIR}/htmldoc

# Note about shared library and exported symbols:
# With gcc, one can control the exported symbols by either using 
# "-fvisibility=hidden -DTIDY_EXPORT='__attribute__((visibility("default")))'"
# or using a linker map (see GNU ld "--version-script").

# Lookup based on hash table can be disabled with 
# "-DELEMENT_HASH_LOOKUP=0 -DATTRIBUTE_HASH_LOOKUP=0"

# Memory mapped i/o can be disabled with -DSUPPORT_POSIX_MAPPED_FILES=0
#

# CFLAGS etc..
# For optimised builds, flags such as "-O2" should be added and -D_DEBUG=1
# disabled.
CC= gcc
CFLAGS= -g -pedantic -Wall -I $(INCDIR)
# flags only supported with gcc 3.x
CFLAGS += -Wunused-parameter

OTHERCFLAGS=
OTHERCFLAGS+= -D_DEBUG=1
# OTHERCFLAGS+= -fvisibility=hidden -DTIDY_EXPORT='__attribute__((visibility("default")))'
ifdef SUPPORT_UTF16_ENCODINGS
CFLAGS += -DSUPPORT_UTF16_ENCODINGS=$(SUPPORT_UTF16_ENCODINGS)
endif
ifdef SUPPORT_ASIAN_ENCODINGS
CFLAGS += -DSUPPORT_ASIAN_ENCODINGS=$(SUPPORT_ASIAN_ENCODINGS)
endif
ifdef SUPPORT_ACCESSIBILITY_CHECKS
CFLAGS += -DSUPPORT_ACCESSIBILITY_CHECKS=$(SUPPORT_ACCESSIBILITY_CHECKS)
endif

DEBUGFLAGS=-g
ifdef DMALLOC
DEBUGFLAGS += -DDMALLOC
endif

LIBS=
DEBUGLIBS=-ldmalloc

# Tidy lib related variables
TIDY_MAJOR = 1
TIDY_MINOR = 0

# This will come from autoconf again
LIBPREFIX = lib
LIBSUFFIX = .a
OBJSUF = .o

LIBRARY = $(LIBDIR)/$(LIBPREFIX)$(PROJECT)$(LIBSUFFIX)
AR=ar -r

XSLTPROC = xsltproc

EXES = $(BINDIR)/$(PROJECT) $(BINDIR)/tab2space

DOCS = $(DOCDIR)/quickref.html $(DOCDIR)/tidy.1

CONFIGXML = $(DOCDIR)/tidy-config.xml
HELPXML = $(DOCDIR)/tidy-help.xml

OBJFILES=\
        $(OBJDIR)/access$(OBJSUF)     $(OBJDIR)/attrs$(OBJSUF)      $(OBJDIR)/istack$(OBJSUF) \
        $(OBJDIR)/parser$(OBJSUF)     $(OBJDIR)/tags$(OBJSUF)       $(OBJDIR)/entities$(OBJSUF) \
        $(OBJDIR)/lexer$(OBJSUF)      $(OBJDIR)/pprint$(OBJSUF)     $(OBJDIR)/clean$(OBJSUF) \
        $(OBJDIR)/localize$(OBJSUF)   $(OBJDIR)/config$(OBJSUF)     $(OBJDIR)/alloc$(OBJSUF) \
        $(OBJDIR)/attrask$(OBJSUF)    $(OBJDIR)/attrdict$(OBJSUF)   $(OBJDIR)/attrget$(OBJSUF) \
        $(OBJDIR)/buffio$(OBJSUF)     $(OBJDIR)/fileio$(OBJSUF)     $(OBJDIR)/streamio$(OBJSUF) \
        $(OBJDIR)/tagask$(OBJSUF)     $(OBJDIR)/tmbstr$(OBJSUF)     $(OBJDIR)/utf8$(OBJSUF) \
        $(OBJDIR)/tidylib$(OBJSUF)    $(OBJDIR)/mappedio$(OBJSUF)

CFILES= \
        $(SRCDIR)/access.c       $(SRCDIR)/attrs.c        $(SRCDIR)/istack.c \
        $(SRCDIR)/parser.c       $(SRCDIR)/tags.c         $(SRCDIR)/entities.c \
        $(SRCDIR)/lexer.c        $(SRCDIR)/pprint.c       $(SRCDIR)/clean.c \
        $(SRCDIR)/localize.c     $(SRCDIR)/config.c       $(SRCDIR)/alloc.c \
        $(SRCDIR)/attrask.c      $(SRCDIR)/attrdict.c     $(SRCDIR)/attrget.c \
        $(SRCDIR)/buffio.c       $(SRCDIR)/fileio.c       $(SRCDIR)/streamio.c \
        $(SRCDIR)/tagask.c       $(SRCDIR)/tmbstr.c       $(SRCDIR)/utf8.c \
        $(SRCDIR)/tidylib.c      $(SRCDIR)/mappedio.c

HFILES= $(INCDIR)/platform.h     $(INCDIR)/tidy.h         $(INCDIR)/tidyenum.h \
        $(INCDIR)/buffio.h

LIBHFILES= \
        $(SRCDIR)/access.h       $(SRCDIR)/attrs.h        $(SRCDIR)/attrdict.h \
        $(SRCDIR)/clean.h        $(SRCDIR)/config.h       $(SRCDIR)/entities.h \
        $(SRCDIR)/fileio.h       $(SRCDIR)/forward.h      $(SRCDIR)/lexer.h \
        $(SRCDIR)/mappedio.h     $(SRCDIR)/message.h      $(SRCDIR)/parser.h \
        $(SRCDIR)/pprint.h       $(SRCDIR)/streamio.h     $(SRCDIR)/tags.h \
        $(SRCDIR)/tmbstr.h       $(SRCDIR)/utf8.h         $(SRCDIR)/tidy-int.h \
        $(SRCDIR)/version.h



all:    $(LIBRARY) $(EXES)

doc:    $(DOCS)

$(LIBRARY): $(OBJFILES)
	if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR); fi
	$(AR) $@ $(OBJFILES)
ifdef RANLIB
	$(RANLIB) $@
endif

$(OBJDIR)/%$(OBJSUF):	$(SRCDIR)/%.c $(HFILES) $(LIBHFILES) Makefile
	if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(CC) $(CFLAGS) $(OTHERCFLAGS) -o $@ -c $<

$(BINDIR)/$(PROJECT):	$(APPDIR)/tidy.c $(HFILES) $(LIBRARY)
	if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi
	$(CC) $(CFLAGS) $(OTHERCFLAGS) -o $@ $(APPDIR)/tidy.c -I$(INCDIR) $(LIBRARY)

$(BINDIR)/tab2space: $(APPDIR)/tab2space.c
	if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi
	$(CC) $(CFLAGS) $(OTHERCFLAGS) -o $@ $(APPDIR)/tab2space.c $(LIBS)

$(HELPXML): $(BINDIR)/$(PROJECT)
	$(BINDIR)/$(PROJECT) -xml-help > $@

$(CONFIGXML): $(BINDIR)/$(PROJECT)
	$(BINDIR)/$(PROJECT) -xml-config > $@

$(DOCDIR)/quickref.html: $(DOCDIR)/quickref-html.xsl $(CONFIGXML)
	$(XSLTPROC) -o $@ $(DOCDIR)/quickref-html.xsl $(CONFIGXML)

$(DOCDIR)/tidy.1: $(DOCDIR)/tidy1.xsl $(HELPXML) $(CONFIGXML)
	$(XSLTPROC) -o $@ $(DOCDIR)/tidy1.xsl $(HELPXML)

debug:
	@$(MAKE) CFLAGS='$(CFLAGS) $(DEBUGFLAGS)' LIBS='$(LIBS) $(DEBUGLIBS)' all

clean:
	rm -f $(OBJFILES) $(EXES) $(LIBRARY) $(DOCS) $(HELPXML) $(CONFIGXML) $(OBJDIR)/*.lo
	if [ -d $(OBJDIR)/.libs ]; then rmdir $(OBJDIR)/.libs; fi
	if [ -d $(LIBDIR)/.libs ]; then rmdir $(LIBDIR)/.libs; fi
	if [ "$(OBJDIR)" != "$(TOPDIR)" -a -d $(OBJDIR) ]; then rmdir $(OBJDIR); fi
	if [ "$(LIBDIR)" != "$(TOPDIR)" -a -d $(LIBDIR) ]; then rmdir $(LIBDIR); fi
	if [ "$(BINDIR)" != "$(TOPDIR)" -a -d $(BINDIR) ]; then rmdir $(BINDIR); fi

installhdrs: $(HFILES)
	if [ ! -d "$(incinst)" ]; then mkdir -p "$(incinst)"; fi
	cp -f $(HFILES) "$(incinst)/"

installib: $(LIBRARY)
	if [ ! -d "$(libinst)" ]; then mkdir -p "$(libinst)"; fi
	cp -f $(LIBRARY) "$(libinst)/"

installexes: $(EXES)
	if [ ! -d "$(bininst)" ]; then mkdir -p "$(bininst)"; fi
	cp -f $(EXES) "$(bininst)/"

installmanpage: $(DOCDIR)/tidy.1
	if [ ! -d "$(maninst)/man1" ]; then mkdir -p "$(maninst)/man1"; fi;
	cp -f $(DOCDIR)/tidy.1 "$(maninst)/man1/tidy.1";

install: installhdrs installib installexes installmanpage
