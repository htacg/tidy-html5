#ifndef language_es_h
#define language_es_h
/*
 * language_es.h
 * Localization support for HTML Tidy.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * This file generated on 2016-01-04 21:43:06 by jderry.
*/

#include "language.h"
#include "access.h"
#include "message.h"

/**
 *  IMPORTANT NOTE:
 *  This file was automatically generated with the `poconvert.rb` tool from
 *  a GNU gettext PO format. As such it is missing all of the commentary that
 *  is typically included in a Tidy language localization header file.
 */

static languageDictionary language_es = {

  /*
   * BEGIN AUTOMATIC CONTENT
   */

  { TIDY_LANGUAGE,            "es"                                                    },
  { FILE_CANT_OPEN,           "No se puede abrir “%s”\n"                              },
  { LINE_COLUMN_STRING,       "línea %d columna %d - "                                },
  { STRING_CONTENT_LOOKS,     "El contenido del documento se parece a %s"             },
  { STRING_DISCARDING,        "descartando"                                           },
  { STRING_DOCTYPE_GIVEN,     "Doctype dado es “%s”"                                  },
  { STRING_ERROR_COUNT,       "%u %s, %u %s se encontraron!"                          },
  { STRING_ERROR_PLURAL,      "errores"                                               },
  { STRING_HELLO_ACCESS,      
      "\n"
      "Los cheques de Accesibilidad: Versión 0.1\n"
      "\n"
  },
  { STRING_HTML_PROPRIETARY,  "HTML Propietario"                                      },
  { STRING_MISSING_MALFORMED, "argumento que falta o mal formado para la opción:%s"   },
  { STRING_NO_ERRORS,      
      "No se encontraron advertencias o errores.\n"
      "\n"
  },
  { TEXT_GENERAL_INFO_PLEA,      
      "\n"
      "¿Le gustaría ver Tidy en un español correcto? Por favor considere \n"
      "ayudarnos a localizar HTML Tidy. Para más detalles consulte \n"
      "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md \n"
  },
  { TidyMakeClean,      
      "Esta opción especifica si Tidy debe realizar la limpieza de algún legado etiquetas de "
      "presentación (actualmente <code>&lt;i&gt;</code>, <code>&lt;b&gt;</code>, <code>&lt;center&gt;</"
      "code> cuando encerrados dentro de las etiquetas apropiadas en línea y <code>&lt;font&gt;</"
      "code>). Si se establece en <code>yes</code>, entonces etiquetas existentes serán reemplazados "
      "con CSS <code>&lt;style&gt;</code> y estructural markup según corresponda. "
  },
  { TC_TXT_HELP_LANG_1,      
      "\n"
      "La opción --language (o --lang) indica el lenguaje Tidy debe \n"
      "utilizar para comunicar su salida. Tenga en cuenta que esto no es \n"
      "un servicio de traducción de documentos, y sólo afecta a los mensajes \n"
      "que Tidy comunica a usted. \n"
      "\n"
      "Cuando se utiliza la línea de comandos el argumento --language debe \n"
      "utilizarse antes de cualquier argumento que dan lugar a la producción, \n"
      "de lo contrario Tidy producirá la salida antes de que se conozca el \n"
      "idioma a utilizar. \n"
      "\n"
      "Además de los códigos de idioma estándar POSIX, Tidy es capaz de \n"
      "entender códigos de idioma legados de Windows. Tenga en cuenta que \n"
      "este lista indica los códigos Tidy entiende, y no indica que \n"
      "actualmente el idioma está instalado. \n"
      "\n"
      "La columna más a la derecha indica cómo Tidy comprenderá el \n"
      "legado nombre de Windows.\n"
      "\n"
  },
  { TC_TXT_HELP_LANG_2,      
      "\n"
      "Los siguientes idiomas están instalados actualmente en Tidy. Tenga \n"
      "en cuenta que no hay garantía de que están completos; sólo quiere decir \n"
      "que un desarrollador u otro comenzaron a añadir el idioma indicado. \n"
      "\n"
      "Localizaciones incompletas por defecto se usan \"en\" cuando sea \n"
      "necesario. ¡Favor de informar los desarrolladores de estes casos! \n"
      "\n"
  },
  { TC_TXT_HELP_LANG_3,      
      "\n"
      "Si Tidy es capaz de determinar la configuración regional entonces \n"
      "Tidy utilizará el lenguaje de forma automática de la configuración \n"
      "regional. Por ejemplo los sistemas de tipo Unix utilizan los variables \n"
      "$LANG y/o $LC_ALL. Consulte a su documentación del sistema para \n"
      "obtener más información.\n"
      "\n"
  },

  /*
   * END AUTOMATIC CONTENT
   */

  /* This MUST be present and last. */
   { TIDY_MESSAGE_TYPE_LAST,   NULL                                                    },
"
};

#endif /* language_es_h */
