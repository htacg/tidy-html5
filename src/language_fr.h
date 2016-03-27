#ifndef language_fr_h
#define language_fr_h
/*
 * language_fr.h
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
 *     language (and maybe region) "fr". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_fr.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_fr.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=
 *   PO_REVISION_DATE=
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
static uint whichPluralForm_fr(uint n) {
    /* Plural-Forms: nplurals=2; */
    return (n > 1);
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_fr = { whichPluralForm_fr, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                0, "fr"
    },
    { ACCESS_URL,                   0, "http://www.w3.org/WAI/GL"                                                              },
    { ATRC_ACCESS_URL,              0, "http://www.html-tidy.org/Accessibility/"                                               },
    { FILE_CANT_OPEN,               0, "Impossible d'ouvrir « %s »\n"                                                        },
    { LINE_COLUMN_STRING,           0, "Ligne: %d Col: %d - "                                                                  },
    { STRING_CONTENT_LOOKS,         0, "Le contenu du document ressemble à %s"                                                },
    { STRING_DISCARDING,            0, "dépose"                                                                               },
    { STRING_DOCTYPE_GIVEN,         0, "DOCTYPE donné est «%s»"                                                             },
    { STRING_ERROR_COUNT,           0, "%u %s, %u %s trouvées!"                                                               },
    { STRING_ERROR_COUNT_ERROR,     0, "erreur"                                                                                },
    { STRING_ERROR_COUNT_ERROR,     1, "erreurs"                                                                               },
    { STRING_ERROR_COUNT_WARNING,   0, "alarme"                                                                                },
    { STRING_ERROR_COUNT_WARNING,   1, "alarmes"                                                                               },
    { STRING_HELLO_ACCESS,          0, "Contrôles d'accessibilité: version 0.1"                                              },
    { STRING_HTML_PROPRIETARY,      0, "HTML Proprietary"                                                                      },
    { STRING_MISSING_MALFORMED,     0, "argument manquant ou incorrect pour l'option: %s"                                      },
    { STRING_NO_ERRORS,             0, "Aucun avertissement ou les erreurs ne trouvées."                                      },
    { STRING_NO_SYSID,              0, "Aucun identificateur de système dans le doctype émis"                                },
    { STRING_NOT_ALL_SHOWN,         0, "Pas tous les avertissements/erreurs ont été présentés."                            },
    { STRING_PLAIN_TEXT,            0, "le texte brut"                                                                         },
    { STRING_REPLACING,             0, "remplaçant"                                                                           },
    { STRING_SPECIFIED,             0, "spécifié"                                                                            },
    { STRING_UNKNOWN_FILE,          0, "%s: Impossible d'ouvrir le fichier \"%s\"\n"                                           },
    { STRING_UNKNOWN_OPTION,        0, "option inconnue: %s"                                                                   },
    { STRING_UNRECZD_OPTION,        0, "option non reconnue -%c utiliser -help pour lister les options\n"                      },
    { STRING_XML_DECLARATION,       0, "déclaration XML"                                                                      },
    { TEXT_HTML_T_ALGORITHM,        0,        
        "\n"
        "       - D'abord, cherchez à gauche de la position de la cellule de trouver \n"
        "         des cellules d'en-tête de ligne.\n"
        "       - Puis rechercher vers le haut pour trouver les cellules d'en-tête \n"
        "         de colonne.\n"
        "       - La recherche dans une direction donnée arrête lorsque le bord \n"
        "         de la table est atteinte ou lorsque la cellule de données est \n"
        "         trouvé après une cellule d'en-tête.\n"
        "       - Têtes de ligne sont insérés dans la liste dans l'ordre où ils \n"
        "         apparaissent dans la table.\n"
        "       - Pour les tables de gauche à droite, en-têtes sont insérés de \n"
        "         gauche à droite.\n"
        "       - Têtes de colonnes sont insérés après-têtes de ligne, dans\n"
        "         l'ordre où ils apparaissent dans le tableau, de haut en bas.\n"
        "       - Si une cellule d'en-tête a les têtes ensemble d'attributs, puis \n"
        "         les en-têtes référencée par cet attribut sont insérés dans la \n"
        "         liste et le recherche arrête pour la direction du courant.\n"
        "         TD cellules qui fixent l'attribut de l'axe sont également \n"
        "         traités comme des cellules d'en-tête.\n"
        "\n"
    },
    { TEXT_WINDOWS_CHARS,           0,        
        "Personnages codes pour les polices Microsoft Windows dans la gamme\n"
        "128-159 ne pas être reconnus sur d'autres plateformes. Vous êtes\n"
        "au lieu recommandé d'utiliser les entités nommées, par exemple &trade; \n"
        "plutôt code que Windows de caractères 153 (0x2122 en Unicode). Notez que\n"
        "à partir de Février 1998 quelques navigateurs supportent les nouvelles \n"
        "entités.\n"
        "\n"
    },
    { TEXT_VENDOR_CHARS,            0,        
        "Il est peu probable que fournisseur spécifique, encodages qui dépendent du système\n"
        "travailler assez largement sur le World Wide Web; vous devriez éviter d'utiliser le "
        "%s codage de caractères de $, à la place il est recommandé \n"
        "de  utiliser entités nommées, par exemple &trade;.\n"
    },
    { TEXT_SGML_CHARS,              0,        
        "Les codes de caractères 128 à 159 (U + 0080 à U + 009F) ne sont pas autorisés \n"
        "en HTML; même si elles l'étaient, ils seraient probablement les \n"
        "caractères non imprimables de contrôle.\n"
        "Tidy supposé que vous vouliez faire référence à un personnage avec la même valeur "
        "d'octet\n"
        "l'encodage %s et remplacé cette référence avec l'équivalent Unicode.\n"
        "\n"
    },
    { TEXT_INVALID_UTF8,            0,        
        "Les codes de caractères UTF-8 doivent être dans la gamme: U + 0000 à U + 10FFFF.\n"
        "La définition de l'UTF-8 à l'annexe D de la norme ISO / CEI 10646-1: 2000 a "
        "également\n"
        "permet l'utilisation de séquences de cinq et six octets pour coder\n"
        "des personnages qui sont en dehors de la gamme de l'ensemble de caractères Unicode;\n"
        "ces séquences de cinq et six octets sont illégales pour l'utilisation de\n"
        "UTF-8 comme une transformation de caractères Unicode. ISO / IEC 10646\n"
        "ne permet pas la cartographie des substituts non appariés, ni U + FFFE et U + FFFF\n"
        "(mais il ne permet d'autres non-caractères). Pour plus d'informations s'il vous "
        "plaît se référer à\n"
        "http://www.unicode.org/ et http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
        "\n"
    },
    { TEXT_INVALID_UTF16,           0,        
        "Codes de caractères pour UTF-16 doit être dans la gamme: U + 0000 à U + 10FFFF.\n"
        "La définition de UTF-16 dans l'annexe C de l'ISO/CEI 10646-1: 2000 n'autorise pas "
        "le\n"
        "mappage des substituts non appariés. Pour plus d'informations, veuillez vous "
        "référer\n"
        "à http://www.unicode.org/ et http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
        "\n"
    },
    { TEXT_INVALID_URI,             0,        
        "URI doit être correctement protégés, ils ne doivent pas contenir unescaped\n"
        "caractères ci-dessous U + 0021, y compris le caractère d'espace et non\n"
        "ci-dessus U + 007E. Tidy échappe à l'URI pour vous comme recommandé par\n"
        "HTML 4.01 section B.2.1 et XML 1.0 section 4.2.2. Certains agents utilisateurs\n"
        "utiliser un autre algorithme pour échapper à ces URI et un serveur-verso\n"
        "scripts dépendent de cela. Si vous voulez compter sur cela, vous devez\n"
        "échapper à l'URI sur votre propre. Pour plus d'informations s'il vous plaît se "
        "référer à\n"
        "http://www.w3.org/International/O-URL-and-ident.html\n"
        "\n"
    },
    { TEXT_BAD_FORM,                0,        
        "Vous devrez peut-être déplacer un ou deux de la<form>et</form>\n"
        "tags. Éléments HTML doivent être correctement imbriquées et les éléments\n"
        "de formulaire ne font pas exception. Par exemple, vous ne devez pas placer la\n"
        "<form>dans une cellule et la </form>dans un autre. Si le <form>est placé\n"
        "devant une table, le </form>ne peut pas être placé à l'intérieur de la table !\n"
        "Notez qu'une forme ne peut pas être imbriquée dans un autre !\n"
        "\n"
    },
    { TEXT_BAD_MAIN,                0,        
        "Qu'un seul <main> élément est autorisé dans un document.\n"
        "Les <main>éléments ont été jetées, qui peut invalider le document\n"
        "\n"
    },
    { TEXT_M_SUMMARY,               0,        
        "L'attribut summary table devrait servir à décrire la structure\n"
        "de la table. Il est très utile pour les personnes utilisant des\n"
        "navigateurs non visuels. Les attributs de portée et en-têtes\n"
        "pour les cellules d'un tableau servent utiles pour spécifier les\n"
        "en-têtes s'appliquent à chaque cellule du tableau, permettant\n"
        "aux navigateurs non visuels fournir un contexte pour chaque cellule.\n"
        "\n"
    },
    { TEXT_M_IMAGE_ALT,             0,        
        "L'attribut alt devrait servir à donner une brève description d'une\n"
        "image ; Il faudrait aussi des descriptions plus longues avec l'attribut\n"
        "longdesc qui prend une URL liée à la description. Ces mesures sont\n"
        "nécessaires pour les personnes utilisant des navigateurs textuels.\n"
        "\n"
    },
    { TEXT_M_IMAGE_MAP,             0,        
        "Utilisation côté client images interactives préférence cartes-images\n"
        "côté serveur comme celui-ci est inaccessibles aux personnes utilisant\n"
        "des navigateurs non graphiques. En outre, les cartes côté client sont\n"
        "plus faciles à mettre en place et fournir une rétroaction immédiate\n"
        "aux utilisateurs.\n"
        "\n"
    },
    { TEXT_M_LINK_ALT,              0,        
        "Liens hypertextes définie à l'aide d'une hyperimage côté client, vous\n"
        "devez utiliser l'attribut alt pour fournir une description textuelle de la\n"
        "liaison pour les personnes utilisant des navigateurs textuels.\n"
        "\n"
    },
    { TEXT_USING_FRAMES,            0,        
        "Pages conçues à l'aide de cadres pose des problèmes pour\n"
        "les personnes qui sont aveugles ou utilisez un navigateur qui\n"
        "ne supporte pas les frames. Une page de base de cadres doit\n"
        "toujours inclure une disposition alternative à l'intérieur d'un\n"
        "élément NOFRAMES.\n"
        "\n"
    },
    { TEXT_ACCESS_ADVICE1,          0,        
        "Pour plus d'informations sur la façon de rendre vos pages\n"
        "accessibles, voir http://www.w3.org/WAI/GL"
    },
    { TEXT_ACCESS_ADVICE2,          0, "et http://www.html-tidy.org/Accessibility/"                                            },
    { TEXT_USING_LAYER,             0,        
        "Les Cascading Style Sheets (CSS) mécanisme de positionnement\n"
        "Il est recommandé de préférence à la propriétaire <LAYER>\n"
        "élément grâce à l'appui du fournisseur limitée pour la LAYER.\n"
        "\n"
    },
    { TEXT_USING_SPACER,            0,        
        "Il est recommandé d'utiliser les CSS pour contrôler blanc\n"
        "espace (par exemple pour retrait, les marges et interlignes).\n"
        "Le <SPACER> élément propriétaire a le soutien des fournisseurs limité.\n"
        "\n"
    },
    { TEXT_USING_FONT,              0,        
        "Il est recommandé d'utiliser les CSS pour spécifier la police et\n"
        "propriétés telles que sa taille et sa couleur. Cela permettra de réduire\n"
        "la taille des fichiers HTML et de les rendre plus faciles à entretenir\n"
        "rapport à l'utilisation <FONT> éléments.\n"
        "\n"
    },
    { TEXT_USING_NOBR,              0,        
        "Il est recommandé d'utiliser les CSS pour contrôler les sauts de ligne.\n"
        "Utilisez \"white-space: nowrap\" pour inhiber emballage en place\n"
        "d'insertion <NOBR> ... </ NOBR> dans le balisage.\n"
        "\n"
    },
    { TEXT_USING_BODY,              0,        
        "Il est recommandé d'utiliser les CSS pour spécifier la page et de liaison des "
        "couleurs\n"
    },
    { TEXT_NEEDS_INTERVENTION,      0,        
        "Ce document contient des erreurs qui doivent être résolus avant\n"
        "utilisant HTML Tidy pour générer une version rangé.\n"
        "\n"
    },
    { TEXT_GENERAL_INFO,            0,        
        "A propos de HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Les rapports de bugs et commentaires: https://github.com/htacg/tidy-html5/issues\n"
        "Liste officielle de diffusion: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Spécification HTML dernière: http://dev.w3.org/html5/spec-author-view/\n"
        "Validez vos documents HTML: http://validator.w3.org/nu/\n"
        "Hall de votre entreprise à rejoindre le W3C: http://www.w3.org/Consortium\n"
        "\n"
    },
    { TEXT_GENERAL_INFO_PLEA,       0,        
        "\n"
        "Parlez-vous une langue autre que l'anglais ou une autre variante de\n"
        "Anglais? Considérez-nous aidant à localiser HTML Tidy. Pour plus de détails s'il "
        "vous plaît voir\n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md\n"
    },
    { TidyInfoString,               0, "Info:"                                                                                 },
    { TidyWarningString,            0, "Attention:"                                                                            },
    { TidyConfigString,             0, "Config:"                                                                               },
    { TidyAccessString,             0, "Accès:"                                                                               },
    { TidyErrorString,              0, "Erreur:"                                                                               },
    { TidyBadDocumentString,        0, "Document:"                                                                             },
    { TidyFatalString,              0, "Panique:"                                                                              },
    { ENCODING_MISMATCH,            0, "codage d'entrée spécifiée (%s) ne correspond pas réelle encodage d'entrée (%s)"   },
    { VENDOR_SPECIFIC_CHARS,        0, "%s de code de caractère invalide l'%s"                                                },
    { INVALID_SGML_CHARS,           0, "%s de code de caractère invalide l'%s"                                                },
    { INVALID_UTF8,                 0, "%s invalides octets UTF-8 de (char. codes %s)"                                         },
    { INVALID_UTF16,                0, "paire de substitution non valide UTF-16 (code de caract. %s) %s"                       },
    { INVALID_NCR,                  0, "Référence de caractère numérique non valide de %s %s"                              },
    { MISSING_SEMICOLON,            0, "entité « %s » ne s'arrête pas à «; »"                                           },
    { MISSING_SEMICOLON_NCR,        0, "Référence de caractère numérique « %s » n'est pas se terminer par «; »"        },
    { UNESCAPED_AMPERSAND,          0, "sans séquence d'échappement & qui devrait être écrit comme &amp;"                  },
    { UNKNOWN_ENTITY,               0, "sans séquence d'échappement & ou entité inconnue « %s »"                          },
    { APOS_UNDEFINED,               0, "nommée l'entité ' seulement défini en XML/XHTML"                                    },
    { INSERTING_ATTRIBUTE,          0, "%s insérer l'attribut « %s »"                                                       },
    { INSERTING_AUTO_ATTRIBUTE,     0, "%s insérer l'attribut « %s », à l'aide de la valeur « %s »"                      },
    { MISSING_ATTR_VALUE,           0, "L'attribut %s a une valeur non valide \"%s\""                                          },
    { UNKNOWN_ATTRIBUTE,            0, "L'attribut %s a une valeur non valide \"%s\""                                          },
    { PROPRIETARY_ATTRIBUTE,        0, "L'attribut %s a une valeur non valide \"%s\""                                          },
    { JOINING_ATTRIBUTE,            0, "%s rejoignant les valeurs d'attribut répétée « %s »"                              },
    { XML_ATTRIBUTE_VALUE,          0, "L'attribut %s a une valeur non valide \"%s\""                                          },
    { XML_ID_SYNTAX,                0, "ID de %s « %s » utilise la syntaxe XML ID"                                           },
    { ATTR_VALUE_NOT_LCASE,         0, "valeur d'attribut de %s « %s » doit être en minuscules pour XHTML"                  },
    { PROPRIETARY_ATTR_VALUE,       0, "valeur d'attribut propriétaire de %s « %s »"                                        },
    { ANCHOR_NOT_UNIQUE,            0, "%s anchor \"%s\" déjà défini"                                                       },
    { BAD_ATTRIBUTE_VALUE,          0, "L'attribut %s \"%s\" a une valeur non valide \"%s\""                                   },
    { BAD_ATTRIBUTE_VALUE_REPLACED, 0, "%s attribut « %s » a une valeur non valide « %s » et a été remplacé"            },
    { INVALID_ATTRIBUTE,            0, "nom d'attribut de %s « %s » (valeur = « %s ») n'est pas valide"                    },
    { REPEATED_ATTRIBUTE,           0, "%s laissant tomber la valeur « %s » pour l'attribut répétée « %s »"             },
    { INVALID_XML_ID,               0, "%s ne peut pas copier le nom attribut id"                                              },
    { UNEXPECTED_GT,                0, "manquant '>' pour tag: %s"                                                             },
    { UNEXPECTED_QUOTEMARK,         0, "%s inattendue ou double quote mark"                                                    },
    { MISSING_QUOTEMARK,            0, "%s attribut manquant apostrophe droite"                                                },
    { UNEXPECTED_END_OF_FILE_ATTR,  0, "%s fin de fichier lors de l'analyse d'attributs"                                       },
    { ID_NAME_MISMATCH,             0, "%s id et le nom valeur d'attribut mismatch"                                            },
    { BACKSLASH_IN_URI,             0, "référence URI %s contient des anti-slash. Faute de frappe ?"                         },
    { FIXED_BACKSLASH,              0, "%s conversion de barre oblique inverse d'URI de slash"                                 },
    { ILLEGAL_URI_REFERENCE,        0, "%s mal échappé référence URI"                                                      },
    { ESCAPED_ILLEGAL_URI,          0, "%s échapper malformé référence URI"                                                },
    { NEWLINE_IN_URI,               0, "rejeter la nouvelle ligne de %s en référence URI"                                    },
    { WHITE_IN_URI,                 0, "jeter le espaces de %s en référence URI"                                             },
    { UNEXPECTED_EQUALSIGN,         0, "%s unexpected '=', nom d'attribut attendu"                                             },
    { MISSING_IMAGEMAP,             0, "%s doivent utiliser côté client image map"                                           },
    { MISSING_ATTRIBUTE,            0, "%s manque attribut \"%s\""                                                             },
    { NESTED_EMPHASIS,              0, "accent imbriquée %s"                                                                  },
    { NESTED_QUOTATION,             0, "imbriqué \"q\" éléments, typo possible"                                             },
    { OBSOLETE_ELEMENT,             0, "remplaçant élément obsolète %s avec %s"                                            },
    { COERCE_TO_ENDTAG_WARN,        0, "<%s> est probablement destinée en tant que </%s>"                                     },
    { REMOVED_HTML5,                0, "L'élément de %s retiré HTML5"                                                       },
    { BAD_SUMMARY_HTML5,            0, "L'attribut summary sur l'élément du %s est obsolète dans HTML5"                     },
    { TRIM_EMPTY_ELEMENT,           0, "rognage vide %s"                                                                       },
    { REPLACING_ELEMENT,            0, "remplaçant %s avec %s"                                                                },
    { COERCE_TO_ENDTAG,             0, "<%s> est probablement destinée en tant que </%s>"                                     },
    { REPLACING_UNEX_ELEMENT,       0, "remplacement inattendu %s avec %s"                                                     },
    { MISSING_ENDTAG_FOR,           0, "manquant </%s>"                                                                        },
    { MISSING_ENDTAG_BEFORE,        0, "manquante </%s> avant %s"                                                              },
    { DISCARDING_UNEXPECTED,        0, "rejet inattendu %s"                                                                    },
    { NON_MATCHING_ENDTAG,          0, "remplacement inattendu %s avec </%s>"                                                  },
    { TAG_NOT_ALLOWED_IN,           0, "%s n'est pas autorisé dans <%s> éléments"                                           },
    { MISSING_STARTTAG,             0, "manquant <%s>"                                                                         },
    { UNEXPECTED_ENDTAG,            0, "rejet inattendu </%s>"                                                                 },
    { TOO_MANY_ELEMENTS,            0, "trop de %s éléments"                                                                 },
    { USING_BR_INPLACE_OF,          0, "utilisant <br> à la place de %s"                                                      },
    { INSERTING_TAG,                0, "insertion implicite <%s>"                                                              },
    { CANT_BE_NESTED,               0, "%s ne peut pas être imbriquée"                                                       },
    { PROPRIETARY_ELEMENT,          0, "%s n'est pas approuvé par le W3C"                                                     },
    { ILLEGAL_NESTING,              0, "%s ne doivent pas être imbriqués"                                                    },
    { NOFRAMES_CONTENT,             0, "%s non à l'intérieur 'noframes'"                                                     },
    { UNEXPECTED_END_OF_FILE,       0, "fin inattendue du fichier %s"                                                          },
    { ELEMENT_NOT_EMPTY,            0, "%s élément non vide ou pas fermée"                                                  },
    { UNEXPECTED_ENDTAG_IN,         0, "inattendus </%s> dans <%s>"                                                            },
    { TOO_MANY_ELEMENTS_IN,         0, "trop de %s éléments dans <%s>"                                                       },
    { UNESCAPED_ELEMENT,            0, "unescaped %s dans le contenu pre"                                                      },
    { DOCTYPE_AFTER_TAGS,           0, "<! DOCTYPE> est pas autorisé après éléments"                                       },
    { MISSING_TITLE_ELEMENT,        0, "insertion manquante élément 'title'"                                                 },
    { INCONSISTENT_VERSION,         0, "DOCTYPE HTML ne correspond pas à un contenu"                                          },
    { MISSING_DOCTYPE,              0, "manquante <!DOCTYPE> déclaration"                                                     },
    { CONTENT_AFTER_BODY,           0, "contenu se produit après la fin du body"                                              },
    { MALFORMED_COMMENT,            0, "tirets adjacents dans un commentaire"                                                  },
    { BAD_COMMENT_CHARS,            0, "attendre -- ou >"                                                                      },
    { BAD_CDATA_CONTENT,            0, "'<' + '/' + lettre non permis ici"                                                     },
    { INCONSISTENT_NAMESPACE,       0, "le namespace HTML ne correspond pas au contenu"                                        },
    { SPACE_PRECEDING_XMLDECL,      0, "supprimant l'espace blanc précédent Déclaration XML"                                },
    { MALFORMED_DOCTYPE,            0, "en rejetant malformé <!DOCTYPE>"                                                      },
    { BAD_XML_COMMENT,              0, "commentaires XML ne peut pas contenir --"                                              },
    { DTYPE_NOT_UPPER_CASE,         0, "SYSTEM, PUBLIC, W3C, DTD, EN doit être en majuscules"                                 },
    { ENCODING_IO_CONFLICT,         0, "encodage de sortie ne fonctionne pas avec la sortie standard"                          },
    { SUSPECTED_MISSING_QUOTE,      0, "manquant guillemet pour la valeur d'attribut"                                          },
    { DUPLICATE_FRAMESET,           0, "élément répété FRAMESET"                                                          },
    { UNKNOWN_ELEMENT,              0, "%s n'est pas reconnue !"                                                               },
    { PREVIOUS_LOCATION,            0, "<%s> précédemment mentionnés"                                                       },
    { TidyXmlDecl,                  0,        
        "Cette option spécifie si Tidy devrait ajouter la déclaration XML lors de la sortie "
        "XML ou XHTML. <br/> Notez que si l'entrée comprend déjà un <code> & lt;?xml ... &&gt;"
        "</code> déclaration alors cette option sera ignorée. <br/> Si l'encodage pour la "
        "sortie est différente de <var>ascii</var>, l'un des l'encodage <var>utf*</var> ou "
        "<var>raw</var>, la déclaration est toujours ajouté que requis par la norme XML."
    },
    { TidyXmlSpace,                 0,        
        "Cette option spécifie si tidy doit ajouter <code>xml:espace=\"préserver \"</code> "
        "pour des éléments tels que <code><pré></code>, <code><style></code> et "
        "<code><script></code> lors de la génération de XML. <br />Il est nécessaire si "
        "l'espace blanc dans ces éléments doit être analysée de manière appropriée sans avoir "
        "accès à la DTD."
    },
    { TidyAltText,                  0,        
        "Cette option spécifie la valeur par défaut <code>alt=</code> utilise le texte Tidy "
        "pour <code>&lt;img&gt;</code> attributs lorsque le <code>alt=</code> attribut est "
        "absent. <br/> Utiliser avec précaution, car il est de votre responsabilité de rendre "
        "vos documents accessibles aux personnes qui ne peuvent pas voir les images."
    },
    { TidyXmlPIs,                   0,        
        "Cette option spécifie si Tidy doit modifier l'analyse syntaxique des instructions de "
        "traitement pour exiger <code>?&gt;</code> comme terminateur plutôt que <code>&gt;</"
        "code>. <br/> Cette option est automatiquement activée si l'entrée est en XML."
    },
    { TidyMakeBare,                 0,        
        "Cette option spécifie si Tidy doit dépouiller Microsoft HTML spécifique à partir de "
        "Word 2000 documents, et des espaces de sortie plutôt que des espaces insécables où "
        "ils existent dans l'entrée."
    },
    { TidyCSSPrefix,                0,        
        "Cette option spécifie le préfixe que Tidy utilise des règles de styles. <br/> Par "
        "défaut, <var>c</var> sera utilisé."
    },
    { TidyMakeClean,                0,        
        "Cette option spécifie si Tidy doit effectuer le nettoyage de certains anciens tags "
        "de présentation (actuellement de <code>& lt; i&gt;</code>, <code>&lt;b&gt;</code>, "
        "<code>&lt;centre&gt;</code> lorsque placé entre les balises inline appropriées, et "
        "<code>&lt; font&gt;</code>). Si <var>yes</var> puis balises existantes seront "
        "remplacées par CSS le <code>&lt;style&gt;</code> balises et le balisage structurel "
        "selon le cas."
    },
    { TidyGDocClean,                0,        
        "Cette option spécifie si Tidy doit permettre un comportement spécifique pour le "
        "nettoyage HTML exporté à partir de Google Docs."
    },
    { TidyDoctype,                  0,        
        "Cette option spécifie la déclaration DOCTYPE générée par Tidy. <br/> Si <var>omit</"
        "var> la sortie ne contiendra une déclaration DOCTYPE. Notez que ce cela implique "
        "aussi <code>numeric-entities</code> est réglé sur <var>yes</var>. <br/> Si "
        "<code>html5</code> le DOCTYPE est réglé sur <code>&lt;! DOCTYPE html&gt;</code>. <br/"
        "> Si <var>auto</var> (par défaut) Tidy utilisera une supposition basée sur le "
        "contenu du document. <br/> Si elle est définie <var>strict</var>, Tidy établira le "
        "DOCTYPE du HTML4 ou XHTML 1 DTD stricte. <br/> Si <var>loose</var>, le DOCTYPE est "
        "réglé sur le HTML4 ou XHTML1 loose (transitional) DTD. <br/> Alternativement, vous "
        "pouvez fournir une chaîne pour l'identificateur public formel (FPI).<br/> Par "
        "exemple: <br/> <code>doctype: \"- // ACME // DTD HTML. 3,14159 //EN\"</code> <br/> "
        "Si vous spécifiez le FPI pour un document XHTML, Tidy établira l'identifiant du "
        "système à une chaîne vide. Pour un document HTML, Tidy ajoute un identificateur de "
        "système que si l'on était déjà présent dans le but de préserver le mode de certains "
        "navigateurs de traitement. Tidy quitte le DOCTYPE pour les documents XML génériques "
        "inchangés. <br/> Cette option ne permet pas une validation du document de conformité."
    },
    { TidyDropEmptyElems,           0, "Cette option spécifie si Tidy doit jeter des éléments vides."                       },
    { TidyDropEmptyParas,           0, "Cette option spécifie si Tidy doit jeter des paragraphes vides."                      },
    { TidyFixUri,                   0,        
        "Cette option spécifie si Tidy doit vérifier les valeurs d'attributs qui portent URI "
        "pour des caractères illégaux et si ce sont trouvés, leur échapper en HTML 4 "
        "recommande."
    },
    { TidyPPrintTabs,               0,        
        "Cette option spécifie si tidy doit Indenter avec tabulation au lieu des espaces, en "
        "supposant <code>indent</code> est <var>yes</var>. <br/>Définir sur <var>yes</var> "
        "pour indenter avec des tabulations au lieu de la valeur par défaut des espaces. <br /"
        ">Utilisez l'option <code>indent-spaces</code> pour contrôler le nombre d'onglets "
        "Sortie par niveau de tiret. Notez que lorsque <code>indent-with-tabs</code> est "
        "activée. La valeur par défaut de <code>indent-spaces</code> est réinitialisé à "
        "<var>1</var>. <br/>Remarque <code>tab-size</code> contrôle la conversion des espaces "
        "d'entrée. Définissez-le à zéro pour conserver onglets de saisie."
    },
    { TidySkipNested,               0,        
        "Cette option spécifie que Tidy doit ignorer les balises imbriquées lors de l'analyse "
        "des données de script et de style."
    },
    { TC_CAT_DIAGNOSTICS,           0, "diagnostics"                                                                           },
    { TC_CAT_ENCODING,              0, "encoding"                                                                              },
    { TC_CAT_MARKUP,                0, "markup"                                                                                },
    { TC_CAT_MISC,                  0, "misc"                                                                                  },
    { TC_CAT_PRETTYPRINT,           0, "imprimer"                                                                              },
    { TC_LABEL_COL,                 0, "colonne"                                                                               },
    { TC_LABEL_FILE,                0, "fichier"                                                                               },
    { TC_LABEL_LANG,                0, "lang"                                                                                  },
    { TC_LABEL_LEVL,                0, "niveau"                                                                                },
    { TC_LABEL_OPT,                 0, "option"                                                                                },
    { TC_MAIN_ERROR_LOAD_CONFIG,    0, "Chargement du fichier de configuration \"%s\" a échoué, err =%d"                     },
    { TC_OPT_ACCESS,                0,        
        "faire des vérifications d'accessibilité supplémentaires (<niveau> = 0, 1, 2, 3). 0 "
        "est supposé si <niveau> est manquant."
    },
    { TC_OPT_ASCII,                 0, "utiliser ISO-8859-1 pour l'entrée, US-ASCII pour la sortie"                           },
    { TC_OPT_UPPER,                 0, "balises de force en majuscules"                                                        },
    { TC_TXT_HELP_3,                0,        
        "\n"
        "Options de configuration Tidy\n"
        "==========================\n"
        "Utilisez les options de configuration de Tidy comme arguments de ligne de commande "
        "sous la forme de «--option <value>\", par exemple, \"--indent-with-tabs yes\"\n"
        "\n"
        "Pour une liste de toutes les options de configuration, utiliser \"-help-config\"\n"
        " ou consultez à la man page (si votre OS en a un).\n"
        "\n"
        "Si votre environnement a un ensemble de variables à un point de Tidy \n"
        "$HTML_TIDY fichier de configuration puis Tidy va tenter de l'utiliser.\n"
        "\n"
        "Sur certaines plateformes Tidy tentera également d'utiliser une configuration "
        "spécifiée dans /etc/tidy.conf ou ~/.tidy.conf.\n"
        "\n"
        "Autre\n"
        "=====\n"
        "Entrée/sortie par défaut utiliser stdin/stdout respectivement.\n"
        "\n"
        "Options de simple lettre en dehors de -f peuvent être combinés\n"
        "comme dans: bien rangé -f errs.txt -imu foo.html\n"
        "\n"
        "renseignements\n"
        "===========\n"
        "Pour plus d'informations à propos de HTML Tidy, voir\n"
        "  http://www.html-tidy.org/\n"
        "\n"
        "Pour plus d'informations sur le langage HTML, consultez les rubriques suivantes:\n"
        "\n"
        "  HTML: Edition pour les auteurs Web (de la dernière spécification de HTML)\n"
        "  http://dev.w3.org/html5/spec-author-view\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG,           0,        
        "\n"
        "HTML Tidy paramètres de configuration\n"
        "\n"
        "Dans un fichier, utilisez le formulaire:\n"
        "\n"
        "envelopper: 72\n"
        "tiret: pas\n"
        "\n"
        "Quand il est spécifié sur la ligne de commande, utilisez le formulaire:\n"
        "\n"
        "--wrap 72 --indent pas\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,      0, "Nom"                                                                                   },
    { TC_TXT_HELP_CONFIG_TYPE,      0, "Type"                                                                                  },
    { TC_TXT_HELP_CONFIG_ALLW,      0, "Les valeurs autorisées"                                                               },
    { TC_TXT_HELP_LANG_1,           0,        
        "\n"
        "L'option --language (ou --lang) indique la langue Tidy\n"
        "doit utiliser pour communiquer sa sortie. S'il vous plaît noter que ce ne sont pas "
        "un service de traduction de documents, et affecte uniquement les messages qui Tidy "
        "communique à vous.\n"
        "\n"
        "Lorsqu'il est utilisé à partir de la ligne de commande de l'argument doit \n"
        "--language être utilisé avant des arguments qui résultent de la production, sinon "
        "Tidy\n"
        "va produire une sortie avant qu'il connaît la langue à utiliser.\n"
        "\n"
        "En plus des codes de langue standard POSIX, Tidy est capable de\n"
        "héritées compréhension codes de langue de Windows. S'il vous plaît noter que \n"
        "cette liste indique les codes Tidy comprend, et ne signifie pas que\n"
        "la langue est actuellement installé.\n"
        "\n"
        "La colonne de droite indique comment Tidy comprendra le\n"
        "héritage nom Windows.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,           0,        
        "\n"
        "Notez qu'il n'y a aucune garantie qu'ils sont complets; seulement ça\n"
        "un développeur ou d'une autre ont commencé à ajouter la langue indiquée.\n"
        "Localisations incomplètes ne seront par défaut \"et\" si nécessaire.\n"
        "S'il vous plaît signaler les cas de chaînes incorrectes à l'équipe Tidy.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,           0,        
        "\n"
        "Si Tidy est capable de déterminer votre localisation puis Tidy utilisera le\n"
        "langue locale automatiquement. Par exemple les systèmes Unix-like utilisent un $LANG "
        "et/ou $LC_ALL variable d'environnement. Consultez votre exploitation documentation "
        "du système pour plus d'informations.\n"
        "\n"
    },

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,       0, NULL
    }

}};


#endif /* language_fr_h */
