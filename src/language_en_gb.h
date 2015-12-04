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
 *  This array specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDictionary language_en_gb = {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                "en_gb"                                                                      },
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	
	{ TEXT_USING_FONT,
		"You are recommended to use CSS to specify the font and\n"
		"properties such as its size and colour. This will reduce\n"
		"the size of HTML files and make them easier to maintain\n"
		"compared with using <FONT> elements.\n\n"
	},
	{ TEXT_USING_BODY,
		"You are recommended to use CSS to specify page and link colours\n"
	},
	{ TEXT_GENERAL_INFO_PLEA,
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
	{ INFORMATION_NOT_CONVEYED_IMAGE,                "[2.1.1.1]: ensure information not conveyed through colour alone (image)." }, /* Access */
	{ INFORMATION_NOT_CONVEYED_APPLET,               "[2.1.1.2]: ensure information not conveyed through colour alone (applet)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_OBJECT,               "[2.1.1.3]: ensure information not conveyed through colour alone (object)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_SCRIPT,               "[2.1.1.4]: ensure information not conveyed through colour alone (script)."}, /* Access */
	{ INFORMATION_NOT_CONVEYED_INPUT,                "[2.1.1.5]: ensure information not conveyed through colour alone (input)." }, /* Access */
	{ COLOR_CONTRAST_TEXT,                           "[2.2.1.1]: poor colour contrast (text)."                                  }, /* Access */
	{ COLOR_CONTRAST_LINK,                           "[2.2.1.2]: poor colour contrast (link)."                                  }, /* Access */
	{ COLOR_CONTRAST_ACTIVE_LINK,                    "[2.2.1.3]: poor colour contrast (active link)."                           }, /* Access */
	{ COLOR_CONTRAST_VISITED_LINK,                   "[2.2.1.4]: poor colour contrast (visited link)."                          }, /* Access */
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
	{ TidyAltText,
		"This option specifies the default <code>alt=</code> text Tidy uses for "
		"<code>&lt;img&gt;</code> attributes when the <code>alt=</code> attribute "
		"is missing. "
		"<br/>"
		"Use with care, as it is your responsibility to make your documents accessible "
		"to people who cannot see the images. "
	},
	{ TidyXmlPIs,
		"This option specifies if Tidy should change the parsing of processing "
		"instructions to require <code>?&gt;</code> as the terminator rather than "
		"<code>&gt;</code>. "
		"<br/>"
		"This option is automatically set if the input is in XML. "
	},
	{ TidyMakeBare,
		"This option specifies if Tidy should strip Microsoft specific HTML "
		"from Word 2000 documents, and output spaces rather than non-breaking "
		"spaces where they exist in the input. "
	},
	{ TidyCSSPrefix,
		"This option specifies the prefix that Tidy uses for styles rules. "
		"<br/>"
		"By default, <code>c</code> will be used. "
	},
	{ TidyMakeClean,
		"This option specifies if Tidy should perform cleaning of some legacy "
		"presentational tags (currently <code>&lt;i&gt;</code>, "
		"<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> when enclosed within "
		"appropriate inline tags, and <code>&lt;font&gt;</code>). If set to "
		"<code>yes</code> then legacy tags will be replaced with CSS "
		"<code>&lt;style&gt;</code> tags and structural markup as appropriate. "
		,
	},
	{ TidyGDocClean,
		"This option specifies if Tidy should enable specific behavior for "
		"cleaning up HTML exported from Google Docs. "
		,
	},
	{ TidyDoctype,
		"This option specifies the DOCTYPE declaration generated by Tidy. "
		"<br/>"
		"If set to <code>omit</code> the output won't contain a DOCTYPE "
		"declaration. Note this this also implies <code>numeric-entities</code> is "
		"set to <code>yes</code>"
		"<br/>"
		"If set to <code>html5</code> the DOCTYPE is set to "
		"<code>&lt;!DOCTYPE html&gt;</code>."
		"<br/>"
		"If set to <code>auto</code> (the default) Tidy will use an educated guess "
		"based upon the contents of the document."
		"<br/>"
		"If set to <code>strict</code>, Tidy will set the DOCTYPE to the HTML4 or "
		"XHTML1 strict DTD."
		"<br/>"
		"If set to <code>loose</code>, the DOCTYPE is set to the HTML4 or XHTML1 "
		"loose (transitional) DTD."
		"<br/>"
		"Alternatively, you can supply a string for the formal public identifier "
		"(FPI)."
		"<br/>"
		"For example: "
		"<br/>"
		"<code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code>"
		"<br/>"
		"If you specify the FPI for an XHTML document, Tidy will set the "
		"system identifier to an empty string. For an HTML document, Tidy adds a "
		"system identifier only if one was already present in order to preserve "
		"the processing mode of some browsers. Tidy leaves the DOCTYPE for "
		"generic XML documents unchanged. "
		"<br/>"
		"This option does not offer a validation of document conformance. "
	},
	{ TidyDropEmptyElems,
		"This option specifies if Tidy should discard empty elements. "
	},
	{ TidyDropEmptyParas,
		"This option specifies if Tidy should discard empty paragraphs. "
	},
	{ TidyDropFontTags,
		"Deprecated; <em>do not use</em>. This option is destructive to "
		"<code>&lt;font&gt;</code> tags, and it will be removed from future "
		"versions of Tidy. Use the <code>clean</code> option instead. "
		"<br/>"
		"If you do set this option despite the warning it will perform "
		"as <code>clean</code> except styles will be inline instead of put into "
		"a CSS class. <code>&lt;font&gt;</code> tags will be dropped completely "
		"and their styles will not be preserved. "
		"<br/>"
		"If both <code>clean</code> and this option are enabled, "
		"<code>&lt;font&gt;</code> tags will still be dropped completely, and "
		"other styles will be preserved in a CSS class instead of inline. "
		"<br/>"
		"See <code>clean</code> for more information. "
	},
	{ TidyDropPropAttrs,
		"This option specifies if Tidy should strip out proprietary attributes, "
		"such as Microsoft data binding attributes. "
	},
	{ TidyEncloseBlockText,
		"This option specifies if Tidy should insert a <code>&lt;p&gt;</code> "
		"element to enclose any text it finds in any element that allows mixed "
		"content for HTML transitional but not HTML strict. "
	},
	{ TidyEncloseBodyText,
		"This option specifies if Tidy should enclose any text it finds in the "
		"body element within a <code>&lt;p&gt;</code> element."
		"<br/>"
		"This is useful when you want to take existing HTML and use it with a "
		"style sheet. "
	},
	{ TidyEscapeCdata,
		"This option specifies if Tidy should convert "
		"<code>&lt;![CDATA[]]&gt;</code> sections to normal text. "
	},
	{ TidyFixComments,
		"This option specifies if Tidy should replace unexpected hyphens with "
		"<code>=</code> characters when it comes across adjacent hyphens. "
		"<br/>"
		"The default is <code>yes</code>. "
		"<br/>"
		"This option is provided for users of Cold Fusion which uses the "
		"comment syntax: <code>&lt;!--- ---&gt;</code>. "
	},
	{ TidyFixUri,
		"This option specifies if Tidy should check attribute values that carry "
		"URIs for illegal characters and if such are found, escape them as HTML4 "
		"recommends. "
	},
	{ TidyHideComments,
		"This option specifies if Tidy should print out comments. "
	},
	{ TidyCoerceEndTags,
		"This option specifies if Tidy should coerce a start tag into an end tag "
		"in cases where it looks like an end tag was probably intended; "
		"for example, given "
		"<br/>"
		"<code>&lt;span&gt;foo &lt;b&gt;bar&lt;b&gt; baz&lt;/span&gt;</code> "
		"<br/>"
		"Tidy will output "
		"<br/>"
		"<code>&lt;span&gt;foo &lt;b&gt;bar&lt;/b&gt; baz&lt;/span&gt;</code> "
	},
	{ TidyOmitOptionalTags,
		"This option specifies if Tidy should omit optional start tags and end tags "
		"when generating output. "
		"<br/>"
		"Setting this option causes all tags for the <code>&lt;html&gt;</code>, "
		"<code>&lt;head&gt;</code>, and <code>&lt;body&gt;</code> elements to be "
		"omitted from output, as well as such end tags as <code>&lt;/p&gt;</code>, "
		"<code>&lt;/li&gt;</code>, <code>&lt;/dt&gt;</code>, "
		"<code>&lt;/dd&gt;</code>, <code>&lt;/option&gt;</code>, "
		"<code>&lt;/tr&gt;</code>, <code>&lt;/td&gt;</code>, and "
		"<code>&lt;/th&gt;</code>. "
		"<br/>"
		"This option is ignored for XML output. "
	},
	{ TidyHideEndTags,
		"This option is an alias for <code>omit-optional-tags</code>. "
	},
	{ TidyIndentCdata,
		"This option specifies if Tidy should indent "
		"<code>&lt;![CDATA[]]&gt;</code> sections. "
	},
	{ TidyXmlTags,
		"This option specifies if Tidy should use the XML parser rather than the "
		"error correcting HTML parser. "
	},
	{ TidyJoinClasses,
		"This option specifies if Tidy should combine class names to generate "
		"a single, new class name if multiple class assignments are detected on "
		"an element. "
	},
	{ TidyJoinStyles,
		"This option specifies if Tidy should combine styles to generate a single, "
		"new style if multiple style values are detected on an element. "
	},
	{ TidyLogicalEmphasis,
		"This option specifies if Tidy should replace any occurrence of "
		"<code>&lt;i&gt;</code> with <code>&lt;em&gt;</code> and any occurrence of "
		"<code>&lt;b&gt;</code> with <code>&lt;strong&gt;</code>. Any attributes "
		"are preserved unchanged. "
		"<br/>"
		"This option can be set independently of the <code>clean</code> option. "
	},
	{ TidyLowerLiterals,
		"This option specifies if Tidy should convert the value of an attribute "
		"that takes a list of predefined values to lower case. "
		"<br/>"
		"This is required for XHTML documents. "
	},
	{ TidyMergeEmphasis,
		"This option specifies if Tidy should merge nested <code>&lt;b&gt;</code> "
		"and <code>&lt;i&gt;</code> elements; for example, for the case "
		"<br/>"
		"<code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, "
		"<br/>"
		"Tidy will output <code>&lt;b class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
	},
	{ TidyMergeDivs,
		"This option can be used to modify the behavior of <code>clean</code> when "
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
	{ TidyMergeSpans,
		"This option can be used to modify the behavior of <code>clean</code> when "
		"set to <code>yes</code>."
		"<br/>"
		"This option specifies if Tidy should merge nested <code>&lt;span&gt;</code> "
		"such as <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. "
		"<br/>"
		"The algorithm is identical to the one used by <code>merge-divs</code>. "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyNCR,
		"This option specifies if Tidy should allow numeric character references. "
	},
#endif
	{ TidyBlockTags,
		"This option specifies new block-level tags. This option takes a space or "
		"comma separated list of tag names. "
		"<br/>"
		"Unless you declare new tags, Tidy will refuse to generate a tidied file if "
		"the input includes previously unknown tags. "
		"<br/>"
		"Note you can't change the content model for elements such as "
		"<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, "
		"<code>&lt;ol&gt;</code> and <code>&lt;dl&gt;</code>. "
		"<br/>"
		"This option is ignored in XML mode. "
	},
	{ TidyEmptyTags,
		"This option specifies new empty inline tags. This option takes a space "
		"or comma separated list of tag names. "
		"<br/>"
		"Unless you declare new tags, Tidy will refuse to generate a tidied file if "
		"the input includes previously unknown tags. "
		"<br/>"
		"Remember to also declare empty tags as either inline or blocklevel. "
		"<br/>"
		"This option is ignored in XML mode. "
	},
	{ TidyInlineTags,
		"This option specifies new non-empty inline tags. This option takes a "
		"space or comma separated list of tag names. "
		"<br/>"
		"Unless you declare new tags, Tidy will refuse to generate a tidied file if "
		"the input includes previously unknown tags. "
		"<br/>"
		"This option is ignored in XML mode. "
	},
	{ TidyPreTags,
		"This option specifies new tags that are to be processed in exactly the "
		"same way as HTML's <code>&lt;pre&gt;</code> element. This option takes a "
		"space or comma separated list of tag names. "
		"<br/>"
		"Unless you declare new tags, Tidy will refuse to generate a tidied file if "
		"the input includes previously unknown tags. "
		"<br/>"
		"Note you cannot as yet add new CDATA elements. "
		"<br/>"
		"This option is ignored in XML mode. "
	},
	{ TidyNumEntities,
		"This option specifies if Tidy should output entities other than the "
		"built-in HTML entities (<code>&amp;amp;</code>, <code>&amp;lt;</code>, "
		"<code>&amp;gt;</code>, and <code>&amp;quot;</code>) in the numeric rather "
		"than the named entity form. "
		"<br/>"
		"Only entities compatible with the DOCTYPE declaration generated are used. "
		"<br/>"
		"Entities that can be represented in the output encoding are translated "
		"correspondingly. "
	},
	{ TidyHtmlOut,
		"This option specifies if Tidy should generate pretty printed output, "
		"writing it as HTML. "
	},
	{ TidyXhtmlOut,
		"This option specifies if Tidy should generate pretty printed output, "
		"writing it as extensible HTML. "
		"<br/>"
		"This option causes Tidy to set the DOCTYPE and default namespace as "
		"appropriate to XHTML, and will use the corrected value in output "
		"regardless of other sources. "
		"<br/>"
		"For XHTML, entities can be written as named or numeric entities according "
		"to the setting of <code>numeric-entities</code>. "
		"<br/>"
		"The original case of tags and attributes will be preserved, regardless of "
		"other options. "
	},
	{ TidyXmlOut,
		"This option specifies if Tidy should pretty print output, writing it as "
		"well-formed XML. "
		"<br/>"
		"Any entities not defined in XML 1.0 will be written as numeric entities to "
		"allow them to be parsed by an XML parser. "
		"<br/>"
		"The original case of tags and attributes will be preserved, regardless of "
		"other options. "
	},
	{ TidyQuoteAmpersand,
		"This option specifies if Tidy should output unadorned <code>&amp;</code> "
		"characters as <code>&amp;amp;</code>. "
	},
	{ TidyQuoteMarks,
		"This option specifies if Tidy should output <code>&quot;</code> characters "
		"as <code>&amp;quot;</code> as is preferred by some editing environments. "
		"<br/>"
		"The apostrophe character <code>'</code> is written out as "
		"<code>&amp;#39;</code> since many web browsers don't yet support "
		"<code>&amp;apos;</code>. "
	},
	{ TidyQuoteNbsp,
		"This option specifies if Tidy should output non-breaking space characters "
		"as entities, rather than as the Unicode character value 160 (decimal). "
	},
	{ TidyDuplicateAttrs,
		"This option specifies if Tidy should keep the first or last attribute, if "
		"an attribute is repeated, e.g. has two <code>align</code> attributes. "
	},
	{ TidySortAttributes,
		"This option specifies that Tidy should sort attributes within an element "
		"using the specified sort algorithm. If set to <code>alpha</code>, the "
		"algorithm is an ascending alphabetic sort. "
	},
	{ TidyReplaceColor,
		"This option specifies if Tidy should replace numeric values in colour "
		"attributes with HTML/XHTML colour names where defined, e.g. replace "
		"<code>#ffffff</code> with <code>white</code>. "
	},
	{ TidyBodyOnly,
		"This option specifies if Tidy should print only the contents of the "
		"body tag as an HTML fragment. "
		"<br/>"
		"If set to <code>auto</code>, this is performed only if the body tag has "
		"been inferred. "
		"<br/>"
		"Useful for incorporating existing whole pages as a portion of another "
		"page. "
		"<br/>"
		"This option has no effect if XML output is requested. "
	},
	{ TidyUpperCaseAttrs,
		"This option specifies if Tidy should output attribute names in upper "
		"case. "
		"<br/>"
		"The default is <code>no</code>, which results in lower case attribute "
		"names, except for XML input, where the original case is preserved. "
	},
	{ TidyUpperCaseTags,
		"This option specifies if Tidy should output tag names in upper case. "
		"<br/>"
		"The default is <code>no</code> which results in lower case tag names, "
		"except for XML input where the original case is preserved. "
	},
	{ TidyWord2000,
		"This option specifies if Tidy should go to great pains to strip out all "
		"the surplus stuff Microsoft Word 2000 inserts when you save Word "
		"documents as \"Web pages\". It doesn't handle embedded images or VML. "
		"<br/>"
		"You should consider using Word's \"Save As: Web Page, Filtered\". "
	},
	{ TidyAccessibilityCheckLevel,
		"This option specifies what level of accessibility checking, if any, "
		"that Tidy should perform. "
		"<br/>"
		"Level <code>0 (Tidy Classic)</code> is equivalent to Tidy Classic's accessibility "
		"checking. "
		"<br/>"
		"For more information on Tidy's accessibility checking, visit "
		"<a href=\"http://www.html-tidy.org/accessibility/\"> Tidy's Accessibility Page</a>. "
	},
	{ TidyShowErrors,
		"This option specifies the number Tidy uses to determine if further errors "
		"should be shown. If set to <code>0</code>, then no errors are shown. "
	},
	{ TidyShowInfo,
		"This option specifies if Tidy should display info-level messages. "
	},
	{ TidyShowWarnings,
		"This option specifies if Tidy should suppress warnings. This can be "
		"useful when a few errors are hidden in a flurry of warnings. "
	},
	{ TidyBreakBeforeBR,
		"This option specifies if Tidy should output a line break before each "
		"<code>&lt;br&gt;</code> element. "
	},
	{ TidyIndentContent,
		"This option specifies if Tidy should indent block-level tags. "
		"<br/>"
		"If set to <code>auto</code> Tidy will decide whether or not to indent the "
		"content of tags such as <code>&lt;title&gt;</code>, "
		"<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, "
		"<code>&lt;td&gt;</code>, or <code>&lt;p&gt;</code> "
		"based on the content including a block-level element. "
		"<br/>"
		"Setting <code>indent</code> to <code>yes</code> can expose layout bugs in "
		"some browsers. "
		"<br/>"
		"Use the option <code>indent-spaces</code> to control the number of spaces "
		"or tabs output per level of indent, and <code>indent-with-tabs</code> to "
		"specify whether spaces or tabs are used. "
	},
	{ TidyIndentAttributes,
		"This option specifies if Tidy should begin each attribute on a new line. "
	},
	{ TidyIndentSpaces,
		"This option specifies the number of spaces or tabs that Tidy uses to "
		"indent content when <code>indent</code> is enabled. "
		"<br/>"
		"Note that the default value for this option is dependent upon the value of "
		"<code>indent-with-tabs</code> (see also). "
	},
	{ TidyLiteralAttribs,
		"This option specifies how Tidy deals with whitespace characters within "
		"attribute values. "
		"<br/>"
		"If the value is <code>no</code> Tidy normalizes attribute values by "
		"replacing any newline or tab with a single space, and further by replacing "
		"any contiguous whitespace with a single space. "
		"<br/>"
		"To force Tidy to preserve the original, literal values of all attributes "
		"and ensure that whitespace within attribute values is passed "
		"through unchanged, set this option to <code>yes</code>. "
	},
	{ TidyShowMarkup,
		"This option specifies if Tidy should generate a pretty printed version "
		"of the markup. Note that Tidy won't generate a pretty printed version if "
		"it finds significant errors (see <code>force-output</code>). "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyPunctWrap,
		"This option specifies if Tidy should line wrap after some Unicode or "
		"Chinese punctuation characters. "
	},
#endif
	{ TidyBurstSlides,
		"This option has no function and is deprecated. "
	},
	{ TidyTabSize,
		"This option specifies the number of columns that Tidy uses between "
		"successive tab stops. It is used to map tabs to spaces when reading the "
		"input. "
	},
	{ TidyVertSpace,   /* Issue #228 - changed to tri-state */
		"This option specifies if Tidy should add some extra empty lines for "
		"readability. "
		"<br/>"
		"The default is <code>no</code>. "
		"<br/>"
		"If set to <code>auto</code> Tidy will eliminate nearly all newline "
		"characters."
	},
	{ TidyWrapLen,
		"This option specifies the right margin Tidy uses for line wrapping. "
		"<br/>"
		"Tidy tries to wrap lines so that they do not exceed this length. "
		"<br/>"
		"Set <code>wrap</code> to <code>0</code>(zero) if you want to disable line "
		"wrapping. "
	},
	{ TidyWrapAsp,
		"This option specifies if Tidy should line wrap text contained within ASP "
		"pseudo elements, which look like: <code>&lt;% ... %&gt;</code>. "
	},
	{ TidyWrapAttVals,
		"This option specifies if Tidy should line-wrap attribute values, meaning "
		"that if the value of an attribute causes a line to exceed the width "
		"specified by <code>wrap</code>, Tidy will add one or more line breaks to "
		"the value, causing it to be wrapped into multiple lines. "
		"<br/>"
		"Note that this option can be set independently of "
		"<code>wrap-script-literals</code>. "
		"By default Tidy replaces any newline or tab with a single space and "
		"replaces any sequences of whitespace with a single space. "
		"<br/>"
		"To force Tidy to preserve the original, literal values of all attributes, "
		"and ensure that whitespace characters within attribute values are passed "
		"through unchanged, set <code>literal-attributes</code> to "
		"<code>yes</code>. "
	},
	{ TidyWrapJste,
		"This option specifies if Tidy should line wrap text contained within "
		"JSTE pseudo elements, which look like: <code>&lt;# ... #&gt;</code>. "
	},
	{ TidyWrapPhp,
		"This option specifies if Tidy should line wrap text contained within PHP "
		"pseudo elements, which look like: <code>&lt;?php ... ?&gt;</code>. "
	},
	{ TidyWrapScriptlets,
		"This option specifies if Tidy should line wrap string literals that "
		"appear in script attributes. "
		"<br/>"
		"Tidy wraps long script string literals by inserting a backslash character "
		"before the line break. "
	},
	{ TidyWrapSection,
		"This option specifies if Tidy should line wrap text contained within "
		"<code>&lt;![ ... ]&gt;</code> section tags. "
	},
	{ TidyAsciiChars,
		"Can be used to modify behavior of the <code>clean</code> option when set "
		"to <code>yes</code>. "
		"<br/>"
		"If set to <code>yes</code> when <code>clean</code>, "
		"<code>&amp;emdash;</code>, <code>&amp;rdquo;</code>, and other named "
		"character entities are downgraded to their closest ASCII equivalents. "
	},
	{ TidyCharEncoding,
		"This option specifies the character encoding Tidy uses for both the input "
		"and output. "
		"<br/>"
		"For <code>ascii</code> Tidy will accept Latin-1 (ISO-8859-1) character "
		"values, but will use entities for all characters whose value &gt;127. "
		"<br/>"
		"For <code>raw</code>, Tidy will output values above 127 without "
		"translating them into entities. "
		"<br/>"
		"For <code>latin1</code>, characters above 255 will be written as entities. "
		"<br/>"
		"For <code>utf8</code>, Tidy assumes that both input and output are encoded "
		"as UTF-8. "
		"<br/>"
		"You can use <code>iso2022</code> for files encoded using the ISO-2022 "
		"family of encodings e.g. ISO-2022-JP. "
		"<br/>"
		"For <code>mac</code> and <code>win1252</code>, Tidy will accept vendor "
		"specific character values, but will use entities for all characters whose "
		"value &gt;127. "
		"<br/>"
		"For unsupported encodings, use an external utility to convert to and from "
		"UTF-8. "
	},
	{ TidyInCharEncoding,
		"This option specifies the character encoding Tidy uses for the input. See "
		"<code>char-encoding</code> for more info. "
	},
#if SUPPORT_ASIAN_ENCODINGS
	{ TidyLanguage,
		"Currently not used, but this option specifies the language Tidy would use "
		"if it were properly localized. For example: <code>en</code>. "
	},
#endif
#if SUPPORT_UTF16_ENCODINGS
	{ TidyOutputBOM,
		"This option specifies if Tidy should write a Unicode Byte Order Mark "
		"character (BOM; also known as Zero Width No-Break Space; has value of "
		"U+FEFF) to the beginning of the output, and only applies to UTF-8 and "
		"UTF-16 output encodings. "
		"<br/>"
		"If set to <code>auto</code> this option causes Tidy to write a BOM to "
		"the output only if a BOM was present at the beginning of the input. "
		"<br/>"
		"A BOM is always written for XML/XHTML output using UTF-16 output "
		"encodings. "
	},
#endif
	{ TidyOutCharEncoding,
		"This option specifies the character encoding Tidy uses for the output. "
		"<br/>"
		"Note that this may only be different from <code>input-encoding</code> for "
		"Latin encodings (<code>ascii</code>, <code>latin0</code>, "
		"<code>latin1</code>, <code>mac</code>, <code>win1252</code>, "
		"<code>ibm858</code>)."
		"<br/>"
		"See <code>char-encoding</code> for more information"
	},
	{ TidyNewline,
		"The default is appropriate to the current platform. "
		"<br/>"
		"Genrally CRLF on PC-DOS, Windows and OS/2; CR on Classic Mac OS; and LF "
		"everywhere else (Linux, Mac OS X, and Unix). "
	},
	{ TidyErrFile,
		"This option specifies the error file Tidy uses for errors and warnings. "
		"Normally errors and warnings are output to <code>stderr</code>. "
	},
	{ TidyFixBackslash,
		"This option specifies if Tidy should replace backslash characters "
		"<code>\\</code> in URLs with forward slashes <code>/</code>. "
	},
	{ TidyForceOutput,
		"This option specifies if Tidy should produce output even if errors are "
		"encountered. "
		"<br/>"
		"Use this option with care; if Tidy reports an error, this "
		"means Tidy was not able to (or is not sure how to) fix the error, so the "
		"resulting output may not reflect your intention. "
	},
	{ TidyEmacs,
		"This option specifies if Tidy should change the format for reporting "
		"errors and warnings to a format that is more easily parsed by GNU Emacs. "
	},
	{ TidyEmacsFile,
		"Used internally. "
	},
	{ TidyKeepFileTimes,
		"This option specifies if Tidy should keep the original modification time "
		"of files that Tidy modifies in place. "
		"<br/>"
		"Setting the option to <code>yes</code> allows you to tidy files without "
		"changing the file modification date, which may be useful with certain "
		"tools that use the modification date for things such as automatic server "
		"deployment."
		"<br/>"
		"Note this feature is not supported on some platforms. "
	},
	{ TidyOutFile,
		"This option specifies the output file Tidy uses for markup. Normally "
		"markup is written to <code>stdout</code>. "
	},
	{ TidyQuiet,
		"This option specifies if Tidy should output the summary of the numbers "
		"of errors and warnings, or the welcome or informational messages. "
	},
	{ TidySlideStyle,
		"This option has no function and is deprecated. "
	},
	{ TidyMark,
		"This option specifies if Tidy should add a <code>meta</code> element to "
		"the document head to indicate that the document has been tidied. "
		"<br/>"
		"Tidy won't add a meta element if one is already present. "
	},
	{ TidyWriteBack,
		"This option specifies if Tidy should write back the tidied markup to the "
		"same file it read from. "
		"<br/>"
		"You are advised to keep copies of important files before tidying them, as "
		"on rare occasions the result may not be what you expect. "
	},
	{ TidyDecorateInferredUL,
		"This option specifies if Tidy should decorate inferred "
		"<code>&lt;ul&gt;</code> elements with some CSS markup to avoid indentation "
		"to the right. "
	},
	{ TidyPreserveEntities,
		"This option specifies if Tidy should preserve well-formed entities "
		"as found in the input. "
	},
	{ TidyAnchorAsName,
		"This option controls the deletion or addition of the <code>name</code> "
		"attribute in elements where it can serve as anchor. "
		"<br/>"
		"If set to <code>yes</code> a <code>name</code> attribute, if not already "
		"existing, is added along an existing <code>id</code> attribute if the DTD "
		"allows it. "
		"<br/>"
		"If set to <code>no</code> any existing name attribute is removed if an"
		"<code>id</code> attribute exists or has been added. "
	},
	{ TidyPPrintTabs,
		"This option specifies if Tidy should indent with tabs instead of spaces, "
		"assuming <code>indent</code> is <code>yes</code>. "
		"<br/>"
		"Set it to <code>yes</code> to indent using tabs instead of the default "
		"spaces. "
		"<br/>"
		"Use the option <code>indent-spaces</code> to control the number of tabs "
		"output per level of indent. Note that when <code>indent-with-tabs</code> "
		"is enabled the default value of <code>indent-spaces</code> is reset to "
		"<code>1</code>. "
		"<br/>"
		"Note <code>tab-size</code> controls converting input tabs to spaces. Set "
		"it to zero to retain input tabs. "
	},
	{ TidySkipNested,
		"This option specifies that Tidy should skip nested tags when parsing "
		"script and style data. "
	},
	
	/*****************************
	 ** Console Application
	 *****************************/
	{ TC_CAT_DIAGNOSTICS,           "diagnostics"                                                             },
	{ TC_CAT_ENCODING,              "encoding"                                                                },
	{ TC_CAT_MARKUP,                "markup"                                                                  },
	{ TC_CAT_MISC,                  "misc"                                                                    },
	{ TC_CAT_PRETTYPRINT,           "print"                                                                   },
	{ TC_LABEL_COL,                 "column"                                                                  },
	{ TC_LABEL_FILE,                "file"                                                                    },
	{ TC_LABEL_LANG,                "lang"                                                                    },
	{ TC_LABEL_LEVL,                "level"                                                                   },
	{ TC_LABEL_OPT,                 "option"                                                                  },
	{ TC_MAIN_ERROR_LOAD_CONFIG,    "Loading config file \"%s\" failed, err = %d\n"                           },
	{ TC_OPT_ACCESS,
		"do additional accessibility checks (<level> = 0, 1, 2, 3). 0 is "
		"assumed if <level> is missing."
	},
	{ TC_OPT_ASCII,                 "use ISO-8859-1 for input, US-ASCII for output"                           },
	{ TC_OPT_ASHTML,                "force XHTML to well formed HTML"                                         },
	{ TC_OPT_ASXML,                 "convert HTML to well formed XHTML"                                       },
	{ TC_OPT_BARE,                  "strip out smart quotes and em dashes, etc."                              },
	{ TC_OPT_BIG5,                  "use Big5 for both input and output"                                      },
	{ TC_OPT_CLEAN,                 "replace FONT, NOBR and CENTER tags with CSS"                             },
	{ TC_OPT_CONFIG,                "set configuration options from the specified <file>"                     },
	{ TC_OPT_ERRORS,                "show only errors and warnings"                                           },
	{ TC_OPT_FILE,                  "write errors and warnings to the specified <file>"                       },
	{ TC_OPT_GDOC,                  "produce clean version of html exported by Google Docs"                   },
	{ TC_OPT_HELP,                  "list the command line options"                                           },
	{ TC_OPT_HELPCFG,               "list all configuration options"                                          },
	{ TC_OPT_HELPOPT,               "show a description of the <option>"                                      },
	{ TC_OPT_IBM858,                "use IBM-858 (CP850+Euro) for input, US-ASCII for output"                 },
	{ TC_OPT_INDENT,                "indent element content"                                                  },
	{ TC_OPT_ISO2022,               "use ISO-2022 for both input and output"                                  },
	{ TC_OPT_LANGUAGE,              "set the two-letter language code <lang> (for future use)"                },
	{ TC_OPT_LATIN0,                "use ISO-8859-15 for input, US-ASCII for output"                          },
	{ TC_OPT_LATIN1,                "use ISO-8859-1 for both input and output"                                },
	{ TC_OPT_MAC,                   "use MacRoman for input, US-ASCII for output"                             },
	{ TC_OPT_MODIFY,                "modify the original input files"                                         },
	{ TC_OPT_NUMERIC,               "output numeric rather than named entities"                               },
	{ TC_OPT_OMIT,                  "omit optional start tags and end tags"                                   },
	{ TC_OPT_OUTPUT,                "write output to the specified <file>"                                    },
	{ TC_OPT_QUIET,                 "suppress nonessential output"                                            },
	{ TC_OPT_RAW,                   "output values above 127 without conversion to entities"                  },
	{ TC_OPT_SHIFTJIS,              "use Shift_JIS for both input and output"                                 },
	{ TC_OPT_SHOWCFG,               "list the current configuration settings"                                 },
	{ TC_OPT_UPPER,                 "force tags to upper case"                                                },
	{ TC_OPT_UTF16,                 "use UTF-16 for both input and output"                                    },
	{ TC_OPT_UTF16BE,               "use UTF-16BE for both input and output"                                  },
	{ TC_OPT_UTF16LE,               "use UTF-16LE for both input and output"                                  },
	{ TC_OPT_UTF8,                  "use UTF-8 for both input and output"                                     },
	{ TC_OPT_VERSION,               "show the version of Tidy"                                                },
	{ TC_OPT_WIN1252,               "use Windows-1252 for input, US-ASCII for output"                         },
	{ TC_OPT_WRAP,
		"wrap text at the specified <column>. 0 is assumed if <column> is "
		"missing. When this option is omitted, the default of the "
		"configuration option 'wrap' applies."
	},
	{ TC_OPT_XML,                   "specify the input is well formed XML"                                    },
	{ TC_OPT_XMLCFG,                "list all configuration options in XML format"                            },
	{ TC_OPT_XMLHELP,               "list the command line options in XML format"                             },
	
	{ TC_STRING_OUT_OF_MEMORY,      "Out of memory. Bailing out."                                             },
	{ TC_STRING_FATAL_ERROR,        "Fatal error: impossible value for id='%d'.\n"                            },
	{ TC_STRING_FILE_MANIP,         "File manipulation"                                                       },
	{ TC_STRING_PROCESS_DIRECTIVES, "Processing directives"                                                   },
	{ TC_STRING_CHAR_ENCODING,      "Character encodings"                                                     },
	{ TC_STRING_LANG_MUST_SPECIFY,  "A POSIX or Windows locale must be specified.\n"                          },
	{ TC_STRING_LANG_NOT_FOUND,     "Tidy doesn't have language '%s,' will use '%s' instead.\n"               },
	{ TC_STRING_MISC,               "Miscellaneous"                                                           },
	{ TC_STRING_MUST_SPECIFY,       "A Tidy option name must be specified."                                   },
	{ TC_STRING_UNKNOWN_OPTION,     "HTML Tidy: unknown option: %c\n"                                         },
	{ TC_STRING_UNKNOWN_OPTION_B,   "HTML Tidy: unknown option."                                              },
	{ TC_STRING_VERS_A,             "HTML Tidy for %s version %s\n"                                           },
	{ TC_STRING_VERS_B,             "HTML Tidy version %s\n"                                                  },
	{ TC_TXT_HELP_1,
		"\n"
		"%s [options...] [file...] [options...] [file...]\n"
		"Utility to clean up and pretty print HTML/XHTML/XML.\n"
		"\n"
		"This is modern HTML Tidy version %s.\n"
		"\n"
	},
	{ TC_TXT_HELP_2A,
		"Options for HTML Tidy for %s:\n"
	},
	{ TC_TXT_HELP_2B,
		"Options for HTML Tidy:\n"
	},
	{ TC_TXT_HELP_3,
		"Use --optionX valueX for any configuration option \"optionX\" with argument\n"
		"\"valueX\". For a list of the configuration options, use \"-help-config\" or refer\n"
		"to the man page.\n\n"
		
		"Input/Output default to stdin/stdout respectively.\n"
		"\n"
		"Single letter options apart from -f may be combined\n"
		"as in:  tidy -f errs.txt -imu foo.html\n"
		"\n"
		"For more information about HTML Tidy, see\n"
		"  http://www.html-tidy.org/\n"
		"\n"
		"For more information on HTML, see the following:\n"
		"\n"
		"  HTML: Edition for Web Authors (the latest HTML specification)\n"
		"  http://dev.w3.org/html5/spec-author-view\n"
		"\n"
		"  HTML: The Markup Language (an HTML language reference)\n"
		"  http://dev.w3.org/html5/markup/\n"
		"\n"
		"File bug reports at https://github.com/htacg/tidy-html5/issues/\n"
		"or send questions and comments to public-htacg@w3.org.\n"
		"\n"
		"Validate your HTML documents using the W3C Nu Markup Validator:\n"
		"  http://validator.w3.org/nu/"
		"\n\n"
	},
	{ TC_TXT_HELP_CONFIG,
		"\nHTML Tidy Configuration Settings\n\n"
		"Within a file, use the form:\n\n"
		"wrap: 72\n"
		"indent: no\n\n"
		"When specified on the command line, use the form:\n\n"
		"--wrap 72 --indent no\n\n"
	},
	{ TC_TXT_HELP_CONFIG_NAME,      "Name"                                                                    },
	{ TC_TXT_HELP_CONFIG_TYPE,      "Type"                                                                    },
	{ TC_TXT_HELP_CONFIG_ALLW,      "Allowable values"                                                        },
	
	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,      NULL                                                                       }
};


#endif /* language_en_gb_h */
