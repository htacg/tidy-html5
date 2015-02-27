<?xml version="1.0"?>
<!--
    For generating the `quickref.html` web page from output of
    `tidy -xml-config`

    (c) 2005 (W3C) MIT, ERCIM, Keio University
    See tidy.h for the copyright notice.

    Written by Charles Reitzel and Jelks Cabaniss

-->

<xsl:stylesheet version="1.0"
                xmlns="http://www.w3.org/1999/xhtml"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" indent="yes"
     encoding="us-ascii"
     omit-xml-declaration="yes"
     doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
     doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd" />

<xsl:template match="/">
  <html lang="en" xml:lang="en" xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title>HTML Tidy Configuration Options Quick Reference</title>
	<xsl:call-template name="Stylesheet" />
  </head>

  <body>
    <h1 id="top">Quick Reference</h1>

    <h2>HTML Tidy Configuration Options</h2>

    <p>Version: <xsl:value-of select="config/@version" /></p>

    <p><a class="h3" href="#MarkupHeader">HTML, XHTML, XML</a><br />
     <a class="h3" href="#DiagnosticsHeader">Diagnostics</a><br />
     <a class="h3" href="#PrettyPrintHeader">Pretty Print</a><br />
     <a class="h3" href="#EncodingHeader">Character Encoding</a><br />
     <a class="h3" href="#MiscellaneousHeader">Miscellaneous</a></p>

    <xsl:call-template name="link-section" />

    <xsl:call-template name="detail-section" />

  </body>
  </html>
</xsl:template>


<!-- Named Templates: -->

<xsl:template name="link-section">
  <table summary="Tidy Options Quick Reference Header Section" border="0"
  cellpadding="3" cellspacing="0">
    <colgroup>
      <col width="33%" />
      <col width="33%" />
      <col width="33%" />
    </colgroup>
    <xsl:call-template name="links">
      <xsl:with-param name="class">markup</xsl:with-param>
      <xsl:with-param name="header">HTML, XHTML, XML</xsl:with-param>
      <xsl:with-param name="headerID">MarkupHeader</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="links">
      <xsl:with-param name="class">diagnostics</xsl:with-param>
      <xsl:with-param name="header">Diagnostics</xsl:with-param>
      <xsl:with-param name="headerID">DiagnosticsHeader</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="links">
      <xsl:with-param name="class">print</xsl:with-param>
      <xsl:with-param name="header">Pretty Print</xsl:with-param>
      <xsl:with-param name="headerID">PrettyPrintHeader</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="links">
      <xsl:with-param name="class">encoding</xsl:with-param>
      <xsl:with-param name="header">Character Encoding</xsl:with-param>
      <xsl:with-param name="headerID">EncodingHeader</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="links">
      <xsl:with-param name="class">misc</xsl:with-param>
      <xsl:with-param name="header">Miscellaneous</xsl:with-param>
      <xsl:with-param name="headerID">MiscellaneousHeader</xsl:with-param>
    </xsl:call-template>
  </table>
</xsl:template>


<xsl:template name="detail-section">
  <table summary="Tidy Options Quick Reference Detail Section" border="0"
    cellpadding="3" cellspacing="0">
    <xsl:call-template name="reference">
      <xsl:with-param name="class">markup</xsl:with-param>
      <xsl:with-param name="header">HTML, XHTML, XML</xsl:with-param>
      <xsl:with-param name="headerID">MarkupReference</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="reference">
      <xsl:with-param name="class">diagnostics</xsl:with-param>
      <xsl:with-param name="header">Diagnostics</xsl:with-param>
      <xsl:with-param name="headerID">DiagnosticsReference</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="reference">
      <xsl:with-param name="class">print</xsl:with-param>
      <xsl:with-param name="header">Pretty Print</xsl:with-param>
      <xsl:with-param name="headerID">PrettyPrintReference</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="reference">
      <xsl:with-param name="class">encoding</xsl:with-param>
      <xsl:with-param name="header">Character Encoding</xsl:with-param>
      <xsl:with-param name="headerID">EncodingReference</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="reference">
      <xsl:with-param name="class">misc</xsl:with-param>
      <xsl:with-param name="header">Miscellaneous</xsl:with-param>
      <xsl:with-param name="headerID">MiscellaneousReference</xsl:with-param>
    </xsl:call-template>
  </table>
</xsl:template>


<xsl:template name="links">
  <xsl:param name="class"/>
  <xsl:param name="header"/>
  <xsl:param name="headerID"/>
  <tr valign="bottom">
    <td class="h3" colspan="2" id="{$headerID}">
      <xsl:value-of select="$header"/> Options</td>
    <td valign="top"><a href="#top">Top</a></td>
  </tr>
  <xsl:call-template name="ClassHeaders" />
  <xsl:for-each select="/config/option[@class=$class]">
    <xsl:sort select="name" order="ascending" />
    <tr>
      <td><a href="#{name}"><xsl:value-of select="name"/></a></td>
      <td><xsl:apply-templates select="type"/></td>
      <td><xsl:choose>
            <xsl:when test="string-length(default) &gt; 0 ">
              <xsl:apply-templates select="default" />
            </xsl:when>
            <xsl:otherwise>
              <strong>-</strong>
            </xsl:otherwise>
        </xsl:choose>
      </td>
    </tr>
  </xsl:for-each>
  <tr valign="bottom">
    <td colspan="3">&#160;</td>
  </tr>
</xsl:template>


<xsl:template name="reference">
  <xsl:param name="class"/>
  <xsl:param name="header"/>
  <xsl:param name="headerID"/>

  <tr>
    <td>&#160;</td>
  </tr>
  <tr valign="bottom">
    <td valign="top" colspan="2" class="h2" id="{$headerID}">
       <xsl:value-of select="$header"/> Options Reference
    </td>
  </tr>
  <tr>
    <td>&#160;</td>
  </tr>

  <xsl:for-each select="/config/option[@class=$class]">
    <xsl:sort select="name" order="ascending" />
    <tr>
      <td class="tabletitle" valign="top" id="{name}">
        <xsl:value-of select="name"/>
      </td>
      <td class="tabletitlelink" valign="top" align="right">
      <a href="#top">Top</a></td>
    </tr>
    <tr>
      <td valign="top">Type: <strong><xsl:value-of
        select="type"/></strong><br />

        <xsl:choose>
          <xsl:when test="string-length(default) &gt; 0">
            Default: <strong><xsl:apply-templates select="default" /></strong>
          </xsl:when>
          <xsl:otherwise>
            Default: <strong>-</strong>
          </xsl:otherwise>
        </xsl:choose>

        <xsl:choose>
          <xsl:when test="string-length(example) &gt; 0">
            <br />Example: <strong><xsl:apply-templates
                select="example"/></strong>
          </xsl:when>
          <xsl:otherwise>
            <br />Example: <strong>-</strong>
          </xsl:otherwise>
        </xsl:choose>
      </td>
      <td align="right" valign="top">
        <xsl:for-each select="seealso">
          <a href="#{.}"><xsl:apply-templates select="." /></a>
          <xsl:if test="position() != last()">
            <br />
          </xsl:if>
        </xsl:for-each>
      </td>
    </tr>

    <tr>
      <td colspan="2"><xsl:apply-templates select="description"/></td>
    </tr>

    <tr>
      <td>&#160;</td>
    </tr>
  </xsl:for-each>
</xsl:template>

<xsl:template name="ClassHeaders">
      <tr>
        <td class="tabletitle">Option</td>
        <td class="tabletitle">Type</td>
        <td class="tabletitle">Default</td>
      </tr>
</xsl:template>

<xsl:template name="Stylesheet">
	<style type="text/css">
		/* 1st Style ignored by Netscape */
		td.dummy, font.dummy, .dummy, a:link.dummy, a:visited.dummy, a:active.dummy
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 16pt;
		color: #336699;
		text-decoration: none;
		font-weight: normal
		}

		body
		{
		margin-left: 10%;
		margin-right: 10%;
		font-family: sans-serif;
		background-color: #FFFFFF
		}

		/* Blue TITLE */
		td.title, font.title, .title, a:link.title, a:visited.title, a:active.title
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 16pt;
		color: #336699;
		text-decoration: none;
		font-weight: normal
		}

		/* BODY TEXT */
		td.text, font.text, .text, a:link.text, a:visited.text, a:active.text
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 9pt;
		color: #000000;
		text-decoration: none;
		font-weight: normal
		}

		/* BOLD BODY TEXT */
		td.textbold, font.textbold, .textbold, a:link.textbold, a:visited.textbold, a:active.textbold
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 9pt;
		color: #000000;
		text-decoration: none;
		font-weight: bold
		}

		/* BOLD BODY TEXT LINK WITH UNDERLINE*/
		td.textboldlink, font.textboldlink, .textboldlink, a:link.textboldlink, a:visited.textboldlink, a:active.textboldlink
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 9pt;
		color: #000000;
		font-weight: bold
		}

		/* SMALL BODY TEXT */
		td.smtext, font.smtext, .smtext, a:link.smtext, a:visited.smtext, a:active.smtext
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 8pt;
		color: #000000;
		text-decoration: none;
		font-weight: normal
		}

		/* SMALL BOLD BODY TEXT */
		td.smtextbold, font.smtextbold, .smtextbold, a:link.smtextbold, a:visited.smtextbold, a:active.smtextbold
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 8pt;
		color: #000000;
		text-decoration: none;
		font-weight: bold
		}

		/* TITLES
		td.title, font.title, .title, a:link.title, a:visited.title, a:active.title
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		color: #CC3300;
		text-decoration: none;
		font-weight: bold
		}
		*/

		/* SUBTITLES */
		td.subtitle, font.subtitle, .subtitle, a:link.subtitle, a:visited.subtitle, a:active.subtitle
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 11pt;
		color: #000000;
		text-decoration: none;
		font-weight: bold
		}

		/* LEGAL TEXT */
		td.legal, font.legal, .legal, a:link.legal, a:visited.legal, a:active.legal
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 8pt;
		color: #000000;
		text-decoration: none;
		font-weight: normal
		}

		td.legallink, font.legallink, .legallink, a:link.legallink, a:visited.legallink, a:active.legallink
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 8pt;
		color: #CC3300;
		font-weight: normal
		}

		/* RED TEXT */
		td.textred, font.textred, .textred, a:link.textred, a:visited.textred, a:active.textred
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #CC3300;
		text-decoration: none;
		font-weight: normal
		}

		/* RED TEXT BOLD*/
		td.textredbold, font.textredbold, .textredbold, a:link.textredbold, a:visited.textredbold, a:active.textredbold
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #CC3300;
		text-decoration: none;
		font-weight: bold
		}

		/* LINKS */
		td.link, font.link, .link, a:link.link, a:visited.link, a:active.link
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #3366CC;
		font-weight: normal
		}

		td.tabletitlelink, font.tabletitlelink, .tabletitlelink, a:link.tabletitlelink, a:visited.tabletitlelink, a:active.tabletitlelink
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		background-color: #e9e9d3;
		color: #000000;
		}

		/* TABLE TITLES */
		td.tabletitle, font.tabletitle, .tabletitle, a:link.tabletitle, a:visited.tabletitle, a:active.tabletitle
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #336699;
		background-color: #e9e9d3;
		/* text-decoration: none; */
		font-weight: bold
		}

		/* TABLE CELL */
		td.cell, tr.cell, font.cell, .cell, a:link.cell, a:visited.cell, a:active.cell
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		color: #000000;
		font-weight: normal;
		/* background-color: #e9e9d3 */
		background-color: #f5f5f5
		}

		/* SHADED TABLE CELL */
		td.shaded, tr.shaded, font.shaded, .shaded, a:link.shaded, a:visited.shaded, a:active.shaded
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		color: #000000;
		font-weight: normal;
		background-color: #f5f5f5
		}

		/* GLOSSARY TERM */
		td.term, font.term, .term, a:link.term, a:visited.term, a:active.term
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		font-style: normal;
		color: #000000;
		text-decoration: none;
		font-weight: normal
		}

		/* ELEMENT TAGS */
		ul
		{
		font-family: Arial, Helvetica, sans-serif;
		font-size: 10pt;
		font-style: normal;
		font-weight: normal
		}
		li
		{
		font-family: Arial, Helvetica, sans-serif;
		font-size: 10pt;
		font-style: normal;
		font-weight: normal
		}

		a:link.h1, a:visited.h1, .h1
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		color: #0066CC
		}
		a:active.h1
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		font-weight: bold;
		color: #0066CC
		}
		h1
		{
		margin-left: -8%;
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 12pt;
		color: #0066CC
		}

		.h2
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 11pt;
		/* font-weight: bold; */
		color: #000000
		}

		h2
		{
		margin-left: -4%;
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 11pt;
		/* font-weight: bold; */
		color: #000000
		}

		A:link.h3, A:visited.h3, .h3
		{  font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #000000;
		font-weight: bold
		}

		A:active.h3
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #000000;
		font-weight: bold
		}

		h3
		{
		margin-left: -4%;
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		font-weight: bold;
		color: #000000
		}

		h4
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 9pt;
		font-weight: bold;
		color: #000000
		}

		.code, A:active.code, A:link.code, A:visited.code
		{
		font-family: "Courier New", Courier, monospace;
		}

		.abstract
		{
			font-style : italic;
		}

		p
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		font-style: normal
		}

		td
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		font-style: normal
		}

		/* LINKS */
		a:link, a:active
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #3366CC;
		font-weight: normal
		}

		a:visited
		{
		font-family: Arial, Helvetica, "Trebuchet MS", sans-serif;
		font-size: 10pt;
		color: #333366;
		font-weight: normal
		}

		code {
		  /* use browser/user default for `font-family` */
		  font-weight: bold;
		  color: brown;
		  background: transparent;
		}
	</style>
</xsl:template>


<!-- Regular Templates: -->
<xsl:template match="a | code | em | strong | br">
    <xsl:element name="{local-name(.)}">
        <xsl:copy-of select="@* | node()" />
    </xsl:element>
</xsl:template>

</xsl:stylesheet>
