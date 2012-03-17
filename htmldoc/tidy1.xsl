<?xml version="1.0"?>
<!--
    For generating the `tidy.1` man page from the
    output of `tidy -xml-help` and `tidy -xml-config`

    (c) 2005-2007 (W3C) MIT, ERCIM, Keio University
    See tidy.h for the copyright notice.

    Written by Jelks Cabaniss and Arnaud Desitter

  CVS Info :

    $Author: arnaud02 $
    $Date: 2007/02/01 12:25:21 $
    $Revision: 1.8 $

-->
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:strip-space elements="description" />

<xsl:output method="text" />

<!--
    The default template match is to the document passed on the
    command line to the XSLT processor, currently "tidy-help.xml".
    For the detailed config options section however, the template
    match is to the file "tidy-config.xml".  This is captured in
    the $CONFIG variable, declared here:
-->

<xsl:variable name="CONFIG" select="document('tidy-config.xml')"/>


<!-- Main Template: -->

<xsl:template match="/">
   <xsl:call-template name="header-section" />
   <xsl:call-template name="cmdline-section" />
   <xsl:call-template name="config-section" />
   <xsl:call-template name="manpage-see-also-section" />
</xsl:template>


<!-- Named Templates: -->


<xsl:template name="header-section">
  <xsl:text/>.\" tidy man page for the HTML5 fork of Tidy
.TH TIDY 1 "<xsl:value-of select="cmdline/@version" />" "HTML Tidy" "<xsl:value-of select="cmdline/@version" />"
</xsl:template>


<xsl:template name="cmdline-section">
.\" disable hyphenation
.nh
.\" disable justification (adjust text to left margin only)
.ad l
.SH NAME
\fBtidy\fR - check, correct, and pretty-print HTML(5) files
.SH SYNOPSIS
\fBtidy\fR [option ...] [file ...] [option ...] [file ...]
.SH DESCRIPTION
Tidy reads HTML(5), XHTML(5) and XML files and writes cleaned-up markup.  For HTML variants, it detects, reports, and corrects many common coding errors and strives to produce visually equivalent markup that is both conformant to the HTML specifications and that works in most browsers.
.LP
A common use of Tidy is to convert plain HTML to XHTML.  For generic XML files, Tidy is limited to correcting basic well-formedness errors and pretty printing.
.LP
If no input file is specified, Tidy reads the standard input.  If no output file is specified, Tidy writes the tidied markup to the standard output.  If no error file is specified, Tidy writes messages to the standard error.
For command line options that expect a numerical argument, a default is assumed if no meaningful value can be found. 
.SH OPTIONS
<xsl:call-template name="show-cmdline-options" />
.SH USAGE
.LP
Use \fB--\fR\fIoptionX valueX\fR for the detailed configuration option "optionX" with argument "valueX".  See also below under \fBDetailed Configuration Options\fR as to how to conveniently group all such options in a single config file.
.LP
Input/Output default to stdin/stdout respectively. Single letter options apart from \fB-f\fR and \fB-o\fR may be combined as in:
.LP
.in 1i
\fBtidy -f errs.txt -imu foo.html\fR
.SH ENVIRONMENT
.TP
.B HTML_TIDY
Name of the default configuration file.  This should be an absolute path, since you will probably invoke \fBtidy\fR from different directories.  The value of HTML_TIDY will be parsed after the compiled-in default (defined with -DTIDY_CONFIG_FILE), but before any of the files specified using \fB-config\fR.
.SH "EXIT STATUS"
.IP 0
All input files were processed successfully.
.IP 1
There were warnings.
.IP 2
There were errors.
</xsl:template>


<xsl:template name="config-section">
.SH ______________________________
.SH "  "
.SH "DETAILED CONFIGURATION OPTIONS"
This section describes the Detailed (i.e., "expanded") Options, which may be specified by preceding each option with \fB--\fR at the command line, followed by its desired value, OR by placing the options and values in a configuration file, and telling tidy to read that file with the \fB-config\fR standard option.
.SH SYNOPSIS
\fBtidy --\fR\fIoption1 \fRvalue1 \fB--\fIoption2 \fRvalue2 [standard options ...]
.br
\fBtidy -config \fIconfig-file \fR[standard options ...]
.SH WARNING
The options detailed here do not include the "standard" command-line options (i.e., those preceded by a single '\fB-\fR') described above in the first section of this man page.
.SH DESCRIPTION
A list of options for configuring the behavior of Tidy, which can be passed either on the command line, or specified in a configuration file.
.LP
A Tidy configuration file is simply a text file, where each option
is listed on a separate line in the form
.LP
.in 1i
\fBoption1\fR: \fIvalue1\fR
.br
\fBoption2\fR: \fIvalue2\fR
.br
etc.
.LP
The permissible values for a given option depend on the option's \fBType\fR.  There are five types: \fIBoolean\fR, \fIAutoBool\fR, \fIDocType\fR, \fIEnum\fR, and \fIString\fR. Boolean types allow any of \fIyes/no, y/n, true/false, t/f, 1/0\fR.  AutoBools allow \fIauto\fR in addition to the values allowed by Booleans.  Integer types take non-negative integers.  String types generally have no defaults, and you should provide them in non-quoted form (unless you wish the output to contain the literal quotes).
.LP
Enum, Encoding, and DocType "types" have a fixed repertoire of items; consult the \fIExample\fR[s] provided below for the option[s] in question.
.LP
You only need to provide options and values for those whose defaults you wish to override, although you may wish to include some already-defaulted options and values for the sake of documentation and explicitness.
.LP
Here is a sample config file, with at least one example of each of the five Types:
.LP
\fI
    // sample Tidy configuration options
    output-xhtml: yes
    add-xml-decl: no
    doctype: strict
    char-encoding: ascii
    indent: auto
    wrap: 76
    repeated-attributes: keep-last
    error-file: errs.txt
\fR
.LP
Below is a summary and brief description of each of the options. They are listed alphabetically within each category.  There are five categories: \fIHTML, XHTML, XML\fR options, \fIDiagnostics\fR options, \fIPretty Print\fR options, \fICharacter Encoding\fR options, and \fIMiscellaneous\fR options.
.LP
.SH OPTIONS
<xsl:call-template name="show-config-options" />
</xsl:template>


<xsl:template name="show-cmdline-options">
.SS File manipulation
  <xsl:call-template name="cmdline-detail">
     <xsl:with-param name="category">file-manip</xsl:with-param>
  </xsl:call-template>
.SS Processing directives
  <xsl:call-template name="cmdline-detail">
     <xsl:with-param name="category">process-directives</xsl:with-param>
  </xsl:call-template>
.SS Character encodings
  <xsl:call-template name="cmdline-detail">
     <xsl:with-param name="category">char-encoding</xsl:with-param>
  </xsl:call-template>
.SS Miscellaneous
  <xsl:call-template name="cmdline-detail">
     <xsl:with-param name="category">misc</xsl:with-param>
  </xsl:call-template>
</xsl:template>


<xsl:template name="cmdline-detail">
<!--
For each option in one of the 3 categories/classes, provide its
    1. names
    2. description
    3. equivalent configuration option
-->
  <xsl:param name="category" />
    <xsl:for-each select='/cmdline/option[@class=$category]'>
<xsl:text>
.TP
</xsl:text>
       <xsl:call-template name="process-names" />
       <xsl:text>
</xsl:text>
       <xsl:apply-templates select="description" />
       <xsl:text>
</xsl:text>
       <xsl:call-template name="process-eqconfig" />
    </xsl:for-each>
</xsl:template>


<xsl:template name="process-names">
<!-- Used only in the cmdline section -->
  <xsl:for-each select="name">
    <xsl:text />\fB<xsl:value-of select="." />\fR<xsl:text />
    <xsl:if test="position() != last()">
      <xsl:text>, </xsl:text>
    </xsl:if>
  </xsl:for-each>
</xsl:template>


<xsl:template name="process-eqconfig">
<!-- Used only in the cmdline section -->
  <xsl:if test="string-length(eqconfig) &gt; 0">
   <xsl:for-each select="eqconfig">
     <xsl:text>(\fI</xsl:text>
     <xsl:value-of select="." />
     <xsl:text>\fR)</xsl:text>
   </xsl:for-each>
  </xsl:if>
</xsl:template>


<xsl:template name="show-config-options">
<!-- Used only in the cmdline section -->
.SS HTML, XHTML, XML options:
  <xsl:call-template name="config-detail">
     <xsl:with-param name="category">markup</xsl:with-param>
  </xsl:call-template>
.SS Diagnostics options:
  <xsl:call-template name="config-detail">
     <xsl:with-param name="category">diagnostics</xsl:with-param>
  </xsl:call-template>
.SS Pretty Print options:
  <xsl:call-template name="config-detail">
     <xsl:with-param name="category">print</xsl:with-param>
  </xsl:call-template>
.SS Character Encoding options:
  <xsl:call-template name="config-detail">
     <xsl:with-param name="category">encoding</xsl:with-param>
  </xsl:call-template>
.SS Miscellaneous options:
  <xsl:call-template name="config-detail">
     <xsl:with-param name="category">misc</xsl:with-param>
  </xsl:call-template>
</xsl:template>


<!--
    Note that any templates called implicitly or explicitly
    from the "config-detail" template below will match on
    the document referred to by the $CONFIG variable, i.e.,
    the file "tidy-config.xml", created by running

        tidy -xml-config > tidy-config.xml

    The $CONFIG variable is set at the top level of this
    stylesheet.
-->

<xsl:template name="config-detail">
<!--
For each option in one of the 5 categories/classes, provide its
    1. name
    2. type
    3. default (if any)
    4. example (if any)
    5. seealso (if any)
    6. description
-->
  <xsl:param name="category" />
    <xsl:for-each select='$CONFIG/config/option[@class=$category]'>
       <xsl:sort select="name" order="ascending" />
.TP
\fB<xsl:apply-templates select="name" />\fR

Type:    \fI<xsl:apply-templates select="type" />\fR
.br
<xsl:call-template name="provide-default" />
.br
<xsl:call-template name="provide-example" />
<xsl:text>

</xsl:text>
<xsl:apply-templates select="description" />
<xsl:call-template name="seealso" />
    </xsl:for-each>
</xsl:template>


<!-- Used only in the config options section: -->
<xsl:template name="seealso">
  <xsl:if test="seealso">
     <xsl:text>

</xsl:text>
.rj 1
\fBSee also\fR: <xsl:text />
    <xsl:for-each select="seealso">
      <xsl:text />\fI<xsl:value-of select="." />\fR<xsl:text />
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
  </xsl:if>
</xsl:template>


<!-- Used only in the config options section: -->
<xsl:template name="provide-default">
<!--
Picks up the default from the XML.  If the `default` element
doesn't exist, or it's empty, a single '-' is provided.
-->
  <xsl:choose>
    <xsl:when test="string-length(default) &gt; 0 ">
      <xsl:text />Default: \fI<xsl:apply-templates
        select="default" />\fR<xsl:text />
    </xsl:when>
    <xsl:otherwise>
      <xsl:text />Default: \fI-\fR<xsl:text />
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- Used only in the config options section: -->
<xsl:template name="provide-example">
<!--
By default, doesn't output examples for String types (mirroring the
quickref page).  But for *any* options in the XML instance that
have an `example` child, that example will be used in lieu of a
stylesheet-provided one. (Useful e.g. for `repeated-attributes`).
-->
  <xsl:choose>
    <xsl:when test="string-length(example) &gt; 0">
      <xsl:text />Example: \fI<xsl:apply-templates
          select="example" />\fR<xsl:text />
    </xsl:when>
    <xsl:otherwise>
      <xsl:text />Default: \fI-\fR<xsl:text />
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- Called from the templates below matching `code`, `em`, `strong`: -->
<xsl:template name="escape-backslash">
<!--
Since backslashes are "special" to the *roff processors used
to generate man pages, we need to escape backslash characters
appearing in content with another backslash.
-->
  <xsl:choose>
    <xsl:when test="contains(.,'\')">
      <xsl:value-of select=
        "concat( substring-before(.,'\'), '\\', substring-after(.,'\') )" />
    </xsl:when>
    <xsl:otherwise>
      <xsl:apply-templates />
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- Appears at the bottom of the man page: -->
<xsl:template name="manpage-see-also-section">
.SH SEE ALSO
For more information about the experimental HTML5 fork of Tidy:
.RS 4
.LP
http://w3c.github.com/tidy-html5/
.RE
.LP
For more information on HTML:
.RS 4
.LP
\fBHTML: Edition for Web Authors\fR (the latest HTML specification)
.br
http://dev.w3.org/html5/spec-author-view
.LP
\fBHTML: The Markup Language\fR (an HTML language reference)
.br
http://dev.w3.org/html5/markup/
.RE
.LP
For bug reports and comments:
.RS 4
.LP
https://github.com/w3c/tidy-html5/issues/
.RE
.LP
Or send questions and comments to \fBhtml-tidy@w3.org\fR
.LP
Validate your HTML documents using the \fBW3C Nu Markup Validator\fR:
.RS 4
.LP
http://validator.w3.org/nu/
.RE
.SH AUTHOR
\fBTidy\fR was written by \fBDave Raggett\fR &lt;dsr@w3.org&gt;, and subsequently maintained by a team at http://tidy.sourceforge.net/
.LP
The sources for the HTML5 fork of \fBTidy\fR are available at https://github.com/w3c/tidy-html5/ under the MIT Licence.
</xsl:template>


<!-- Regular Templates: -->


<xsl:template match="description">
   <xsl:apply-templates />
</xsl:template>

<xsl:template match="a">
   <xsl:apply-templates />
   <xsl:text /> at \fI<xsl:value-of select="@href" />\fR<xsl:text />
</xsl:template>

<xsl:template match="code | em">
   <xsl:text />\fI<xsl:call-template name="escape-backslash" />\fR<xsl:text />
</xsl:template>

<xsl:template match="br">
   <xsl:text>
.br
</xsl:text>
</xsl:template>

<xsl:template match="strong">
   <xsl:text />\fB<xsl:call-template name="escape-backslash" />\fR<xsl:text />
</xsl:template>


<!--
The following templates
  a) normalize whitespace, primarily necessary for `description`
  b) do so without stripping possible whitespace surrounding `code`
  d) strip leading and trailing whitespace in 'description` and `code`
(courtesy of Ken Holman on the XSL-list):
-->

<xsl:template match="text()[preceding-sibling::node() and
                             following-sibling::node()]">
   <xsl:variable name="ns" select="normalize-space(concat('x',.,'x'))"/>
   <xsl:value-of select="substring( $ns, 2, string-length($ns) - 2 )" />
</xsl:template>

<xsl:template match="text()[preceding-sibling::node() and
                             not( following-sibling::node() )]">
   <xsl:variable name="ns" select="normalize-space(concat('x',.))"/>
   <xsl:value-of select="substring( $ns, 2, string-length($ns) - 1 )" />
</xsl:template>

<xsl:template match="text()[not( preceding-sibling::node() ) and
                             following-sibling::node()]">
   <xsl:variable name="ns" select="normalize-space(concat(.,'x'))"/>
   <xsl:value-of select="substring( $ns, 1, string-length($ns) - 1 )" />
</xsl:template>

<xsl:template match="text()[not( preceding-sibling::node() ) and
                             not( following-sibling::node() )]">
   <xsl:value-of select="normalize-space(.)"/>
</xsl:template>

</xsl:stylesheet>
