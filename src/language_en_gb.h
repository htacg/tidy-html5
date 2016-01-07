#ifndef language_en_gb_h
#define language_en_gb_h
/*
 * language_en_gb.h
 * Localization support for HTML Tidy.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#include "language.h"
#include "access.h"
#include "message.h"


/**
 *  This language-specific fuction returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_en_gb(uint n) {
	return n != 1;
}


/**
 *  This array specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_en_gb = { whichPluralForm_en_gb, {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                0,   "en_gb"                                                                      },
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	
	{ TEXT_USING_FONT,              0,
		"You are recommended to use CSS to specify the font and\n"
		"properties such as its size and colour. This will reduce\n"
		"the size of HTML files and make them easier to maintain\n"
		"compared with using <FONT> elements.\n\n"
	},
	{ TEXT_USING_BODY,              0,
		"You are recommended to use CSS to specify page and link colours\n"
	},
	{ TEXT_GENERAL_INFO_PLEA,       0,
		"\n"
		"Would you like to see Tidy in proper, British English? Please consider \n"
		"helping us to localise HTML Tidy. For details please see \n"
		"https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
	},
	
	/*****************************
	 ** Message Severity Level
	 *****************************/
	
	
	/*****************************
	 ** Warnings and Errors
	 *****************************/
	
	/* ReportEncodingWarning */
	
	/* ReportEncodingError */
	
	/* ReportEntityError */
	
	/* ReportAttrError */
	
	/* attribute name */
	
	/* attribute value */
	
	/* attribute name, attribute value */
	
	/* attribute value, attribute name */
	
	/* no arguments */
	
	/* ReportMissingAttr */
	
	/* ReportWarning */
	
	/* HTML5 */
	
	/* ReportNotice */
	
	/* ReportError */
	
	/* no arguments */
	
	/* ReportFatal */
	
	/* */
	
#if SUPPORT_ACCESSIBILITY_CHECKS
	
	/* ReportAccess */
	/*
	 List of error/warning messages.  The error code corresponds to
	 the check that is listed in the AERT (HTML specifications).
	 */
	{ INFORMATION_NOT_CONVEYED_IMAGE,                0, "[2.1.1.1]: ensure information not conveyed through colour alone (image)." }, /* Access */
	{ INFORMATION_NOT_CONVEYED_APPLET,               0, "[2.1.1.2]: ensure information not conveyed through colour alone (applet)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_OBJECT,               0, "[2.1.1.3]: ensure information not conveyed through colour alone (object)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_SCRIPT,               0, "[2.1.1.4]: ensure information not conveyed through colour alone (script)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_INPUT,                0, "[2.1.1.5]: ensure information not conveyed through colour alone (input)." }, /* Access */
	{ COLOR_CONTRAST_TEXT,                           0, "[2.2.1.1]: poor colour contrast (text)."                                  }, /* Access */
	{ COLOR_CONTRAST_LINK,                           0, "[2.2.1.2]: poor colour contrast (link)."                                  }, /* Access */
	{ COLOR_CONTRAST_ACTIVE_LINK,                    0, "[2.2.1.3]: poor colour contrast (active link)."                           }, /* Access */
	{ COLOR_CONTRAST_VISITED_LINK,                   0, "[2.2.1.4]: poor colour contrast (visited link)."                          }, /* Access */
#endif /* SUPPORT_ACCESSIBILITY_CHECKS */
	
	/*****************************
	 ** Options Documentation
	 *****************************/
	/*
	 * As of 2015-November these descriptions are used uniquely by
	 * printXMLDescription from which quickref.html and the Unix
	 * man pages are generated. The xslt for building all
	 * documentation now supports the following tags in descriptions:
	 *    <code>, <em>, <strong>, <br />, <p>
	 * Note that the xslt processor requires <br /> to be self closing!
	 */
	{ TidyMergeDivs,                0,
		"This option can be used to modify the behaviour of <code>clean</code> when "
		"set to <code>yes</code>."
		"<br/>"
		"This option specifies if Tidy should merge nested <code>&lt;div&gt;</code> "
		"such as <code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. "
		"<br/>"
		"If set to <code>auto</code> the attributes of the inner "
		"<code>&lt;div&gt;</code> are moved to the outer one. Nested "
		"<code>&lt;div&gt;</code> with <code>id</code> attributes are <em>not</em> "
		"merged. "
		"<br/>"
		"If set to <code>yes</code> the attributes of the inner "
		"<code>&lt;div&gt;</code> are discarded with the exception of "
		"<code>class</code> and <code>style</code>. "
	},
	{ TidyMergeSpans,               0,
		"This option can be used to modify the behaviour of <code>clean</code> when "
		"set to <code>yes</code>."
		"<br/>"
		"This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
		"such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
		"<br/>"
		"The algorithm is identical to the one used by <code>merge-divs</code>. "
	},
	{ TidyReplaceColor,             0,
		"This option specifies if Tidy should replace numeric values in colour "
		"attributes with HTML/XHTML colour names where defined, e.g. replace "
		"<code>#ffffff</code> with <code>white</code>. "
	},
	
	/*****************************
	 ** Console Application
	 *****************************/
	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,      0,   NULL                                                                       }
}};


#endif /* language_en_gb_h */
