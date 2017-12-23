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
 * (c) 2015-2017 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Orginating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2017-10-05 15:13:40
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


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
      TIDY_LANGUAGE,                                 0, "fr"
    },
    { TidyAccessibilityCheckLevel,                   0,        
        "Cette option précise le niveau de contrôle d'accessibilité que Tidy doit éventuellement exécuter. "
        "Le <br/>niveau <var>0 (Tidy Classic)</var> est équivalent au contrôle d'accessibilité de Tidy "
        "Classic. <br/>Pour plus d'informations sur le contrôle d'accessibilité de Tidy, consultez <a href="
        "\"http://www.html-tidy.org/accessibility/\"> la page d'accessibilité de Tidy</a>. "
    },
    { TidyAltText,                                   0,        
        "Cette option précise la valeur par défaut du texte <code>alt=</code> qu'utilise Tidy pour les "
        "attributs <code>&lt;img&gt;</code> lorsque l'attribut <code>alt=</code> est absent. <br/> Utiliser "
        "avec toute l'attention nécessaire, il est en effet de votre responsabilité de rendre vos documents "
        "accessibles aux personnes qui ne peuvent pas voir les images."
    },
    { TidyAnchorAsName,                              0,        
        "Cette option contrôle la suppression ou l'ajout de l'attribut <code>name</code> pour les éléments "
        "qui peuvent servir d'ancre. <br/>Si la valeur de l'attribut <code>name</code> est <var>yes</var>, "
        "et qu'il n'existe pas déjà, il est ajouté à la suite d'un attribut <code>id</code> existant, si la "
        "DTD le permet. <br/>Si sa valeur est <var>no</var>, tout attribut <code>name</code> existant est "
        "supprimé, si un attribut <code>id</code> existe ou a été ajouté. "
    },
    { TidyAsciiChars,                                0,        
        "Peut être utilisé pour modifier le comportement de l'option <code>clean</code> si sa valeur est "
        "<var>yes</var>. <br/> Lorsque la valeur de <code>clean</code> vaut <var>yes</var>, <code>&amp;"
        "emdash;</code>, <code>&amp;rdquo;</code>, et d'autres entités nommées sont déclassées vers leurs "
        "plus proches équivalents ASCII."
    },
    { TidyBlockTags,                                 0,        
        "Cette option définit de nouvelles balises de type bloc. Elle prend une liste de noms de balises "
        "séparés par un espace ou une virgule. <br/>À moins que vous ne déclariez de nouvelles balises, Tidy "
        "refusera de produire une sortie si l'entrée introduit préalablement des balises inconnues. <br/"
        ">Notez qu'il est impossible de modifier le modèle de contenu pour des éléments comme <code>&lt;"
        "table&gt;</code>, <code>&lt;ul&gt;</code>, <code>&lt;ol&gt;</code> et <code>&lt;dl&gt;</code>. <br/"
        ">Cette option est ignorée avec le mode XML. "
    },
    { TidyBodyOnly,                                  0,        
        "Cette option précise si Tidy doit seulement afficher les contenus de la balise <code>&lt;body&gt;</"
        "code> en tant que fragment HTML. <br/>Si sa valeur est <var>auto</var>, ceci est effectué seulement "
        "si la balise <code>&lt;body&gt;</code> a été déduite. <br/>L'intérêt est de pouvoir incorporer "
        "entièrement des pages existantes en tant que partie d'une autre page. <br/>Cette option n'a pas "
        "d'effet si la sortie XML a été demandée. "
    },
    { TidyBreakBeforeBR,                             0,        
        "Cette option précise si Tidy doit ajouter un saut de ligne avant chaque élément <code>&lt;br&gt;</"
        "code>."
    },
    { TidyCharEncoding,                              0,        
        "Cette option permet de préciser l'encodage des caractères qui sera utilisé par Tidy pour l'entrée "
        "et la sortie. <br/>Pour l'<var>ascii</var> Tidy acceptera les valeurs de caractère Latin-1 "
        "(ISO-8859-1), mais utilisera les entités pour tous les caractères de valeur &gt;127. <br/>Pour la "
        "valeur <var>raw</var>, Tidy produira des valeurs au dessus de 127, sans les traduires en entités. "
        "<br/>Pour <var>latin1</var>, les caractères au dessus de 255 seront écrits en entités. <br/>Pour "
        "<var>utf8</var>, Tidy suppose qu'aussi bien l'entrée que la sortie sont encodés en UTF-8. <br/>Vous "
        "pouvez utiliser <var>iso2022</var> pour les fichiers utilisant la famille d'encodage ISO-2022, par "
        "exemple ISO-2022-JP. <br/>Pour <var>mac</var> et <var>win1252</var>, Tidy acceptera les valeurs de "
        "caractères spécifiques de l'éditeur, mais utilisera les entités pour tous les caractères de valeur "
        "&gt;127. <br/>Pour les encodages non supportés, utilisez un utilitaire tiers pour convertir depuis "
        "et vers l'UTF-8. "
    },
    { TidyCoerceEndTags,                             0,        
        "Cette option précise si Tidy doit forcer la fermeture d'une balise d'ouverture, dans les cas où il "
        "semble qu'une balise de fin soit attendue; Dans cet exemple,<br/><code>&lt;span&gt;foo &lt;b&gt;"
        "bar&lt;b&gt; baz&lt;/span&gt;</code> <br/>Tidy va produire <br/><code>&lt;span&gt;foo &lt;b&gt;"
        "bar&lt;/b&gt; baz&lt;/span&gt;</code> "
    },
    { TidyCSSPrefix,                                 0,        
        "Cette option précise le préfixe que Tidy utilise pour les règles de styles. <br/> Par défaut, "
        "<var>c</var> sera utilisé."
    },
    { TidyDecorateInferredUL,                        0,        
        "Cette option précise si Tidy doit décorer le code déduit des éléments <code>&lt;ul&gt;</code> avec "
        "du balisage CSS pour éviter un décalage d'indentation vers la droite. "
    },
    { TidyDoctype,                                   0,        
        "Cette option spécifie la déclaration DOCTYPE générée par Tidy. <br/> Si <var>omit</var>, la sortie "
        "ne contiendra pas de déclaration DOCTYPE. Notez que cela implique aussi que <code>numeric-entities</"
        "code> soit réglé sur <var>yes</var>. <br/> Si <code>html5</code>, la déclaration DOCTYPE est réglée "
        "sur <code>&lt;! DOCTYPE html&gt;</code>. <br/> Si <var>auto</var> (par défaut), Tidy tentera de "
        "déduire la déclaration DOCTYPE à partir du contenu du document. <br/> Si elle est définie "
        "<var>strict</var>, Tidy utilisera la déclaration DOCTYPE HTML4 ou XHTML 1 DTD strict. <br/> Si "
        "<var>loose</var>, la déclaration DOCTYPE est réglée sur HTML4 ou XHTML1 loose (transitional) DTD. "
        "<br/> En alternative, vous pouvez fournir une chaîne pour l'identificateur public formel (FPI).<br/"
        "> Par exemple: <br/> <code>doctype: \"- // ACME // DTD HTML. 3,14159 //EN\"</code> <br/> Si vous "
        "spécifiez le FPI pour un document XHTML, Tidy établira l'identifiant système à une chaîne vide. "
        "Pour un document HTML, Tidy ajoute un identifiant système seulement s'il était déjà présent, dans "
        "le but de préserver le mode de rendu de certains navigateurs. Tidy ne tient pas compte de la "
        "déclaration DOCTYPE pour les documents XML génériques inchangés. <br/> Cette option ne permet pas "
        "une validation de la conformité du document."
    },
    { TidyDropEmptyElems,                            0, "Cette option précise si Tidy doit rejeter les éléments vides."                                          },
    { TidyDropEmptyParas,                            0, "Cette option précise si Tidy doit rejeter les paragraphes vides."                                       },
    { TidyDropPropAttrs,                             0,        
        "Cette option précise si Tidy doit enlever les attributs propriétaires, comme les attributs de "
        "liaison de données Microsoft. Les attributs supplémentaires qui ne sont pas autorisés dans la "
        "version HTML en sortie, seront supprimés avec l'utilisation conjointe de l'option <code>strict-tags-"
        "attributes</code>."
    },
    { TidyDuplicateAttrs,                            0,        
        "Cette option précise quel attribut, du premier ou du dernier, Tidy doit garder s'il est répété, par "
        "exemple dans le cas de deux attributs <code>align</code>."
    },
    { TidyEmacs,                                     0,        
        "Cette option précise si Tidy doit adopter un format de rapports d'erreurs et d'avertissements plus "
        "facilement exploitable par GNU Emacs."
    },
    { TidyEmptyTags,                                 0,        
        "Cette option précise les nouvelles balises inline. Cette option prend une liste de noms de balises "
        "séparés par un espace ou une virgule. <br/>Tant que vous n'avez pas déclaré de nouvelles balises, "
        "Tidy refusera de générer un fichier nettoyé si l'entrée contient des balises inconnues. <br/> "
        "pensez aussi à déclarer les balises vides, soit inline, soit bloc. <br/>Cette option est ignorée "
        "par le mode XML."
    },
    { TidyEncloseBlockText,                          0,        
        "Cette option précise si Tidy doit insérer un élément <code>&lt;p&gt;</code> pour encadrer un "
        "quelconque texte trouvé, dans n'importe quel élément qui permet de mélanger du contenu pour "
        "<var>HTML transitional</var> mais pas HTML strict. "
    },
    { TidyEncloseBodyText,                           0,        
        "Cette option précise si Tidy doit encadrer les textes trouvés dans l'élément <code>body</code>, par "
        "un élément <code>&lt;p&gt;</code>. <br/>Elle peut être utile lorsque vous voulez modifier du HTML "
        "existant au moyen d'une feuille de style. "
    },
    { TidyErrFile,                                   0,        
        "Cette option précise le fichier d'erreur que Tidy utilise pour les erreurs et avertissements. En "
        "principe les erreurs et avertissements sont envoyés vers la sortie <code>stderr</code>."
    },
    { TidyEscapeCdata,                               0,        
        "Cette option précise si Tidy doit convertir les sections <code>&lt;![CDATA[]]&gt;</code> en texte "
        "normal. "
    },
    { TidyEscapeScripts,                             0,        
        "Cette option entraîne l'échappement des items qui semblent être des balises de fermeture, ainsi "
        "<code>&lt;/g</code> sera échappée en <code>&lt;\\/g</code>. Positionner cette option à <var>no</"
        "var> si vous ne voulez pas cette fonctionnalité."
    },
    { TidyFixBackslash,                              0,        
        "Cette option précise si Tidy doit remplacer les caractères de barre oblique inversée (anti-slash, "
        "<code>\\</code>) dans les URLs avec des barres obliques (slash, <code>/</code>). "
    },
    { TidyFixComments,                               0,        
        "Cette option précise si Tidy doit remplacer les traits d'unions par le caractère <code>=</code> "
        "s'il rencontre des traits-d'unions adjacents. <br/>La valeur par défaut est <var>yes</var>. <br/"
        ">Cette option est fourni pour les utilisateurs de ColdFusion qui utilisent la syntaxe de "
        "commentaire: <code>&lt;!--- ---&gt;</code>. "
    },
    { TidyFixUri,                                    0,        
        "Cette option précise si Tidy doit vérifier les valeurs d'attributs qui comportent des caractères "
        "interdits pour les URI, et auquel cas les échapper selon les recommandations HTML 4."
    },
    { TidyForceOutput,                               0,        
        "Cette option précise si Tidy doit produire une sortie, même si des erreurs ont été rencontrées. <br/"
        ">Utilisez cette option avec attention; si Tidy affiche une erreur, cela implique que Tidy n'a pas "
        "été en mesure (ou n'est pas sûr) de pouvoir corriger cette erreur; en conséquence le résultat en "
        "sortie pourrait ne pas être conforme à vos attentes. "
    },
    { TidyGDocClean,                                 0,        
        "Cette option précise si Tidy doit activer un comportement spécifique pour le nettoyage du HTML "
        "exporté à partir de Google Docs."
    },
    { TidyHideComments,                              0, "Cette option précise si Tidy doit afficher en sortie les commentaires."                                 },
    { TidyHtmlOut,                                   0, "Cette option précise si Tidy doit embellir les sorties, lorsqu'il produit du HTML."                     },
    { TidyInCharEncoding,                            0,        
        "Cette option précise l'encodage de caractère que Tidy utilise pour l'entrée. Voir <code>char-"
        "encoding</code> pour plus d'informations."
    },
    { TidyIndentAttributes,                          0, "Cette option précise si Tidy doit placer chaque attribut sur une nouvelle ligne."                       },
    { TidyIndentCdata,                               0, "Cette option précise si Tidy doit indenter les sections <code>&lt;![CDATA[]]&gt;</code>."               },
    { TidyIndentContent,                             0,        
        "Cette option précise si Tidy doit indenter les balises de portée bloc. <br/>Si la valeur est "
        "<var>auto</var> Tidy décidera d'indenter ou pas le contenu des balises comme <code>&lt;title&gt;</"
        "code>, <code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, <code>&lt;td&gt;</"
        "code>, or <code>&lt;p&gt;</code> en s'appuyant sur le contenu incluant un élément de bloc. <br/"
        ">Positionner <code>indent</code> à <var>yes</var> peut engendrer des bugs de structure pour "
        "certains navigateurs. <br/>Utiliser l'option <code>indent-spaces</code> pour contrôler le nombre "
        "d'espaces ou de tabulations en sortie par niveau d'indentation, et <code>indent-with-tabs</code> "
        "pour préciser si les espaces ou tabulations sont utilisées. "
    },
    { TidyIndentSpaces,                              0,        
        "Cette option précise le nombre d'espaces ou de tabulations que Tidy utilise pour indenter le "
        "contenu lorsque <code>indent</code> est activé. <br/>Notez que la valeur par défaut pour cette "
        "option dépend de la valeur de <code>indent-with-tabs</code> (voir aussi cette option). "
    },
    { TidyInlineTags,                                0,        
        "Cette option porte sur les nouvelles balises inline non vides. Elle prend en valeur une liste de "
        "noms de balises, séparés par un espace ou une virgule. <br/>Sans déclaration de nouvelles balises, "
        "Tidy refusera de générer un fichier de sortie, si l'entrée comporte des balises inconnues. <br/"
        ">Cette option est ignorée avec le mode XML. "
    },
    { TidyJoinClasses,                               0,        
        "Cette option précise si Tidy doit combiner les noms de classe pour produire un nouveau nom de "
        "classe unique, lorsque plusieurs affectations de classes sont détectées sur un élément."
    },
    { TidyJoinStyles,                                0,        
        "Cette option indique si Tidy doit combiner les styles pour produire un nouveau style unique, "
        "lorsque plusieurs styles sont détectés sur un élément."
    },
    { TidyKeepFileTimes,                             0,        
        "Cette option précise si Tidy doit préserver la date de modification des fichiers sur lesquels il "
        "travaille directement. <br/>Mettre cette option à <var>yes</var> vous autorise à nettoyer les "
        "fichiers sans changer la date de modification, ce qui peut avoir une utilité avec certains outils "
        "qui utilisent la date de modification pour des traitements comme le déploiement automatique.<br/"
        ">Notez que cette fonctionnalité n'est pas supportée par toutes les plateformes. "
    },
    { TidyLiteralAttribs,                            0,        
        "Cette option précise le comportement de Tidy avec les caractères d'espacement pour les valeurs "
        "d'attributs. <br/>Si la valeur de l'option est <var>no</var>, Tidy normalise les valeurs "
        "d'attributs en remplaçant n'importe quel nouveau saut de ligne ou tabulation par un espace unique, "
        "et ensuite en remplaçant n'importe quel espace contigu par un espace unique. <br/>Pour forcer Tidy "
        "à préserver les valeurs initiales, les valeurs littérales de tous les attributs, et assurer que les "
        "espacements dans les valeurs d'attributs soient inchangés, passer cette option à <var>yes</var>. "
    },
    { TidyLogicalEmphasis,                           0,        
        "Cette option précise si Tidy doit remplacer les occurrences de <code>&lt;i&gt;</code> par <code>&lt;"
        "em&gt;</code> et les occurrences de <code>&lt;b&gt;</code> par <code>&lt;strong&gt;</code>. Les "
        "attributs sont préservés et inchangés. <br/>Cette option peut être indiquée indépendamment de "
        "l'option <code>clean</code>. "
    },
    { TidyLowerLiterals,                             0,        
        "Cette option précise si Tidy doit convertir en minuscules la valeur d'un attribut qui prend une "
        "liste de valeur prédéfinies. <br/>Ceci est requis pour les documents XHTML. "
    },
    { TidyMakeBare,                                  0,        
        "Cette option précise si Tidy doit supprimer des documents Word 2000, le HTML spécifique de "
        "Microsoft, et afficher des espaces en sortie plutôt que des espaces insécables, lorsque ceux-ci "
        "sont présents en entrée."
    },
    { TidyMakeClean,                                 0,        
        "Cette option précise si Tidy doit effectuer le nettoyage de certaines balises historiques de "
        "présentation (actuellement <code>&lt; i&gt;</code>, <code>&lt;b&gt;</code>, <code>&lt;center&gt;</"
        "code> lorsque placé entre les balises inline appropriées, ainsi que <code>&lt; font&gt;</code>). Si "
        "la valeur est <var>yes</var>, les balises historiques seront remplacées par des balises CSS "
        "<code>&lt;style&gt;</code> et par une structure de balisage appropriée."
    },
    { TidyMark,                                      0,        
        "Cette option précise si Tidy doit ajouter un élément <code>meta</code> dans l'entête de document, "
        "pour indiquer que le document a été nettoyé par Tidy. <br/>Tidy n'ajoutera pas cet élément "
        "<code>meta</code> s'il existe déjà. "
    },
    { TidyMergeDivs,                                 0,        
        "Cette option peut être utilisée pour modifier le comportement de l'option <code>clean</code>, "
        "lorsqu'elle vaut <var>yes</var>. <br/>Cette option précise si Tidy doit concaténer les éléments "
        "<code>&lt;div&gt;</code> imbriqués, comme <code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</"
        "code>. <br/>Si la valeur vaut <var>auto</var>, les attributs internes du <code>&lt;div&gt;</code> "
        "sont déplacés vers son div externe. Les <code>&lt;div&gt;</code> imbriqués avec des attributs "
        "<code>id</code> ne sont <em>pas</em> concaténés. <br/>Si la valeur vaut <var>yes</var>, les "
        "attributs du <code>&lt;div&gt;</code> interne ne sont pas pris en compte, à l'exception de "
        "<code>class</code> et de <code>style</code>. "
    },
    { TidyMergeEmphasis,                             0,        
        "Cette option précise si Tidy doit concaténer les éléments <code>&lt;b&gt;</code> et <code>&lt;i&gt;"
        "</code>; par exemple, pour le cas <br/><code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;"
        "bar&lt;/b&gt; baz&lt;/b&gt;</code>, <br/>Tidy produira la sortie <code>&lt;b class=\"rtop-2\"&gt;"
        "foo bar baz&lt;/b&gt;</code>. "
    },
    { TidyMergeSpans,                                0,        
        "Cette option peut être utlisée pour modifier le comportement de <code>clean</code>, si elle vaut "
        "<var>yes</var>.<br/>Cette option précise si Tidy doit concaténer les <code>&lt;span&gt;</code> "
        "imbriqués, comme suit : <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. <br/"
        ">L'algorithme est le même que celui de <code>merge-divs</code>. "
    },
    { TidyNCR,                                       0, "Cette option précise si Tidy doit autoriser les références numériques de caractères. "                  },
    { TidyNewline,                                   0,        
        "La valeur par défaut est appropriée à la plateforme d'exécution de Tidy. <br/>Généralement "
        "<var>CRLF</var> sur PC-DOS, Windows et OS/2; <var>CR</var> sur Classic Mac OS; et <var>LF</var> "
        "partout ailleurs (Linux, Mac OS X, et Unix). "
    },
    { TidyNumEntities,                               0,        
        "Cette option précise si Tidy doit afficher les entités autres que les entités HTML intégrées "
        "(<code>&amp;amp;</code>, <code>&amp;lt;</code>, <code>&amp;gt;</code>, et <code>&amp;quot;</code>) "
        "dans la forme numérique plutôt que dans la forme nommée. <br/>Seules les entités compatibles avec "
        "la déclaration DOCTYPE générée sont utilisées. <br/>Les entités qui peuvent être représentées dans "
        "l'encodage de sortie sont traduites avec leur correspondance. "
    },
    { TidyOmitOptionalTags,                          0,        
        "Cette option précise si Tidy doit omettre les balises optionnelles ouvrantes et fermantes, "
        "lorsqu'il produit une sortie. <br/>Activer cette option entraîne l'omission en sortie de toutes les "
        "balises correspondantes aux éléments <code>&lt;html&gt;</code>, <code>&lt;head&gt;</code>, and "
        "<code>&lt;body&gt;</code>, de même que les balises de fermeture comme <code>&lt;/p&gt;</code>, "
        "<code>&lt;/li&gt;</code>, <code>&lt;/dt&gt;</code>, <code>&lt;/dd&gt;</code>, <code>&lt;/option&gt;"
        "</code>, <code>&lt;/tr&gt;</code>, <code>&lt;/td&gt;</code>, et <code>&lt;/th&gt;</code>. <br/"
        ">Cette option est ignorée pour la sortie XML. "
    },
    { TidyOutCharEncoding,                           0,        
        "Cette option précise l'encodage de caractère utilisé par Tidy pour la sortie. <br/>Notez que cela "
        "peut être différent de <code>input-encoding</code> seulement pour les encodages latins (<var>ascii</"
        "var>, <var>latin0</var>, <var>latin1</var>, <var>mac</var>, <var>win1252</var>, <var>ibm858</var>)."
        "<br/>Voir <code>char-encoding</code> pour plus d'informations."
    },
    { TidyOutFile,                                   0,        
        "Cette option précise le fichier de sortie que Tidy utilise pour la structure de balises. En "
        "principe la structure est écrite vers <code>stdout</code>. "
    },
    { TidyOutputBOM,                                 0,        
        "Cette option précise si Tidy doit écrire un caractère indicateur d'ordre des octets (Unicode Byte "
        "Order Mark ou BOM; connu aussi sous Zero Width No-Break Space; a la valeur de U+FEFF) au début de "
        "la sortie, ce qui ne s'applique qu'aux sorties encodées en UTF-8 et UTF-16. <br/>Si l'option vaut "
        "<var>auto</var>, Tidy écrira un BOM vers la sortie seulement si un BOM était présent au début de "
        "l'entrée. <br/>Un BOM est toujours écrit pour la sortie XML/XHTML des sorties encodées en UTF-16. "
    },
    { TidyPPrintTabs,                                0,        
        "Cette option précise si tidy doit indenter avec des tabulations plutôt que des espaces, en "
        "supposant que <code>indent</code> vaut <var>yes</var>. <br/>Définir cette option à <var>yes</var> "
        "indente avec des tabulations plutôt que des espaces, valeur par défaut. <br />Utilisez l'option "
        "<code>indent-spaces</code> pour redéfinir le nombre de tabulations en sortie par niveau "
        "d'indentation. Notez que lorsque <code>indent-with-tabs</code> est activé, la valeur par défaut de "
        "<code>indent-spaces</code> est réinitialisée à <var>1</var>. <br/>Notez que <code>tab-size</code> "
        "contrôle la conversion des tabulations d'entrée en des espaces de sortie. Définissez-la à zéro pour "
        "conserver les tabulations en entrée."
    },
    { TidyPreserveEntities,                          0, "Cette option précise si Tidy doit préserver les entités bien formées telles que trouvées en entrée. "   },
    { TidyPreTags,                                   0,        
        "Cette option précise les nouvelles balises qui doivent être traitées exactement de la même façon "
        "que l'élément HTML <code>&lt;pre&gt;</code>. Cette option prend une liste de nom de balises "
        "séparées par un espace ou une virgule. <br/>Sauf si vous déclarez de nouvelles balises, Tidy "
        "refusera de générer un fichier Tidy en sortie si l'entrée inclut préalablement des balises "
        "inconnues. <br/>Notez que vous ne pouvez encore ajouter de nouveaux éléments CDATA. <br/>Cette "
        "option est ignorée avec le mode XML. "
    },
    { TidyPunctWrap,                                 0,        
        "Cette option précise si Tidy doit passer à la ligne après certains caractères de ponctuation "
        "Unicode ou chinois."
    },
    { TidyQuiet,                                     0,        
        "Cette option précise si Tidy doit afficher le résumé du nombre des erreurs et avertissements, ou "
        "les messages de bienvenue et d'information."
    },
    { TidyQuoteAmpersand,                            0,        
        "Cette option précise si Tidy doit afficher en sortie les caractères <code>&amp;</code> en les "
        "écrivant <code>&amp;amp;</code>. "
    },
    { TidyQuoteMarks,                                0,        
        "Cette option précise si Tidy doit afficher les caractères <code>&quot;</code> comme <code>&amp;quot;"
        "</code> comme préféré par certains environnements d'édition. <br/>Le caractère apostrophe <code>'</"
        "code> est écrit <code>&amp;#39;</code> car de nombreux navigateurs webs ne supportent pas encore "
        "l'écriture <code>&amp;apos;</code>. "
    },
    { TidyQuoteNbsp,                                 0,        
        "Cette option précise si Tidy doit afficher les espaces insécables en tant qu'entités, plutôt qu'en "
        "utilisant la valeur de caractère unicode 160 (décimale). "
    },
    { TidyReplaceColor,                              0,        
        "Cette option précise si Tidy doit remplacer les valeurs numériques dans les attributs de couleur "
        "par les noms de couleurs HTML/XHTML lorsque définies, par exemple en remplaçant <code>#ffffff</"
        "code> par <code>white</code>. "
    },
    { TidyShowErrors,                                0,        
        "Cette option précise le nombre utilisé par Tidy pour déterminer si les erreurs suivantes doivent "
        "être montrées. Si la valeur est <var>0</var>, aucune erreur n'est affichée. "
    },
    { TidyShowInfo,                                  0, "Cette option précise si Tidy doit afficher les messages de niveau info-level."                          },
    { TidyShowMarkup,                                0,        
        "Cette option précise si Tidy doit générer un affichage embelli de la structure de balises. Notez "
        "que Tidy ne générera pas un affichage embelli s'il trouve des erreurs significatives (voir "
        "<code>force-output</code>). "
    },
    { TidyShowWarnings,                              0,        
        "Cette option précise si Tidy doit supprimer les avertissements. Cela peut être utile lorsque "
        "quelques erreurs sont cachées dans une masse d'avertissements. "
    },
    { TidySkipNested,                                0,        
        "Cette option précise que Tidy doit ignorer les balises imbriquées lors de l'analyse des données de "
        "script et de style."
    },
    { TidySortAttributes,                            0,        
        "Cette option précise que Tidy doit classer les attributs d'un élément en utilisant un algorithme de "
        "classement. Si la valeur est <var>alpha</var>, l'algorithme est un classement alphabétique "
        "ascendant. "
    },
    { TidyStrictTagsAttr,                            0,        
        "Ces options garantissent que les balises et attributs sont valides pour la version HTML en sortie "
        "de Tidy. Si la valeur est <var>yes</var> (par défaut) et que le type de document en sortie est une "
        "déclaration doctype stricte, alors Tidy rapportera les erreurs. Si le type de document en sortie "
        "est une déclaration doctype loose ou transitional, alors Tidy rapportera les avertissements. <br/"
        ">En complément, si l'option <code>drop-proprietary-attributes</code> est activée, alors les "
        "attributs non valables seront aussi supprimés. <br/>Si la valeur est <var>no</var>, ces contrôles "
        "ne sont pas effectués. "
    },
    { TidyTabSize,                                   0,        
        "Cette option précise le nombre de colonnes que Tidy utilise entre deux tabulations successives. "
        "Ceci est utilisé pour lier les tabulations aux espaces pendant la lecture de l'entrée."
    },
    { TidyUpperCaseAttrs,                            0,        
        "Cette option précise si Tidy doit afficher les noms d'attributs en majuscules. <br/>La valeur par "
        "défaut est <var>no</var>, ce qui produit un affichage des attributs en minuscules, excepté pour une "
        "entrée XML, pour laquelle la casse originale est préservée. "
    },
    { TidyUpperCaseTags,                             0,        
        "Cette option précise si Tidy doit afficher les noms de balises en majuscules. <br/>La valeur par "
        "défaut est <var>no</var>, ce qui produit un affichage des balises en minuscules, excepté pour une "
        "entrée XML, pour laquelle la casse originale est préservée. "
    },
    { TidyUseCustomTags,                             0,        
        "Cette option active dans Tidy l'utilisation de balises pour les éléments personnalisés autonomes, "
        "par exemple &lt;flag-icon&gt;. Les balises personnalisées sont désactivées si cette valeur est "
        "<var>no</var>. Autres configurations - <var>blocklevel</var>, <var>empty</var>, <var>inline</var>, "
        "et <var>pre</var> seront <em>all</em> traités en conséquence comme des balises personnalisées "
        "détectées. <br/>L'usage de <code>new-blocklevel-tags</code>, <code>new-empty-tags</code>, <code>new-"
        "inline-tags</code>, ou <code>new-pre-tags</code> surchargera le traitement des balises "
        "personnalisées par cette option de configuration. Ceci peut être utile si vous avez différents "
        "types de balises personnalisées. <br/>Lorsque l'option est activée, ces balises sont déterminées "
        "pendant la phase de traitement de votre document, par la balise d'ouverture; les balises de "
        "fermeture correspondantes seront reconnues en conséquence, et les balises de fermeture inconnues "
        "seront ignorées. "
    },
    { TidyVertSpace,                                 0,        
        "Cette option précise si Tidy doit ajouter quelques lignes vides supplémentaires pour la lisibilité. "
        "<br/>La valeur par défaut est <var>no</var>. <br/>Si la valeur est <var>auto</var> Tidy éliminera "
        "presque tous les caractères de nouvelle ligne."
    },
    { TidyWarnPropAttrs,                             0, "Cette option précise si Tidy doit avertir des attributs propriétaires."                                 },
    { TidyWord2000,                                  0,        
        "Cette option précise si Tidy doit se donner du mal pour supprimer tous les surplus que Microsoft "
        "Word 2000 ajoute lorsque vous enregistrez des documents Word comme des \"pages Web\". Il ne prend "
        "pas en charge les images embarquées ou le VML. <br/>Vous devriez songer à utiliser la "
        "fonctionnalité de Word \"Enregistrer Sous: Page Web, Filtrée\". "
    },
    { TidyWrapAsp,                                   0,        
        "Cette option précise si Tidy doit ajouter un saut de ligne au texte contenu dans les pseudos-"
        "éléments ASP, qui ressemblent à <code>&lt;% ... %&gt;</code>. "
    },
    { TidyWrapAttVals,                               0,        
        "Cette option précise si Tidy doit ajouter des sauts de ligne aux valeurs d'attributs, ce qui "
        "signifie que si la valeur d'un attribut entraîne le dépassement de la largeur précisée par "
        "<code>wrap</code>, Tidy ajoutera un ou plusieurs sauts de lignes à la valeur, ce qui implique son "
        "découpage en plusieurs lignes. <br/>Notez que cette option peut être précisée indépendamment de "
        "<code>wrap-script-literals</code>. Par défaut, Tidy remplace n'importe quelle nouvelle ligne ou "
        "tabulation par un espace simple et remplace n'importe quelle séquence d'espacement par un espace "
        "simple. <br/>Pour forcer Tidy à préserver les valeurs littérales initiales de tous les attributs, "
        "et garantir que les caractères d'espacement dans les valeurs d'attributs sont maintenus inchangés, "
        "préciser la valeur de <code>literal-attributes</code> à <var>yes</var>. "
    },
    { TidyWrapJste,                                  0,        
        "Cette option précise si Tidy doit ajouter un saut de ligne au texte contenu dans les pseudos-"
        "éléments JSTE, qui ressemblent à <code>&lt;# ... #&gt;</code>. "
    },
    { TidyWrapLen,                                   0,        
        "Cette option précise à Tidy la marge de droite à utiliser pour le saut de ligne. <br/> Tidy tente "
        "de couper les lignes de façon à ce qu'elles ne dépassent pas cette longueur. <br/>Passer la valeur "
        "de <code>wrap</code> à <var>0</var>(zéro) désactive l'ajout de saut de ligne. "
    },
    { TidyWrapPhp,                                   0,        
        "Cette option précise si Tidy doit ajouter un saut de ligne au texte contenu dans les pseudos-"
        "éléments PHP, qui ressemblent à: <code>&lt;?php ... ?&gt;</code>. "
    },
    { TidyWrapScriptlets,                            0,        
        "Cette option précise si Tidy doit ajouter des sauts de lignes aux chaînes littérales dans les "
        "attributs de script. <br/>Tidy prend en charge la césure des longues chaînes littérales de scripts "
        "en ajoutant un caractère de barre oblique arrière (backslash) avant le saut de ligne. "
    },
    { TidyWrapSection,                               0,        
        "Cette option précise si Tidy doit ajouter des sauts de ligne pour le texte compris dans des balises "
        "de section <code>&lt;![ ... ]&gt;</code> section tags. "
    },
    { TidyWriteBack,                                 0,        
        "Cette option précise si Tidy doit réécrire la structure de balise qu'il a produit vers le même "
        "fichier à partir duquel il l'a lu. <br/> Il est conseillé de garder une copie des fichiers "
        "importants avant de les faire modifier par Tidy, car dans de rares occasions le résultat peut être "
        "inattendu. "
    },
    { TidyXhtmlOut,                                  0,        
        "Cette option précise si Tidy doit afficher une sortie embellie, en l'écrivant avec HTML étendu. <br/"
        "> Avec cette option activée, Tidy définit la déclaration DOCTYPE et l'espace de nom par défaut "
        "approprié pour du XHTML, et utilisera la valeur corrigée en sortie indépendamment des autres "
        "sources. <br/>Pour le XHTML, les entités seront écrites en entités nommées ou numériques "
        "conformément à la valeur de configuration de <code>numeric-entities</code>. <br/>La casse originale "
        "des balises et attributs sera préservée, indépendamment des autres options. "
    },
    { TidyXmlDecl,                                   0,        
        "Cette option précise si Tidy doit ajouter la déclaration XML lors de la sortie XML ou XHTML. <br/> "
        "Notez que si l'entrée comprend déjà une déclaration <code>&lt;?xml ... ?&gt;</code>, alors cette "
        "option sera ignorée. <br/>Si l'encodage pour la sortie est différent de <var>ascii</var>, de l'un "
        "des encodages <var>utf*</var> ou <var>raw</var>, alors la déclaration est toujours ajoutée, comme "
        "indiqué dans le standard XML."
    },
    { TidyXmlOut,                                    0,        
        "Cette option précise si Tidy doit afficher une sortie embellie, en l'écrivant avec du XML bien "
        "structuré. <br/> Toutes les entités non définies en XML 1.0 seront réécrites en entités numériques "
        "pour leur permettre d'être parcourues par un analyseur XML. <br/>La casse originale des balises et "
        "attributs sera préservée, indépendamment des autres options. "
    },
    { TidyXmlPIs,                                    0,        
        "Cette option précise si Tidy doit modifier l'analyse syntaxique des instructions de traitement pour "
        "exiger <code>?&gt;</code> comme terminaison plutôt que <code>&gt;</code>. <br/> Cette option est "
        "automatiquement activée si l'entrée est en XML."
    },
    { TidyXmlSpace,                                  0,        
        "Cette option précise si tidy doit ajouter <code>xml:space=\"preserve\"</code> pour des éléments "
        "tels que <code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> and <code>&lt;script&gt;</code> lors "
        "de la production de XML. <br />Ceci est nécessaire si l'espace blanc dans de tels éléments doit "
        "être analysé convenablement sans avoir accès à la DTD."
    },
    { TidyXmlTags,                                   0,        
        "Cette option précise si Tidy doit utiliser l'analyseur XML plutôt que l'analyseur de correction "
        "d'erreur HTML."
    },
    { TidyInfo,                                      0, "Info:"                                                                                                  },
    { TidyWarning,                                   0, "Avertissement:"                                                                                         },
    { TidyConfig,                                    0, "Config:"                                                                                                },
    { TidyAccess,                                    0, "Accès:"                                                                                                 },
    { TidyError,                                     0, "Erreur:"                                                                                                },
    { TidyBadDocument,                               0, "Document:"                                                                                              },
    { TidyFatal,                                     0, "Panique:"                                                                                               },
    { TidyDialogueSummary,                           0, "Résumé:"                                                                                                },
    { TidyDialogueInfo,                              0, "Informations: "                                                                                         },
    { TidyDialogueFootnote,                          0, "Remarque:"                                                                                              },
    { LINE_COLUMN_STRING,                            0, "Ligne: %d Col: %d - "                                                                                   },
    { STRING_DISCARDING,                             0, "rejet"                                                                                                  },
    { STRING_ERROR_COUNT_ERROR,                      0, "erreur"                                                                                                 },
    { STRING_ERROR_COUNT_ERROR,                      1, "erreurs"                                                                                                },
    { STRING_ERROR_COUNT_WARNING,                    0, "avertissement"                                                                                          },
    { STRING_ERROR_COUNT_WARNING,                    1, "avertissements"                                                                                         },
    { STRING_HELLO_ACCESS,                           0,        
        "\n"
        "Contrôles d'accessibilité:\n"
    },
    { STRING_HTML_PROPRIETARY,                       0, "HTML Propriétaire"                                                                                      },
    { STRING_XML_DECLARATION,                        0, "déclaration XML"                                                                                        },
    { STRING_PLAIN_TEXT,                             0, "texte brut"                                                                                             },
    { STRING_REPLACING,                              0, "remplacement"                                                                                           },
    { STRING_SPECIFIED,                              0, "précisé"                                                                                                },
    { TIDYCUSTOMNO_STRING,                           0, "aucune"                                                                                                 },
    { TIDYCUSTOMBLOCKLEVEL_STRING,                   0, "élément de bloc"                                                                                        },
    { TIDYCUSTOMEMPTY_STRING,                        0, "vide"                                                                                                   },
    { TEXT_HTML_T_ALGORITHM,                         0,        
        "\n"
        "       - D'abord, cherchez depuis la gauche de la position de la cellule \n"
        "         pour trouver la rangée des cellules d'entête de lignes. \n"
        "       - Puis rechercher vers le haut pour trouver les cellules d'entête \n"
        "         de colonne.\n"
        "       - La recherche dans une direction donnée s'arrête lorsque le bout \n"
        "         du tableau est atteint ou lorsque la cellule de données est \n"
        "         trouvée après une cellule d'en-tête.\n"
        "       - Les entêtes de ligne sont insérés dans la liste, dans l'ordre dans \n"
        "         lequel ils apparaissent dans le tableau.\n"
        "       - Pour les tableaux de gauche à droite, les entêtes sont insérés de \n"
        "         gauche à droite.\n"
        "       - Les entêtes de colonnes sont insérés après les entêtes de ligne,\n"
        "         dans l'ordre dans lequel ils apparaissent dans le tableau, de haut \n"
        "         en bas.\n"
        "       - Si une cellule d'entête a ses entêtes d'attributs complétés, alors \n"
        "         les entêtes référencés par cet attribut sont insérés dans la \n"
        "         liste et la recherche s'arrête pour la direction courante.\n"
        "         Les cellules TD qui fixent l'attribut de l'axe sont également \n"
        "         traitées comme des cellules d'entête.\n"
    },
    { TEXT_VENDOR_CHARS,                             0,        
        "Il est peu probable que des encodages spécifiques à un éditeur,\n"
        "dépendants d'un système, fonctionnent suffisamment largement\n"
        "pour le World Wide Web; vous devriez éviter d'utiliser l'encodage\n"
        "de caractère %s, et utiliser plutôt des entités nommées,\n"
        "par exemple &trade;.\n"
    },
    { TEXT_SGML_CHARS,                               0,        
        "Les codes de caractères 128 à 159 (U + 0080 à U + 009F) ne sont pas \n"
        "autorisés en HTML; même si ils l'étaient, il seraient probablement non \n"
        "imprimables comme des caractères de contrôle .\n"
        "Tidy a supposé que vous vouliez faire référence à un caractère avec la \n"
        "même valeur d'encodage d'octet %s et a remplacé cette référence par \n"
        "son équivalent Unicode.\n"
    },
    { TEXT_INVALID_UTF8,                             0,        
        "Les codes de caractères UTF-8 doivent être dans l'intervalle : U+0000 à U+10FFFF.\n"
        "La définition de l'UTF-8 à l'annexe D de la norme ISO/CEI 10646-1: 2000 permet \n"
        "également l'utilisation de séquences de cinq et six octets pour coder des caractères \n"
        "qui sont en dehors de l'intervalle des caractères Unicode;\n"
        "ces séquences de cinq et six octets sont inappropriées pour l'utilisation de l'UTF-8 \n"
        "dans l'objectif de transformation de caractères Unicode. ISO/IEC 10646 \n"
        "ne permet pas la liaison des substituts non appairés, ni U+FFFE ni U+FFFF \n"
        "(mais il permet d'autres non-caractères). Pour plus d'informations veuillez-vous\n"
        "référer à http://www.unicode.org/ et http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_UTF16,                            0,        
        "Les codes de caractères pour UTF-16 doivent être dans l'intervalle: U+0000 à U+10FFFF.\n"
        "La définition de UTF-16 dans l'annexe C de l'ISO/IEC 10646-1:2000 n'autorise pas la \n"
        "liaison de substituts non appairés. Pour plus d'informations, veuillez vous référer\n"
        "à http://www.unicode.org/ et http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_URI,                              0,        
        "Les URIs doivent être correctement protégés, ils ne doivent pas contenir \n"
        "les caractères non-échappés ci-après U+0021, y-compris le caractère \n"
        "d'espacement et non plus le U+007E. Tidy échappe l'URI pour vous \n"
        "comme recommandé par HTML 4.01 section B.2.1 et XML 1.0 \n"
        "section 4.2.2. Certains user-agents utilisent un autre algorithme pour \n"
        "échapper ces URI et quelques scripts côté serveur dépendent de ceci. \n"
        "Si vous voulez dépendre de ceci, vous devez échapper l'URI de votre \n"
        "côté. Pour plus d'informations, veuillez vous référer à\n"
        "http://www.w3.org/International/O-URL-and-ident.html\n"
    },
    { TEXT_BAD_FORM,                                 0,        
        "Vous devrez peut-être déplacer une, ou les deux, balises <form>et</form>. \n"
        "Les éléments HTML doivent être correctement imbriquées et les éléments \n"
        "de formulaire ne font pas exception. Par exemple, vous ne devez pas placer \n"
        "<form>dans une cellule et </form>dans une autre. Si <form>est placé devant \n"
        "un tableau, </form> ne peut pas être placé à l'intérieur du tableau !\n"
        "Notez qu'un form ne peut pas être imbriqué dans un autre !\n"
    },
    { TEXT_BAD_MAIN,                                 0,        
        "Un seul élément <main> est permis dans un document.\n"
        "Les éléments <main> suivants ont été rejetés, ce qui peut rendre \n"
        "le document non valide.\n"
    },
    { TEXT_M_SUMMARY,                                0,        
        "L'attribut summary du tableau devrait servir à décrire la structure\n"
        "du tableau. Il est très utile pour les personnes utilisant des \n"
        "navigateurs non visuels. Les attributs de portée et entêtes \n"
        "pour les cellules d'un tableau sont utiles pour préciser les entêtes \n"
        "s'appliquant à chaque cellule du tableau, permettant aux navigateurs \n"
        "non visuels de fournir un contexte significatif pour chaque cellule.\n"
        "\n"
    },
    { TEXT_M_IMAGE_ALT,                              0,        
        "L'attribut alt devrait servir à donner une brève description d'une\n"
        "image ; Il faudrait aussi des descriptions plus longues avec l'attribut\n"
        "longdesc qui prend une URL liée à la description. Ces mesures sont\n"
        "nécessaires pour les personnes utilisant des navigateurs textuels.\n"
        "\n"
    },
    { TEXT_M_IMAGE_MAP,                              0,        
        "Utiliser des images interactives côté client est préférable à celles côté \n"
        "serveur, ces dernières sont inaccessibles aux personnes utilisant des \n"
        "navigateurs non-graphiques. En outre, les cartes côté client sont plus \n"
        "faciles à mettre en place et fournissent une interactivité immédiate \n"
        "aux utilisateurs.\n"
        "\n"
    },
    { TEXT_M_LINK_ALT,                               0,        
        "Pour les liens hypertextes définis à l'aide d'une image interactive \n"
        "côté client, vous devez utiliser l'attribut alt pour fournir une \n"
        "description textuelle du lien, pour les personnes utilisant des \n"
        "\n"
    },
    { TEXT_USING_FRAMES,                             0,        
        "Les pages conçues à l'aide de cadres posent des problèmes aux \n"
        "personnes malvoyantes ou à celles qui utilisent un navigateur ne \n"
        "supportant pas les frames. Une structure de page basée sur des \n"
        "cadres doit toujours inclure une structure alternative à l'intérieur \n"
        "d'un élément NOFRAMES.\n"
        "\n"
    },
    { TEXT_ACCESS_ADVICE1,                           0,        
        "Pour plus d'informations sur la façon de rendre vos pages\n"
        "accessibles, voir http://www.w3.org/WAI/GL"
    },
    { TEXT_ACCESS_ADVICE2,                           0,        
        "Pour plus d'informations sur la façon de rendre vos pages \n"
        "accessibles, voir http://www.w3.org/WAI/GL et \n"
        "http://www.html-tidy.org/Accessibility/"
    },
    { TEXT_USING_LAYER,                              0,        
        "Le mécanisme de positionnement au moyen des feuilles de style \n"
        "en cascade (CSS) est préférable à l'élément propriétaire <LAYER>, \n"
        "en raison du support limité des éditeurs pour LAYER.\n"
    },
    { TEXT_USING_SPACER,                             0,        
        "Il est recommandé d'utiliser les CSS pour contrôler les espacements \n"
        "(par exemple pour le retrait, les marges et les interlignes).\n"
        "L'élément propriétaire <SPACER> a un soutien limité des éditeurs.\n"
        "\n"
    },
    { TEXT_USING_FONT,                               0,        
        "Il est recommandé d'utiliser les CSS pour préciser la police et les \n"
        "propriétés telles que la taille et la couleur. Cela permettra de réduire \n"
        "la taille des fichiers HTML et de les rendre plus faciles à entretenir \n"
        "\n"
    },
    { TEXT_USING_NOBR,                               0,        
        "Il est recommandé d'utiliser les CSS pour contrôler les sauts de ligne.\n"
        "Utilisez \"white-space: nowrap\" pour inhiber les sauts de ligne plutôt que \n"
        "d'insérer <NOBR> ... </ NOBR> dans la structure de balises.\n"
        "\n"
    },
    { TEXT_USING_BODY,                               0,        
        "Il est recommandé d'utiliser les CSS pour préciser les couleurs \n"
        "de la page et des liens"
    },
    { STRING_CONTENT_LOOKS,                          0, "Le contenu du document ressemble à %s"                                                                  },
    { STRING_DOCTYPE_GIVEN,                          0, "DOCTYPE donnée est «%s»"                                                                                },
    { STRING_ERROR_COUNT,                            0, "Tidy a trouvé %u %s et %u %s!\n"                                                                        },
    { STRING_NEEDS_INTERVENTION,                     0,        
        "Ce document contient des erreurs qui doivent d'abord être résolues\n"
        "en utilisant HTML Tidy pour produire une version nettoyée.\n"
    },
    { STRING_NO_ERRORS,                              0, "Aucun avertissement ou erreur trouvée.\n"                                                               },
    { STRING_NO_SYSID,                               0, "Aucun identifiant système dans le doctype soumis"                                                       },
    { STRING_NOT_ALL_SHOWN,                          0, "Tidy a trouvé %u %s et %u %s! Tous les avertissements et erreurs n'ont pas été affichés.\n"             },
    { TEXT_GENERAL_INFO,                             0,        
        "À propos de HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Rapports de bugs et commentaires: https://github.com/htacg/tidy-html5/issues\n"
        "Liste officielle de diffusion: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Dernière spécification HTML: http://dev.w3.org/html5/spec-author-view/\n"
        "Validez vos documents HTML: http://validator.w3.org/nu/\n"
        "Encouragez votre entreprise à rejoindre le W3C: http://www.w3.org/Consortium\n"
        "\n"
    },
    { TEXT_GENERAL_INFO_PLEA,                        0,        
        "Parlez-vous une autre langue que le français, ou une variante du français?\n"
        "Merci de nous aider à traduire HTML Tidy. Pour plus d'informations, consultez \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },
    { ANCHOR_NOT_UNIQUE,                             0, "%s ancre \"%s\" déjà défini"                                                                            },
    { APOS_UNDEFINED,                                0, "l'entité nommée &apos; est défini seulement en XML/XHTML"                                               },
    { ATTR_VALUE_NOT_LCASE,                          0, "valeur d'attribut de %s « %s » doit être en minuscule pour XHTML"                                       },
    { ATTRIBUTE_IS_NOT_ALLOWED,                      0, "L'attribut %s n'\"est\" pas autorisé pour les balises personnalisées autonomes."                        },
    { BACKSLASH_IN_URI,                              0, "La référence d'URI %s contient des anti-slash. Faute de frappe ?"                                       },
    { BAD_ATTRIBUTE_VALUE_REPLACED,                  0, "%s l'attribut « %s » a une valeur non valide « %s » et a été remplacé"                                  },
    { BAD_ATTRIBUTE_VALUE,                           0, "%s l'attribut \"%s\" a une valeur non valide \"%s\""                                                    },
    { BAD_CDATA_CONTENT,                             0, "'<' + '/' + lettres non permises ici"                                                                   },
    { BAD_SUMMARY_HTML5,                             0, "L'attribut summary sur l'élément %s est obsolète avec HTML5"                                            },
    { BAD_SURROGATE_LEAD,                            0,        
        "Paire de substitution U+%04X de terminaison (Bas), sans entité principale (Haut), remplacée par U"
        "+FFFD."
    },
    { BAD_SURROGATE_PAIR,                            0, "Présence d'une paire de substitution hors intervalle U+%04X:U+%04X, remplacée par la valeur U+FFFD."    },
    { BAD_SURROGATE_TAIL,                            0,        
        "Paire de substitution principale (Haute) U+%04X, sans entité de terminaison (Haut), remplacée par U"
        "+FFFD."
    },
    { CANT_BE_NESTED,                                0, "%s ne peut pas être imbriqué"                                                                           },
    { COERCE_TO_ENDTAG,                              0, "<%s> est probablement souhaité pour </%s>"                                                              },
    { CONTENT_AFTER_BODY,                            0, "contenu trouvé après la fin de body"                                                                    },
    { CUSTOM_TAG_DETECTED,                           0, "balise personnalisée autonome détectée %s; sera traitée comme %s"                                       },
    { DISCARDING_UNEXPECTED,                         0, "inhibition de valeur inattendue %s"                                                                     },
    { DOCTYPE_AFTER_TAGS,                            0, "<!DOCTYPE> n'est pas autorisée après les éléments"                                                      },
    { DUPLICATE_FRAMESET,                            0, "élément répété FRAMESET"                                                                                },
    { ELEMENT_NOT_EMPTY,                             0, "%s élément non vide ou non fermé"                                                                       },
    { ELEMENT_VERS_MISMATCH_ERROR,                   0, "%s élément non disponible dans %s"                                                                      },
    { ELEMENT_VERS_MISMATCH_WARN,                    0, "%s élément non disponible dans %s"                                                                      },
    { ENCODING_MISMATCH,                             0, "l'encodage de caractère précisé en entrée (%s) ne correspond pas à l'encodage réellement entré (%s)"    },
    { ESCAPED_ILLEGAL_URI,                           0, "%s échappement de la référence d''URI mal formée"                                                       },
    { FILE_CANT_OPEN,                                0, "Impossible d'ouvrir « %s »\n"                                                                           },
    { FILE_NOT_FILE,                                 0, "\"%s\" n'est pas un fichier!\n"                                                                         },
    { FIXED_BACKSLASH,                               0, "%s conversion des antislash vers slash dans l'URI "                                                     },
    { ID_NAME_MISMATCH,                              0, "%s discordance entre id et valeur de nom d'attribut"                                                    },
    { ILLEGAL_NESTING,                               0, "%s ne doit pas être imbriqué"                                                                           },
    { ILLEGAL_URI_CODEPOINT,                         0, "%s caractères interdits trouvés dans l'URI"                                                             },
    { ILLEGAL_URI_REFERENCE,                         0, "%s mal échappé dans la référence d'URI"                                                                 },
    { INSERTING_AUTO_ATTRIBUTE,                      0, "%s insertion de l'attribut « %s », en utilisant la valeur « %s »"                                       },
    { INSERTING_TAG,                                 0, "insertion implicite de <%s>"                                                                            },
    { INVALID_ATTRIBUTE,                             0, "%s nom d'attribut « %s » (valeur=« %s ») n'est pas valide"                                              },
    { INVALID_NCR,                                   0, "%s référence de caractère numérique non valide %s"                                                      },
    { INVALID_SGML_CHARS,                            0, "%s code de caractère non valide %s"                                                                     },
    { INVALID_UTF8,                                  0, "%s octets UTF-8 non valides (code de caract. %s)"                                                       },
    { INVALID_UTF16,                                 0, "%s paire de substitution UFT-16 non valide (code de caract. %s)"                                        },
    { INVALID_XML_ID,                                0, "%s impossible de copier le nom attribut vers id"                                                        },
    { JOINING_ATTRIBUTE,                             0, "%s regroupement des valeurs répétées de l'attribut « %s »"                                              },
    { MALFORMED_COMMENT,                             0, "tirets adjacents dans un commentaire"                                                                   },
    { MALFORMED_DOCTYPE,                             0, "inhibition de la <!DOCTYPE> mal formée"                                                                 },
    { MISMATCHED_ATTRIBUTE_ERROR,                    0, "%s attribut \"%s\" non permis pour %s"                                                                  },
    { MISMATCHED_ATTRIBUTE_WARN,                     0, "%s attribut \"%s\" non permis pour %s"                                                                  },
    { MISSING_ATTR_VALUE,                            0, "%s attribut \"%s\" n'a pas de valeur"                                                                   },
    { MISSING_ATTRIBUTE,                             0, "%s absence d'attribut \"%s\""                                                                           },
    { MISSING_DOCTYPE,                               0, "déclaration <!DOCTYPE> manquante"                                                                       },
    { MISSING_ENDTAG_BEFORE,                         0, "absence de </%s> avant %s"                                                                              },
    { MISSING_ENDTAG_FOR,                            0, "absence de </%s>"                                                                                       },
    { MISSING_IMAGEMAP,                              0, "%s doivent utiliser une image-map côté client"                                                          },
    { MISSING_QUOTEMARK,                             0, "%s attribut avec apostrophe de fin manquante"                                                           },
    { MISSING_SEMICOLON_NCR,                         0, "La référence de caractère numérique « %s » ne se termine pas par « ; »"                                 },
    { MISSING_SEMICOLON,                             0, "l'entité « %s » ne se termine pas par « ; »"                                                            },
    { MISSING_STARTTAG,                              0, "absence de <%s>"                                                                                        },
    { MISSING_TITLE_ELEMENT,                         0, "ajout d'un élément 'title' manquant"                                                                    },
    { NESTED_EMPHASIS,                               0, "accentuation imbriquée %s"                                                                              },
    { NESTED_QUOTATION,                              0, "éléments \"q\" imbriqués, erreur typographique possible"                                                },
    { NEWLINE_IN_URI,                                0, "%s inhibition des nouvelles lignes dans la référence d'URI"                                             },
    { NOFRAMES_CONTENT,                              0, "%s non positionné dans l'élément 'noframes'"                                                            },
    { NON_MATCHING_ENDTAG,                           0, "remplacement des %s inattendus par </%s>"                                                               },
    { OBSOLETE_ELEMENT,                              0, "remplacement de l'élément obsolète %s par %s"                                                           },
    { PREVIOUS_LOCATION,                             0, "<%s> précédemment mentionnés"                                                                           },
    { PROPRIETARY_ATTR_VALUE,                        0, "%s valeur d'attribut propriétaire « %s »"                                                               },
    { PROPRIETARY_ATTRIBUTE,                         0, "%s attribut propriétaire \"%s\""                                                                        },
    { PROPRIETARY_ELEMENT,                           0, "%s n'est pas approuvé par le W3C"                                                                       },
    { REMOVED_HTML5,                                 0, "élément %s retiré de HTML5"                                                                             },
    { REPEATED_ATTRIBUTE,                            0, "%s abandon de la valeur « %s » pour l'attribut répété « %s »"                                           },
    { REPLACING_ELEMENT,                             0, "remplacement de %s par %s"                                                                              },
    { REPLACING_UNEX_ELEMENT,                        0, "remplacement des %s inattendus par %s"                                                                  },
    { SPACE_PRECEDING_XMLDECL,                       0, "suppression de l'espace précédant la déclaration XML"                                                   },
    { STRING_MISSING_MALFORMED,                      0, "argument manquant ou incorrect pour l'option: %s"                                                       },
    { STRING_UNKNOWN_OPTION,                         0, "option inconnue: %s"                                                                                    },
    { SUSPECTED_MISSING_QUOTE,                       0, "absence de guillemet pour la valeur d'attribut"                                                         },
    { TAG_NOT_ALLOWED_IN,                            0, "%s n'est pas permis dans les éléments <%s>"                                                             },
    { TOO_MANY_ELEMENTS_IN,                          0, "trop d'éléments %s dans <%s>"                                                                           },
    { TOO_MANY_ELEMENTS,                             0, "trop d'éléments %s"                                                                                     },
    { TRIM_EMPTY_ELEMENT,                            0, "réduction des %s vides"                                                                                 },
    { UNESCAPED_AMPERSAND,                           0, "symbole & non échappé qui devrait être écrit &amp;"                                                     },
    { UNEXPECTED_END_OF_FILE_ATTR,                   0, "%s fin de fichier lors de l'analyse des attributs"                                                      },
    { UNEXPECTED_END_OF_FILE,                        0, "fin de fichier inattendue %s"                                                                           },
    { UNEXPECTED_ENDTAG_ERR,                         0, "</%s> inattendu"                                                                                        },
    { UNEXPECTED_ENDTAG_IN,                          0, "</%s> inattendu dans <%s>"                                                                              },
    { UNEXPECTED_ENDTAG,                             0, "</%s> inattendu"                                                                                        },
    { UNEXPECTED_EQUALSIGN,                          0, "%s symbole imprévu '=', nom d'attribut attendu"                                                         },
    { UNEXPECTED_GT,                                 0, "%s symbole '>' manquant pour la fin de balise"                                                          },
    { UNEXPECTED_QUOTEMARK,                          0, "%s guillemet double inattendu ou dupliqué"                                                              },
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM,                  0, "%s n'est pas reconnue! Vouliez-vous activer l'option custom-tags?"                                      },
    { UNKNOWN_ELEMENT,                               0, "%s n'est pas reconnue!"                                                                                 },
    { UNKNOWN_ENTITY,                                0, "symbole & non échappé ou entité inconnue « %s »"                                                        },
    { USING_BR_INPLACE_OF,                           0, "utilisation de <br> à la place de %s"                                                                   },
    { VENDOR_SPECIFIC_CHARS,                         0, "%s code de caractère non valide %s"                                                                     },
    { WHITE_IN_URI,                                  0, "%s rejet des espaces dans la référence URI"                                                             },
    { XML_DECLARATION_DETECTED,                      0, "Une déclaration XML a été détectée. Voulez-vous utiliser l'option input-xml?"                           },
    { XML_ID_SYNTAX,                                 0, "%s ID « %s » utilise la syntaxe XML ID"                                                                 },
    { IMG_MISSING_ALT,                               0, "[1.1.1.1]: <img> texte manquant 'alt'."                                                                 },
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0, "[1.1.1.2]: texte 'alt' suspect (nom de fichier)."                                                       },
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0, "[1.1.1.3]: texte 'alt' suspect (taille de fichier)."                                                    },
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0, "[1.1.1.4]: texte 'alt' suspect (espace réservé)."                                                       },
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0, "[1.1.1.10]: texte 'alt' suspect (trop long)."                                                           },
    { IMG_MISSING_LONGDESC_DLINK,                    0, "[1.1.2.1]: <img> absence de 'longdesc' et d-link."                                                      },
    { IMG_MISSING_DLINK,                             0, "[1.1.2.2]: <img> absence de d-link."                                                                    },
    { IMG_MISSING_LONGDESC,                          0, "[1.1.2.3]: <img> absence de 'longdesc'."                                                                },
    { IMG_BUTTON_MISSING_ALT,                        0, "[1.1.3.1]: <img> (bouton) absence de texte 'alt'."                                                      },
    { APPLET_MISSING_ALT,                            0, "[1.1.4.1]: <applet> absence de contenu alternatif."                                                     },
    { OBJECT_MISSING_ALT,                            0, "[1.1.5.1]: <object> absence de contenu alternatif."                                                     },
    { AUDIO_MISSING_TEXT_WAV,                        0, "[1.1.6.1]: texte de transcription audio manquant (wav)."                                                },
    { AUDIO_MISSING_TEXT_AU,                         0, "[1.1.6.2]: texte de transcription audio manquant (au)."                                                 },
    { AUDIO_MISSING_TEXT_AIFF,                       0, "[1.1.6.3]: texte de transcription audio manquant (aiff)."                                               },
    { AUDIO_MISSING_TEXT_SND,                        0, "[1.1.6.4]: texte de transcription audio manquant (snd)."                                                },
    { AUDIO_MISSING_TEXT_RA,                         0, "[1.1.6.5]: texte de transcription audio manquant (ra)."                                                 },
    { AUDIO_MISSING_TEXT_RM,                         0, "[1.1.6.6]: texte de transcription audio manquant (rm)."                                                 },
    { FRAME_MISSING_LONGDESC,                        0, "[1.1.8.1]: <frame> peut nécessiter 'longdesc'."                                                         },
    { AREA_MISSING_ALT,                              0, "[1.1.9.1]: <area> absence de texte 'alt'."                                                              },
    { SCRIPT_MISSING_NOSCRIPT,                       0, "[1.1.10.1]: <script> section <noscript> manquante."                                                     },
    { ASCII_REQUIRES_DESCRIPTION,                    0, "[1.1.12.1]: ascii art nécessite une description."                                                       },
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0, "[1.2.1.1]: image map (côté serveur) nécessite des liens textes."                                        },
    { MULTIMEDIA_REQUIRES_TEXT,                      0, "[1.4.1.1]: le multimédia nécessite une équivalence de textes correspondants."                           },
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0, "[1.5.1.1]: image map (côté client) liens textes manquants."                                             },
    { INFORMATION_NOT_CONVEYED_IMAGE,                0, "[2.1.1.1]: Vérifiez que l'information n'est pas transmise uniquement par la couleur (image)."           },
    { INFORMATION_NOT_CONVEYED_APPLET,               0, "[2.1.1.2]: Vérifiez que l'information n'est pas transmise uniquement par la couleur (applet)."          },
    { INFORMATION_NOT_CONVEYED_OBJECT,               0, "[2.1.1.3]: Vérifiez que l'information n'est pas transmise uniquement par la couleur (object)."          },
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0, "[2.1.1.4]: Vérifiez que l'information n'est pas transmise uniquement par la couleur (script)."          },
    { INFORMATION_NOT_CONVEYED_INPUT,                0,        
        "[2.1.1.5]: Vérifiez que l'information n'est pas transmise uniquement par la couleur (champs de "
        "formulaire)."
    },
    { COLOR_CONTRAST_TEXT,                           0, "[2.2.1.1]: contraste couleur faible (texte)."                                                           },
    { COLOR_CONTRAST_LINK,                           0, "2.2.1.2]: contraste couleur faible (lien)."                                                             },
    { COLOR_CONTRAST_ACTIVE_LINK,                    0, "2.2.1.3]: contraste couleur faible (lien actif)."                                                       },
    { COLOR_CONTRAST_VISITED_LINK,                   0, "2.2.1.4]: contraste couleur faible (lien visité)."                                                      },
    { DOCTYPE_MISSING,                               0, "[3.2.1.1]: déclaration <doctype> manquante."                                                            },
    { STYLE_SHEET_CONTROL_PRESENTATION,              0, "[3.3.1.1]: Utiliser les feuilles de style pour contrôler la présentation."                              },
    { HEADERS_IMPROPERLY_NESTED,                     0, "[3.5.1.1]: entêtes imbriqués incorrectement."                                                           },
    { POTENTIAL_HEADER_BOLD,                         0, "[3.5.2.1]: entête potentiel (gras)."                                                                    },
    { POTENTIAL_HEADER_ITALICS,                      0, "[3.5.2.2]: entête potentiel (italique)."                                                                },
    { POTENTIAL_HEADER_UNDERLINE,                    0, "[3.5.2.3]: entête potentiel (soulignement)."                                                            },
    { HEADER_USED_FORMAT_TEXT,                       0, "[3.5.3.1]: entête utilisé pour formater du texte."                                                      },
    { LIST_USAGE_INVALID_UL,                         0, "[3.6.1.1]: Usage non valide de liste <ul>."                                                             },
    { LIST_USAGE_INVALID_OL,                         0, "[3.6.1.2]: usage non valide de liste <ol>."                                                             },
    { LIST_USAGE_INVALID_LI,                         0, "[3.6.1.4]: usage non valide de liste <li>."                                                             },
    { LANGUAGE_NOT_IDENTIFIED,                       0, "[4.3.1.1]: langage non identifié."                                                                      },
    { LANGUAGE_INVALID,                              0, "[4.3.1.2]: attribut de langage non valide."                                                             },
    { DATA_TABLE_MISSING_HEADERS,                    0, "[5.1.2.1]: data <table> absence d'entêtes rangée/colonne (tous)."                                       },
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0, "[5.1.2.2]: data <table> absence d'entêtes rang/colonne (1 col)."                                        },
    { DATA_TABLE_MISSING_HEADERS_ROW,                0, "[5.1.2.3]: data <table> absence d'entêtes rang/colonne (1 rang)."                                       },
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0, "[5.2.1.1]: data <table> peut nécessiter une structure de balises (entêtes de colonne)."                 },
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0, "[5.2.1.1]: data <table> peut nécessiter une structure de balises (entêtes de rangée)."                  },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0, "[5.3.1.1]: vérifie que la structure des tableaux est correctement sérialisée."                          },
    { LAYOUT_TABLE_INVALID_MARKUP,                   0, "[5.4.1.1]: structure de balises incorrecte dans l'agencement de <table>."                               },
    { TABLE_MISSING_SUMMARY,                         0, "[5.5.1.1]: <table> absence de résumé."                                                                  },
    { TABLE_SUMMARY_INVALID_NULL,                    0, "[5.5.1.2]: <table> résumé non valide (null)."                                                           },
    { TABLE_SUMMARY_INVALID_SPACES,                  0, "[5.5.1.3]: <table> résumé non valide (espaces)."                                                        },
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0, "[5.5.1.6]: <table> résumé non valide (texte de l'emplacement réservé)."                                 },
    { TABLE_MISSING_CAPTION,                         0, "[5.5.2.1]: <table> absence de légende (<caption>)."                                                     },
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0, "[5.6.1.1]: <table> peut nécessiter des abréviations d'entête."                                          },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0, "[5.6.1.2]: <table> abréviations d'entête non valide (null)."                                            },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0, "[5.6.1.3]: <table> abréviations d'entête non valide (espaces)."                                         },
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0, "[6.1.1.1]: les feuilles de style nécessitent un examen (link)."                                         },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0, "[6.1.1.2]: les feuilles de style nécessitent un examen (élément style)."                                },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0, "[6.1.1.3]: les feuilles de style nécessitent un examen (attribut style)."                               },
    { FRAME_SRC_INVALID,                             0, "[6.2.1.1]: <frame> source non valide."                                                                  },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0, "[6.2.2.1]: les équivalences de texte nécessitent une mise à jour (applet)."                             },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0, "[6.2.2.2]: les équivalences de texte nécessitent une mise à jour (script)."                             },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0, "[6.2.2.3]: les équivalences de texte nécessitent une mise à jour (object)."                             },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0, "[6.3.1.1]: les objets programmatiques nécessitent un examen (script)."                                  },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0, "[6.3.1.2]: les objets programmatiques nécessitent un examen (object)."                                  },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0, "[6.3.1.3]: les objets programmatiques nécessitent un examen (embed)."                                   },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0, "[6.3.1.4]: les objets programmatiques nécessitent un examen (applet)."                                  },
    { FRAME_MISSING_NOFRAMES,                        0, "[6.5.1.1]: <frameset> section <noframes> manquante."                                                    },
    { NOFRAMES_INVALID_NO_VALUE,                     0, "[6.5.1.2]: <noframes> section non valide (pas de valeur)."                                              },
    { NOFRAMES_INVALID_CONTENT,                      0, "[6.5.1.3]: <noframes> section non valide (contenu)."                                                    },
    { NOFRAMES_INVALID_LINK,                         0, "[6.5.1.4]: <noframes> section non valide (lien)."                                                       },
    { REMOVE_FLICKER_SCRIPT,                         0, "[7.1.1.1]: suppression de scintillement (script)."                                                      },
    { REMOVE_FLICKER_OBJECT,                         0, "[7.1.1.2]: suppression de scintillement (object)."                                                      },
    { REMOVE_FLICKER_EMBED,                          0, "[7.1.1.1]: suppression de scintillement (embed)."                                                       },
    { REMOVE_FLICKER_APPLET,                         0, "[7.1.1.1]: suppression de scintillement (applet)."                                                      },
    { REMOVE_FLICKER_ANIMATED_GIF,                   0, "[7.1.1.1]: suppression de scintillement (gif animé)."                                                   },
    { REMOVE_BLINK_MARQUEE,                          0, "[7.2.1.1]: suppression de blink/marquee."                                                               },
    { REMOVE_AUTO_REFRESH,                           0, "[7.4.1.1]: suppression de auto-refresh."                                                                },
    { REMOVE_AUTO_REDIRECT,                          0, "[7.5.1.1]: suppression de auto-redirect."                                                               },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0, "[8.1.1.1]: garantir que les objets programmatiques sont accessibles (script)."                          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0, "[8.1.1.2]: garantir que les objets programmatiques sont accessibles (object)."                          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0, "[8.1.1.3]: garantir que les objets programmatiques sont accessibles (applet)."                          },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0, "[8.1.1.4]: garantir que les objets programmatiques sont accessibles (embed)."                           },
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0, "[9.1.1.1]: image map (côté serveur) nécessite une conversion."                                          },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0, "[9.3.1.1]: <script> non accessible par le clavier (onMouseDown)."                                       },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0, "[9.3.1.2]: <script> non accessible par le clavier (onMouseUp)."                                         },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0, "[9.3.1.3]: <script> non accessible par le clavier (onClick)."                                           },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0, "[9.3.1.4]: <script> non accessible par le clavier (onMouseOver)."                                       },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0, "[9.3.1.5]: <script> non accessible par le clavier (onMouseOut)."                                        },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0, "[9.3.1.6]: <script> non accessible par le clavier (onMouseMove)."                                       },
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0, "[10.1.1.1]: les nouvelles fenêtres nécessitent un avertissement (_new)."                                },
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0, "[10.1.1.2]: les nouvelles fenêtres nécessitent un avertissement (_blank)."                              },
    { REPLACE_DEPRECATED_HTML_APPLET,                0, "[11.2.1.1]: remplacer l'élément HTML déprécié <applet>."                                                },
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0, "[11.2.1.2]: remplacer l'élément HTML déprécié <basefont>."                                              },
    { REPLACE_DEPRECATED_HTML_CENTER,                0, "[11.2.1.3]: remplacer l'élément HTML déprécié <center>."                                                },
    { REPLACE_DEPRECATED_HTML_DIR,                   0, "[11.2.1.4]: remplacer l'élément HTML déprécié <dir>."                                                   },
    { REPLACE_DEPRECATED_HTML_FONT,                  0, "[11.2.1.5]: remplacer l'élément HTML déprécié <font>."                                                  },
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0, "[11.2.1.6]: remplacer l'élément HTML déprécié <isindex>."                                               },
    { REPLACE_DEPRECATED_HTML_MENU,                  0, "[11.2.1.7]: remplacer l'élément HTML déprécié <menu>."                                                  },
    { REPLACE_DEPRECATED_HTML_S,                     0, "[11.2.1.8]: remplacer l'élément HTML déprécié <s>."                                                     },
    { REPLACE_DEPRECATED_HTML_STRIKE,                0, "[11.2.1.9]: remplacer l'élément HTML déprécié <strike>."                                                },
    { REPLACE_DEPRECATED_HTML_U,                     0, "[11.2.1.10]: remplacer l'élément HTML déprécié <u>."                                                    },
    { FRAME_MISSING_TITLE,                           0, "[12.1.1.1]: <frame> absence de titre."                                                                  },
    { FRAME_TITLE_INVALID_NULL,                      0, "[12.1.1.2]: <frame> titre non valide (null)."                                                           },
    { FRAME_TITLE_INVALID_SPACES,                    0, "[12.1.1.3]: <frame> titre non valide (espaces)."                                                        },
    { ASSOCIATE_LABELS_EXPLICITLY,                   0, "[12.4.1.1]: associer explicitement les étiquettes avec les contrôles de formulaire."                    },
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0, "[12.4.1.2]: associer explicitement les étiquettes avec les contrôles de formulaire (for)."              },
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0, "[12.4.1.3]: associer explicitement les étiquettes avec les contrôles de formulaire (id)."               },
    { LINK_TEXT_NOT_MEANINGFUL,                      0, "[13.1.1.1]: texte du lien peu significatif."                                                            },
    { LINK_TEXT_MISSING,                             0, "[13.1.1.2]: texte du lien manquant."                                                                    },
    { LINK_TEXT_TOO_LONG,                            0, "[13.1.1.3]: texte du lien trop long."                                                                   },
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0, "[13.1.1.4]: texte du lien peu significatif (click here)."                                               },
    { METADATA_MISSING,                              0, "[13.2.1.1]: Métadonnées manquantes."                                                                    },
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0, "[13.2.1.3]: Métadonnées manquantes (redirect/auto-refresh)."                                            },
    { SKIPOVER_ASCII_ART,                            0, "[13.10.1.1]: ignore l'ascii art."                                                                       },

#if SUPPORT_CONSOLE_APP
    { TC_LABEL_COL,                                  0, "colonne"                                                                                                },
    { TC_LABEL_FILE,                                 0, "fichier"                                                                                                },
    { TC_LABEL_LANG,                                 0, "langue"                                                                                                 },
    { TC_LABEL_LEVL,                                 0, "niveau"                                                                                                 },
    { TC_LABEL_OPT,                                  0, "option"                                                                                                 },
    { TC_MAIN_ERROR_LOAD_CONFIG,                     0, "Le chargement du fichier de configuration \"%s\" a échoué, err = %d"                                    },
    { TC_OPT_ACCESS,                                 0,        
        "faire des vérifications d'accessibilité supplémentaires (<niveau> = 0, 1, 2, 3). implicitement 0 si "
        "<niveau> est manquant."
    },
    { TC_OPT_ASCII,                                  0, "utilise ISO-8859-1 pour l'entrée, US-ASCII pour la sortie"                                              },
    { TC_OPT_ASHTML,                                 0, "force le XHTML en HTML bien structuré"                                                                  },
    { TC_OPT_ASXML,                                  0, "converti le HTML en XHTML bien structuré"                                                               },
    { TC_OPT_BARE,                                   0, "enlève les guillemets à double chevron et les tirets longs."                                            },
    { TC_OPT_BIG5,                                   0, "utilise Big5 pour l'entrée et la sortie"                                                                },
    { TC_OPT_CLEAN,                                  0, "remplace les balises FONT, NOBR et CENTER par du CSS"                                                   },
    { TC_OPT_CONFIG,                                 0, "détermine les options de configuration à partir du <fichier> spécifié "                                 },
    { TC_OPT_ERRORS,                                 0, "affiche seulement les erreurs et avertissements"                                                        },
    { TC_OPT_FILE,                                   0, "écrit les erreurs et avertissements vers le <fichier> précisé "                                         },
    { TC_OPT_GDOC,                                   0, "produit une version nettoyée du html exporté par Google Docs"                                           },
    { TC_OPT_HELP,                                   0, "liste toutes les options de ligne de commande"                                                          },
    { TC_OPT_HELPCFG,                                0, "liste toutes les options de configuration"                                                              },
    { TC_OPT_HELPOPT,                                0, "Affiche une description de l'<option>"                                                                  },
    { TC_OPT_IBM858,                                 0, "utilise IBM-858 (CP850+Euro) pour l'entrée, US-ASCII pour la sortie"                                    },
    { TC_OPT_INDENT,                                 0, "indente le contenu d'un élément"                                                                        },
    { TC_OPT_ISO2022,                                0, "utilise ISO-2022 pour l'entrée et la sortie"                                                            },
    { TC_OPT_LANGUAGE,                               0,        
        "Précise le langage de sortie de Tidy pour <lang>. Ajouter '-language help' pour plus d'aide. "
        "Utiliser avant les arguments produisant des sorties pour garantir que le langage sera pris en "
        "compte, par exemple `tidy -lang fr -lang help`."
    },
    { TC_OPT_LATIN0,                                 0, "utilise ISO-8859-15 pour l'entrée, US-ASCII pour la sortie"                                             },
    { TC_OPT_LATIN1,                                 0, "utilise ISO-8859-1 pour l'entrée et la sortie"                                                          },
    { TC_OPT_MAC,                                    0, "utilise MacRoman pour l'entrée, US-ASCII pour la sortie"                                                },
    { TC_OPT_MODIFY,                                 0, "modifie le fichier original en entrée"                                                                  },
    { TC_OPT_NUMERIC,                                0, "sortie numérique plutôt qu'entités nommées"                                                             },
    { TC_OPT_OMIT,                                   0, "Omettre les tags optionnels d'ouverture et de fermeture"                                                },
    { TC_OPT_OUTPUT,                                 0, "écrit la sortie vers le fichier <file>"                                                                 },
    { TC_OPT_QUIET,                                  0, "supprime les sorties non-essentielles"                                                                  },
    { TC_OPT_RAW,                                    0, "Valeurs de sortie supérieures à 127 sans conversion en entités"                                         },
    { TC_OPT_SHIFTJIS,                               0, "utilise Shift_JIS à la fois pour l'entrée et la sortie"                                                 },
    { TC_OPT_SHOWCFG,                                0, "liste les options de configuration"                                                                     },
    { TC_OPT_UPPER,                                  0, "force les balises en lettres majuscules"                                                                },
    { TC_OPT_UTF16,                                  0, "utilise UTF-16 à la fois pour l'entrée et la sortie"                                                    },
    { TC_OPT_UTF16BE,                                0, "utilise UTF-16BE à la fois pour l'entrée et la sortie"                                                  },
    { TC_OPT_UTF16LE,                                0, "utilise UTF-16LE à la fois pour l'entrée et la sortie"                                                  },
    { TC_OPT_UTF8,                                   0, "utilise UTF-8 à la fois pour l'entrée et la sortie"                                                     },
    { TC_OPT_VERSION,                                0, "affiche la version de Tidy"                                                                             },
    { TC_OPT_WIN1252,                                0, "utilise Windows-1252 pour l'entrée, US-ASCII pour la sortie"                                            },
    { TC_OPT_WRAP,                                   0,        
        "coupe le texte à la colonne <column>. 0 est supposé si <column> est manquante. Si cette option "
        "n'est pas précisée, la valeur par défaut de l'option 'wrap' s'applique."
    },
    { TC_OPT_XML,                                    0, "précise que l'entrée est un XML bien structuré"                                                         },
    { TC_OPT_XMLCFG,                                 0, "liste toutes les options de configuration au format XML"                                                },
    { TC_OPT_XMLHELP,                                0, "liste les options de ligne de commande au format XML"                                                   },
    { TC_OPT_XMLSTRG,                                0, "sortie de toutes les chaînes Tidy au format XML"                                                        },
    { TC_OPT_XMLERRS,                                0, "constantes et chaînes de sortie d'erreur au format XML"                                                 },
    { TC_OPT_XMLOPTS,                                0, "descriptions des options de sortie au format XML"                                                       },
    { TC_STRING_CONF_HEADER,                         0, "Fichier de configuration:"                                                                              },
    { TC_STRING_CONF_NAME,                           0, "Nom"                                                                                                    },
    { TC_STRING_CONF_TYPE,                           0, "Type"                                                                                                   },
    { TC_STRING_CONF_VALUE,                          0, "Valeur courante"                                                                                        },
    { TC_STRING_OPT_NOT_DOCUMENTED,                  0, "Attention: l'option `%s' n'est pas documentée."                                                         },
    { TC_STRING_OUT_OF_MEMORY,                       0, "Mémoire insuffisante. Abandon."                                                                         },
    { TC_STRING_FATAL_ERROR,                         0, "Erreur fatale: valeur impossible pour id='%d'."                                                         },
    { TC_STRING_FILE_MANIP,                          0, "Manipulation de fichier"                                                                                },
    { TC_STRING_PROCESS_DIRECTIVES,                  0, "Directives de traitement"                                                                               },
    { TC_STRING_CHAR_ENCODING,                       0, "Encodages de caractère"                                                                                 },
    { TC_STRING_LANG_MUST_SPECIFY,                   0, "Une locale POSIX ou Windows doit être précisée."                                                        },
    { TC_STRING_LANG_NOT_FOUND,                      0, "Tidy n'a pas la langue '%s', '%s' sera utilisé à la place."                                             },
    { TC_STRING_MISC,                                0, "Divers"                                                                                                 },
    { TC_STRING_XML,                                 0, "XML"                                                                                                    },
    { TC_STRING_MUST_SPECIFY,                        0, "Un nom d'option doit être précisé."                                                                     },
    { TC_STRING_UNKNOWN_OPTION,                      0, "HTML Tidy: option inconnue: %c"                                                                         },
    { TC_STRING_UNKNOWN_OPTION_B,                    0, "HTML Tidy: option inconnue."                                                                            },
    { TC_STRING_VERS_A,                              0, "HTML Tidy pour %s version %s"                                                                           },
    { TC_STRING_VERS_B,                              0, "HTML Tidy version %s"                                                                                   },
    { TC_TXT_HELP_1,                                 0,        
        "\n"
        "%s [options...] [fichier...] [options...] [fichier...]\n"
        "Utilitaire pour nettoyer et embellir le HTML/XHTML/XML.\n"
        "\n"
        "Ceci est le HTML Tidy modernisé version %s.\n"
        "\n"
    },
    { TC_TXT_HELP_2A,                                0, "Arguments en ligne de commande de HTML Tidy pour %s:"                                                   },
    { TC_TXT_HELP_2B,                                0, "Arguments en ligne de commande de HTML Tidy:"                                                           },
    { TC_TXT_HELP_3,                                 0,        
        "\n"
        "Options de configuration de Tidy\n"
        "==========================\n"
        "Utilisez les options de configuration de Tidy comme arguments de \n"
        "ligne de commande, sous la forme «--option <valeur>\", par exemple \n"
        "\"--indent-with-tabs yes\"\n"
        "\n"
        "Pour une liste de toutes les options de configuration, utilisez \n"
        "\"-help-config\" ou consultez la page de manuel (si votre OS a la \n"
        "commande man).\n"
        "\n"
        "Si votre environnement a déclaré une variable $HTML_TIDY qui pointe \n"
        "vers un fichier de configuration, alors Tidy tentera de l'utiliser.\n"
        "\n"
        "Sur certaines plateformes, Tidy essaiera également d'utiliser une \n"
        "configuration décrite dans /etc/tidy.conf ou ~/.tidy.conf.\n"
        "\n"
        "Autre\n"
        "=====\n"
        "Pour l'entrée/sortie par défaut, utilisez stdin/stdout respectivement. \n"
        "\n"
        "Les options en lettre simple, en dehors de -f, peuvent être combinées \n"
        "comme dans: tidy -f errs.txt -imu foo.html\n"
        "\n"
        "Renseignements\n"
        "===========\n"
        "Pour plus d'informations à propos de HTML Tidy, voir\n"
        "  http://www.html-tidy.org/\n"
        "\n"
        "Pour plus d'informations sur le langage HTML, consultez les rubriques suivantes:\n"
        "\n"
        "  HTML: Édition pour les auteurs Web (de la dernière spécification HTML)\n"
        "  http://dev.w3.org/html5/spec-author-view\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG,                            0,        
        "\n"
        "Paramètres de configuration de HTML Tidy\n"
        "\n"
        "Dans un fichier, utilisez la forme:\n"
        "\n"
        "wrap: 72\n"
        "indent: no\n"
        "\n"
        "Quand il sont précisés en ligne de commande, utilisez la forme:\n"
        "\n"
        "--wrap 72 --indent no\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,                       0, "Nom"                                                                                                    },
    { TC_TXT_HELP_CONFIG_TYPE,                       0, "Type"                                                                                                   },
    { TC_TXT_HELP_CONFIG_ALLW,                       0, "Valeurs possibles"                                                                                      },
    { TC_TXT_HELP_LANG_1,                            0,        
        "\n"
        "L'option -language (ou -lang) indique la langue que Tidy doit utiliser \n"
        "en sortie. Veuillez noter que ce n'est pas un service de traduction de \n"
        "documents, et que cela affecte uniquement les messages que Tidy \n"
        "renvoie.\n"
        "\n"
        "Lorsqu'il est utilisé depuis la ligne de commande, l'argument -language \n"
        "doit être utilisé avant des arguments qui ont un impact sur la sortie, \n"
        "sinon Tidy va produire une sortie avant de connaître la langue à utiliser.\n"
        "\n"
        "En plus des codes de langue du standard POSIX, Tidy est capable de\n"
        "comprendre les codes de langue historiques de Windows. \n"
        "Veuillez noter que cette liste indique les codes que Tidy comprend, et \n"
        "ne signifie pas que la langue est pour autant installée.\n"
        "\n"
        "La colonne de droite indique comment Tidy comprendra le nom \n"
        "Windows historique.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,                            0,        
        "\n"
        "Les langages suivants sont installés pour le moment dans Tidy.\n"
        "Veuillez noter qu'il n'y a pas de garantie qu'ils soient complets ; \n"
        "Seul un développeur (ou plusieurs) a commencé à ajouter le \n"
        "langage indiqué.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,                            0,        
        "\n"
        "Si Tidy est capable de déterminer votre locale, Tidy utilisera alors la langue \n"
        "locale automatiquement. Par exemple, les systèmes basés sur Unix utilisent \n"
        "une variable d'environnement $LANG et/ou $LC_ALL.\n"
        "Consultez la documentation de votre système d'exploitation pour plus \n"
        "d'informations. \n"
        "\n"
        "Tidy utilise pour l'instant la locale %s. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,                        0, NULL
    }

}};


#endif /* language_fr_h */

