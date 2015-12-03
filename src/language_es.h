#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
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
static languageDictionary language_es = {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                "es"                                                                      },
	
	
	/*****************************
	 ** Localization test strings
	 *****************************/
	{ TEST_PRESENT_IN_BASE,         "This is es base language (TEST_PRESENT_IN_BASE)."                        },
	
	
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
	{ TidyMakeClean,
		"Esta opción especifica si Tidy debe realizar la limpieza de algún "
		"legado etiquetas de presentación (actualmente <code>&lt;i&gt;</code>, "
		"<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> cuando encerrados "
		"dentro de las etiquetas apropiadas en línea y "
		"<code>&lt;font&gt;</code>). Si se establece en <code>yes</code>, "
		"entonces etiquetas existentes serán reemplazados con CSS "
		"<code>&lt;style&gt;</code> y estructural markup según corresponda. "
		,
	},

	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,       NULL                                                                      }
};


#endif /* language_es_h */
