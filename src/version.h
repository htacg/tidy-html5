/* version information

  (c) 2007-2015 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

#ifdef RELEASE_DATE
static const char TY_(release_date)[] = RELEASE_DATE;
#else
static const char TY_(release_date)[] = "1970/01/01";
#endif
#ifdef LIBTIDY_VERSION
static const char TY_(library_version)[] = LIBTIDY_VERSION;
#else
static const char TY_(library_version)[] = "5.0.0";
#endif

/* eof */
