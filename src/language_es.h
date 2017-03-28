#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
 * Localization support for HTML Tidy.
 *
 *
 * This file is a localization file for HTML Tidy. It will have been machine
 * generated or created and/or edited by hand. Both are valid options, but
 * please help keep our localization efforts simple to maintain by maintaining
 * the structure of this file, and changing the check box below if you make
 * changes (so others know the file origin):
 *
 * [X] THIS FILE IS MACHINE GENERATED. It is a localization file for the
 *     language (and maybe region) "es". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_es.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_es.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-03-22 15:54:52
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


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
    { TidyMakeClean,          0,        
        "Esta opción especifica si Tidy debe realizar la limpieza de algún legado etiquetas de "
        "presentación (actualmente <code>&lt;i&gt;</code>, <code>&lt;b&gt;</code>, <code>&lt;center&gt;</"
        "code> cuando encerrados dentro de las etiquetas apropiadas en línea y <code>&lt;font&gt;</"
        "code>). Si se establece en <code>yes</code>, entonces etiquetas existentes serán reemplazados "
        "con CSS <code>&lt;style&gt;</code> y estructural markup según corresponda. "
    },

#if SUPPORT_ASIAN_ENCODINGS
    { TidyNCR,                0, "Esta opción especifica si Tidy debe permitir referencias de caracteres numéricos. "   },
#endif /* SUPPORT_ASIAN_ENCODINGS */

    { TEXT_GENERAL_INFO_PLEA, 0,        
        "¿Le gustaría ver Tidy en un español correcto? Por favor considere "
        "ayudarnos a localizar HTML Tidy. Para más detalles consulte "
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },

#if SUPPORT_CONSOLE_APP
    { TC_TXT_HELP_LANG_1,     0,        
        "La opción -language (o -lang) indica el lenguaje Tidy debe "
        "utilizar para comunicar su salida. Tenga en cuenta que esto no es "
        "un servicio de traducción de documentos, y sólo afecta a los mensajes "
        "que Tidy comunica a usted. "
        "\n\n"
        "Cuando se utiliza la línea de comandos el argumento -language debe "
        "utilizarse antes de cualquier argumento que dan lugar a la producción, "
        "de lo contrario Tidy producirá la salida antes de que se conozca el "
        "idioma a utilizar. "
        "\n\n"
        "Además de los códigos de idioma estándar POSIX, Tidy es capaz de "
        "entender códigos de idioma legados de Windows. Tenga en cuenta que "
        "este lista indica los códigos Tidy entiende, y no indica que "
        "actualmente el idioma está instalado. "
        "\n\n"
        "La columna más a la derecha indica cómo Tidy comprenderá el "
        "legado nombre de Windows."
        "\n\n"
        "Tidy está utilizando la configuración regional %s."
    },
    { TC_TXT_HELP_LANG_2,     0,        
        "Los siguientes idiomas están instalados actualmente en Tidy. Tenga "
        "en cuenta que no hay garantía de que están completos; sólo quiere decir "
        "que un desarrollador u otro comenzaron a añadir el idioma indicado."
        "\n\n"
        "Localizaciones incompletas por defecto se usan \"en\" cuando sea "
        "necesario. ¡Favor de informar los desarrolladores de estes casos!"
    },
    { TC_TXT_HELP_LANG_3,     0,        
        "Si Tidy es capaz de determinar la configuración regional entonces "
        "Tidy utilizará el lenguaje de forma automática de la configuración "
        "regional. Por ejemplo los sistemas de tipo Unix utilizan los variables "
        "$LANG y/o $LC_ALL. Consulte a su documentación del sistema para "
        "obtener más información."
        "\n\n"
        "Tidy está utilizando la configuración regional %s."
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST, 0, NULL
    }

}};


#endif /* language_es_h */
