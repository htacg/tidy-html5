#ifndef language_en_h
#define language_en_h
/*
 * language_en.h
 * Localization support for HTML Tidy.
 *
 * This file consists of the strings for Tidy's base language and is a
 * required localization for Tidy to compile and work. Unlike the other
 * localization files this file is NOT machine-generated.
 *
 * This file also serves as the master template for generating additional
 * language localizations. As such do not edit PO files for this language;
 * modify this file directly.
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_en(uint n) {
    /* Plural-Forms: nplurals=2; */
    return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 *
 *  This file serves as the master template for generating `gettext`
 *  PO and POT files using our `potool.rb` script. Certain comments
 *  entered below will be included in the PO/POT files as developer
 *  comments. To enable this, use only standard C-style comments that
 *  begin immediately after the opening brace without whitespace.
 */

static languageDefinition language_en = { whichPluralForm_en, {
    /***************************************
     ** This MUST be present and first.
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                0,   "en"
    },

    /*********************************************************************
     ** Options Documentation
     **  As of 2016-January these descriptions are used uniquely by the
     **  console application but are made available for LibTidy users as
     **  well. Because we generate documentation from these descriptions
     **  it's important to use ONLY the following tags:
     **    <code>, <em>, <strong>, <br/>, <p>
     **  Note that the xslt processor requires <br/> to be self closing!
     ** @remark enum source is TidyOptionId
     *********************************************************************/
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAccessibilityCheckLevel,  0,
        "This option specifies what level of accessibility checking, if any, "
        "that Tidy should perform."
        "<br/>"
        "Level <var>0 (Tidy Classic)</var> does not perform any specific WCAG "
        "accessibility checks."
        "<br/>"
        "Other values enable additional checking in accordance with the Web "
        "Content Accessibility Guidelines (WCAG) version 1.0, with each option "
        "adding an increased amount of lower priority checks."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAltText,                  0,
        "This option specifies the default <code>alt</code> text Tidy uses for "
        "<code>&lt;img&gt;</code> attributes when the <code>alt</code> "
        "attribute is missing."
        "<br/>"
        "Use with care, as it is your responsibility to make your documents "
        "accessible to people who cannot see the images."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAnchorAsName,             0,
        "This option controls the deletion or addition of the "
        "<code>name</code> attribute in elements where it can serve as anchor."
        "<br/>"
        "If set to <var>yes</var>, a <code>name</code> attribute, if not "
        "already present, is added along an existing <code>id</code> attribute "
        "if the DTD allows it."
        "<br/>"
        "If set to <var>no</var>, any existing <code>name</code> attribute is "
        "removed if an <code>id</code> attribute is present or has been added."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyAsciiChars,               0,
        "Can be used to modify behavior of the <code>clean</code> option when "
        "set to <var>yes</var>."
        "<br/>"
        "If set to <var>yes</var> when using <code>clean</code>, "
        "<code>&amp;emdash;</code>, <code>&amp;rdquo;</code>, and other named "
        "character entities are downgraded to their closest ASCII equivalents."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyBlockTags,                0,
        "This option specifies new block-level tags. This option takes a "
        "space- or comma-separated list of tag names."
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied "
        "file if the input includes previously unknown tags."
        "<br/>"
        "Note you can't change the content model for elements such as "
        "<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, "
        "<code>&lt;ol&gt;</code> and <code>&lt;dl&gt;</code>."
        "<br/>"
        "This option is ignored in XML mode."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyBodyOnly,                 0,
        "This option specifies if Tidy should print only the contents of the "
        "<code>body</code> tag as an HTML fragment."
        "<br/>"
        "If set to <var>auto</var>, then this is performed only if the "
        "<code>body</code> tag has been inferred."
        "<br/>"
        "This option can be useful for tidying snippets of HTML, or for "
        "extracting HTML from a complete document for re-used elsewhere."
        "<br/>"
        "This option has no effect if XML output is requested."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyBreakBeforeBR,            0,
        "This option specifies if Tidy should output a line break before each "
        "<code>&lt;br&gt;</code> element."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyCharEncoding,             0,
        "This option specifies the character encoding Tidy uses for both the "
        "input and output."
        "<br/>"
        "For <var>ascii</var> Tidy will accept Latin-1 (ISO-8859-1) character "
        "values, but will use entities for all characters of value &gt;127."
        "<br/>"
        "For <var>raw</var>, Tidy will output values above 127 without "
        "translating them into entities. "
        "<br/>"
        "For <var>latin1</var>, characters above 255 will be written as "
        "entities."
        "<br/>"
        "For <var>utf8</var>, Tidy assumes that both input and output are "
        "encoded as UTF-8. "
        "<br/>"
        "You can use <var>iso2022</var> for files encoded using the ISO-2022 "
        "family of encodings e.g. ISO-2022-JP."
        "<br/>"
        "For <var>mac</var> and <var>win1252</var>, Tidy will accept vendor "
        "specific character values, but will use entities for all characters "
        "of value &gt;127."
        "<br/>"
        "For unsupported encodings, use an external utility to convert to and "
        "from UTF-8."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyCoerceEndTags,            0,
        "This option specifies if Tidy should coerce a start tag into an end "
        "tag in cases where it looks like an end tag was probably intended; "
        "for example, given "
        "<br/>"
        "<code>&lt;span&gt;foo &lt;b&gt;bar&lt;b&gt; baz&lt;/span&gt;</code>"
        "<br/>"
        "Tidy will output "
        "<br/>"
        "<code>&lt;span&gt;foo &lt;b&gt;bar&lt;/b&gt; baz&lt;/span&gt;</code>"
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyConsoleWidth,             0,
        "This option specifies the maximum width of messages that Tidy, "
        "toutputs, hat is, the point that Tidy starts to word wrap messages."
        "<br/>"
        "In no value is specified, then in general the default of 80 "
        "characters will be used. However, when running in an interactive "
        "shell the Tidy console application will attempt to determine your "
        "console size. If you prefer a fixed size despite the console size, "
        "then set this option."
        "<br/>"
        "Note that when using the <code>file</code> option or piping any output "
        "to a file, then the width of the interactive shell will be ignored."
        "<br/>"
        "Specifying <var>0</var> will disable Tidy's word wrapping entirely."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyCSSPrefix,                0,
        "This option specifies the prefix that Tidy uses when creating new "
        "style rules."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyDecorateInferredUL,       0,
        "This option specifies if Tidy should decorate inferred "
        "<code>&lt;ul&gt;</code> elements with some CSS markup to avoid "
        "indentation to the right."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyDoctype,                  0,
        "This option specifies the DOCTYPE declaration generated by Tidy."
        "<br/>"
        "If set to <var>omit</var> the output won't contain a DOCTYPE "
        "declaration. Note that this this also implies "
        "<code>numeric-entities</code> is set to <var>yes</var>."
        "<br/>"
        "If set to <var>html5</var> the DOCTYPE is set to "
        "<code>&lt;!DOCTYPE html&gt;</code>."
        "<br/>"
        "If set to <var>auto</var> Tidy will use an educated guess based upon "
        "the contents of the document."
        "<br/>"
        "If set to <var>strict</var>, Tidy will set the DOCTYPE to the HTML4 "
        "or XHTML1 strict DTD."
        "<br/>"
        "If set to <var>loose</var>, the DOCTYPE is set to the HTML4 or XHTML1 "
        "loose (transitional) DTD."
        "<br/>"
        "Alternatively, you can supply a string for the formal public "
        "identifier (FPI)."
        "<br/>"
        "For example: "
        "<br/>"
        "<code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code>"
        "<br/>"
        "If you specify the FPI for an XHTML document, Tidy will set the "
        "system identifier to an empty string. For an HTML document, Tidy adds "
        "a system identifier only if one was already present in order to "
        "preserve the processing mode of some browsers. Tidy leaves the "
        "DOCTYPE for generic XML documents unchanged."
        "<br/>"
        "This option does not offer a validation of document conformance."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyDropEmptyElems,           0,
        "This option specifies if Tidy should discard empty elements."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyDropEmptyParas,           0,
        "This option specifies if Tidy should discard empty paragraphs."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyDropPropAttrs,            0,
        "This option specifies if Tidy should strip out proprietary "
        "attributes, such as Microsoft data binding attributes. Additionally "
        "attributes that aren't permitted in the output version of HTML will "
        "be dropped if used with <code>strict-tags-attributes</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyDuplicateAttrs,           0,
        "This option specifies if Tidy should keep the first or last attribute "
        "in event an attribute is repeated, e.g. has two <code>align</code> "
        "attributes."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEmacs,                    0,
        "This option specifies if Tidy should change the format for reporting "
        "errors and warnings to a format that is more easily parsed by "
        "GNU Emacs."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEmptyTags,                0,
        "This option specifies new empty inline tags. This option takes a "
        "space- or comma-separated list of tag names."
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied "
        "file if the input includes previously unknown tags."
        "<br/>"
        "Remember to also declare empty tags as either inline or blocklevel."
        "<br/>"
        "This option is ignored in XML mode."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEncloseBlockText,         0,
        "This option specifies if Tidy should insert a <code>&lt;p&gt;</code> "
        "element to enclose any text it finds in any element that allows mixed "
        "content for HTML transitional but not HTML strict."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEncloseBodyText,          0,
        "This option specifies if Tidy should enclose any text it finds in the "
        "body element within a <code>&lt;p&gt;</code> element."
        "<br/>"
        "This is useful when you want to take existing HTML and use it with a "
        "style sheet."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyErrFile,                  0,
        "This option specifies the error file Tidy uses for errors and "
        "warnings. Normally errors and warnings are output to "
        "<code>stderr</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEscapeCdata,              0,
        "This option specifies if Tidy should convert "
        "<code>&lt;![CDATA[]]&gt;</code> sections to normal text."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyEscapeScripts,          0,
        "This option causes items that look like closing tags, like "
        "<code>&lt;/g</code>, to be escaped to <code>&lt;\\/g</code>. Set "
        "this option to <var>no</var> if you do not want this."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyFixBackslash,             0,
        "This option specifies if Tidy should replace backslash characters "
        "<code>\\</code> in URLs with forward slashes <code>/</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyFixComments,              0,
        "This option specifies if Tidy should replace unexpected hyphens with "
        "<code>=</code> characters when it comes across adjacent hyphens."
        "<br/>"
        "This option is provided for users of Cold Fusion which uses the "
        "comment syntax: <code>&lt;!--- ---&gt;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyFixUri,                   0,
        "This option specifies if Tidy should check attribute values that "
        "carry URIs for illegal characters, and if such are found, escape "
        "them as HTML4 recommends."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyForceOutput,              0,
        "This option specifies if Tidy should produce output even if errors "
        " are encountered."
        "<br/>"
        "Use this option with care; if Tidy reports an error, this means that "
        "Tidy was not able to (or is not sure how to) fix the error, so the "
        "resulting output may not reflect your intention."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyGDocClean,                0,
        "This option specifies if Tidy should enable specific behavior for "
        "cleaning up HTML exported from Google Docs."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyHideComments,             0,
        "This option specifies if Tidy should print out comments."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyHtmlOut,                  0,
        "This option specifies if Tidy should generate pretty printed output, "
        "writing it as HTML."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyInCharEncoding,           0,
        "This option specifies the character encoding Tidy uses for the input. "
        "See <code>char-encoding</code> for more information."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyIndentAttributes,         0,
        "This option specifies if Tidy should begin each attribute on a new "
        "line."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyIndentCdata,              0,
        "This option specifies if Tidy should indent "
        "<code>&lt;![CDATA[]]&gt;</code> sections."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyIndentContent,            0,
        "This option specifies if Tidy should indent block-level tags."
        "<br/>"
        "If set to <var>auto</var> Tidy will decide whether or not to indent "
        "the content of tags such as "
        "<code>&lt;title&gt;</code>, "
        "<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, "
        "<code>&lt;li&gt;</code>, "
        "<code>&lt;td&gt;</code>, or "
        "<code>&lt;p&gt;</code> based on the content including a block-level "
        "element."
        "<br/>"
        "Setting <code>indent</code> to <var>yes</var> can expose layout bugs "
        "in some browsers."
        "<br/>"
        "Use the option <code>indent-spaces</code> to control the number of "
        "spaces or tabs output per level of indent, and "
        "<code>indent-with-tabs</code> to specify whether spaces or tabs are "
        "used."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyIndentSpaces,             0,
        "This option specifies the number of spaces or tabs that Tidy uses to "
        "indent content when <code>indent</code> is enabled."
        "<br/>"
        "Note that the default value for this option is dependent upon the "
        "value of <code>indent-with-tabs</code> (see also)."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyInlineTags,               0,
        "This option specifies new non-empty inline tags. This option takes a "
        "space- or comma-separated list of tag names."
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied "
        "file if the input includes previously unknown tags."
        "<br/>"
        "This option is ignored in XML mode."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyJoinClasses,              0,
        "This option specifies if Tidy should combine class names to generate "
        "a single, new class name if multiple class assignments are detected "
        "on an element."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyJoinStyles,               0,
        "This option specifies if Tidy should combine styles to generate a "
        "single, new style if multiple style values are detected on an "
        "element."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyKeepFileTimes,            0,
        "This option specifies if Tidy should keep the original modification "
        "time of files that Tidy modifies in place."
        "<br/>"
        "Setting the option to <var>yes</var> allows you to tidy files without "
        "changing the file modification date, which may be useful with certain "
        "tools that use the modification date for things such as automatic "
        "server deployment."
        "<br/>"
        "Note this feature is not supported on some platforms."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyLiteralAttribs,           0,
        "This option specifies how Tidy deals with whitespace characters "
        "within attribute values."
        "<br/>"
        "If the value is <var>no</var> Tidy normalizes attribute values by "
        "replacing any newline or tab with a single space, and further b "
        "replacing any contiguous whitespace with a single space."
        "<br/>"
        "To force Tidy to preserve the original, literal values of all "
        "attributes and ensure that whitespace within attribute values is "
        "passed through unchanged, set this option to <var>yes</var>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyLogicalEmphasis,          0,
        "This option specifies if Tidy should replace any occurrence of "
        "<code>&lt;i&gt;</code> with <code>&lt;em&gt;</code> "
        "and any occurrence of "
        "<code>&lt;b&gt;</code> with <code>&lt;strong&gt;</code>. "
        "Any attributes are preserved unchanged. "
        "<br/>"
        "This option can be set independently of the <code>clean</code> option."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyLowerLiterals,            0,
        "This option specifies if Tidy should convert the value of a "
        "attribute that takes a list of predefined values to lower case."
        "<br/>"
        "This is required for XHTML documents."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMakeBare,                 0,
        "This option specifies if Tidy should strip Microsoft specific HTML "
        "from Word 2000 documents, and output spaces rather than non-breaking "
        "spaces where they exist in the input."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMakeClean,                0,
        "This option specifies if Tidy should perform cleaning of some legacy "
        "presentational tags (currently "
        "<code>&lt;i&gt;</code>, "
        "<code>&lt;b&gt;</code>, "
        "<code>&lt;center&gt;</code> "
        "when enclosed within appropriate inline tags, and "
        "<code>&lt;font&gt;</code>). If set to <var>yes</var> then legacy tags "
        "will be replaced with CSS "
        "<code>&lt;style&gt;</code> tags and structural markup as appropriate."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMark,                     0,
        "This option specifies if Tidy should add a <code>meta</code> element "
        "to the document head to indicate that the document has been tidied."
        "<br/>"
        "Tidy won't add a meta element if one is already present."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMergeDivs,                0,
        "This option can be used to modify the behavior of <code>clean</code> "
        "when set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested "
        "<code>&lt;div&gt;</code> "
        "such as "
        "<code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>."
        "<br/>"
        "If set to <var>auto</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are moved to the outer one. Nested "
        "<code>&lt;div&gt;</code> with <code>id</code> attributes are "
        "<em>not</em> merged."
        "<br/>"
        "If set to <var>yes</var> the attributes of the inner "
        "<code>&lt;div&gt;</code> are discarded with the exception of "
        "<code>class</code> and <code>style</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMergeEmphasis,            0,
        "This option specifies if Tidy should merge nested "
        "<code>&lt;b&gt;</code> and "
        "<code>&lt;i&gt;</code> elements; for example, for the case "
        "<br/>"
        "<code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, "
        "<br/>"
        "Tidy will output <code>&lt;b class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyMergeSpans,               0,
        "This option can be used to modify the behavior of <code>clean</code> "
        "when set to <var>yes</var>."
        "<br/>"
        "This option specifies if Tidy should merge nested "
        "<code>&lt;span&gt;</code> such as "
        "<code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>."
        "<br/>"
        "The algorithm is identical to the one used by <code>merge-divs</code>."
    },
#if SUPPORT_ASIAN_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyNCR,                      0,
        "This option specifies if Tidy should allow numeric character "
        "references."
    },
#endif
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyNewline,                  0,
        "The default is appropriate to the current platform."
        "<br/>"
        "Genrally CRLF on PC-DOS, Windows and OS/2; CR on Classic Mac OS; and "
        "LF everywhere else (Linux, Mac OS X, and Unix)."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyNumEntities,              0,
        "This option specifies if Tidy should output entities other than the "
        "built-in HTML entities ("
        "<code>&amp;amp;</code>, "
        "<code>&amp;lt;</code>, "
        "<code>&amp;gt;</code>, and "
        "<code>&amp;quot;</code>) "
        "in the numeric rather than the named entity form."
        "<br/>"
        "Only entities compatible with the DOCTYPE declaration generated are "
        "used."
        "<br/>"
        "Entities that can be represented in the output encoding are translated "
        "correspondingly."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyOmitOptionalTags,         0,
        "This option specifies if Tidy should omit optional start tags and end "
        "tags when generating output. "
        "<br/>"
        "Setting this option causes all tags for the "
        "<code>&lt;html&gt;</code>, "
        "<code>&lt;head&gt;</code>, and "
        "<code>&lt;body&gt;</code> "
        "elements to be omitted from output, as well as such end tags as "
        "<code>&lt;/p&gt;</code>, "
        "<code>&lt;/li&gt;</code>, <code>&lt;/dt&gt;</code>, "
        "<code>&lt;/dd&gt;</code>, <code>&lt;/option&gt;</code>, "
        "<code>&lt;/tr&gt;</code>, <code>&lt;/td&gt;</code>, and "
        "<code>&lt;/th&gt;</code>."
        "<br/>"
        "This option is ignored for XML output."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyOutCharEncoding,          0,
        "This option specifies the character encoding Tidy uses for output."
        "<br/>"
        "Note that this may only be different from <code>input-encoding</code> "
        "for Latin encodings (<var>ascii</var>, <var>latin0</var>, "
        "<var>latin1</var>, <var>mac</var>, <var>win1252</var>, "
        "<var>ibm858</var>)."
        "<br/>"
        "See <code>char-encoding</code> for more information."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyOutFile,                  0,
        "This option specifies the output file Tidy uses for markup. Normally "
        "markup is written to <code>stdout</code>."
    },
#if SUPPORT_UTF16_ENCODINGS
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyOutputBOM,                0,
        "This option specifies if Tidy should write a Unicode Byte Order Mark "
        "character (BOM; also known as Zero Width No-Break Space; has value of "
        "U+FEFF) to the beginning of the output, and only applies to UTF-8 and "
        "UTF-16 output encodings."
        "<br/>"
        "If set to <var>auto</var> this option causes Tidy to write a BOM to "
        "the output only if a BOM was present at the beginning of the input."
        "<br/>"
        "A BOM is always written for XML/XHTML output using UTF-16 output "
        "encodings."
    },
#endif
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyPPrintTabs,               0,
        "This option specifies if Tidy should indent with tabs instead of "
        "spaces, assuming <code>indent</code> is <var>yes</var>."
        "<br/>"
        "Set it to <var>yes</var> to indent using tabs instead of the default "
        "spaces."
        "<br/>"
        "Use the option <code>indent-spaces</code> to control the number of "
        "tabs output per level of indent. Note that when "
        "<code>indent-with-tabs</code> is enabled the default value of "
        "<code>indent-spaces</code> is reset to <var>1</var>."
        "<br/>"
        "Note <code>tab-size</code> controls converting input tabs to spaces. "
        "Set it to zero to retain input tabs."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyPreserveEntities,         0,
        "This option specifies if Tidy should preserve well-formed entities "
        "as found in the input."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyPreTags,                  0,
        "This option specifies new tags that are to be processed in exactly "
        "the same way as HTML's <code>&lt;pre&gt;</code> element. This option "
        "takes a space- or comma-separated list of tag names."
        "<br/>"
        "Unless you declare new tags, Tidy will refuse to generate a tidied "
        "file if the input includes previously unknown tags."
        "<br/>"
        "Note you cannot as yet add new CDATA elements."
        "<br/>"
        "This option is ignored in XML mode."
    },
#if SUPPORT_ASIAN_ENCODINGS
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyPunctWrap,                0,
        "This option specifies if Tidy should line wrap after some Unicode or "
        "Chinese punctuation characters."
    },
#endif
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyQuiet,                    0,
        "This option specifies if Tidy should output the summary of the "
        "numbers of errors and warnings, or the welcome or informational "
        "messages."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyQuoteAmpersand,           0,
        "This option specifies if Tidy should output unadorned "
        "<code>&amp;</code> characters as <code>&amp;amp;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyQuoteMarks,               0,
        "This option specifies if Tidy should output <code>&quot;</code> "
        "characters as <code>&amp;quot;</code> as is preferred by some editing "
        "environments."
        "<br/>"
        "The apostrophe character <code>'</code> is written out as "
        "<code>&amp;#39;</code> since many web browsers don't yet support "
        "<code>&amp;apos;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyQuoteNbsp,                0,
        "This option specifies if Tidy should output non-breaking space "
        "characters as entities, rather than as the Unicode character "
        "value 160 (decimal)."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyReplaceColor,             0,
        "This option specifies if Tidy should replace numeric values in color "
        "attributes with HTML/XHTML color names where defined, e.g. replace "
        "<code>#ffffff</code> with <code>white</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyShowErrors,               0,
        "This option specifies the number Tidy uses to determine if further "
        "errors should be shown. If set to <var>0</var>, then no errors are "
        "shown."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyShowInfo,                 0,
        "This option specifies if Tidy should display info-level messages."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyShowMarkup,               0,
        "This option specifies if Tidy should generate a pretty printed "
        "version of the markup. Note that Tidy won't generate a pretty printed "
        "version if it finds significant errors "
        "(see <code>force-output</code>)."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyShowWarnings,             0,
        "This option specifies if Tidy should suppress warnings. This can be "
        "useful when a few errors are hidden in a flurry of warnings."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidySkipNested,               0,
        "This option specifies that Tidy should skip nested tags when parsing "
        "script and style data."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidySortAttributes,           0,
        "This option specifies that Tidy should sort attributes within an "
        "element using the specified sort algorithm. If set to "
        "<var>alpha</var>, the algorithm is an ascending alphabetic sort."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyStrictTagsAttr,           0,
        "This options ensures that tags and attributes are applicable for the "
        "version of HTML that Tidy outputs. When set to <var>yes</var> (the "
        "default) and the output document type is a strict doctype, then Tidy "
        "will report errors. If the output document type is a loose or "
        "transitional doctype, then Tidy will report warnings."
        "<br/>"
        "Additionally if <code>drop-proprietary-attributes</code> is enabled, "
        "then not applicable attributes will be dropped, too."
        "<br/>"
        "When set to <var>no</var>, these checks are not performed."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyTabSize,                  0,
        "This option specifies the number of columns that Tidy uses between "
        "successive tab stops. It is used to map tabs to spaces when reading "
        "the input."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyUpperCaseAttrs,           0,
        "This option specifies if Tidy should output attribute names in upper "
        "case."
        "<br/>"
        "The default is <var>no</var>, which results in lower case attribute "
        "names, except for XML input, where the original case is preserved."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyUpperCaseTags,            0,
        "This option specifies if Tidy should output tag names in upper case."
        "<br/>"
        "The default is <var>no</var> which results in lower case tag names, "
        "except for XML input where the original case is preserved."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyUseCustomTags,          0,
        "This option enables the use of tags for autonomous custom elements, "
        "e.g. &lt;flag-icon&gt; with Tidy. Custom tags are disabled if this "
        "value is <var>no</var>. Other settings - <var>blocklevel</var>, "
        "<var>empty</var>, <var>inline</var>, and <var>pre</var> will treat "
        "<em>all</em> detected custom tags accordingly."
        "<br/>"
        "The use of <code>new-blocklevel-tags</code>, "
        "<code>new-empty-tags</code>, <code>new-inline-tags</code>, or "
        "<code>new-pre-tags</code> will override the treatment of custom tags "
        "by this configuration option. This may be useful if you have "
        "different types of custom tags."
        "<br/>"
        "When enabled these tags are determined during the processing of your "
        "document using opening tags; matching closing tags will be recognized "
        "accordingly, and unknown closing tags will be discarded."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyVertSpace,                0,
        "This option specifies if Tidy should add some extra empty lines for "
        "readability."
        "<br/>"
        "The default is <var>no</var>."
        "<br/>"
        "If set to <var>auto</var> Tidy will eliminate nearly all newline "
        "characters."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWord2000,                 0,
        "This option specifies if Tidy should go to great pains to strip out "
        "all the surplus stuff Microsoft Word inserts when you save Word "
        "documents as \"Web pages\". It doesn't handle embedded images or VML."
        "<br/>"
        "You should consider using Word's \"Save As: Web Page, Filtered\"."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapAsp,                  0,
        "This option specifies if Tidy should line wrap text contained within "
        "ASP pseudo elements, which look like: <code>&lt;% ... %&gt;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapAttVals,              0,
        "This option specifies if Tidy should line-wrap attribute values, "
        "meaning that if the value of an attribute causes a line to exceed the "
        "width specified by <code>wrap</code>, Tidy will add one or more line "
        "breaks to the value, causing it to be wrapped into multiple lines."
        "<br/>"
        "Note that this option can be set independently of "
        "<code>wrap-script-literals</code>. "
        "By default Tidy replaces any newline or tab with a single space and "
        "replaces any sequences of whitespace with a single space."
        "<br/>"
        "To force Tidy to preserve the original, literal values of all "
        "attributes, and to ensure that whitespace characters within attribute "
        "values are passed through unchanged, set "
        "<code>literal-attributes</code> to <var>yes</var>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapJste,                 0,
        "This option specifies if Tidy should line wrap text contained within "
        "JSTE pseudo elements, which look like: <code>&lt;# ... #&gt;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapLen,                  0,
        "This option specifies the right margin Tidy uses for line wrapping."
        "<br/>"
        "Tidy tries to wrap lines so that they do not exceed this length."
        "<br/>"
        "Set <code>wrap</code> to <var>0</var>(zero) if you want to disable "
        "line wrapping. "
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapPhp,                  0,
        "This option specifies if Tidy should line wrap text contained within "
        "PHP pseudo elements, which look like: "
        "<code>&lt;?php ... ?&gt;</code>."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapScriptlets,           0,
        "This option specifies if Tidy should line wrap string literals that "
        "appear in script attributes."
        "<br/>"
        "Tidy wraps long script string literals by inserting a backslash "
        "character before the line break."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWrapSection,              0,
        "This option specifies if Tidy should line wrap text contained within "
        "<code>&lt;![ ... ]&gt;</code> section tags."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyWriteBack,                0,
        "This option specifies if Tidy should write back the tidied markup to "
        "the same file it read from."
        "<br/>"
        "You are advised to keep copies of important files before tidying "
        "them, as on rare occasions the result may not be what you expect."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyXhtmlOut,                 0,
        "This option specifies if Tidy should generate pretty printed output, "
        "writing it as extensible HTML."
        "<br/>"
        "This option causes Tidy to set the DOCTYPE and default namespace as "
        "appropriate to XHTML, and will use the corrected value in output "
        "regardless of other sources."
        "<br/>"
        "For XHTML, entities can be written as named or numeric entities "
        "according  to the setting of <code>numeric-entities</code>."
        "<br/>"
        "The original case of tags and attributes will be preserved, "
        "regardless of other options."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyXmlDecl,                  0,
        "This option specifies if Tidy should add the XML declaration when "
        "outputting XML or XHTML."
        "<br/>"
        "Note that if the input already includes an "
        "<code>&lt;?xml ... ?&gt;</code> "
        "declaration then this option will be ignored."
        "<br/>"
        "If the encoding for the output is different from <var>ascii</var>, "
        "one of the <var>utf*</var> encodings, or <var>raw</var>, then the "
        "declaration is always added as required by the XML standard."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyXmlOut,                   0,
        "This option specifies if Tidy should pretty print output, writing it "
        "as well-formed XML."
        "<br/>"
        "Any entities not defined in XML 1.0 will be written as numeric "
        "entities to allow them to be parsed by an XML parser."
        "<br/>"
        "The original case of tags and attributes will be preserved, "
        "regardless of other options."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyXmlPIs,                   0,
        "This option specifies if Tidy should change the parsing of processing "
        "instructions to require <code>?&gt;</code> as the terminator rather "
        "than <code>&gt;</code>."
        "<br/>"
        "This option is automatically set if the input is in XML."
    },
    {/* Important notes for translators:
      - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
      <br/>.
      - Entities, tags, attributes, etc., should be enclosed in <code></code>.
      - Option values should be enclosed in <var></var>.
      - It's very important that <br/> be self-closing!
      - The strings "Tidy" and "HTML Tidy" are the program name and must not
      be translated. */
        TidyXmlSpace,                 0,
        "This option specifies if Tidy should add "
        "<code>xml:space=\"preserve\"</code> to elements such as "
        "<code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> and "
        "<code>&lt;script&gt;</code> when generating XML."
        "<br/>"
        "This is needed if the whitespace in such elements is to "
        "be parsed appropriately without having access to the DTD."
    },
    {/* Important notes for translators:
        - Use only <code></code>, <var></var>, <em></em>, <strong></strong>, and
          <br/>.
        - Entities, tags, attributes, etc., should be enclosed in <code></code>.
        - Option values should be enclosed in <var></var>.
        - It's very important that <br/> be self-closing!
        - The strings "Tidy" and "HTML Tidy" are the program name and must not
          be translated. */
      TidyXmlTags,                  0,
        "This option specifies if Tidy should use the XML parser rather than "
        "the error correcting HTML parser. "
    },


    /********************************************
     ** TidyConfigCategory enumeration
     ** @remark enum source TidyConfigCategory
     ********************************************/
    { TidyUnknownCategory,          0,   "unknown category!"                                                       },
    { TidyDiagnostics,              0,   "diagnostics"                                                             },
    { TidyEncoding,                 0,   "encoding"                                                                },
    { TidyInternalCategory,         0,   "internal (private)"                                                      },
    { TidyMarkup,                   0,   "markup"                                                                  },
    { TidyMiscellaneous,            0,   "misc"                                                                    },
    { TidyPrettyPrint,              0,   "print"                                                                   },


    /********************************************
     ** Message Severity Level
     ** @remark enum source TidyConfigCategory
     ********************************************/
    { TidyInfo,               0,   "Info: "          },
    { TidyWarning,            0,   "Warning: "       },
    { TidyConfig,             0,   "Config: "        },
    { TidyAccess,             0,   "Access: "        },
    { TidyError,              0,   "Error: "         },
    { TidyBadDocument,        0,   "Document: "      },
    { TidyFatal,              0,   "Panic: "         },
    { TidyDialogueInfo,       0,   "Information: "   },
    { TidyDialogueSummary,    0,   "Summary: "       },
    { TidyDialogueDoc,        0,   "Document: "      },
    
    
    /********************************************
     ** Miscellaneous Strings
     ** @remark enum source TidyStrings
     ** @rename enum generator FOREACH_MSG_MISC
     ********************************************/
    { FILE_CANT_OPEN,               0,   "Can't open \"%s\""                                                     },
    { LINE_COLUMN_STRING,           0,   "line %d column %d - "                                                    },
    { STRING_CONTENT_LOOKS,         0,   "Document content looks like %s"                                          },
    {/* For example, "discarding invalid UTF-16 surrogate pair" */
      STRING_DISCARDING,            0,   "discarding"
    },
    { STRING_DOCTYPE_GIVEN,         0,   "Doctype given is \"%s\""                                                 },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      STRING_ERROR_COUNT,           0,   "Tidy found %u %s and %u %s!"
    },
    { STRING_ERROR_COUNT_ERROR,     0,   "error"                                                                   },
    { STRING_ERROR_COUNT_ERROR,     1,   "errors"                                                                  },
    { STRING_ERROR_COUNT_WARNING,   0,   "warning"                                                                 },
    { STRING_ERROR_COUNT_WARNING,   1,   "warnings"                                                                },
    { STRING_HELLO_ACCESS,          0,   "WCAG (Accessibility) 1.0 Checks:"                                        },
    {/* This is not a formal name and can be translated. */
      STRING_HTML_PROPRIETARY,      0,   "HTML Proprietary"
    },
    { STRING_MISSING_MALFORMED,     0,   "missing or malformed argument for option: %s"                            },
    { STRING_XML_DECLARATION,       0,   "XML declaration"                                                         },
    {/* This console output should be limited to 78 characters per line.
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      STRING_NEEDS_INTERVENTION,    0,
        "This document has errors that must be fixed before using "
        "HTML Tidy to generate a tidied up version."
    },
    { STRING_NO_ERRORS,             0,   "No warnings or errors were found."                                       },
    { STRING_NO_SYSID,              0,   "No system identifier in emitted doctype"                                 },
    { STRING_NOT_ALL_SHOWN,         0,   "Tidy found %u %s and %u %s! Not all warnings/errors were shown."         },
    { STRING_PLAIN_TEXT,            0,   "plain text"                                                              },
    {/* For example, "replacing invalid UTF-8 bytes" */
      STRING_REPLACING,             0,   "replacing"
    },
    {/* For example, "you should avoid using the specified encoding." */
      STRING_SPECIFIED,             0,   "specified"
    },
    { STRING_UNKNOWN_OPTION,        0,   "unknown option: %s"                                                      },
    { TIDYCUSTOMNO_STRING,          0,   "no"                                                                      },
    { TIDYCUSTOMBLOCKLEVEL_STRING,  0,   "block level"                                                             },
    { TIDYCUSTOMEMPTY_STRING,       0,   "empty"                                                                   },
    { TIDYCUSTOMINLINE_STRING,      0,   "inline"                                                                  },
    { TIDYCUSTOMPRE_STRING,         0,   "pre"                                                                     },
  
    
    /********************************************
     ** Miscellaneous Strings
     ** @remark enum source TidyStrings
     ** @rename enum generator FOREACH_DIALOG_MSG
     ********************************************/
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_HTML_T_ALGORITHM,        0,
        "- First, search left from the cell's position to find row header cells."
        "\n"
        "- Then search upwards to find column header cells."
        "\n"
        "- The search in a given direction stops when the edge of the table is "
        "reached or when a data cell is found after a header cell."
        "\n"
        "- Row headers are inserted into the list in the order they appear in "
        "the table."
        "\n"
        "- For left-to-right tables, headers are inserted from left to right."
        "\n"
        "- Column headers are inserted after row headers, in the order they "
        "appear in the table, from top to bottom."
        "\n"
        "- If a header cell has the headers attribute set, then the headers "
        "referenced by this attribute are inserted into the list and the "
        "search stops for the current direction."
        "\n"
        "- TD cells that set the axis attribute are also treated as header cells."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_WINDOWS_CHARS,           0,
        "Characters codes for the Microsoft Windows fonts in the range "
        "128 - 159 may not be recognized on other platforms. You are "
        "instead recommended to use named entities, e.g. &trade; rather "
        "than Windows character code 153 (0x2122 in Unicode). Note that "
        "as of February 1998 few browsers support the new entities."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - %s represents a string-encoding name which may be localized in your language. */
      TEXT_VENDOR_CHARS,            0,
        "It is unlikely that vendor-specific, system-dependent encodings "
        "work widely enough on the World Wide Web; you should avoid using the "
        "%s character encoding, instead you are recommended to"
        "use named entities, e.g. &trade;."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - %s represents a string-encoding name which may be localized in your language.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_SGML_CHARS,              0,
        "Character codes 128 to 159 (U+0080 to U+009F) are not allowed in HTML; "
        "even if they were, they would likely be unprintable control characters. "
        "Tidy assumed you wanted to refer to a character with the same byte "
        "value in the %s encoding and replaced that reference with the Unicode "
        "equivalent."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_INVALID_UTF8,            0,
        "Character codes for UTF-8 must be in the range: U+0000 to U+10FFFF. "
        "The definition of UTF-8 in Annex D of ISO/IEC 10646-1:2000 also "
        "allows for the use of five- and six-byte sequences to encode "
        "characters that are outside the range of the Unicode character set; "
        "those five- and six-byte sequences are illegal for the use of "
        "UTF-8 as a transformation of Unicode characters. ISO/IEC 10646 "
        "does not allow mapping of unpaired surrogates, nor U+FFFE and U+FFFF "
        "(but it does allow other noncharacters). For more information please refer to "
        "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_INVALID_UTF16,           0,
        "Character codes for UTF-16 must be in the range: U+0000 to U+10FFFF. "
        "The definition of UTF-16 in Annex C of ISO/IEC 10646-1:2000 does not allow the "
        "mapping of unpaired surrogates. For more information please refer to "
        "http://www.unicode.org/ and http://www.cl.cam.ac.uk/~mgk25/unicode.html"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_INVALID_URI,             0,
        "URIs must be properly escaped, they must not contain unescaped "
        "characters below U+0021 including the space character and not "
        "above U+007E. Tidy escapes the URI for you as recommended by "
        "HTML 4.01 section B.2.1 and XML 1.0 section 4.2.2. Some user agents "
        "use another algorithm to escape such URIs and some server-sided "
        "scripts depend on that. If you want to depend on that, you must "
        "escape the URI on your own. For more information please refer to "
        "http://www.w3.org/International/O-URL-and-ident.html"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_BAD_FORM,                0,
        "You may need to move one or both of the <form> and </form> "
        "tags. HTML elements should be properly nested and form elements "
        "are no exception. For instance you should not place the <form> "
        "in one table cell and the </form> in another. If the <form> is "
        "placed before a table, the </form> cannot be placed inside the "
        "table! Note that one form can't be nested inside another!"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_BAD_MAIN,                0,
        "Only one <main> element is allowed in a document. "
        "Subsequent <main> elements have been discarded, which may "
        "render the document invalid."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_M_SUMMARY,               0,
        "The table summary attribute should be used to describe "
        "the table structure. It is very helpful for people using "
        "non-visual browsers. The scope and headers attributes for "
        "table cells are useful for specifying which headers apply "
        "to each table cell, enabling non-visual browsers to provide "
        "a meaningful context for each cell."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_M_IMAGE_ALT,             0,
        "The alt attribute should be used to give a short description "
        "of an image; longer descriptions should be given with the "
        "longdesc attribute which takes a URL linked to the description. "
        "These measures are needed for people using non-graphical browsers."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_M_IMAGE_MAP,             0,
        "Use client-side image maps in preference to server-side image maps as "
        "the latter are inaccessible to people using non-graphical browsers. "
        "In addition, client-side maps are easier to set up and provide "
        "immediate feedback to users."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_M_LINK_ALT,              0,
        "For hypertext links defined using a client-side image map, you "
        "need to use the alt attribute to provide a textual description "
        "of the link for people using non-graphical browsers."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_FRAMES,            0,
        "Pages designed using frames present problems for "
        "people who are either blind or using a browser that "
        "doesn't support frames. A frames-based page should always "
        "include an alternative layout inside a NOFRAMES element."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The URL should not be translated unless you find a matching URL in your language. */
      TEXT_ACCESS_ADVICE1,          0,
        "For further advice on how to make your pages accessible see "
        "http://www.w3.org/WAI/GL."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The URL should not be translated unless you find a matching URL in your language. */
      TEXT_ACCESS_ADVICE2,          0,
        "For further advice on how to make your pages accessible see "
        "http://www.w3.org/WAI/GL and http://www.html-tidy.org/accessibility/."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_LAYER,             0,
        "The Cascading Style Sheets (CSS) Positioning mechanism "
        "is recommended in preference to the proprietary <LAYER> "
        "element due to limited vendor support for LAYER."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_SPACER,            0,
        "You are recommended to use CSS for controlling white "
        "space (e.g. for indentation, margins and line spacing). "
        "The proprietary <SPACER> element has limited vendor support."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_FONT,              0,
        "You are recommended to use CSS to specify the font and "
        "properties such as its size and color. This will reduce "
        "the size of HTML files and make them easier to maintain "
        "compared with using <FONT> elements."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_NOBR,              0,
        "You are recommended to use CSS to control line wrapping. "
        "Use \"white-space: nowrap\" to inhibit wrapping in place "
        "of inserting <NOBR>...</NOBR> into the markup."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules. */
      TEXT_USING_BODY,              0,
        "You are recommended to use CSS to specify page and link colors."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO,            0,
        "About HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Bug reports and comments: https://github.com/htacg/tidy-html5/issues\n"
        "Official mailing list: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Latest HTML specification: http://dev.w3.org/html5/spec-author-view/\n"
        "Validate your HTML documents: http://validator.w3.org/nu/\n"
        "Lobby your company to join the W3C: http://www.w3.org/Consortium"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated.
      - Don't terminate the last line with a newline. */
      TEXT_GENERAL_INFO_PLEA,       0,
        "Do you speak a language other than English, or a different variant of "
        "English? Consider helping us to localize HTML Tidy. For details please see "
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },
    
    
    /********************************************
     ** Report Output
     ** @remark enum source TidyStrings
     ** @rename enum generator FOREACH_DIALOG_MSG
     ********************************************/
    { ANCHOR_NOT_UNIQUE,            0,   "%s anchor \"%s\" already defined"                                        }, /* ReportAttrError */
    { ATTR_VALUE_NOT_LCASE,         0,   "%s attribute value \"%s\" must be lower case for XHTML"                  }, /* ReportAttrError */
    { ATTRIBUTE_IS_NOT_ALLOWED,     0,   "%s attribute \"is\" not allowed for autonomous custom tags."             }, /* ReportAttrError */
    { BACKSLASH_IN_URI,             0,   "%s URI reference contains backslash. Typo?"                              }, /* ReportAttrError */
    { BAD_ATTRIBUTE_VALUE_REPLACED, 0,   "%s attribute \"%s\" had invalid value \"%s\" and has been replaced"      }, /* ReportAttrError */
    { BAD_ATTRIBUTE_VALUE,          0,   "%s attribute \"%s\" has invalid value \"%s\""                            }, /* ReportAttrError */
    { ESCAPED_ILLEGAL_URI,          0,   "%s escaping malformed URI reference"                                     }, /* ReportAttrError */
    { FIXED_BACKSLASH,              0,   "%s converting backslash in URI to slash"                                 }, /* ReportAttrError */
    { ID_NAME_MISMATCH,             0,   "%s id and name attribute value mismatch"                                 }, /* ReportAttrError */
    { ILLEGAL_URI_REFERENCE,        0,   "%s improperly escaped URI reference"                                     }, /* ReportAttrError */
    { INSERTING_AUTO_ATTRIBUTE,     0,   "%s inserting \"%s\" attribute using value \"%s\""                        }, /* ReportAttrError */
    { INVALID_ATTRIBUTE,            0,   "%s attribute name \"%s\" (value=\"%s\") is invalid"                      }, /* ReportAttrError */
    { INVALID_XML_ID,               0,   "%s cannot copy name attribute to id"                                     }, /* ReportAttrError */
    { JOINING_ATTRIBUTE,            0,   "%s joining values of repeated attribute \"%s\""                          }, /* ReportAttrError */
    { MISMATCHED_ATTRIBUTE_ERROR,   0,   "%s attribute \"%s\" not allowed for %s"                                  }, /* ReportAttrError */
    { MISMATCHED_ATTRIBUTE_WARN,    0,   "%s attribute \"%s\" not allowed for %s"                                  }, /* ReportAttrError */
    { MISSING_ATTR_VALUE,           0,   "%s attribute \"%s\" lacks value"                                         }, /* ReportAttrError */
    { MISSING_IMAGEMAP,             0,   "%s should use client-side image map"                                     }, /* ReportAttrError */
    { MISSING_QUOTEMARK,            0,   "%s attribute with missing trailing quote mark"                           }, /* ReportAttrError */
    { NEWLINE_IN_URI,               0,   "%s discarding newline in URI reference"                                  }, /* ReportAttrError */
    { PROPRIETARY_ATTR_VALUE,       0,   "%s proprietary attribute value \"%s\""                                   }, /* ReportAttrError */
    { PROPRIETARY_ATTRIBUTE,        0,   "%s proprietary attribute \"%s\""                                         }, /* ReportAttrError */
    { REPEATED_ATTRIBUTE,           0,   "%s dropping value \"%s\" for repeated attribute \"%s\""                  }, /* ReportAttrError */
    { UNEXPECTED_END_OF_FILE_ATTR,  0,   "%s end of file while parsing attributes"                                 }, /* ReportAttrError */
    { UNEXPECTED_EQUALSIGN,         0,   "%s unexpected '=', expected attribute name"                              }, /* ReportAttrError */
    { UNEXPECTED_GT,                0,   "%s missing '>' for end of tag"                                           }, /* ReportAttrError */
    { UNEXPECTED_QUOTEMARK,         0,   "%s unexpected or duplicate quote mark"                                   }, /* ReportAttrError */
    { WHITE_IN_URI,                 0,   "%s discarding whitespace in URI reference"                               }, /* ReportAttrError */
    { XML_ATTRIBUTE_VALUE,          0,   "%s has XML attribute \"%s\""                                             }, /* ReportAttrError */
    { XML_ID_SYNTAX,                0,   "%s ID \"%s\" uses XML ID syntax"                                         }, /* ReportAttrError */
    
    { INVALID_NCR,                  0,   "%s invalid numeric character reference %s"                               }, /* ReportEncodingError */
    { INVALID_SGML_CHARS,           0,   "%s invalid character code %s"                                            }, /* ReportEncodingError */
    { INVALID_UTF16,                0,   "%s invalid UTF-16 surrogate pair (char. code %s)"                        }, /* ReportEncodingError */
    { INVALID_UTF8,                 0,   "%s invalid UTF-8 bytes (char. code %s)"                                  }, /* ReportEncodingError */
    { VENDOR_SPECIFIC_CHARS,        0,   "%s invalid character code %s"                                            }, /* ReportEncodingError */
    
    { ENCODING_MISMATCH,            0,   "specified input encoding (%s) does not match actual input encoding (%s)" }, /* ReportEncodingWarning */
    
    { APOS_UNDEFINED,               0,   "named entity &apos; only defined in XML/XHTML"                           }, /* ReportEntityError */
    { MISSING_SEMICOLON_NCR,        0,   "numeric character reference \"%s\" doesn't end in ';'"                   }, /* ReportEntityError */
    { MISSING_SEMICOLON,            0,   "entity \"%s\" doesn't end in ';'"                                        }, /* ReportEntityError */
    { UNESCAPED_AMPERSAND,          0,   "unescaped & which should be written as &amp;"                            }, /* ReportEntityError */
    { UNKNOWN_ENTITY,               0,   "unescaped & or unknown entity \"%s\""                                    }, /* ReportEntityError */
    
    { BAD_CDATA_CONTENT,            0,   "'<' + '/' + letter not allowed here"                                     }, /* ReportError */
    { BAD_COMMENT_CHARS,            0,   "expecting -- or >"                                                       }, /* ReportError */
    { BAD_XML_COMMENT,              0,   "XML comments can't contain --"                                           }, /* ReportError */
    { CANT_BE_NESTED,               0,   "%s can't be nested"                                                      }, /* ReportError */
    { CONTENT_AFTER_BODY,           0,   "content occurs after end of body"                                        }, /* ReportError */
    { DISCARDING_UNEXPECTED,        0,   "discarding unexpected %s"                                                }, /* ReportError */
    { DOCTYPE_AFTER_TAGS,           0,   "<!DOCTYPE> isn't allowed after elements"                                 }, /* ReportError */
    { DTYPE_NOT_UPPER_CASE,         0,   "SYSTEM, PUBLIC, W3C, DTD, EN must be upper case"                         }, /* ReportError */
    { ELEMENT_VERS_MISMATCH_ERROR,  0,   "%s element not available in %s"                                          }, /* ReportError */
    { ELEMENT_VERS_MISMATCH_WARN,   0,   "%s element not available in %s"                                          }, /* ReportError */
    { ENCODING_IO_CONFLICT,         0,   "Output encoding does not work with standard output"                      }, /* ReportError */
    { ILLEGAL_NESTING,              0,   "%s shouldn't be nested"                                                  }, /* ReportError */
    { INCONSISTENT_NAMESPACE,       0,   "HTML namespace doesn't match content"                                    }, /* ReportError */
    { INCONSISTENT_VERSION,         0,   "HTML DOCTYPE doesn't match content"                                      }, /* ReportError */
    { INSERTING_TAG,                0,   "inserting implicit <%s>"                                                 }, /* ReportError */
    { MALFORMED_COMMENT,            0,   "adjacent hyphens within comment"                                         }, /* ReportError */
    { MALFORMED_DOCTYPE,            0,   "discarding malformed <!DOCTYPE>"                                         }, /* ReportError */
    { MISSING_DOCTYPE,              0,   "missing <!DOCTYPE> declaration"                                          }, /* ReportError */
    { MISSING_ENDTAG_BEFORE,        0,   "missing </%s> before %s"                                                 }, /* ReportError */
    { MISSING_ENDTAG_FOR,           0,   "missing </%s>"                                                           }, /* ReportError */
    { MISSING_STARTTAG,             0,   "missing <%s>"                                                            }, /* ReportError */
    { MISSING_TITLE_ELEMENT,        0,   "inserting missing 'title' element"                                       }, /* ReportError */
    { NOFRAMES_CONTENT,             0,   "%s not inside 'noframes' element"                                        }, /* ReportError */
    { NON_MATCHING_ENDTAG,          0,   "replacing unexpected %s with </%s>"                                      }, /* ReportError */
    { PREVIOUS_LOCATION,            0,   "<%s> previously mentioned"                                               }, /* ReportError */
    { PROPRIETARY_ELEMENT,          0,   "%s is not approved by W3C"                                               }, /* ReportError */
    { REPLACING_UNEX_ELEMENT,       0,   "replacing unexpected %s with %s"                                         }, /* ReportError */
    { SPACE_PRECEDING_XMLDECL,      0,   "removing whitespace preceding XML Declaration"                           }, /* ReportError */
    { TAG_NOT_ALLOWED_IN,           0,   "%s isn't allowed in <%s> elements"                                       }, /* ReportError */
    { TOO_MANY_ELEMENTS_IN,         0,   "too many %s elements in <%s>"                                            }, /* ReportError */
    { TOO_MANY_ELEMENTS,            0,   "too many %s elements"                                                    }, /* ReportError */
    { UNESCAPED_ELEMENT,            0,   "unescaped %s in pre content"                                             }, /* ReportError */
    { USING_BR_INPLACE_OF,          0,   "using <br> in place of %s"                                               }, /* ReportError */
    
    { DUPLICATE_FRAMESET,           0,   "repeated FRAMESET element"                                               }, /* ReportFatal */
    { SUSPECTED_MISSING_QUOTE,      0,   "missing quote mark for attribute value"                                  }, /* ReportFatal */
    { UNEXPECTED_ENDTAG_IN,         0,   "unexpected </%s> in <%s>"                                                }, /* ReportFatal */
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM, 0,   "%s is not recognized! Did you mean to enable the custom-tags option?"    }, /* ReportFatal */
    { UNKNOWN_ELEMENT,              0,   "%s is not recognized!"                                                   }, /* ReportFatal */
    
    { MISSING_ATTRIBUTE,            0,   "%s lacks \"%s\" attribute"                                               }, /* ReportMissingAttr */
    
    { CUSTOM_TAG_DETECTED,          0,   "detected autonomous custom tag %s; will treat as %s"                     }, /* ReportNotice */
    { REPLACING_ELEMENT,            0,   "replacing %s with %s"                                                    }, /* ReportNotice */
    { TRIM_EMPTY_ELEMENT,           0,   "trimming empty %s"                                                       }, /* ReportNotice */
    
    { BAD_SURROGATE_LEAD,           0,   "Trailing (Low) surrogate pair U+%04X, with no leading (High) entity, replaced with U+FFFD." }, /* ReportSurrogateError */
    { BAD_SURROGATE_PAIR,           0,   "Have out-of-range surrogate pair U+%04X:U+%04X, replaced with U+FFFD value."                }, /* ReportSurrogateError */
    { BAD_SURROGATE_TAIL,           0,   "Leading (High) surrogate pair U+%04X, with no trailing (Low) entity, replaced with U+FFFD." }, /* ReportSurrogateError */
    
    { BAD_SUMMARY_HTML5,            0,   "The summary attribute on the %s element is obsolete in HTML5"            }, /* ReportWarning */
    { COERCE_TO_ENDTAG_WARN,        0,   "<%s> is probably intended as </%s>"                                      }, /* ReportWarning */
    { NESTED_EMPHASIS,              0,   "nested emphasis %s"                                                      }, /* ReportWarning */
    { NESTED_QUOTATION,             0,   "nested q elements, possible typo."                                       }, /* ReportWarning */
    { OBSOLETE_ELEMENT,             0,   "replacing obsolete element %s with %s"                                   }, /* ReportWarning */
    { REMOVED_HTML5,                0,   "%s element removed from HTML5"                                           }, /* ReportWarning */
    { XML_DECLARATION_DETECTED,     0,   "An XML declaration was detected. Did you mean to use input-xml?"         }, /* ReportWarning */
    
    { COERCE_TO_ENDTAG,             0,   "<%s> is probably intended as </%s>"                                      }, /* ReportError, ReportWarning */
    { ELEMENT_NOT_EMPTY,            0,   "%s element not empty or not closed"                                      }, /* ReportError, ReportAttrError */
    { UNEXPECTED_END_OF_FILE,       0,   "unexpected end of file %s"                                               }, /* ReportError, ReportAttrError */
    { UNEXPECTED_ENDTAG,            0,   "unexpected </%s>"                                                        }, /* ReportError, ReportFatal */

    
#if SUPPORT_ACCESSIBILITY_CHECKS
    
    /***************************************
     ** Report Output -- Accessibility
     ***************************************/
    { IMG_MISSING_ALT,                               0,   "[1.1.1.1]: <img> missing 'alt' text."                                     },
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0,   "[1.1.1.2]: suspicious 'alt' text (filename)."                             },
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0,   "[1.1.1.3]: suspicious 'alt' text (file size)."                            },
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0,   "[1.1.1.4]: suspicious 'alt' text (placeholder)."                          },
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0,   "[1.1.1.10]: suspicious 'alt' text (too long)."                            },
    { IMG_MISSING_LONGDESC_DLINK,                    0,   "[1.1.2.1]: <img> missing 'longdesc' and d-link."                          },
    { IMG_MISSING_DLINK,                             0,   "[1.1.2.2]: <img> missing d-link."                                         },
    { IMG_MISSING_LONGDESC,                          0,   "[1.1.2.3]: <img> missing 'longdesc'."                                     },
    { IMG_BUTTON_MISSING_ALT,                        0,   "[1.1.3.1]: <img> (button) missing 'alt' text."                            },
    { APPLET_MISSING_ALT,                            0,   "[1.1.4.1]: <applet> missing alternate content."                           },
    { OBJECT_MISSING_ALT,                            0,   "[1.1.5.1]: <object> missing alternate content."                           },
    { AUDIO_MISSING_TEXT_WAV,                        0,   "[1.1.6.1]: audio missing text transcript (wav)."                          },
    { AUDIO_MISSING_TEXT_AU,                         0,   "[1.1.6.2]: audio missing text transcript (au)."                           },
    { AUDIO_MISSING_TEXT_AIFF,                       0,   "[1.1.6.3]: audio missing text transcript (aiff)."                         },
    { AUDIO_MISSING_TEXT_SND,                        0,   "[1.1.6.4]: audio missing text transcript (snd)."                          },
    { AUDIO_MISSING_TEXT_RA,                         0,   "[1.1.6.5]: audio missing text transcript (ra)."                           },
    { AUDIO_MISSING_TEXT_RM,                         0,   "[1.1.6.6]: audio missing text transcript (rm)."                           },
    { FRAME_MISSING_LONGDESC,                        0,   "[1.1.8.1]: <frame> may require 'longdesc'."                               },
    { AREA_MISSING_ALT,                              0,   "[1.1.9.1]: <area> missing 'alt' text."                                    },
    { SCRIPT_MISSING_NOSCRIPT,                       0,   "[1.1.10.1]: <script> missing <noscript> section."                         },
    { ASCII_REQUIRES_DESCRIPTION,                    0,   "[1.1.12.1]: ascii art requires description."                              },
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0,   "[1.2.1.1]: image map (server-side) requires text links."                  },
    { MULTIMEDIA_REQUIRES_TEXT,                      0,   "[1.4.1.1]: multimedia requires synchronized text equivalents."            },
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0,   "[1.5.1.1]: image map (client-side) missing text links."                   },
    { INFORMATION_NOT_CONVEYED_IMAGE,                0,   "[2.1.1.1]: ensure information not conveyed through color alone (image)."  },
    { INFORMATION_NOT_CONVEYED_APPLET,               0,   "[2.1.1.2]: ensure information not conveyed through color alone (applet)." },
    { INFORMATION_NOT_CONVEYED_OBJECT,               0,   "[2.1.1.3]: ensure information not conveyed through color alone (object)." },
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0,   "[2.1.1.4]: ensure information not conveyed through color alone (script)." },
    { INFORMATION_NOT_CONVEYED_INPUT,                0,   "[2.1.1.5]: ensure information not conveyed through color alone (input)."  },
    { COLOR_CONTRAST_TEXT,                           0,   "[2.2.1.1]: poor color contrast (text)."                                   },
    { COLOR_CONTRAST_LINK,                           0,   "[2.2.1.2]: poor color contrast (link)."                                   },
    { COLOR_CONTRAST_ACTIVE_LINK,                    0,   "[2.2.1.3]: poor color contrast (active link)."                            },
    { COLOR_CONTRAST_VISITED_LINK,                   0,   "[2.2.1.4]: poor color contrast (visited link)."                           },
    { DOCTYPE_MISSING,                               0,   "[3.2.1.1]: <doctype> missing."                                            },
    { STYLE_SHEET_CONTROL_PRESENTATION,              0,   "[3.3.1.1]: use style sheets to control presentation."                     },
    { HEADERS_IMPROPERLY_NESTED,                     0,   "[3.5.1.1]: headers improperly nested."                                    },
    { POTENTIAL_HEADER_BOLD,                         0,   "[3.5.2.1]: potential header (bold)."                                      },
    { POTENTIAL_HEADER_ITALICS,                      0,   "[3.5.2.2]: potential header (italics)."                                   },
    { POTENTIAL_HEADER_UNDERLINE,                    0,   "[3.5.2.3]: potential header (underline)."                                 },
    { HEADER_USED_FORMAT_TEXT,                       0,   "[3.5.3.1]: header used to format text."                                   },
    { LIST_USAGE_INVALID_UL,                         0,   "[3.6.1.1]: list usage invalid <ul>."                                      },
    { LIST_USAGE_INVALID_OL,                         0,   "[3.6.1.2]: list usage invalid <ol>."                                      },
    { LIST_USAGE_INVALID_LI,                         0,   "[3.6.1.4]: list usage invalid <li>."                                      },
    { INDICATE_CHANGES_IN_LANGUAGE,                  0,   "[4.1.1.1]: indicate changes in language."                                 },
    { LANGUAGE_NOT_IDENTIFIED,                       0,   "[4.3.1.1]: language not identified."                                      },
    { LANGUAGE_INVALID,                              0,   "[4.3.1.2]: language attribute invalid."                                   },
    { DATA_TABLE_MISSING_HEADERS,                    0,   "[5.1.2.1]: data <table> missing row/column headers (all)."                },
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0,   "[5.1.2.2]: data <table> missing row/column headers (1 col)."              },
    { DATA_TABLE_MISSING_HEADERS_ROW,                0,   "[5.1.2.3]: data <table> missing row/column headers (1 row)."              },
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0,   "[5.2.1.1]: data <table> may require markup (column headers)."             },
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0,   "[5.2.1.2]: data <table> may require markup (row headers)."                },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0,   "[5.3.1.1]: verify layout tables linearize properly."                      },
    { LAYOUT_TABLE_INVALID_MARKUP,                   0,   "[5.4.1.1]: invalid markup used in layout <table>."                        },
    { TABLE_MISSING_SUMMARY,                         0,   "[5.5.1.1]: <table> missing summary."                                      },
    { TABLE_SUMMARY_INVALID_NULL,                    0,   "[5.5.1.2]: <table> summary invalid (null)."                               },
    { TABLE_SUMMARY_INVALID_SPACES,                  0,   "[5.5.1.3]: <table> summary invalid (spaces)."                             },
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0,   "[5.5.1.6]: <table> summary invalid (placeholder text)."                   },
    { TABLE_MISSING_CAPTION,                         0,   "[5.5.2.1]: <table> missing <caption>."                                    },
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0,   "[5.6.1.1]: <table> may require header abbreviations."                     },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0,   "[5.6.1.2]: <table> header abbreviations invalid (null)."                  },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0,   "[5.6.1.3]: <table> header abbreviations invalid (spaces)."                },
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0,   "[6.1.1.1]: style sheets require testing (link)."                          },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0,   "[6.1.1.2]: style sheets require testing (style element)."                 },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0,   "[6.1.1.3]: style sheets require testing (style attribute)."               },
    { FRAME_SRC_INVALID,                             0,   "[6.2.1.1]: <frame> source invalid."                                       },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0,   "[6.2.2.1]: text equivalents require updating (applet)."                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0,   "[6.2.2.2]: text equivalents require updating (script)."                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0,   "[6.2.2.3]: text equivalents require updating (object)."                   },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0,   "[6.3.1.1]: programmatic objects require testing (script)."                },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0,   "[6.3.1.2]: programmatic objects require testing (object)."                },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0,   "[6.3.1.3]: programmatic objects require testing (embed)."                 },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0,   "[6.3.1.4]: programmatic objects require testing (applet)."                },
    { FRAME_MISSING_NOFRAMES,                        0,   "[6.5.1.1]: <frameset> missing <noframes> section."                        },
    { NOFRAMES_INVALID_NO_VALUE,                     0,   "[6.5.1.2]: <noframes> section invalid (no value)."                        },
    { NOFRAMES_INVALID_CONTENT,                      0,   "[6.5.1.3]: <noframes> section invalid (content)."                         },
    { NOFRAMES_INVALID_LINK,                         0,   "[6.5.1.4]: <noframes> section invalid (link)."                            },
    { REMOVE_FLICKER_SCRIPT,                         0,   "[7.1.1.1]: remove flicker (script)."                                      },
    { REMOVE_FLICKER_OBJECT,                         0,   "[7.1.1.2]: remove flicker (object)."                                      },
    { REMOVE_FLICKER_EMBED,                          0,   "[7.1.1.3]: remove flicker (embed)."                                       },
    { REMOVE_FLICKER_APPLET,                         0,   "[7.1.1.4]: remove flicker (applet)."                                      },
    { REMOVE_FLICKER_ANIMATED_GIF,                   0,   "[7.1.1.5]: remove flicker (animated gif)."                                },
    { REMOVE_BLINK_MARQUEE,                          0,   "[7.2.1.1]: remove blink/marquee."                                         },
    { REMOVE_AUTO_REFRESH,                           0,   "[7.4.1.1]: remove auto-refresh."                                          },
    { REMOVE_AUTO_REDIRECT,                          0,   "[7.5.1.1]: remove auto-redirect."                                         },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0,   "[8.1.1.1]: ensure programmatic objects are accessible (script)."          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0,   "[8.1.1.2]: ensure programmatic objects are accessible (object)."          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0,   "[8.1.1.3]: ensure programmatic objects are accessible (applet)."          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0,   "[8.1.1.4]: ensure programmatic objects are accessible (embed)."           },
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0,   "[9.1.1.1]: image map (server-side) requires conversion."                  },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0,   "[9.3.1.1]: <script> not keyboard accessible (onMouseDown)."               },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0,   "[9.3.1.2]: <script> not keyboard accessible (onMouseUp)."                 },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0,   "[9.3.1.3]: <script> not keyboard accessible (onClick)."                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0,   "[9.3.1.4]: <script> not keyboard accessible (onMouseOver)."               },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0,   "[9.3.1.5]: <script> not keyboard accessible (onMouseOut)."                },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0,   "[9.3.1.6]: <script> not keyboard accessible (onMouseMove)."               },
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0,   "[10.1.1.1]: new windows require warning (_new)."                          },
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0,   "[10.1.1.2]: new windows require warning (_blank)."                        },
    { FORM_CONTROL_REQUIRES_DEFAULT_TEXT,            0,   "[10.4.1.1]: form control requires default text."                          },
    { FORM_CONTROL_DEFAULT_TEXT_INVALID_NULL,        0,   "[10.4.1.2]: form control default text invalid (null)."                    },
    { FORM_CONTROL_DEFAULT_TEXT_INVALID_SPACES,      0,   "[10.4.1.3]: form control default text invalid (spaces)."                  },
    { REPLACE_DEPRECATED_HTML_APPLET,                0,   "[11.2.1.1]: replace deprecated html <applet>."                            },
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0,   "[11.2.1.2]: replace deprecated html <basefont>."                          },
    { REPLACE_DEPRECATED_HTML_CENTER,                0,   "[11.2.1.3]: replace deprecated html <center>."                            },
    { REPLACE_DEPRECATED_HTML_DIR,                   0,   "[11.2.1.4]: replace deprecated html <dir>."                               },
    { REPLACE_DEPRECATED_HTML_FONT,                  0,   "[11.2.1.5]: replace deprecated html <font>."                              },
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0,   "[11.2.1.6]: replace deprecated html <isindex>."                           },
    { REPLACE_DEPRECATED_HTML_MENU,                  0,   "[11.2.1.7]: replace deprecated html <menu>."                              },
    { REPLACE_DEPRECATED_HTML_S,                     0,   "[11.2.1.8]: replace deprecated html <s>."                                 },
    { REPLACE_DEPRECATED_HTML_STRIKE,                0,   "[11.2.1.9]: replace deprecated html <strike>."                            },
    { REPLACE_DEPRECATED_HTML_U,                     0,   "[11.2.1.10]: replace deprecated html <u>."                                },
    { FRAME_MISSING_TITLE,                           0,   "[12.1.1.1]: <frame> missing title."                                       },
    { FRAME_TITLE_INVALID_NULL,                      0,   "[12.1.1.2]: <frame> title invalid (null)."                                },
    { FRAME_TITLE_INVALID_SPACES,                    0,   "[12.1.1.3]: <frame> title invalid (spaces)."                              },
    { ASSOCIATE_LABELS_EXPLICITLY,                   0,   "[12.4.1.1]: associate labels explicitly with form controls."              },
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0,   "[12.4.1.2]: associate labels explicitly with form controls (for)."        },
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0,   "[12.4.1.3]: associate labels explicitly with form controls (id)."         },
    { LINK_TEXT_NOT_MEANINGFUL,                      0,   "[13.1.1.1]: link text not meaningful."                                    },
    { LINK_TEXT_MISSING,                             0,   "[13.1.1.2]: link text missing."                                           },
    { LINK_TEXT_TOO_LONG,                            0,   "[13.1.1.3]: link text too long."                                          },
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0,   "[13.1.1.4]: link text not meaningful (click here)."                       },
    { METADATA_MISSING,                              0,   "[13.2.1.1]: Metadata missing."                                            },
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0,   "[13.2.1.3]: Metadata missing (redirect/auto-refresh)."                    },
    { SKIPOVER_ASCII_ART,                            0,   "[13.10.1.1]: skip over ascii art."                                        },
#endif /* SUPPORT_ACCESSIBILITY_CHECKS */
    
    
#if SUPPORT_CONSOLE_APP
    /********************************************************
     ** Console Application
     **  Although these strings are not used within LibTidy
     **  and only for the console application, they are
     **  provided as part of LibTidy for convenience to
     **  developers.
     ********************************************************/
    { TC_LABEL_COL,                 0,   "column"                                                                  },
    { TC_LABEL_FILE,                0,   "file"                                                                    },
    { TC_LABEL_LANG,                0,   "lang"                                                                    },
    { TC_LABEL_LEVL,                0,   "level"                                                                   },
    { TC_LABEL_OPT,                 0,   "option"                                                                  },
    { TC_MAIN_ERROR_LOAD_CONFIG,    0,   "Loading config file \"%s\" failed, err = %d"                             },
    { TC_OPT_ACCESS,                0,
        "perform additional accessibility checks (<level> = 0, 1, 2, 3). 0 is "
        "assumed if <level> is missing."
    },
    { TC_OPT_ASCII,                 0,   "use ISO-8859-1 for input, US-ASCII for output"                           },
    { TC_OPT_ASHTML,                0,   "force XHTML to well formed HTML"                                         },
    { TC_OPT_ASXML,                 0,   "convert HTML to well formed XHTML"                                       },
    { TC_OPT_BARE,                  0,   "strip out smart quotes and em dashes, etc."                              },
    { TC_OPT_BIG5,                  0,   "use Big5 for both input and output"                                      },
    { TC_OPT_CLEAN,                 0,   "replace FONT, NOBR and CENTER tags with CSS"                             },
    { TC_OPT_CONFIG,                0,   "set configuration options from the specified <file>"                     },
    { TC_OPT_ERRORS,                0,   "show only errors and warnings"                                           },
    { TC_OPT_FILE,                  0,   "write errors and warnings to the specified <file>"                       },
    { TC_OPT_GDOC,                  0,   "produce clean version of html exported by Google Docs"                   },
    { TC_OPT_HELP,                  0,   "list the command line options"                                           },
    { TC_OPT_HELPCFG,               0,   "list all configuration options"                                          },
    { TC_OPT_HELPOPT,               0,   "show a description of the <option>"                                      },
    { TC_OPT_IBM858,                0,   "use IBM-858 (CP850+Euro) for input, US-ASCII for output"                 },
    { TC_OPT_INDENT,                0,   "indent element content"                                                  },
    { TC_OPT_ISO2022,               0,   "use ISO-2022 for both input and output"                                  },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_LANGUAGE,              0,
        "set Tidy's output language to <lang>. Specify '-language help' for more help. "
        "Use before output-causing arguments to ensure the language takes effect, e.g.,"
        "`tidy -lang es -lang help`."
    },

    { TC_OPT_LATIN0,                0,   "use ISO-8859-15 for input, US-ASCII for output"                          },
    { TC_OPT_LATIN1,                0,   "use ISO-8859-1 for both input and output"                                },
    { TC_OPT_MAC,                   0,   "use MacRoman for input, US-ASCII for output"                             },
    { TC_OPT_MODIFY,                0,   "modify the original input files"                                         },
    { TC_OPT_NUMERIC,               0,   "output numeric rather than named entities"                               },
    { TC_OPT_OMIT,                  0,   "omit optional start tags and end tags"                                   },
    { TC_OPT_OUTPUT,                0,   "write output to the specified <file>"                                    },
    { TC_OPT_QUIET,                 0,   "suppress nonessential output"                                            },
    { TC_OPT_RAW,                   0,   "output values above 127 without conversion to entities"                  },
    { TC_OPT_SHIFTJIS,              0,   "use Shift_JIS for both input and output"                                 },
    { TC_OPT_SHOWCFG,               0,   "list the current configuration settings"                                 },
    { TC_OPT_UPPER,                 0,   "force tags to upper case"                                                },
    { TC_OPT_UTF16,                 0,   "use UTF-16 for both input and output"                                    },
    { TC_OPT_UTF16BE,               0,   "use UTF-16BE for both input and output"                                  },
    { TC_OPT_UTF16LE,               0,   "use UTF-16LE for both input and output"                                  },
    { TC_OPT_UTF8,                  0,   "use UTF-8 for both input and output"                                     },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_VERSION,               0,   "show the version of Tidy"
    },

    { TC_OPT_WIN1252,               0,   "use Windows-1252 for input, US-ASCII for output"                         },
    { TC_OPT_WRAP,                  0,
        "wrap text at the specified <column>. 0 is assumed if <column> is "
        "missing. When this option is omitted, the default of the "
        "configuration option 'wrap' applies."
    },
    { TC_OPT_XML,                   0,   "specify the input is well formed XML"                                    },
    { TC_OPT_XMLCFG,                0,   "list all configuration options in XML format"                            },
    { TC_OPT_XMLHELP,               0,   "list the command line options in XML format"                             },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_OPT_XMLSTRG,               0,   "output all of Tidy's strings in XML format"
    },

    { TC_OPT_XMLERRS,               0,   "output error constants and strings in XML format"                        },

    { TC_OPT_XMLOPTS,               0,   "output option descriptions in XML format"                                },
    
    { TC_STRING_CONF_HEADER,        0,   "Configuration File Settings:"                                            },

    {/* Must be 27 characters or fewer. */
      TC_STRING_CONF_NAME,          0,   "Name"
    },
    {/* Must be 9 characters or fewer. */
      TC_STRING_CONF_TYPE,          0,   "Type"
    },
    {/* Must be 40 characters or fewer. */
      TC_STRING_CONF_VALUE,         0,   "Current Value"
    },

    { TC_STRING_OPT_NOT_DOCUMENTED, 0,   "Warning: option `%s' is not documented."                                 },
    { TC_STRING_OUT_OF_MEMORY,      0,   "Out of memory. Bailing out."                                             },
    { TC_STRING_FATAL_ERROR,        0,   "Fatal error: impossible value for id='%d'."                              },
    { TC_STRING_FILE_MANIP,         0,   "File manipulation"                                                       },
    { TC_STRING_PROCESS_DIRECTIVES, 0,   "Processing directives"                                                   },
    { TC_STRING_CHAR_ENCODING,      0,   "Character encodings"                                                     },
    { TC_STRING_LANG_MUST_SPECIFY,  0,   "A POSIX or Windows locale must be specified."                            },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_LANG_NOT_FOUND,     0,   "Tidy doesn't have language '%s,' will use '%s' instead."
    },

    { TC_STRING_MISC,               0,   "Miscellaneous"                                                           },
    { TC_STRING_XML,                0,   "XML"                                                                     },
    { TC_STRING_MUST_SPECIFY,       0,   "A Tidy option name must be specified."                                   },

    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_UNKNOWN_OPTION,     0,   "HTML Tidy: unknown option: %c"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_UNKNOWN_OPTION_B,   0,   "HTML Tidy: unknown option."
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_A,             0,   "HTML Tidy for %s version %s"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_STRING_VERS_B,             0,   "HTML Tidy version %s"
    },

    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - First %s represents the name of the executable from the file system, and is mostly like going to be "tidy".
        - Second %s represents a version number, typically x.x.xx.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_1,                0,
        "%s [options...] [file...] [options...] [file...]"
        "\n"
        "Utility to clean up and pretty print HTML/XHTML/XML."
        "\n\n"
        "This is modern HTML Tidy version %s."
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated.
        - %s represents the platform, for example, "Mac OS X" or "Windows". */
      TC_TXT_HELP_2A,               0,
        "Command Line Arguments for HTML Tidy for %s:"
    },
    {/* The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_2B,               0,
        "Command Line Arguments for HTML Tidy:"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_3,                0,
        "Tidy Configuration Options\n"
        "==========================\n"
        "Use Tidy's configuration options as command line arguments in the "
        "form of \"--some-option <value>\", for example "
        "\"--indent-with-tabs yes\"."
        "\n\n"
        "For a list of all configuration options, use \"-help-config\" or refer "
        "to the man page (if your OS has one)."
        "\n\n"
        "If your environment has an $HTML_TIDY variable set point to a Tidy "
        "configuration file then Tidy will attempt to use it."
        "\n\n"
        "On some platforms Tidy will also attempt to use a configuration "
        "specified in /etc/tidy.conf or ~/.tidy.conf."
        "\n\n\n"
        "Other\n"
        "=====\n"
        "Input/Output default to stdin/stdout respectively."
        "\n\n"
        "Single letter options apart from -f may be combined, as in:"
        "\n"
        "\"tidy -f errs.txt -imu foo.html\""
        "\n\n\n"
        "Information\n"
        "===========\n"
        "For more information about HTML Tidy, see"
        "\n"
        "- http://www.html-tidy.org/"
        "\n\n"
        "For more information on HTML, see the following:"
        "\n\n"
        "HTML: Edition for Web Authors (the latest HTML specification)"
        "\n"
        "- http://dev.w3.org/html5/spec-author-view"
        "\n\n"
        "HTML: The Markup Language (an HTML language reference)"
        "\n"
        "- http://dev.w3.org/html5/markup/"
        "\n\n"
        "File bug reports at https://github.com/htacg/tidy-html5/issues/"
        "or send questions and comments to public-htacg@w3.org."
        "\n\n"
        "Validate your HTML documents using the W3C Nu Markup Validator:"
        "\n"
        "- http://validator.w3.org/nu/"
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_CONFIG,           0,
        "HTML Tidy Configuration Settings"
        "\n\n"
        "Within a file, use the form:"
        "\n\n"
        "wrap: 72"
        "\n"
        "indent: no"
        "\n\n"
        "When specified on the command line, use the form:"
        "\n\n"
        "--wrap 72 --indent no"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,      0,   "Name"                                                                    },
    { TC_TXT_HELP_CONFIG_TYPE,      0,   "Type"                                                                    },
    { TC_TXT_HELP_CONFIG_ALLW,      0,   "Allowable values"                                                        },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_1,           0,
        "The -language (or -lang) option indicates which language Tidy "
        "should use to communicate its output. Please note that this is not "
        "a document translation service, and only affects the messages that "
        "Tidy communicates to you."
        "\n\n"
        "When used from the command line the -language argument must "
        "be used before any arguments that result in output, otherwise Tidy "
        "will produce output before it knows which language to use."
        "\n\n"
        "In addition to standard POSIX language codes, Tidy is capable of "
        "understanding legacy Windows language codes. Please note that this "
        "list indicates codes Tidy understands, and does not indicate that "
        "the language is currently installed."
        "\n\n"
        "The rightmost column indicates how Tidy will understand the "
        "legacy Windows name."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_2,           0,
        "The following languages are currently installed in Tidy. Please "
        "note that there's no guarantee that they are complete; only that "
        "one developer or another started to add the language indicated."
        "\n\n"
        "Incomplete localizations will default to \"en\" when necessary. "
        "Please report instances of incorrect strings to the Tidy team."
    },
    {/* Languages that do not wrap at blank spaces should limit this console
        output to 78 characters per line according to language rules.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated.
        - The parameter %s is likely to be two to five characters, e.g., en or en_US. */
      TC_TXT_HELP_LANG_3,           0,
        "If Tidy is able to determine your locale then Tidy will use the "
        "locale's language automatically. For example Unix-like systems use a "
        "$LANG and/or $LC_ALL environment variable. Consult your operating "
        "system documentation for more information."
        "\n\n"
        "Tidy is currently using locale %s."
    },
#endif /* SUPPORT_CONSOLE_APP */
    
    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,      0,   NULL
    }
}};


#endif /* language_en_h */
