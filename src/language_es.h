#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
 * Localization support for HTML Tidy.
 *
 * THIS FILE IS MACHINE GENERATED. It is a localization file for the
 * language (and maybe region) "es" and it should not be
 * edited manually. The source of these strings is a gettext PO file,
 * probably called "language_es.po" in Tidy's source.
 *
 * Tidy's source distribution also includes a script to convert PO files
 * into this file. Because PO files are friendly to translators and a
 * standard industry tool, please translate ONLY the PO files.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2016-01-29 10:54:42
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "language.h"
#include "access.h"
#include "message.h"


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_es(uint n) {
    /* Plural-Forms: nplurals=2; */
    return n != 1;
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_es = { whichPluralForm_es, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,          0, "es"
    },
    {/* This console output should be limited to 78 characters per line. 
      - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TEXT_GENERAL_INFO_PLEA, 0,        
        "\n"
        "\xc2\xbfLe gustar\xc3\xad""a ver Tidy en un espa\xc3\xb1ol correcto? Por favor considere \n"
        "ayudarnos a localizar HTML Tidy. Para m\xc3\xa1s detalles consulte \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
    },
    {/* Please use _only_ <code></code>, <em></em>, <strong></strong>, and <br/>.
        It's very important that <br/> be self-closing in this manner! 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TidyMakeClean,          0,        
        "Esta opci\xc3\xb3n especifica si Tidy debe realizar la limpieza de alg\xc3\xban legado etiquetas de "
        "presentaci\xc3\xb3n (actualmente <code>&lt;i&gt;</code>, <code>&lt;b&gt;</code>, <code>&lt;center&gt;</"
        "code> cuando encerrados dentro de las etiquetas apropiadas en l\xc3\xadnea y <code>&lt;font&gt;</"
        "code>). Si se establece en <code>yes</code>, entonces etiquetas existentes ser\xc3\xa1n reemplazados "
        "con CSS <code>&lt;style&gt;</code> y estructural markup seg\xc3\xban corresponda. "
    },

#if SUPPORT_ASIAN_ENCODINGS
    {/* Please use _only_ <code></code>, <em></em>, <strong></strong>, and <br/>.
        It's very important that <br/> be self-closing in this manner! 
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TidyNCR,                0, "Esta opci\xc3\xb3n especifica si Tidy debe permitir referencias de caracteres num\xc3\xa9ricos. "
    },
#endif /* SUPPORT_ASIAN_ENCODINGS */

    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_1,     0,        
        "\n"
        "La opci\xc3\xb3n --language (o --lang) indica el lenguaje Tidy debe \n"
        "utilizar para comunicar su salida. Tenga en cuenta que esto no es \n"
        "un servicio de traducci\xc3\xb3n de documentos, y s\xc3\xb3lo afecta a los mensajes \n"
        "que Tidy comunica a usted. \n"
        "\n"
        "Cuando se utiliza la l\xc3\xadnea de comandos el argumento --language debe \n"
        "utilizarse antes de cualquier argumento que dan lugar a la producci\xc3\xb3n, \n"
        "de lo contrario Tidy producir\xc3\xa1 la salida antes de que se conozca el \n"
        "idioma a utilizar. \n"
        "\n"
        "Adem\xc3\xa1s de los c\xc3\xb3""digos de idioma est\xc3\xa1ndar POSIX, Tidy es capaz de \n"
        "entender c\xc3\xb3""digos de idioma legados de Windows. Tenga en cuenta que \n"
        "este lista indica los c\xc3\xb3""digos Tidy entiende, y no indica que \n"
        "actualmente el idioma est\xc3\xa1 instalado. \n"
        "\n"
        "La columna m\xc3\xa1s a la derecha indica c\xc3\xb3mo Tidy comprender\xc3\xa1 el \n"
        "legado nombre de Windows.\n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_2,     0,        
        "\n"
        "Los siguientes idiomas est\xc3\xa1n instalados actualmente en Tidy. Tenga \n"
        "en cuenta que no hay garant\xc3\xad""a de que est\xc3\xa1n completos; s\xc3\xb3lo quiere decir \n"
        "que un desarrollador u otro comenzaron a a\xc3\xb1""adir el idioma indicado. \n"
        "\n"
        "Localizaciones incompletas por defecto se usan \"en\" cuando sea \n"
        "necesario. \xc2\xa1""Favor de informar los desarrolladores de estes casos! \n"
        "\n"
    },
    {/* This console output should be limited to 78 characters per line.
        - The strings "Tidy" and "HTML Tidy" are the program name and must not be translated. */
      TC_TXT_HELP_LANG_3,     0,        
        "\n"
        "Si Tidy es capaz de determinar la configuraci\xc3\xb3n regional entonces \n"
        "Tidy utilizar\xc3\xa1 el lenguaje de forma autom\xc3\xa1tica de la configuraci\xc3\xb3n \n"
        "regional. Por ejemplo los sistemas de tipo Unix utilizan los variables \n"
        "$LANG y/o $LC_ALL. Consulte a su documentaci\xc3\xb3n del sistema para \n"
        "obtener m\xc3\xa1s informaci\xc3\xb3n.\n"
        "\n"
    },

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST, 0, NULL
    }

}};


#endif /* language_es_h */
