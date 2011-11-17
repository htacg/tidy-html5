# Makefile [Makefile.am] - for tidy - HTML parser and pretty printer
#
#  CVS Info :
#
#     $Author: arnaud02 $ 
#     $Date: 2008/03/17 12:49:41 $ 
#     $Revision: 1.8 $ 
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

AM_CFLAGS = @CFLAGS@ @WARNING_CFLAGS@

INCLUDES = -I$(top_srcdir)/include

lib_LTLIBRARIES = libtidy.la

libtidy_la_SOURCES = \
	access.c	attrs.c		istack.c	parser.c \
	tags.c		entities.c	lexer.c		pprint.c \
	clean.c		localize.c	config.c	alloc.c \
	attrask.c	attrdict.c	attrget.c	buffio.c \
	fileio.c	streamio.c	tagask.c	tmbstr.c \
	utf8.c		tidylib.c	mappedio.c

libtidy_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-release $(LT_RELEASE) -no-undefined -export-dynamic

HFILES = \
	access.h	attrdict.h	attrs.h		clean.h \
	config.h	entities.h	fileio.h 	forward.h \
	lexer.h		mappedio.h	message.h	parser.h \
	pprint.h	streamio.h	tags.h		tmbstr.h \
	utf8.h		tidy-int.h	version.h

EXTRA_DIST = $(HFILES)
