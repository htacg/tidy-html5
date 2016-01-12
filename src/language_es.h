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

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "language.h"
#include "access.h"
#include "message.h"


/**
 *  This language-specific fuction returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_es(uint n) {
	/* Plural-Forms: nplurals=2; */
	return n != 1;
}


/**
 *  This array specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_es = { whichPluralForm_es, {
	/* Specify the code for this language. */
	{ TIDY_LANGUAGE,                0,    "es"                                                                      },
	
	
	/*****************************
	 ** Miscellaneous Strings
	 *****************************/
	
	{ TEXT_GENERAL_INFO_PLEA,       0,
		"\n"
		"¿Le gustaría ver Tidy en un español correcto? Por favor considere \n"
		"ayudarnos a localizar HTML Tidy. Para más detalles consulte \n"
		"https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
	},
	
	
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
	{ TidyMakeClean,                0,
		"Esta opción especifica si Tidy debe realizar la limpieza de algún "
		"legado etiquetas de presentación (actualmente <code>&lt;i&gt;</code>, "
		"<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> cuando encerrados "
		"dentro de las etiquetas apropiadas en línea y "
		"<code>&lt;font&gt;</code>). Si se establece en <code>yes</code>, "
		"entonces etiquetas existentes serán reemplazados con CSS "
		"<code>&lt;style&gt;</code> y estructural markup según corresponda. "
	},
	
	
	/*****************************
	 ** Console Application
	 *****************************/
	{ TC_TXT_HELP_LANG_1,           0,
		"\nLa opción --language (o --lang) indica el lenguaje Tidy debe \n"
		"utilizar para comunicar su salida. Tenga en cuenta que esto no es \n"
		"un servicio de traducción de documentos, y sólo afecta a los mensajes \n"
		"que Tidy comunica a usted. \n"
		"\nCuando se utiliza la línea de comandos el argumento --language debe \n"
		"utilizarse antes de cualquier argumento que dan lugar a la producción, \n"
		"de lo contrario Tidy producirá la salida antes de que se conozca el \n"
		"idioma a utilizar. \n"
		"\nAdemás de los códigos de idioma estándar POSIX, Tidy es capaz de \n"
		"entender códigos de idioma legados de Windows. Tenga en cuenta que \n"
		"este lista indica los códigos Tidy entiende, y no indica que \n"
		"actualmente el idioma está instalado. \n"
		"\nLa columna más a la derecha indica cómo Tidy comprenderá el \n"
		"legado nombre de Windows.\n\n"
	},
	{ TC_TXT_HELP_LANG_2,           0,
		"\nLos siguientes idiomas están instalados actualmente en Tidy. Tenga \n"
		"en cuenta que no hay garantía de que están completos; sólo quiere decir \n"
		"que un desarrollador u otro comenzaron a añadir el idioma indicado. \n"
		"\nLocalizaciones incompletas por defecto se usan \"en\" cuando sea \n"
		"necesario. ¡Favor de informar los desarrolladores de estes casos! \n\n"
	},
	{ TC_TXT_HELP_LANG_3,           0,
		"\nSi Tidy es capaz de determinar la configuración regional entonces \n"
		"Tidy utilizará el lenguaje de forma automática de la configuración \n"
		"regional. Por ejemplo los sistemas de tipo Unix utilizan los variables \n"
		"$LANG y/o $LC_ALL. Consulte a su documentación del sistema para \n"
		"obtener más información.\n\n"
	},
	
	
	/* This MUST be present and last. */
	{ TIDY_MESSAGE_TYPE_LAST,       0,   NULL                                                                      }
}};


#endif /* language_es_h */
