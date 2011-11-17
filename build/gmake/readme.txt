This Makefile works on most Unix platforms.  Although, by default, it
runs gcc, by setting the CC macro, it runs with many C compilers.

You can override the default build options by setting environment 
variables of the same name as the corresponding macro: DMALLOC,
SUPPORT_ACCESSIBILITY_CHECKS, SUPPORT_UTF16_ENCODINGS and
SUPPORT_ASIAN_ENCODINGS.  

$ DMALLOC=1 gmake

Note this Makefile will only run with gmake.  But you should be able
to easily locate a pre-built executable for your platform.

To customize the location of output files or install locations, just
edit the Makefile.  There are variable definitions for just about 
everything, so you shouldn't have to alter the build rules.
