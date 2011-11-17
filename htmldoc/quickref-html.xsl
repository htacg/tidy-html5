<?xml version="1.0"?>
<!--
    For generating the `quickref.html` web page from output of
    `tidy -xml-config`

    (c) 2005 (W3C) MIT, ERCIM, Keio University
    See tidy.h for the copyright notice.

    Written by Charles Reitzel and Jelks Cabaniss

  CVS Info :

    $Author: arnaud02 $
    $Date: 2005/04/13 11:10:58 $
    $Revision: 1.2 $

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
    <link type="text/css" rel="stylesheet" href="tidy.css" />
  </head>

  <body>
    <h1 id="top">Quick Reference</h1>

    <h2>HTML Tidy Configuration Options</h2>

    <p><em>Generated automatically with HTML Tidy released
    on <xsl:value-of select="config/@version" />.</em></p>

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


<!-- Regular Templates: -->
<xsl:template match="a | code | em | strong | br">
    <xsl:element name="{local-name(.)}">
        <xsl:copy-of select="@* | node()" />
    </xsl:element>
</xsl:template>

</xsl:stylesheet>
