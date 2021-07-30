#ifndef language_de_h
#define language_de_h
/*
 * language_de.h
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
 *     language (and maybe region) "de". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_de.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_de.h` (our own
 *     conversion tool) to generate a fresh PO from this file first!
 *
 * (c) 2015-2021 Michael Uplawski <michael.uplawski@uplawski.eu>
 * See tidy.h and access.h for the copyright notice.
 *
 * Template Created by Jim Derry on 01/14/2016.
 *
 * Originating PO file metadata:
 *   PO_LAST_TRANSLATOR=jderry
 *   PO_REVISION_DATE=2021-07-30 10:35:03
 */

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif


/**
 *  This language-specific function returns the correct pluralForm
 *  to use given n items, and is used as a member of each language
 *  definition.
 */
static uint whichPluralForm_de(uint n) {
    /* Plural-Forms: nplurals=2; */
    return (n > 1);
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_de = { whichPluralForm_de, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                                 0, "de"
    },
    { TidyAccessibilityCheckLevel,                   0,        
        "Diese Option bestimmt, wenn nötig, das Niveau der Überprüfungen der Barrierefreiheit, "
        "die Tidy durchführen soll. "
        "<br/>"
        "Niveau <var>0 (Tiidy Classic)</var> entsprichte dem Niveau der Prüfugen von Tidy Classic."
        "<br/>"
        "Auf dieser Seite finden Sie weitere Informationen zur Prüfung der Barrierefreiheit mit Tidy: "
        "<a href=\"https://www.html-tidy.org/accessibility/\">Barrierefreiheit mit Tidy</a>. "
    },
    { TidyAltText,                                   0,        
        "Diese Option bestimmt den Standardwert für das <code>alt=</code> Attribut, "
        "das von Tidy eingesetzt wird, wo es in <code>&lt;img&gt;</code> Tags fehlt. "
        "<br/>"
        "Gehen Sie behutsam damit um; es liegt in Ihrer Verantwortung, Dokumente barrierefrei "
        " zu gestalten, für Leute die die Bilder nicht sehen können. "
    },
    { TidyAnchorAsName,                              0,        
        "Diese Option steuert das Entfernen oder Hinzufügen des <code>name</code> "
        "Attributs in solchen Elementen, die als Verweisanker dienen können. "
        "<br/>"
        "Wenn hier <var>yes</var> gewählt wird und ein <code>name</code> Attribut "
        "bisher nicht vorhanden ist, wird es zusammen mit einem <code>id</code> Attribut "
        "ergänzt, soweit die DTD dies erlaubt. "
        "<br/>"
        "Mit dem Wert <var>no</var>, wird ein vorhandenes <code>name</code> Attribut "
        "entfernt, sofern en <code>id</code> existiert oder hinzugefügt wurde."
    },
    { TidyAsciiChars,                                0,        
        "Kann verwendet werden, um die Wirkung der Option <code>clean</code> "
        "zu modifizieren, wenn der den Wert <var>yes</var> hat."
        "<br/>"
        "Hier <var>yes</var> zusammen mit <code>clean</code> zu verwenden, "
        "hat zur Folge, dass <code>&amp;emdash;</code>, <code>&amp;rdquo;</code> "
        "und andere typografische Zeichen in ihre nächstliegenden ASCII-Äquivalente "
        "umgewandelt werden. "
    },
    { TidyBlockTags,                                 0,        
        "Diese Option dient der Einführung neuer Block-Elemente. Der Wert muss "
        "eine Liste von leerzeichen- oder komma-separierten Tag-Namen sein."
        "<br/>"
        "Solange Sie die neuen Tags nicht definieren, wird Tidy keine bereinigte "
        "Datei erzeugen, wenn die Eingabe bisher unbekannte Tags enthält. "
        "<br/>"
        "Beachten Sie, dass Sie das Content Model für Elemente wie "
        "<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, "
        "<code>&lt;ol&gt;</code> and <code>&lt;dl&gt;</code> nicht ändern können. "
        "<br/>"
        "Die Option wird im XML Modus ignoriert. "
    },
    { TidyBodyOnly,                                  0,        
        "Die Option legt fest, ob Tidy nur den Inhalt des <code>body</code> "
        "Elements als HTML-Fragment ausgeben soll. "
        "<br/>"
        "Hier <var>auto</var> einzustellen hat zur Folge, dass die Wirkung nur "
        "eintritt, wenn das <code>body</code> Element hergeleitet wurde."
        "<br/>"
        "Die Methode ist nützlich, um ganze Seiten als Teil einer anderen Seite auszugeben. "
        "<br/>"
        "Die Option ist wirkungslos, wenn XML Ausgabe gefordert ist. "
    },
    { TidyBreakBeforeBR,                             0,        
        "Diese Option legt fest, ob Tidy einen Zeilenumbruch vor jedem "
        "<code>&lt;br&gt;</code> Element einfügen soll. "
    },
    { TidyCharEncoding,                              0,        
        "Diese Option bestimmt, welche Zeichenkodierung Tidy für Eingaben annehmen soll und, "
        "falls zutreffend, dass Tidy für Ausgaben automatisch eine geeignete Zeichenkodierung "
        "wählt. Die Kodierungen für Ein- und Ausgaben können sich unterscheiden. "
        "<br/>"
        "Wird für die Eingabe eine der Kodierungen <var>ascii</var>, <var>latin0</var>, "
        "<var>ibm858</var>, <var>mac</var> oder <var>win1252</var> gefordert, "
        "wird die Option <code>output-encoding</code> automatisch auf <var>ascii</var> "
        "eingestellt. Sie können dies verhindern, indem Sie den Wert für "
        "<code>output-encoding</code> selbst bestimmen. "
        "<br/>"
        "Bei anders kodierten Eingaben wird die Option <code>output-encoding</code> "
        "automatisch auf den identischen Wert eingestellt. "
        "<br/>"
        "Sie können den voreingestellten Wert für <code>output-encoding</code> "
        "überschreiben, indem Sie die Option selbst setzen. "
        "<br/>"
        "Tidy ist kein Konverter für Zeichenkodierungen. Auch, wenn Latin- und "
        "UTF-Kodierungen frei vermischt sein können, ist es mit Tidy nicht möglich, "
        "asiatische Kodierungen nach Latin zu konvertieren."
    },
    { TidyCoerceEndTags,                             0,        
        "Diese Option bestimmt, ob Tidy ein Start-Tag in ein End-Tag umwandelt, "
        "wo es wahrscheinlich erscheint, dass ein solches End-Tag eigentlich "
        "gewünscht war; zum Beispiel kann die Eingabe "
        "<br/>"
        "<code>&lt;span&gt;ein &lt;b&gt;wichtiges&lt;b&gt; Wort&lt;/span&gt;</code> "
        "<br/>"
        "von Tidy umgewandelt werden in "
        "<br/>"
        "<code>&lt;span&gt;ein &lt;b&gt;wichtiges&lt;/b&gt; Wort&lt;/span&gt;</code> "
    },
    { TidyCSSPrefix,                                 0,        
        "Diese Option setzt den Präfix, den Tidy für Style-Regeln verwendet. "
        "<br/>"
        "Standardmäßig wird <var>c</var> verwendet. "
    },
    { TidyDecorateInferredUL,                        0,        
        "Diese Option legt fest, ob Tidy hergeleitete <code>&lt;ul&gt;</code> "
        "Elemente mit CSS-Auszeichnungen ausstatten soll, um Einrückungen nach "
        "rechts zu verhindern. "
    },
    { TidyDoctype,                                   0,        
        "Diese Option setzt die DOCTYPE Deklaration, die von Tidy generiert wird. "
        "<br/>"
        "Wenn hier <var>omit</var> eingestellt ist, enthält die Ausgabe keine "
        "DOCTYPE Deklaration. Beachten Sie, dass damit auch <code>numeric-entities</code> "
        "auf <var>yes</var> eingestellt wird. "
        "<br/>"
        "Mit dem Wert <var>html5</var> wird der DOCTYPE auf "
        "<code>&lt;!DOCTYPE html&gt;</code> festgelegt."
        "<br/>"
        "Wird statt dessen <var>auto</var> (der Standard) verwendet, wird Tidy versuchen, "
        "einen aufgrund des Dokumentinhalts vermuteten DOCTYPE zu verwenden. "
        "Beachten Sie, dass auf diese Weise der DOCTYPE des aktuellen Dokuments "
        "<em>nicht</em> geändert wird. "
        "<br/>"
        "Der Wert <var>strict</var> veranlasst Tidy, den DOCTYPE auf HTML4 oder "
        "XHTML1 strict DTD einzustellen. "
        "<br/>"
        "Mit dem Wert <var>loose</var> wird der DOCTYPE HTML4 oder "
        "XHTML1 loose (transitional) DTD eingestellt. "
        "<br/>"
        "Alternatif können Sie eine Zeichenkette für den Formal Public Identifier (FPI) "
        "angeben."
        "<br/>"
        "Zum Beispiel: "
        "<br/>"
        "<code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code>"
        "<br/>"
        "Wenn Sie den FPI für ein XHTML Dokument angeben, erzeugt Tidy eine "
        "leere Zeichenkette für den System Identifyer. In HTML-Dokumenten "
        "fügt Tidy einen System Identifier nur dann ein, wenn er schon vorher "
        "vorhanden war, im Hinblick auf die Verarbeitungsmodi einiger Browser. "
        "Tidy lässt den DOCTYPE generischer XML-Dokumente unangetastet."
        "<br/>"
        "Die Option bedingt keinerlei Überprüfung der Dokumentkonformität. "
    },
    { TidyDropEmptyElems,                            0, "Diese Option legt fest, ob Tidy leere Elemente verwerfen soll. "                                                 },
    { TidyDropEmptyParas,                            0, "Diese Option legt fest, ob Tidy leere Absätze verwerfen soll. "                                                  },
    { TidyDropPropAttrs,                             0,        
        "Mit dieser Option wird bestimmt, ob Tidy proprietäre Attribute "
        "entfernen soll, wie Microsoft data binding Attribute. Außerdem "
        "werden solche Attribute, die in der ausgegebenen Version des HTML-"
        "Codes nicht erlaubt sind, verworfen, wenn gleichzeitig <code>strict-tags-attributes</code> "
        "gesetzt wurde. "
    },
    { TidyDuplicateAttrs,                            0,        
        "Mit dieser Option wird festgelegt, ob Tidy das erste oder das letzte "
        "Vorkommen eines wiederholten Attributs übernehmen soll, z.B. bei "
        "aufeinanderfolgenden <code>align</code> Attributen im selben Tag. "
    },
    { TidyEmacs,                                     0,        
        "Mit dieser Option ändert Tidy das Format von Fehler- und Warnmeldungen "
        "so, dass sie leichter von GNU Emacs und einigen anderen Programmen geparst "
        "werden. Aus dem standardmäßigen "
        "<br/>"
        "  Zeile &lt;Zeilennummer&gt; Spalte &lt;Spaltennummer&gt; - (Fehler|Warnung): &lt;Meldung&gt; "
        "<br/>"
        "wird eine Ausgabe, die den Dateinamen der Eingabe enthält: "
        "<br/>"
        "  &lt;Dateiname&gt;:&lt;Zeilennummer&gt;:&lt;Spaltennummer&gt;: (Fehler|Warnung): &lt;Meldung&gt; "
    },
    { TidyEmptyTags,                                 0,        
        "Diese Option führt neue, leere Inline-Elemente ein. Der Wert muss eine leerzeichen- "
        "oder komma-separierte Lste von Tagnamen sein. "
        "<br/>"
        "Sollten Sie neue Elemente nicht deklarieren, verweigert Tidy das Generieren einer "
        "bereinigten Datei, wenn die Eingabe bisher unbekannte Elemente enthält. "
        "<br/>"
        "Achten Sie darauf, auch leere Elemente als entweder Inline- oder Blockelemente "
        "zu deklarieren. "
        "<br/>"
        "Diese Option wird im XML-Modus ignoriert. "
    },
    { TidyEncloseBlockText,                          0,        
        "Diese Option legt fest, ob Tidy ein <code>&lt;p&gt;</code> Element "
        "einfügen soll, um Text zu umschließen, den es in solchen Elementen findet, "
        "die gemischten Inhalt für HTML transitional, nicht aber für HTML strict "
        "erlauben. "
    },
    { TidyEncloseBodyText,                           0,        
        "Diese Option legt fest, ob Text, der im <code>body</code> Element "
        "gefunden wird, von einem <code>&lt;p&gt;</code> Element umschlossen "
        "werden soll. "
        "<br/>"
        "Das ist sinnvoll, wenn Sie bereits vorhandenen HTML-Code mit einem "
        "Style-Sheet verwenden wollen. "
    },
    { TidyErrFile,                                   0,        
        "Diese Option nennt die Fehlerdatei, in der Tidy Fehler und Warnungen "
        "vermerkt. "
        "Normalerweise werden Fehler und Warnungen auf <code>stderr</code> "
        "ausgegeben. "
    },
    { TidyEscapeCdata,                               0,        
        "Mit dieser Option bestimmen Sie, ob Tidy "
        "<code>&lt;![CDATA[]]&gt;</code> Abschnitte in normlen Text umwandeln "
        "soll. "
    },
    { TidyEscapeScripts,                             0,        
        "Diese Option bewirkt, dass Zeichen oder Zeichenketten, die wie "
        "schließende Tags aussehen, wie "
        "<code>&lt;/g</code> mit backslashes maskiert werden, wie in "
        "<code>&lt;\\/g</code>. Setzen Sie en Wert <var>no</var>, um dies zu "
        "verhindern. "
    },
    { TidyFixBackslash,                              0,        
        "Diese Option bestimmt, ob Tidy Backslashes <code>\\</code> in URLs "
        "durch normale Schrägstriche <code>/</code> ersetzen soll. "
    },
    { TidyFixComments,                               0,        
        "Diese Option bestimmt, ob Tidy unerwartete Bindestriche durch "
        "<code>=</code> Zeichen ersetzen soll, wenn Bindestriche aufeinanderfolgen. "
        "<br/>"
        "Der Standard ist <var>auto</var>, was für HTML5 Dokumente das gleiche wie "
        "<var>no</var> bedeutet, für alle anderen aber <var>yes</var>. "
        "<br/>"
        "Die SGML Kommentarsyntax wurde für HTML aufgegeben, alle Versionen von HTML "
        "erlauben aufeinanderfolgende Bindestriche, auch wenn das nicht für XML "
        "und XHTML gilt. Wenn Sie ältere Browser unterstützen wollen, die SGML "
        "Syntax verlangen, sollten Sie hier den Wert <var>yes</var> setzen."
    },
    { TidyFixUri,                                    0,        
        "Diese Option legt fest, ob Tidy Attributwerte mit URIs auf ungültige "
        "Zeichen überprüft und sie, wenn solche gefunden werden, maskiert, wie "
        "von HTML4 empfohlen. "
    },
    { TidyForceOutput,                               0,        
        "Diese Option legt fest, ob Tidy auch dann eine Ausgabe erzeugt, "
        "wenn Fehler auftreten. "
        "<br/>"
        "Verwenden Sie diese Einstellung mit Vorsicht; wenn Tidy einen Fehler "
        "meldet, heißt das, dass Tidy nicht (oder nicht sicher) in der Lage "
        "ist, den Fehler zu beheben. Die erzeugte Ausgabe kann darum Ihren "
        "Erwartungen widersprechen. "
    },
    { TidyGDocClean,                                 0,        
        "Diese Option bestimmt, ob sich Tidy beim Bereinigen von HTML-Code, "
        "der aus Google Docs exportiert wurde, speziell verhalten soll. "
    },
    { TidyHideComments,                              0,        
        "Mit dieser Option bestimmen Sie, ob Tidy Kommentare aus der Ausgabe "
        "entfernt. "
    },
    { TidyHtmlOut,                                   0,        
        "Diese Option bestimmt, ob Tidy eine formatierte Ausgabe als HTML "
        "schreiben soll. "
    },
    { TidyInCharEncoding,                            0,        
        "Diese Option legt die Zeichenkodierung fest, die Tidy für die Eingabe "
        "verwendet. "
        "Tidy geht bei manchen Eingabekodierungen von ein paar Annahmen aus. "
        "<br/>"
        "Für <var>ascii</var> akzeptiert Tidy Latin-1 (ISO-8859-1) Zeichenwerte "
        "und konvertiert sie nötigenfalls in Entities. "
        "<br/>"
        "Für <var>raw</var> stellt Tidy keinerlei Vermutungen über die "
        "Zeichenwerte an und reicht sie unverändert an die Ausgabe weiter. "
        "<br/>"
        "Für <var>mac</var> und <var>win1252</var> werden händlerspezifische "
        "Zeichenwerte akzeptiert und nötigenfalls in Entities umgewandelt. "
        "<br/>"
        "Asiatische Zeichenkodierungen, wie <var>iso2022</var>, werden in "
        "geeigneter Weise behandelt, unter der Annahme, dass auch "
        "<code>output-encoding</code> entsprechend angegeben ist. "
        "<br/>"
        "Tidy ist kein Konverter für Zeichenkodierungen. Auch, wenn Latin- und "
        "UTF-Kodierungen frei gemischt werden können, ist es nicht möglich, "
        "asiatische Kodierungen mit Tidy in Latin umzuwandeln. "
    },
    { TidyIndentAttributes,                          0,        
        "Mit dieser Option wird festgelegt, ob Tidy jedes Attribut auf einer "
        "neuen Zeile beginnen soll.  "
    },
    { TidyIndentCdata,                               0,        
        "Diese Option bestimmt, ob Tidy "
        "<code>&lt;![CDATA[]]&gt;</code> Abschnitte einrücken soll. "
    },
    { TidyIndentSpaces,                              0,        
        "Diese Option bestimmt die Anzahl von Leerzeichen oder Tabulatoren, "
        "mit denen Tidy Einrückungen vornimmt, wenn <code>indent</code> "
        "aktiviert ist. "
        "<br/>"
        "Beachten Sie, dass der Standardwert für diese Option vom aktuellen Wert "
        "der Option <code>indent-with-tabs</code> abhängt (siehe dort). "
    },
    { TidyJoinClasses,                               0,        
        "Diese Option bestimmt, ob Tidy mehrere CSS-Klassen zu einer einzigen "
        "neuen Klasse kombiniert, wo ein Element mit mehrere Klassennamen "
        "versehen wurde. "
    },
    { TidyJoinStyles,                                0,        
        "Diese Option bestimmt, ob Tidy mehrere style-Attribute zu einem einzigen "
        "kombiniert, wo ein Element mit mehreren style-Attributen versehen wurde. "
    },
    { TidyKeepTabs,                                  0,        
        "Der Standardwert dieser Option ist <var>no</var>. Damit ersetzt Tidy alle "
        "Tabulatoren durch Leerzeichen, entsprechend der Option <code>tab-size</code> und "
        "dem aktuellen Zeileneinzug. "
        "Dieser Zwischenraum wird später natürlich auf nur ein Leerzeichen reduziert, mit "
        "Ausnahme der Abstände, die in den nachfolgend gelisteten Blöcken und Elementen auftreten. "
        "<br/>"
        "Wenn der Wert auf <var>yes</var> eingestellt ist, lässt Tidy einige Tabulatoren "
        "unangetastet, aber nur in präformatierten Blöcken, wie "
        "<code>&lt;pre&gt;</code> und weiteren CDATA elementen, wie "
        "<code>&lt;script&gt;</code>, <code>&lt;style&gt;</code>, sowie Pseudo-Elementen "
        "wie <code>&lt;?php ... ?&gt;</code>. "
        "Wie immer werden alle anderen Tabulatoren und Tabulatorfolgen im Quelldokument durch "
        "Leerzeichen ersetzt."
    },
    { TidyLogicalEmphasis,                           0,        
        "Diese Option bestimmt, ob Tidy jedes "
        "<code>&lt;i&gt;</code> durch <code>&lt;em&gt;</code> und jedes "
        "<code>&lt;b&gt;</code> durch <code>&lt;strong&gt;</code> ersetzen soll. "
        "Attribute dieser Tags bleiben unverändert erhalten. "
        "<br/>"
        "Diese Option kann unabhängig von <code>clean</code> aktiviert werden. "
    },
    { TidyLowerLiterals,                             0,        
        "Diese Option legt fest, ob Tidy solche Attributwerte, die aus einer Liste "
        "vordefinierter Werte bestehen, in Kleinbuchstaben konvertieren soll. "
        "<br/>"
        "Für XHTML-Dokumente ist das notwendig. "
    },
    { TidyMergeDivs,                                 0,        
        "Diese Option kann das Verhalten von <code>clean</code> beeinflussen, wenn "
        "ihr Wert auf <var>yes</var> gesetzt ist. "
        "<br/>"
        "Tidy wird dann verschachtelte <code>&lt;div&gt;</code> zu einem einzigen verschmelzen, "
        "wie <code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. "
        "<br/>"
        "Wenn der Wert statt dessen <var>auto</var> ist, werden die Attribute des innersten "
        "<code>&lt;div&gt;</code> ins äußerste verschoben. Verschachtelte "
        "<code>&lt;div&gt;</code> mit <code>id</code>-Attributen werden <em>nicht</em> "
        "verschmolzen. "
        "<br/>"
        "Mit <var>yes</var> werden die Attribute des innersten "
        "<code>&lt;div&gt;</code> verworfen, mit Ausnahme von "
        "<code>class</code> und <code>style</code>. "
    },
    { TidyMergeEmphasis,                             0,        
        "Diese Option legt fest, ob Tidy verschachtelte <code>&lt;b&gt;</code> "
        "und <code>&lt;i&gt;</code>-Elemente verschmelzen soll; zum Beispiel würde im Falle von "
        "<br/>"
        "<code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\"&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, "
        "<br/>"
        "Tidy diese Ausgabe erzeugen: <code>&lt;b class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
    },
    { TidyMergeSpans,                                0,        
        "Diese Option kann das Verhalten von <code>clean</code> beeinflussen, wenn "
        "ihr Wert <var>yes</var> ist."
        "<br/>"
        "Dann wird Tidy verschachtelte <code>&lt;span&gt;</code>, "
        "wie in <code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code> zu "
        "einem einzigen verschmelzen."
        "<br/>"
        "Der Algorithmus ist identisch mit dem der Option <code>merge-divs</code> (siehe dort). "
    },
    { TidyNCR,                                       0, "Diese Option bestimmt, ob Tidy numerische Zeichenreferenzen akzeptieren soll. "                                  },
    { TidyOmitOptionalTags,                          0,        
        "Mit dieser Option können optionale Start- und End-Tags von der Ausgabe "
        "ausgenommen werden. "
        "<br/>"
        "Ist diese Option aktiviert, werden alle Tags der Elemente <code>&lt;html&gt;</code>, "
        "<code>&lt;head&gt;</code>, und <code>&lt;body&gt;</code> für die Ausgabe verworfen, "
        "wie auch die End-Tags <code>&lt;/p&gt;</code>, "
        "<code>&lt;/li&gt;</code>, <code>&lt;/dt&gt;</code>, "
        "<code>&lt;/dd&gt;</code>, <code>&lt;/option&gt;</code>, "
        "<code>&lt;/tr&gt;</code>, <code>&lt;/td&gt;</code>, und "
        "<code>&lt;/th&gt;</code>. "
        "<br/>"
        "Diese Option wird für XML-Ausgaben ignoriert. "
    },
    { TidyOutputBOM,                                 0,        
        "Diese Option bestimmt, ob Tidy eine Byte-Reihenfolge-Markierung (BOM) an den Anfang der Ausgabe schreiben soll. "
        "Dies betrifft nur UTF-8 und UTF-16 Ausgabekodierungen, wo das BOM-Zeichen entweder den Wert U+EFBBBF (UTF-8) oder "
        "U+FEFF (UTF-16) hat. "
        "<br/>"
        "Wenn die Option den Wert <var>auto</var> hat, wird Tidy die BOM nur dann in die Ausgabe schreiben, "
        "wenn sie bereits zu Beginn der Eingabedaten vorhanden war. "
        "<br/>"
        "XML/XMLHTML-Ausgaben in UTF-16 Kodierung erhalten immer eine BOM. "
    },
    { TidyPreserveEntities,                          0,        
        "Diese Option bestimmt, ob Tidy wohlgeformte Entities, wie in der Eingabe vorgefunden, "
        "beibehält. "
    },
    { TidyPriorityAttributes,                        0,        
        "Mit dieser Option können Sie bestimmen, dass Attribute Vorrang vor anderen "
        "haben und, im Ausgabedokument, den anderen Attributen eines Elements "
        "vorangestellt werden. Zum Beispiel können Sie festlegen, dass <strong>id</strong> "
        "und <strong>name</strong> vor allen anderen Attributen genannt werden. "
        "<br/>"
        "Die Option erwartet als Wert eine Liste von leerzeichen- oder kommaseparierten "
        "Attributnamen. "
    },
    { TidyQuiet,                                     0,        
        "Wenn diese Option aktiv is, beschränkt Tidy andere Ausgaben als die des bereinigten Dokuments "
        "auf Fehler- und Warnmeldungen. "
    },
    { TidyQuoteAmpersand,                            0,        
        "Diese Option bestimmt, ob Tidy alleinstehende <code>&amp;</code> "
        "als <code>&amp;amp;</code> ausgeben soll. "
    },
    { TidyQuoteMarks,                                0,        
        "Diese Option bestimmt, ob Tidy <code>&quot;</code> Zeichen als "
        "<code>&amp;quot;</code> ausgeben soll, wie es manche Redaktionssysteme "
        "bevorzugen. "
        "<br/>"
        "Das Auslassungszeichen <code>'</code> wird als <code>&amp;#39;</code> "
        "ausgegeben, weil viele Web-Browser <code>&amp;apo;</code> noch nicht "
        "unterstützen. "
    },
    { TidyQuoteNbsp,                                 0,        
        "Diese Option bestimmt, ob Tidy geschützte Leerzeichen als Entities "
        "und nicht als Unicode-Zeichen 160 (dezimal) ausgeben soll. "
    },
    { TidyReplaceColor,                              0,        
        "Mit dieser Option können Sie Tidy auffordern, numerische Werte in "
        "Farb-Attributen durch HTML/XHTML Farbnamen zu ersetzen, so weit "
        "sie definiert sind. Zum Beispiel würde <code>#ffffff</code> zu "
        "<code>white</code>. "
    },
    { TidyShowErrors,                                0,        
        "Mit dem Wert dieser Option wird gesteuert, ob Tidy weitere Fehler "
        "meldet. Wenn der Wert <var>0</var> ist, werden gar keine Fehler "
        "gemeldet. "
    },
    { TidyShowFilename,                              0,        
        "Diese Option legt fest, ob Tidy den Dateinamen in Meldungen anzeigt. z.B.: "
        "<br/>"
        " tidy -q -e --show-filename yes index.html<br/>"
        " index.html: line 43 column 3 - Warning: replacing invalid UTF-8 bytes (char. code U+00A9) "
    },
    { TidyShowInfo,                                  0,        
        "Mit dieser Option wird festgelegt, ob Tidy Protokollmeldungen auf dem "
        "Niveau INFO anzeigen soll."
    },
    { TidyShowWarnings,                              0,        
        "Diese Option legt fest, ob Tidy Warnungen ausgeben soll oder nicht. "
        "Es kann nützlich sein, Warnungen zu deaktivieren, wenn wenige Fehler "
        "in einer Masse von Warnmeldungen untergehen. "
    },
    { TidySkipNested,                                0,        
        "Diese Option bestimmt, ob Tidy verschachtelte Elemente ausnehmen soll, "
        "wenn Script- und Style-Daten analysiert werden. "
    },
    { TidySortAttributes,                            0,        
        "Diese Option legt fest, dass Tidy Attribute innerhalb eines Elements "
        "anhand eines bestimmten Algorithmus sortieren soll. Wenn hier <var>alpha</var> "
        "gewählt wird, wird in aufsteigender, alphabetischer Reihenfolge sortiert. "
        "<br/>"
        "Wenn dagegen gleichzeitig <code>priority-attributes</code> verwendet wird, "
        "werden zunächst die priorisierten Attribute ausgegeben, bevor die restlichen sortiert werden. "
    },
    { TidyTabSize,                                   0,        
        "Diese Option legt die Anzahl der Spalten fest, die Tidy zwischen aufeinanderfolgenden "
        "Tabulatorzeichen vorsieht. Damit werden beim Lesen der Eingabe Tabulatoren in Leerzeichen umgewandelt. "
    },
    { TidyUpperCaseTags,                             0,        
        "Diese Option legt fest, ob Tidy Tagnamen groß oder klein schreibt. "
        "<br/>"
        "Der Standardwert ist <var>no</var> und setzt kleingeschriebene Tagnamen durch, "
        "außer für die XML-Ausgabe, wo die originale Schreibweise beibehalten wird. "
    },
    { TidyWord2000,                                  0,        
        "Diese Option bestimmt, ob Tidy große Anstrengungen unternehmen soll, "
        "um all den zusätzlichen Code, den Microsoft Word 2000 beim Speichern als \"Web-Seite\" einfügt, "
        "wieder zu entfernen. Eingebettete Bilder oder VML werden nicht behandelt. "
        "<br/>"
        "Sie sollten in Betracht ziehen, beim Auslösen der Funktion <strong>Speichern als...</strong>, "
        "dem Dateityp <strong>Web-Seite, gefiltert</strong> Vorrang zu geben."
    },
    { TidyWrapAsp,                                   0,        
        "Mit dieser Option können Sie festlegen, ob Tidy Text innerhalb von "
        "ASP Pseudoelementen, wie <code>&lt;% ... %&gt;</code>, umbrechen soll. "
    },
    { TidyWrapJste,                                  0,        
        "Mit dieser Option wird bestimmt, ob Tidy den Text innerhalb von "
        "JSTE Peseudo-Elementen, wie <code>&lt;# ... #&gt;</code>, umbrechen soll. "
    },
    { TidyWrapLen,                                   0,        
        
        "Diese Option legt den rechten Rand für Zeilenumbrüche fest. "
        "<br/>"
        "Tidy wird versuchen, Zeilen so umzubrechen, dass sie diese Länge nicht überschreiten. "
        "<br/>"
        "Setzen Sie <code>wrap</code> auf <var>0</var> (Null), wenn Sie Zeilenumbrüche unterbinden möchten. "
    },
    { TidyWrapPhp,                                   0,        
        "Diese Option legt fest, ob Tidy nach PHP Pseudoelementen, "
        "wie <code>&lt;?php ... ?&gt;</code> einen Zeilenumbruch einfügen soll. "
    },
    { TidyWrapScriptlets,                            0,        
        
        "Mit dieser Option wird bestimmt, ob Tidy Literale, die in Skript-Attributen "
        "auftauchen, umbrechen soll. "
    },
    { TidyWriteBack,                                 0,        
        "Mit dieser Option wird bestimmt, ob Tidy den bereinigten Auszeichnungscode "
        "in die selbe Datei schreiben soll, aus der er gelesen worden ist. "
        "<br/>"
        "Sie sollten Kopien wichtiger Dateien anlegen, bevor Sie sie bereinigen, da, "
        "in Ausnahmefällen, das Ergebnis nicht Ihren Erwartungen entsprechen kann. "
    },
    { TidyWarning,                                   0, "Warnung: "                                                                                                       },
    { TidyAccess,                                    0, "Zugriff: "                                                                                                       },
    { TidyError,                                     0, "Fehler: "                                                                                                        },
    { TidyBadDocument,                               0, "Dokument: "                                                                                                      },
    { TidyFatal,                                     0, "Panik: "                                                                                                         },
    { TidyDialogueSummary,                           0, "Resümee: "                                                                                                       },
    { TidyDialogueFootnote,                          0, "Fußnote: "                                                                                                       },
    { LINE_COLUMN_STRING,                            0, "Zeile %d Spalte %d - "                                                                                           },
    { FN_LINE_COLUMN_STRING,                         0, "%s: Zeile %d Spalte %d - "                                                                                       },
    { STRING_DISCARDING,                             0, "verwerfe"                                                                                                        },
    { STRING_ERROR_COUNT_ERROR,                      0, "Fehler"                                                                                                          },
    { STRING_ERROR_COUNT_ERROR,                      1, "Fehler"                                                                                                          },
    { STRING_ERROR_COUNT_WARNING,                    0, "Warnung"                                                                                                         },
    { STRING_ERROR_COUNT_WARNING,                    1, "Warnungen"                                                                                                       },
    { STRING_HELLO_ACCESS,                           0, "\nTests der Barrierefreiheit:\n"                                                                                 },
    { STRING_HTML_PROPRIETARY,                       0, "HTML Proprietär"                                                                                                 },
    { STRING_XML_DECLARATION,                        0, "XML Deklaration"                                                                                                 },
    { STRING_PLAIN_TEXT,                             0, "Klartext"                                                                                                        },
    { STRING_REPLACING,                              0, "ersetze"                                                                                                         },
    { STRING_SPECIFIED,                              0, "genannte"                                                                                                        },
    { TIDYCUSTOMNO_STRING,                           0, "nein"                                                                                                            },
    { TIDYCUSTOMBLOCKLEVEL_STRING,                   0, "Blockniveau"                                                                                                     },
    { TIDYCUSTOMEMPTY_STRING,                        0, "leer"                                                                                                            },
    { TEXT_HTML_T_ALGORITHM,                         0,        
        "\n"
        "      - Zunächst suche links von der Zellenposition nach weiteren Zeilenköpfen.\n"
        "      - Dann suche oberhalb nach Spaltenköpfen.\n"
        "      - Die Suche in der angegebenen Richtung wird am Tabellenrand beendet\n"
        "        oder wenn eine Datenzelle hinter einer Kopfzelle gefunden wird\n"
        "      - Zeilenköpfe werden in die Liste eingefügt in der Reihenfolge Ihres\n"
        "        Erscheinens in der Tabelle. \n"
        "      - Bei links-nach-rechts Tabellen werden Kopfzellen von links nach rechts\n"
        "        eingefügt"
        "      - Spaltenköpfe werden nach Zeilenköpfenn eingefügt, in der Reihenfolge\n"
        "        ihres Erscheinens in der Tabelle, von Oben nach Unten. \n"
        "      - Wenn eine Kopfzelle ein Attribut headers besitzt, dann werden die\n"
        "        so bezeichneten Zellen in die Liste eingefügt und die Suche in der\n"
        "        aktuellen Richtung eingestellt.\n"
        "        TD-Zellen, die das Attribut axis besitzen, werden ebenfalls als\n"
        "        Kopfzellen behandelt.\n"
    },
    { TEXT_VENDOR_CHARS,                             0,        
        "Es ist unwahrscheinlich, dass händlerspezifische, systemabhängige\n"
        "Zeichenkodierungen im World Wide Web ausreichend zuverlässig\n"
        "funktionieren; Sie sollten die Vewendung der Zeichenkodieriung %s\n"
        "vermeiden und statt dessen benannte Entitäten, z.B. &trade;\n"
        "verwenden.\n"
    },
    { TEXT_SGML_CHARS,                               0,        
        "Die Zeichencodes zwischen 128 und 159 (U+0080 bis U+009F) sind in HTMl nicht\n"
        "erlaubt; selbst wenn sie es wären, wären sie wohl nicht-druckbare\n"
        "Steuerzeichen. Tidy vermutete dass Sie ein Zeichen mit dem gleichen Bytewert\n"
        "in der Kodierung %s meinten und hat darum die Ersetzung durch das\n"
        "Unicode-Äquivalent vorgenommen.\n"
    },
    { TEXT_INVALID_UTF8,                             0,        
        "Zeichencodes für UTF-8 müssen zwischen U+000 und U+10FFFF liegen.\n"
        "Die UTF-8 Definition erlaubt im Anhang D zu ISO/IEC 10646-1:2000\n"
        "auch die Benutzung von 6-Byte Sequenzen für die Kodierung von\n"
        "Buchstaben die außerhalb des Unicode Zeichensatzes liegen;\n"
        "Diese fünf- und sechs Byte langen Sequencen sind unerlaubt für\n"
        "UTF-8 als Transformation von Unicode Zeichen. ISO/IEC 10646\n"
        "erlaubt kein Mapping nicht paarweise zugeordneter Ersatzzeichen,\n"
        "auch nicht U+FFFE oder U+FFFF (es erlaubt aber andere\n"
        "nichtdruckbare Zeichen). Mehr Informationen, erhalten Sie auf\n"
        "https://home.unicode.org/ und https://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_UTF16,                            0,        
        "Zeichencodes für UTF-16 müssen im Breich U+0000 bis U+10FFFF liegen.\n"
        "Die UTF-16 Definition im Anhang C zu ISO/IEC 10646-1:2000 erlaubt\n"
        "kein Mapping nicht paarweise zugeordneter Ersatzzeichen. Weitere\n"
        "Informationen finden Sie auf\n"
        "https://home.unicode.org/ und https://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_URI,                              0,        
        "URIs müssen richtig mit Escape-Sequenzen ausgestatten werden\n"
        "und darf keine unmaskierten Zeichen unter U+0021 einschließlich,\n"
        "des Leerzeichens und keine Zeichen über U+007E. Tidy fügt,\n"
        "Escape-Sequenzen in URIs ein wie es von HTML 4.01 im Abschnitt\n"
        "B.2.1 der Spezifikation und XML 1.0 im Abschnitt 4.2.2 empfohlen\n"
        "ist. Einige Endbenutzerprogramme verwenden andere Algorithmen\n"
        "für Escape-Sequenzen in solchen URIs und die Funktion manche\n"
        "server-seitiger Skripte ist davon abhängig. Wenn Sie damit nicht\n"
        "einverstanden sind, müssen Sie die Escape-Sequenzuen selbst\n"
        "schreiben. Dazu gibt es mehr Informationen auf\n"
        "https://www.w3.org/International/O-URL-and-ident.html\n"
    },
    { TEXT_BAD_FORM,                                 0,        
        "Es ist vielleicht nötig eines-, oder beide Tags <form> und </form>\n"
        "zu verschieben. HTML-Elemente sollten richtig verschachtelt sein und\n"
        "form-Elemente sind keine Ausnahme. Zum Beispiel sollten Sie das\n"
        "<form> Tag nicht in eine Tabellenzelle und </form> in eine andere\n"
        "schreiben. Wenn <form> einer Tabelle vorangeht, kann </form> nicht\n"
        "innerhalb der Tabelle erscheinen! Bachten Sie auch, dass ein\n"
        "Formular nicht mit einem anderen verschachtelt werden kann."
    },
    { TEXT_BAD_MAIN,                                 0,        
        "Nur ein einziges <main> Element ist in einem Dokument erlaubt.\n"
        "Weitere <main> Elemente wurden verworfen, was das Dokument\n"
        "ungültig machen kann.\n"
    },
    { TEXT_M_SUMMARY,                                0,        
        "Das summary-Attribut sollte in Tabellen verwendet werden, \n"
        "um die Tabellenstruktur zu beschreiben. Es ist sehr hilfreich\n"
        "für Leute, die nicht-optische Browser verwenden. Die Attribute\n"
        "scope und header in Tabellenzellen sind nützlich, um zu\n"
        "präzisieren, welcher Tabellenkopf zu welcher Tabellenzelle\n"
        "gehört, was nicht-optischen Browsern ermöglicht, sinnvollen\n"
        "Kontext zu jeder Zelle zu liefern.\n"
    },
    { TEXT_M_IMAGE_ALT,                              0,        
        "Das alt-Attribut sollte für die Kurzbeschreibung eines Bildes\n"
        "verwendet werden; für längere Beschreibungen ist das longdesc-\n"
        "Attribut gedacht, das die URL zur Beschreibung enthält.\n"
        "Diese Details helfen Menschen, die nicht-grafische Browser verwenden.\n"
    },
    { TEXT_M_IMAGE_MAP,                              0,        
        "Geben Sie client-seitigen Vorrang vor server-seitigen Image maps\n"
        "weil letztere für Menschen mit nicht-grafischen Browsern unzugänglich\n"
        "sind. Außerdem werden client-seitige maps leichter erzeugt und\n"
        "sind reaktiver."
    },
    { TEXT_M_LINK_ALT,                               0,        
        "Im Zusammenhang mit client-seitigen Image Maps müssen Sie das\n"
        "alt-Attribut mit einer textuellen Beschreibung des Links\n"
        "verwenden, für Leute, die nicht-grafische Browser benutzen.\n"
    },
    { TEXT_USING_FRAMES,                             0,        
        "Seiten, die mit Frames gestaltet werden, stellen ein Problem dar\n"
        "für Leute, die entweder blind sind oder Browser verwenden, die\n"
        "Frames gar nicht unterstützen. Eine Frame-basierte Seite sollte\n"
        "stets über ein alternatives Layout innerhalb des NOFRAMES\n"
        "Elements verfügen."
    },
    { FOOTNOTE_TRIM_EMPTY_ELEMENT,                   0,        
        "Eines oder mehrere leere Elemente waren im Quelldokument vorhanden,\n"
        "wurden aber bei der Ausgabe verworfen. Sollten diese Element für Sie\n"
        "wichtig sein oder wenn Sie ein anderes Vorgehen wünschen,\n"
        "ziehen Sie in Betracht, die Option \"drop.empty-elements\" auf\n"
        "no zu setzen.\n"
    },
    { TEXT_ACCESS_ADVICE1,                           0,        
        "Weitere Ratschläge zur Barrierefreiheit finden Sie auf\n"
        "https://www.w3.org/WAI/GL."
    },
    { TEXT_ACCESS_ADVICE2,                           0,        
        "Weitere Ratschläge zur Barrierefreiheit finden Sie auf\n"
        "https://www.w3.org/WAI/GL und https://www.html-tidy.org/accessibility/."
    },
    { TEXT_USING_LAYER,                              0,        
        "Es wird empfohlen, dem Positionierungsmechanismus von Cascading\n"
        "Style Sheets (CSS) Vorrang vor dem proprietären Element <LAYER>\n"
        "zu geben, weil LAYER nur beschränkt unterstützt wird."
    },
    { TEXT_USING_SPACER,                             0,        
        "Es wird empfohlen, CSS zur Kontrolle von Leerraum zu verwenden,\n"
        "z.B. für Einrückungen, Ränder und Abständen.\n"
        "Das proprietäre <SPACER> Element wird nur beschränkt unterstützt.\n"
    },
    { TEXT_USING_FONT,                               0,        
        "Es wird empfohlen, CSS zur Festlegung von Schriften und\n"
        "Schrifteigenschaften zu verwenden, sie Schriftgrad und -Farbe.\n"
        "Damit wird die Größe der HTML-Datei verringert und sie ist,\n"
        "verglichen zum <FONT>-Element, leichter zu warten.\n"
    },
    { TEXT_USING_NOBR,                               0,        
        "Es wird empfohlen, CSS zur Kontrolle der Zeilenumbrüche zu\n"
        "verwenden, insbesondere \"white-space: nowrap\" um Zeilenumbrüche\n"
        "in einem Element zu verhindern, anstelle von <NOBR>...</NOBR>.\n"
    },
    { TEXT_USING_BODY,                               0,        
        "Es wird empfohlen, CSS zur Festlegung der Farben von Seiten und\n"
        "Links zu verwenden.\n"
    },
    { STRING_CONTENT_LOOKS,                          0, "Dokumentinhalt scheint %s zu sein"                                                                               },
    { STRING_DOCTYPE_GIVEN,                          0, "angegebener Doctype ist \"%s\""                                                                                  },
    { STRING_ERROR_COUNT,                            0, "Tidy hat %u %s und %u %s gefunden!\n"                                                                            },
    { STRING_NEEDS_INTERVENTION,                     0,        
        "Dieses Dokument hat Fehler, die korrigiert werden müssen,\n"
        "bevor HTML Tidy eine bereinigte Version generieren kann.\n"
    },
    { STRING_NO_ERRORS,                              0, "Es wurden keine Warnungen oder Fehler gefunden.\n"                                                               },
    { STRING_NO_SYSID,                               0, "Kein System-Identifikator im übermittelten doctype"                                                              },
    { STRING_NOT_ALL_SHOWN,                          0,        
        "Tidy hat %u %s und %u %s gefunden! \n"
        "Nicht alle Warnungen oder Fehler wurden angezeigt.\n"
    },
    { TEXT_GENERAL_INFO,                             0,        
        "Über HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Fehlerberichte und Kommentare (in English):\n"
        "\thttps://github.com/htacg/tidy-html5/issues\n"
        "Offizielle Mailing-Liste:\n"
        "\thttps://lists.w3.org/Archives/Public/public-htacg/\n"
        "Neueste HTML Spezifikation:\n"
        "\thttps://html.spec.whatwg.org/multipage/\n"
        "Validieren Sie Ihre HTML-Dokumente:\n"
        "\thttps://validator.w3.org/nu/\n"
        "Setzen Sie sich für den Eintritt Ihrer Firma ins W3C ein:\n"
        "\thttps://www.w3.org/Consortium\n"
    },
    { TEXT_GENERAL_INFO_PLEA,                        0,        
        "Sprechen Sie eine andere Sprache als Englisch oder eine andere Variante\n"
        "von Englisch? Überlegen Sie, ob Sie uns helfen möchten, HTML Tidy zu\n"
        "übersetzen. Details finden Sie auf\n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },
    { ADDED_MISSING_CHARSET,                         0, "Fehlendes <meta charset=...> wurde in %s hinzugefügt"                                                            },
    { ANCHOR_NOT_UNIQUE,                             0, "%s Verweisanker \"%s\" ist bereits definiert"                                                                    },
    { ANCHOR_DUPLICATED,                             0, "impliziter %s Anker \"%s\" von Tidy dupliziert."                                                                 },
    { APOS_UNDEFINED,                                0, "benannte Entität &apos; nur in XML/XHTML definiert"                                                              },
    { ATTR_VALUE_NOT_LCASE,                          0, "%s Attributwert \"%s\" muss für XHTML klein geschrieben sein"                                                    },
    { ATTRIBUTE_IS_NOT_ALLOWED,                      0, "%s Attribut \"is\" nicht in autonomen, benutzerdefnierten Tags erlaubt."                                         },
    { ATTRIBUTE_VALUE_REPLACED,                      0, "%s Attribut \"%s\", falscher Wert \"%s\" ersetzt"                                                                },
    { BACKSLASH_IN_URI,                              0, "%s URI Referenz enthält Backslash. Eingabefehler?"                                                               },
    { BAD_ATTRIBUTE_VALUE_REPLACED,                  0, "%s Attribut \"%s\" hatte den ungültigen Wert \"%s\" und wurde ersetzt"                                           },
    { BAD_ATTRIBUTE_VALUE,                           0, "%s Attribut \"%s\" hat den ungültigen Wert \"%s\""                                                               },
    { BAD_CDATA_CONTENT,                             0, "'<' + '/' + Zeichen hier nicht erlaubt"                                                                          },
    { BAD_SUMMARY_HTML5,                             0, "Das summary Attribute im Element %s ist in HTML5 obsolet"                                                        },
    { BAD_SURROGATE_LEAD,                            0, "Vorderes (niederes) Surrogat-Paar U+%04X, ohne vordere (obere) Entität, durch U+FFFD ersetzt."                   },
    { BAD_SURROGATE_PAIR,                            0, "Unzulässiges Surrogat-Paar U+%04X:U+%04X wurde durch U+FFFD ersetzt."                                            },
    { BAD_SURROGATE_TAIL,                            0, "Vorangestelltes (oberes) Surrogat-Paar U+%04X, ohne anschließennde (niedere) Entität, durch U+FFFD ersetzt."     },
    { CANT_BE_NESTED,                                0, "%s kann nicht verschachtelt sein"                                                                                },
    { COERCE_TO_ENDTAG,                              0, "<%s> ist wahrscheinlich als </%s> gedacht"                                                                       },
    { CONTENT_AFTER_BODY,                            0, "Inhalt nach dem Ende von body"                                                                                   },
    { CUSTOM_TAG_DETECTED,                           0, "Habe autonomes, benutzerdefiniertes Tag %s gefunden; Behandele als %s"                                           },
    { DISCARDING_UNEXPECTED,                         0, "Unerwartetes %s verworfen"                                                                                       },
    { DOCTYPE_AFTER_TAGS,                            0, "<!DOCTYPE> ist nach Elementen nicht erlaubt"                                                                     },
    { DUPLICATE_FRAMESET,                            0, "Wiederholung des FRAMESET Elements"                                                                              },
    { ELEMENT_NOT_EMPTY,                             0, "%s Element nicht leer oder nicht geschlossen"                                                                    },
    { ELEMENT_VERS_MISMATCH_ERROR,                   0, "%s Element steht in %s nicht zur Verfügung"                                                                      },
    { ELEMENT_VERS_MISMATCH_WARN,                    0, "%s Element steht in %s nicht zur Verfügung"                                                                      },
    { ENCODING_MISMATCH,                             0, "genannte Eingabe-Kodierung (%s) stimmt nicht mit der vorgefundenen Kodierung überein (%s)"                       },
    { ESCAPED_ILLEGAL_URI,                           0, "%s maskiere falsch formatierten URI Verweis"                                                                     },
    { FILE_CANT_OPEN,                                0, "Kann \"%s\" nicht öffnen\n"                                                                                      },
    { FILE_CANT_OPEN_CFG,                            0, "Kann die Konfigurationsdatei \"%s\" nicht öffnen\n"                                                              },
    { FILE_NOT_FILE,                                 0, "\"%s\" ist keine Datei!\n"                                                                                       },
    { FIXED_BACKSLASH,                               0, "%s Konvertiere einen Backslash im URI in Schrägstrich"                                                           },
    { FOUND_STYLE_IN_BODY,                           0, "<style> Tag in <body>! fix-style-tags: yes, um es zu verschieben"                                                },
    { ID_NAME_MISMATCH,                              0, "%s id und name Attribute unterscheiden sich im Wert"                                                             },
    { ILLEGAL_NESTING,                               0, "%s sollten nicht verschachtelt sein"                                                                             },
    { ILLEGAL_URI_CODEPOINT,                         0, "%s unerlaubte Zeichen im URI"                                                                                    },
    { ILLEGAL_URI_REFERENCE,                         0, "%s inkorrekt maskierter URI Verweis"                                                                             },
    { INSERTING_AUTO_ATTRIBUTE,                      0, "%s füge \"%s\" Attribut mit Wert \"%s\" ein"                                                                     },
    { INSERTING_TAG,                                 0, "füge implizites <%s> ein"                                                                                        },
    { INVALID_ATTRIBUTE,                             0, "%s Attributname \"%s\" (wert=\"%s\") ist ungültig"                                                               },
    { INVALID_NCR,                                   0, "%s ungültiger, numeriascher Zeichencode %s"                                                                      },
    { INVALID_SGML_CHARS,                            0, "%s ungültiger Zeichencode %s"                                                                                    },
    { INVALID_UTF8,                                  0, "%s ungültige UTF-8 Bytes (Zeichencode %s)"                                                                       },
    { INVALID_UTF16,                                 0, "%s Ungültiges UTF-16 Ersetzungspaar (Zeichencode %s)"                                                            },
    { INVALID_XML_ID,                                0, "%s Kann Attribut name nicht in id kopieren"                                                                      },
    { JOINING_ATTRIBUTE,                             0, "%s Konsolidiere Werte des wiederholten Attributs \"%s\""                                                         },
    { MALFORMED_COMMENT,                             0, "Tidy hat aufeinanderfolgende \"-\" durch \"=\" ersetzt"                                                          },
    { MALFORMED_COMMENT_DROPPING,                    0, "Verwerfe eventuellen Kommentar, weil ein Bindestrich fehlt"                                                      },
    { MALFORMED_COMMENT_EOS,                         0, "Das Ende des Dokuments wurde vor dem Ende des Kommentars erreicht"                                               },
    { MALFORMED_COMMENT_WARN,                        0, "Aufeinanderfolgende Bindestriche im Kommentar; erwägen Sie fix-bad-comments zu setzen"                           },
    { MALFORMED_DOCTYPE,                             0, "Verwerfe fehlformatierten <!DOCTYPE>"                                                                            },
    { MISMATCHED_ATTRIBUTE_ERROR,                    0, "%s Attribut \"%s\" in %s nicht erlaubt"                                                                          },
    { MISMATCHED_ATTRIBUTE_WARN,                     0, "%s Attribut \"%s\" in %s nicht erlaubt"                                                                          },
    { MISSING_ATTR_VALUE,                            0, "%s Attribut \"%s\" ohne Wert"                                                                                    },
    { MISSING_ATTRIBUTE,                             0, "%s Attribut \"%s\" fehlt"                                                                                        },
    { MISSING_DOCTYPE,                               0, "fehlende <!DOCTYPE> Deklaration"                                                                                 },
    { MISSING_ENDTAG_BEFORE,                         0, "fehlendes </%s> vor %s"                                                                                          },
    { MISSING_ENDTAG_FOR,                            0, "fehlendes </%s>"                                                                                                 },
    { MISSING_ENDTAG_OPTIONAL,                       0, "fehlendes, optionales Abschlusstag </%s>"                                                                        },
    { MISSING_IMAGEMAP,                              0, "%s sollte client-seitige Image Map verwenden"                                                                    },
    { MISSING_QUOTEMARK,                             0, "%s Attribut mit fehlendem, abschließenden Gänsefüßchen"                                                          },
    { MISSING_QUOTEMARK_OPEN,                        0, "im Wert des Attributs \"%s\" fehlen Gänsefüßchen"                                                                },
    { MISSING_SEMICOLON_NCR,                         0, "numerische Zeichenreferenz \"%s\" endet nicht mit ';'"                                                           },
    { MISSING_SEMICOLON,                             0, "Entität \"%s\" endet nicht mit ';'"                                                                              },
    { MISSING_STARTTAG,                              0, "fehlendes <%s>"                                                                                                  },
    { MISSING_TITLE_ELEMENT,                         0, "füge fehlendes 'title' Element ein"                                                                              },
    { MOVED_STYLE_TO_HEAD,                           0, "habe <style> Tag in den Kopfbereich (<head>) verschoben! Setzen Sie fix-style-tags: no, um dies zu vermeiden."   },
    { NESTED_EMPHASIS,                               0, "verschachtelte Hervorhebung %s"                                                                                  },
    { NESTED_QUOTATION,                              0, "verschachtelte q Elemente, möglicher Tippfehler"                                                                 },
    { NEWLINE_IN_URI,                                0, "%s verwerfe Zeilenumbruch im URI-Verweis"                                                                        },
    { NOFRAMES_CONTENT,                              0, "%s nicht im 'noframes' Element"                                                                                  },
    { NON_MATCHING_ENDTAG,                           0, "ersetze unerwartetes %s durch </%s>"                                                                             },
    { OBSOLETE_ELEMENT,                              0, "ersetze obsoletes Element %s durch %s"                                                                           },
    { OPTION_REMOVED,                                0, "Option \"%s\" existiert nicht mehr und keine Ersetzung gefunden."                                                },
    { OPTION_REMOVED_APPLIED,                        0, "Option \"%s\" ersetzt durch \"%s\", von Tidy auf \"%s\" gesetzt."                                                },
    { OPTION_REMOVED_UNAPPLIED,                      0, "Option \"%s\" ersetzt durch \"%s\" aber Tidy konnte sie nicht für sie setzen."                                   },
    { PREVIOUS_LOCATION,                             0, "<%s> bereits vermerkt"                                                                                           },
    { PROPRIETARY_ATTR_VALUE,                        0, "%s proprietäres Attribut mit Wert \"%s\""                                                                        },
    { PROPRIETARY_ATTRIBUTE,                         0, "%s proprietäres Attribut \"%s\""                                                                                 },
    { PROPRIETARY_ELEMENT,                           0, "%s ist vom W3C nicht zugelassen"                                                                                 },
    { REMOVED_HTML5,                                 0, "%s Element aus HTML5 entfernt"                                                                                   },
    { REPEATED_ATTRIBUTE,                            0, "%s verwerfe Wert \"%s\" für wiederholtes Attribut \"%s\""                                                        },
    { REPLACING_ELEMENT,                             0, "ersetze %s durch %s"                                                                                             },
    { REPLACING_UNEX_ELEMENT,                        0, "ersetze unerwartetes %s durch %s"                                                                                },
    { SPACE_PRECEDING_XMLDECL,                       0, "entferne Leerraum vor der XML-Deklaration"                                                                       },
    { STRING_ARGUMENT_BAD,                           0, "Option \"%s\" mit ungeeignetem Argument \"%s\""                                                                  },
    { STRING_MISSING_MALFORMED,                      0, "fehlendes oder fehl-formatiertes Argument für Option: %s"                                                        },
    { STRING_MUTING_TYPE,                            0, "Mitteilungen vom Typ \"%s\" werden nicht ausgegeben"                                                             },
    { STRING_UNKNOWN_OPTION,                         0, "unbekannte Option: %s"                                                                                           },
    { SUSPECTED_MISSING_QUOTE,                       0, "vermute fehlendes Gänsefüßchen im Attributwert"                                                                  },
    { TAG_NOT_ALLOWED_IN,                            0, "%s ist im Element <%s> nicht erlaubt"                                                                            },
    { TOO_MANY_ELEMENTS_IN,                          0, "zu viele %s Elemente in <%s>"                                                                                    },
    { TOO_MANY_ELEMENTS,                             0, "zu viele %s Elemente"                                                                                            },
    { TRIM_EMPTY_ELEMENT,                            0, "kürze leeres %s"                                                                                                 },
    { UNESCAPED_AMPERSAND,                           0, "unmaskiertes & sollte als &amp; geschrieben werden"                                                              },
    { UNEXPECTED_END_OF_FILE_ATTR,                   0, "%s Dateiende erreicht, während noch Attribute ausgewertet werden"                                                },
    { UNEXPECTED_END_OF_FILE,                        0, "unerwartetes Dateiende %s"                                                                                       },
    { UNEXPECTED_ENDTAG_ERR,                         0, "unerwartetes </%s>"                                                                                              },
    { UNEXPECTED_ENDTAG_IN,                          0, "unerwartetes </%s> in <%s>"                                                                                      },
    { UNEXPECTED_ENDTAG,                             0, "unerwartetes </%s>"                                                                                              },
    { UNEXPECTED_EQUALSIGN,                          0, "%s unerwartetes '=' anstelle von Attributnamen"                                                                  },
    { UNEXPECTED_GT,                                 0, "%s fehlendes '>' am Ende eines Tags"                                                                             },
    { UNEXPECTED_QUOTEMARK,                          0, "%s unerwartetes oder doppeltes Gänsefüßchen"                                                                     },
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM,                  0, "%s wird nicht erkannt! Wollten Sie die Option custom-tags aktivieren?"                                           },
    { UNKNOWN_ELEMENT,                               0, "%s wird nicht erkannt!"                                                                                          },
    { UNKNOWN_ENTITY,                                0, "unmaskiertes & oder unbekannte Entität \"%s\""                                                                   },
    { USING_BR_INPLACE_OF,                           0, "verwende <br> anstelle von %s"                                                                                   },
    { VENDOR_SPECIFIC_CHARS,                         0, "%s ungültiger Zeichencode %s"                                                                                    },
    { WHITE_IN_URI,                                  0, "%s verwerfe Leerzeichen in einem URI Verweis"                                                                    },
    { XML_DECLARATION_DETECTED,                      0, "Eine XML Deklaration wurde entdeckt. Wollten Sie input-xml verwenden?"                                           },
    { XML_ID_SYNTAX,                                 0, "%s ID \"%s\" verwendet XML ID Syntax"                                                                            },
    { IMG_MISSING_ALT,                               0, "[1.1.1.1]: <img> ohne 'alt' Text."                                                                               },
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0, "[1.1.1.2]: suspekter 'alt' Text (Dateiname)."                                                                    },
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0, "[1.1.1.3]: suspekter 'alt' Text (Dateigröße)."                                                                   },
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0, "[1.1.1.4]: suspekter 'alt' Text (Platzhalter)."                                                                  },
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0, "[1.1.1.10]: suspekter 'alt' Text (zu lang)."                                                                     },
    { IMG_MISSING_LONGDESC_DLINK,                    0, "[1.1.2.1]: <img> Attribute 'longdesc' und d-link fehlen."                                                        },
    { IMG_MISSING_DLINK,                             0, "[1.1.2.2]: <img> Attribut d-link fehlt."                                                                         },
    { IMG_MISSING_LONGDESC,                          0, "[1.1.2.3]: <img> Attribut 'longdesc' fehlt."                                                                     },
    { IMG_BUTTON_MISSING_ALT,                        0, "[1.1.3.1]: <img> (Button) fehlender 'alt' Text."                                                                 },
    { APPLET_MISSING_ALT,                            0, "[1.1.4.1]: <applet> fehlender alternativer Inhalt."                                                              },
    { OBJECT_MISSING_ALT,                            0, "[1.1.5.1]: <object> fehlender alternativer Inhalt."                                                              },
    { AUDIO_MISSING_TEXT_WAV,                        0, "[1.1.6.1]: Tonausgabe ohne Text-Transkription (wav)."                                                            },
    { AUDIO_MISSING_TEXT_AU,                         0, "[1.1.6.2]: Tonausgabe ohne Text-Transkription (au)."                                                             },
    { AUDIO_MISSING_TEXT_AIFF,                       0, "[1.1.6.3]: Tonausgabe ohne Text-Transkription (aiff)."                                                           },
    { AUDIO_MISSING_TEXT_SND,                        0, "[1.1.6.4]: Tonausgabe ohne Text-Transkription (snd)."                                                            },
    { AUDIO_MISSING_TEXT_RA,                         0, "[1.1.6.5]: Tonausgabe ohne Text-Transkription (ra)."                                                             },
    { AUDIO_MISSING_TEXT_RM,                         0, "[1.1.6.6]: Tonausgabe ohne Text-Transkription (rm)."                                                             },
    { FRAME_MISSING_LONGDESC,                        0, "[1.1.8.1]: <frame> benötigt vielleicht 'longdesc' Attribut."                                                     },
    { AREA_MISSING_ALT,                              0, "[1.1.9.1]: <area> fehlender 'alt' Text."                                                                         },
    { SCRIPT_MISSING_NOSCRIPT,                       0, "[1.1.10.1]: <script> fehlender <noscript> Abschnitt."                                                            },
    { ASCII_REQUIRES_DESCRIPTION,                    0, "[1.1.12.1]: ASCII Bild benötigt Beschreibung."                                                                   },
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0, "[1.2.1.1]: (Server-seitige) Image-Map benötigt Textverweise."                                                    },
    { MULTIMEDIA_REQUIRES_TEXT,                      0, "[1.4.1.1]: Multimediadaten benötigen synchronisierte Textentsprechung."                                          },
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0, "[1.5.1.1]: (Client-seitige) Image-Map benötigt Textverweise."                                                    },
    { INFORMATION_NOT_CONVEYED_IMAGE,                0, "[2.1.1.1]: Vermeiden Sie, dass Information nur durch Farbe vermittelt wird (image)."                             },
    { INFORMATION_NOT_CONVEYED_APPLET,               0, "[2.1.1.2]: Vermeiden Sie, dass Information nur durch Farbe vermittelt wird (applet)."                            },
    { INFORMATION_NOT_CONVEYED_OBJECT,               0, "[2.1.1.3]: Vermeiden Sie, dass Information nur durch Farbe vermittelt wird (object)."                            },
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0, "[2.1.1.4]: Vermeiden Sie, dass Information nur durch Farbe vermittelt wird (script)."                            },
    { INFORMATION_NOT_CONVEYED_INPUT,                0, "[2.1.1.5]: Vermeiden Sie, dass Information nur durch Farbe vermittelt wird (input)."                             },
    { COLOR_CONTRAST_TEXT,                           0, "[2.2.1.1]: schlechter Farbkontrast (Text)."                                                                      },
    { COLOR_CONTRAST_LINK,                           0, "[2.2.1.2]: schlechter Farbkontrast (Link)."                                                                      },
    { COLOR_CONTRAST_ACTIVE_LINK,                    0, "[2.2.1.3]: schlechter Farbkontrast (Aktiver Link)."                                                              },
    { COLOR_CONTRAST_VISITED_LINK,                   0, "[2.2.1.4]: schlechter Farbkontrast (Besuchter Link)."                                                            },
    { DOCTYPE_MISSING,                               0, "[3.2.1.1]: <doctype> fehlt."                                                                                     },
    { STYLE_SHEET_CONTROL_PRESENTATION,              0, "[3.3.1.1]: Kontrollieren Sie die Präsentation mit Style Sheets."                                                 },
    { HEADERS_IMPROPERLY_NESTED,                     0, "[3.5.1.1]: inkorrekt verschachtelte Überschriften."                                                              },
    { POTENTIAL_HEADER_BOLD,                         0, "[3.5.2.1]: potentielle Überschrift (Fettdruck)."                                                                 },
    { POTENTIAL_HEADER_ITALICS,                      0, "[3.5.2.2]: potentielle Überschrift (kursiv)."                                                                    },
    { POTENTIAL_HEADER_UNDERLINE,                    0, "[3.5.2.3]: potentielle Überschrift (unterstrichen)."                                                             },
    { HEADER_USED_FORMAT_TEXT,                       0, "[3.5.3.1]: Überschrift zur Textformatierung verwendet."                                                          },
    { LIST_USAGE_INVALID_UL,                         0, "[3.6.1.1]: falsche Verwendung von Listenelementen <ul>."                                                         },
    { LIST_USAGE_INVALID_OL,                         0, "[3.6.1.2]: falsche Verwendung von Listenelementen <ol>."                                                         },
    { LIST_USAGE_INVALID_LI,                         0, "[3.6.1.4]: falsche Verwendung von Listenelementen <li>."                                                         },
    { LANGUAGE_NOT_IDENTIFIED,                       0, "[4.3.1.1]: Sprache nicht identifiziert."                                                                         },
    { LANGUAGE_INVALID,                              0, "[4.3.1.2]: ungültiges Attribut language."                                                                        },
    { DATA_TABLE_MISSING_HEADERS,                    0, "[5.1.2.1]: Datentabelle <table> ohne Spalten-/Zeilenköpfe (alle)."                                               },
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0, "[5.1.2.2]: Datentabelle <table> ohne Spalten-/Zeilenköpfe (1 Spalte)."                                           },
    { DATA_TABLE_MISSING_HEADERS_ROW,                0, "[5.1.2.3]: Datentabelle <table> ohne Spalten-/Zeilenköpfe (1 Zeile)."                                            },
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0, "[5.2.1.1]: Datentabelle <table> benötigt vielleicht Auszeichnung (Spaltenköpfe)."                                },
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0, "[5.2.1.2]: Datentabelle <table> benötigt vielleicht Auszeichnung (Zeilenköpfe)."                                 },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0, "[5.3.1.1]: Stellen Sie sicher, dass Layout-Tabellen richtig linearisieren."                                      },
    { LAYOUT_TABLE_INVALID_MARKUP,                   0, "[5.4.1.1]: Ungültige Auszeichnung in der Layout-Tabelle."                                                        },
    { TABLE_MISSING_SUMMARY,                         0, "[5.5.1.1]: <table> ohne Zusammenfassung (summary)."                                                              },
    { TABLE_SUMMARY_INVALID_NULL,                    0, "[5.5.1.2]: Ungültige Zusammenfassung in <table> (null)."                                                         },
    { TABLE_SUMMARY_INVALID_SPACES,                  0, "[5.5.1.3]: Ungültige Zusammenfassung in <table> (Leerzeichen)."                                                  },
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0, "[5.5.1.6]: Ungültige Zusammenfassung in <table> (Platzhaltertext)."                                              },
    { TABLE_MISSING_CAPTION,                         0, "[5.5.2.1]: <table> ohne Titelzeile (<caption>)."                                                                 },
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0, "[5.6.1.1]: Kopfdaten in <table> sollten abgekürzt sein."                                                         },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0, "[5.6.1.2]: Abgekürzte Kopfdaten in <table> sind ungültig (null)."                                                },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0, "[5.6.1.3]: Abgekürzte Kopfdaten in <table> sind ungültig (Leerzeichen)."                                         },
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0, "[6.1.1.1]: Style Sheets sollten getestet werden (Link)."                                                         },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0, "[6.1.1.2]: Style Sheets sollten getestet werden (Style-Element)."                                                },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0, "[6.1.1.3]: Style Sheets sollten getestet werden (Style-Attribut)."                                               },
    { FRAME_SRC_INVALID,                             0, "[6.2.1.1]: Quelle des Rahmeninhalts in <frame> ist ungültig."                                                    },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0, "[6.2.2.1]: Text-Äquivalente müssen getestet werden (applet)."                                                    },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0, "[6.2.2.2]: Text-Äquivalente müssen getestet werden (script)."                                                    },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0, "[6.2.2.3]: Text-Äquivalente müssen getestet werden (object)."                                                    },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0, "[6.3.1.1]: Programmatische Objekte sollten getestet werden (script)."                                            },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0, "[6.3.1.2]: Programmatische Objekte sollten getestet werden (object)."                                            },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0, "[6.3.1.3]: Programmatische Objekte sollten getestet werden (embed)."                                             },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0, "[6.3.1.4]: Programmatische Objekte sollten getestet werden (applet)."                                            },
    { FRAME_MISSING_NOFRAMES,                        0, "[6.5.1.1]: <frameset> ohne <noframes> Abschnitt."                                                                },
    { NOFRAMES_INVALID_NO_VALUE,                     0, "[6.5.1.2]: <noframes> Abschnitt ungültig (kein Wert)."                                                           },
    { NOFRAMES_INVALID_CONTENT,                      0, "[6.5.1.3]: <noframes> Abschnitt ungültig (Inhalt)."                                                              },
    { NOFRAMES_INVALID_LINK,                         0, "[6.5.1.4]: <noframes> Abschnitt ungültig (Verweis)."                                                             },
    { REMOVE_FLICKER_SCRIPT,                         0, "[7.1.1.1]: Flimmern entfernen (script)."                                                                         },
    { REMOVE_FLICKER_OBJECT,                         0, "[7.1.1.2]: Flimmern entfernen (object)."                                                                         },
    { REMOVE_FLICKER_EMBED,                          0, "[7.1.1.3]: Flimmern entfernen (embed)."                                                                          },
    { REMOVE_FLICKER_APPLET,                         0, "[7.1.1.4]: Flimmern entfernen (applet)."                                                                         },
    { REMOVE_FLICKER_ANIMATED_GIF,                   0, "[7.1.1.5]: Flimmern etfernen (animated gif)."                                                                    },
    { REMOVE_BLINK_MARQUEE,                          0, "[7.2.1.1]: blink/marquee entfernen."                                                                             },
    { REMOVE_AUTO_REFRESH,                           0, "[7.4.1.1]: auto-refresh entfernen."                                                                              },
    { REMOVE_AUTO_REDIRECT,                          0, "[7.5.1.1]: auto-redirect entfernen."                                                                             },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0, "[8.1.1.1]: sicherstellen, dass programmatische objekte zugänglich sind (script)."                                },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0, "[8.1.1.2]: sicherstellen, dass programmatische objekte zugänglich sind (object)."                                },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0, "[8.1.1.3]: sicherstellen, dass programmatische objekte zugänglich sind (applet)."                                },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0, "[8.1.1.4]: sicherstellen, dass programmatische objekte zugänglich sind (embed)."                                 },
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0, "[9.1.1.1]: (serverseitige) image map muss umgewandelt werden."                                                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0, "[9.3.1.1]: <script> für Tastatur ungeeignet (onMouseDown)."                                                      },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0, "[9.3.1.2]: <script> für Tastatur ungeeignet (onMouseUp)."                                                        },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0, "[9.3.1.3]: <script> für Tastatur ungeeignet (onClick)."                                                          },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0, "[9.3.1.4]: <script> für Tastatur ungeeignet (onMouseOver)."                                                      },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0, "[9.3.1.5]: <script> für Tastatur ungeeignet (onMouseOut)."                                                       },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0, "[9.3.1.6]: <script> für Tastatur ungeeignet (onMouseMove)."                                                      },
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0, "[10.1.1.1]: neue Fenster benötigen Warnhinweis (_new)."                                                          },
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0, "[10.1.1.2]: neue Fenster benötigen Warnhinweis (_blank)."                                                        },
    { REPLACE_DEPRECATED_HTML_APPLET,                0, "[11.2.1.1]: ersetze veraltetes html <applet>."                                                                   },
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0, "[11.2.1.2]: ersetze veraltetes html <basefont>."                                                                 },
    { REPLACE_DEPRECATED_HTML_CENTER,                0, "[11.2.1.3]: ersetze veraltetes html <center>."                                                                   },
    { REPLACE_DEPRECATED_HTML_DIR,                   0, "[11.2.1.4]: ersetze veraltetes html <dir>."                                                                      },
    { REPLACE_DEPRECATED_HTML_FONT,                  0, "[11.2.1.5]: ersetze veraltetes html <font>."                                                                     },
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0, "[11.2.1.6]: ersetze veraltetes html <isindex>."                                                                  },
    { REPLACE_DEPRECATED_HTML_MENU,                  0, "[11.2.1.7]: ersetze veraltetes html <menu>."                                                                     },
    { REPLACE_DEPRECATED_HTML_S,                     0, "[11.2.1.8]: ersetze veraltetes html <s>."                                                                        },
    { REPLACE_DEPRECATED_HTML_STRIKE,                0, "[11.2.1.9]: ersetze veraltetes html <strike>."                                                                   },
    { REPLACE_DEPRECATED_HTML_U,                     0, "[11.2.1.10]: ersetze veraltetes html <u>."                                                                       },
    { FRAME_MISSING_TITLE,                           0, "[12.1.1.1]: <frame> ohne Titel."                                                                                 },
    { FRAME_TITLE_INVALID_NULL,                      0, "[12.1.1.2]: <frame> Titel ungültig (null)."                                                                      },
    { FRAME_TITLE_INVALID_SPACES,                    0, "[12.1.1.3]: <frame> Titel ungültig (spaces)."                                                                    },
    { ASSOCIATE_LABELS_EXPLICITLY,                   0, "[12.4.1.1]: ordne Beschriftungen explizit Formularelementen zu."                                                 },
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0, "[12.4.1.2]: ordne Beschriftungen explizit Formularelementen zu (for)."                                           },
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0, "[12.4.1.3]: ordne Beschriftungen explizit Formularelementen zu (id)."                                            },
    { LINK_TEXT_NOT_MEANINGFUL,                      0, "[13.1.1.1]: Link Text nicht aussagekräftig."                                                                     },
    { LINK_TEXT_MISSING,                             0, "[13.1.1.2]: Link Text fehlt."                                                                                    },
    { LINK_TEXT_TOO_LONG,                            0, "[13.1.1.3]: Link Text zu lang."                                                                                  },
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0, "[13.1.1.4]: Link Text nicht aussagekräftig (hier klicken)."                                                      },
    { METADATA_MISSING,                              0, "[13.2.1.1]: Metadaten fehlen."                                                                                   },
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0, "[13.2.1.3]: Metadaten fehlen (redirect/auto-refresh)."                                                           },
    { SKIPOVER_ASCII_ART,                            0, "[13.10.1.1]: Ignoriere Ascii Art."                                                                               },

#if SUPPORT_CONSOLE_APP
    { TC_LABEL_COL,                                  0, "Spalte"                                                                                                          },
    { TC_LABEL_FILE,                                 0, "Datei"                                                                                                           },
    { TC_LABEL_LANG,                                 0, "Sprache"                                                                                                         },
    { TC_LABEL_LEVL,                                 0, "Niveau"                                                                                                          },
    { TC_LABEL_OPT,                                  0, "Option"                                                                                                          },
    { TC_MAIN_ERROR_LOAD_CONFIG,                     0, "Problem beim laden der Konfigurationsdatei \"%s\", Fehler = %d"                                                  },
    { TC_OPT_ACCESS,                                 0,        
        "Führe zusätzliche Prüfungen der Barrierefreiheit durch (<Niveau> = 0, 1, 2, 3). 0 wird "
        "angenommen, wenn <Niveau> fehlt."
    },
    { TC_OPT_ASCII,                                  0, "verwende ISO-8859-1 für Eingaben, US-ASCII für Ausgaben"                                                         },
    { TC_OPT_ASHTML,                                 0, "erzwinge Umwandlung von XHTML in wohlgeformtes HTML"                                                             },
    { TC_OPT_ASXML,                                  0, "konvertiere HTML zu wohlgeformtem XHTML"                                                                         },
    { TC_OPT_BARE,                                   0, "entferne typografische Anführungsstriche, Geviertstriche, etc."                                                  },
    { TC_OPT_BIG5,                                   0, "verwende Big5 für Ein- und Ausgaben"                                                                             },
    { TC_OPT_CLEAN,                                  0, "ersetze FONT, NOBR und CENTER Tags durch CSS"                                                                    },
    { TC_OPT_CONFIG,                                 0, "setze Konfigurationseinstellungen aus der genannten <Datei>"                                                     },
    { TC_OPT_ERRORS,                                 0, "nur Fehler und Warnungen anzeigen"                                                                               },
    { TC_OPT_FILE,                                   0, "schreibe Fehler und Warnungen in die genannte <Datei>"                                                           },
    { TC_OPT_GDOC,                                   0, "erzeuge saubere Version des aus Google Docs exportierten HTML"                                                   },
    { TC_OPT_HELP,                                   0, "liste Kommandozeilenoptionen"                                                                                    },
    { TC_OPT_HELPCFG,                                0, "alle Konfigurationseinstellungen auflisten"                                                                      },
    { TC_OPT_HELPENV,                                0, "Informationen zu Umgebung und Laufzeiteinstellungen anzeigen"                                                    },
    { TC_OPT_HELPOPT,                                0, "zeige eine Beschreibung der <Option>"                                                                            },
    { TC_OPT_IBM858,                                 0, "verwende IBM-858 (CP850+Euro) für Eingaben, US-ASCII für Ausgaben"                                               },
    { TC_OPT_INDENT,                                 0, "Element Inhalt einrücken"                                                                                        },
    { TC_OPT_ISO2022,                                0, "Verwende ISO-2022 für Ein- und Ausgaben"                                                                         },
    { TC_OPT_LANGUAGE,                               0,        
        "Sprache für Ausgaben von Tidy auf <Sprache> einstellen. Für weitere Hinweise geben Sie '-language help' ein. "
        "Verwendung vor Argumenten, die Ausgaben erzeugen, damit die Spracheinstellung beachtet wird, z.B.,"
        "`tidy -lang es -lang help`."
    },
    { TC_OPT_LATIN0,                                 0, "verwende ISO-8859-15 für Eingaben, US-ASCII für Ausgaben"                                                        },
    { TC_OPT_LATIN1,                                 0, "verwende ISO-8859-1 für Ein- und Ausgaben"                                                                       },
    { TC_OPT_MAC,                                    0, "verwende MacRoman für Eingaben, US-ASCII für Ausgaben"                                                           },
    { TC_OPT_MODIFY,                                 0, "originale Eingabedateien verändern"                                                                              },
    { TC_OPT_NUMERIC,                                0, "eher numerische- als benannte Entities ausgeben"                                                                 },
    { TC_OPT_OMIT,                                   0, "optionale Start- und End-Tags weglassen"                                                                         },
    { TC_OPT_OUTPUT,                                 0, "Ausgaben in die genannte <Datei> schreiben"                                                                      },
    { TC_OPT_QUIET,                                  0, "unwesentliche Ausgaben unterdrücken"                                                                             },
    { TC_OPT_RAW,                                    0, "Werte über 127 ausgeben, ohne Konvertierung zu Entities"                                                         },
    { TC_OPT_SHIFTJIS,                               0, "verwende Shift_JIS für Ein- und Ausgaben"                                                                        },
    { TC_OPT_SHOWCFG,                                0, "Aktuelle Konfigurationseinstellungen auflisten"                                                                  },
    { TC_OPT_EXP_CFG,                                0, "Aktuelle Konfigurationseinstellungen so auflisten, wie sie für eine Konfigurationsdatei geeignet sind"           },
    { TC_OPT_EXP_DEF,                                0, "Standard Konfigurationseinstellungen so auflisten, wie sie für eine Konfigurationsdatei geeignet sind"           },
    { TC_OPT_UPPER,                                  0, "erzwinge Großschreibung für Tags"                                                                                },
    { TC_OPT_UTF16,                                  0, "verwende UTF-16 für Ein- und Ausgaben"                                                                           },
    { TC_OPT_UTF16BE,                                0, "verwende UTF-16BE für Ein- und Ausgaben"                                                                         },
    { TC_OPT_UTF16LE,                                0, "verwende UTF-16LE für Ein- und Ausgaben"                                                                         },
    { TC_OPT_UTF8,                                   0, "verwende UTF-8 für Ein- und Ausgaben"                                                                            },
    { TC_OPT_VERSION,                                0, "Tidy-Version anzeigen"                                                                                           },
    { TC_OPT_WIN1252,                                0, "verwende Windows-1252 für Eingaben, US-ASCII für Ausgaben"                                                       },
    { TC_OPT_WRAP,                                   0,        
        "Text an der genannten <Spalte> umbrechen. 0 wird angenommen, wenn <Spalte> fehlt. "
        "Wenn diese Option fehlt, gilt der Standard für die Option 'wrap'."
    },
    { TC_OPT_XML,                                    0, "bestimmen, dass die Eingabe wohlgeformtes XML ist"                                                               },
    { TC_OPT_XMLCFG,                                 0, "alle Konfigurationsoptionen im XML Format auflisten"                                                             },
    { TC_OPT_XMLHELP,                                0, "Kommandozeilenparameter im XML Format auflisten"                                                                 },
    { TC_OPT_XMLSTRG,                                0, "Alle Zeichenketten als XML ausgeben"                                                                             },
    { TC_OPT_XMLERRS,                                0, "Fehlerkonstanten und Zeichenketten im XML-Format ausgeben"                                                       },
    { TC_OPT_XMLOPTS,                                0, "Optionsbeschreibungen in XML ausgeben"                                                                           },
    { TC_STRING_CONF_HEADER,                         0, "Einstellungen der Konfigurationsdatei:"                                                                          },
    { TC_STRING_CONF_NAME,                           0, "Name"                                                                                                            },
    { TC_STRING_CONF_TYPE,                           0, "Typ"                                                                                                             },
    { TC_STRING_CONF_VALUE,                          0, "Aktueller Wert"                                                                                                  },
    { TC_STRING_OPT_NOT_DOCUMENTED,                  0, "Warnung: Option `%s' ist undokumentiert."                                                                        },
    { TC_STRING_OUT_OF_MEMORY,                       0, "Speicher voll. Breche ab."                                                                                       },
    { TC_STRING_FATAL_ERROR,                         0, "Schwerwiegender Fehler: Unmöglicher Wert für id='%d'."                                                           },
    { TC_STRING_FILE_MANIP,                          0, "Dateimanipulation"                                                                                               },
    { TC_STRING_PROCESS_DIRECTIVES,                  0, "Verarbeite Anweisungen"                                                                                          },
    { TC_STRING_CHAR_ENCODING,                       0, "Zeichenkodierung"                                                                                                },
    { TC_STRING_LANG_MUST_SPECIFY,                   0, "Ein POSIX- oder Windows Gebietsschema muss angegeben werden."                                                    },
    { TC_STRING_LANG_NOT_FOUND,                      0, "Tidy beherrscht die Sprache '%s' nicht, werde statt dessen '%s' verwenden."                                      },
    { TC_STRING_MISC,                                0, "Verschiedenes"                                                                                                   },
    { TC_STRING_XML,                                 0, "XML"                                                                                                             },
    { TC_STRING_MUST_SPECIFY,                        0, "Eine Option muss angegeben werden."                                                                              },
    { TC_STRING_UNKNOWN_OPTION,                      0, "HTML Tidy: unbekannte Option: %c"                                                                                },
    { TC_STRING_UNKNOWN_OPTION_B,                    0, "HTML Tidy: unbekannte Option."                                                                                   },
    { TC_STRING_VERS_A,                              0, "HTML Tidy für %s, Version %s"                                                                                    },
    { TC_STRING_VERS_B,                              0, "HTML Tidy Version %s"                                                                                            },
    { TC_TXT_HELP_1,                                 0,        
        "%s [Optionen...] [Datei...] [Optionen...] [Datei...]\n"
        "Werkzeug zum Bereinigen und zur formatierten Ausgabe von HTML/XHTML/XML.\n"
        "\n"
        "Das ist die moderne HTML Tidy Version %s.\n"
        "\n"
    },
    { TC_TXT_HELP_2A,                                0, "Kommmandozeilenargumente für HTML Tidy für %s:"                                                                  },
    { TC_TXT_HELP_2B,                                0, "Kommandozeilenargumente für HTML Tidy:"                                                                          },
    { TC_TXT_HELP_3,                                 0,        
        "\n"
        "Tidy Konfigurationseinstellungen\n"
        "================================\n"
        " Verwenden Sie die Konfigurationseinstellungen als Kommandozeilenargumente\n"
        " in der Form\n"
        " \"--eine-option <wert>\", zum Beispiel, \"--indent-with-tabs yes\".\n"
        "\n"
        " Sie können auch eine Datei nennen, die die Konfigurationseinstellungen enthält. \n"
        " Verwenden Sie dazu die Anweisung -options <Datei> oder in eine oder mehrere\n"
        " Dateien gemäß Ihrer Arbeitsumgebung (siehe nächsten Abschnitt). \n"
        "\n"
        " Für eine Liste aller Konfigurationseinstellungen verwenden Sie \"-help-config\"\n"
        " oder konsultieren Sie die man-page (sofern es für Ihr Betriebssystem eine gibt).\n"
        "\n"
        "Konfigurationsdateien\n"
        "=====================\n"
        " Wenn in Ihrer Umgebung eine Variable $HTML_TIDY gesetzt ist und sie auf eine \n"
        " Tidy Konfigurationsdatei verweist, wird Tidy versuchen, sie zu verwenden. \n"
        "%s"
        " Benutzen Sie \"-help-env\", um mehr Informationen zur Anzeige weiterer\n"
        " Informationen darüber, wie Sie die Umgebung verwenden, um Einstellungen für\n"
        " Tidy vorzunehmen. \n"
        "\n"
        "Weiteres\n"
        "========\n"
        " Die Ein- und Ausgabenkanäle sind standardmäßig stdin und stdout.\n"
        "\n"
        " Optionen, die aus einem einzelnen Zeichen bestehen – mit Ausnahme von -f – \n"
        " können kombiniert werden wie in:  tidy -f errs.txt -imu foo.html\n"
        "\n"
        "Information\n"
        "===========\n"
        " Für weitere Informationen über HTML Tidy, besuchen Sie\n"
        "  https://www.html-tidy.org/\n"
        "\n"
        " Mehr zu HTML finden Sie auf den folgenden Seiten (in englischer Sprache):\n"
        "\n"
        "   HTML Living Standard (die neueste HTML Spezifikation)\n"
        "   https://html.spec.whatwg.org/multipage/\n"
        "\n"
        " Senden Sie Fehlerberichte an https://github.com/htacg/tidy-html5/issues/\n"
        " oder senden Sie Fragen und Kommentare an public-htacg@w3.org.\n"
        "\n"
        " Überprüfen Sie Ihre HTML Dokumente mit dem W3C Nu Validierer:\n"
        "   https://validator.w3.org/nu/\n"
        "\n"
    },
    { TC_TXT_HELP_3A,                                0,        
        "\n"
        " Außerdem wird Tidy automatisch versuchen, Konfigurationen aus diesen\n"
        " Dateien zu verwenden, wenn sie vorhanden sind:\n"
        "\n"
        "  %s \n"
        "  %s \n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG,                            0,        
        "\n"
        "HTML Tidy Konfigurationseinstellungen\n"
        "\n"
        "Innerhalb einer Datei notieren auf diese Weise:\n"
        "\n"
        "wrap: 72\n"
        "indent: no\n"
        "\n"
        "In der Kommandozeile:\n"
        "\n"
        "--wrap 72 --indent no\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,                       0, "Name"                                                                                                            },
    { TC_TXT_HELP_CONFIG_TYPE,                       0, "Typ"                                                                                                             },
    { TC_TXT_HELP_CONFIG_ALLW,                       0, "Erlaubte Werte"                                                                                                  },
    { TC_TXT_HELP_ENV_1,                             0,        
        "\n"
        " Tidy kann seine Konfigurationswerte aus mehreren Quellen lesen, in der\n"
        " nachfolgend beschriebenen Reihenfolge. Wiederholte Verwendung der\n"
        " gleichen Option überschreibt die vorhergehende Einstellung \n"
        "\n"
        " - In Tidy vordefinierte Standardwerte. \n"
        "%s"
        " - Die Datei, die in der Umgebungsvariablen $HTML_TIDY genannt ist: \n"
        "     %s \n"
        " - Optionen aus einer Datei, die in der Kommandozeile genannt ist. \n"
        " - Optionen, die direkt in der Kommandozeile gesetzt werden. \n"
    },
    { TC_TXT_HELP_ENV_1A,                            0,        
        " - Die systemweite Konfigurationsdatei: \n"
        "     %s \n"
        " - The benutzerspezifische Konfigurationsdatei: \n"
        "     %s \n"
    },
    { TC_TXT_HELP_ENV_1B,                            0, "(augenblicklich nicht gesetzt)"                                                                                  },
    { TC_TXT_HELP_ENV_1C,                            0,        
        "\n"
        "Beachten Sie, dass die benutzerspezifische Konfigurationsdatei %s\n"
        "nicht gelesen wird, weil $HTML_TIDY gesetzt ist\n"
    },
    { TC_TXT_HELP_LANG_1,                            0,        
        "\n"
        "Die Option -language (oder -lang) gibt an, in welcher Sprache Tidy \n"
        "Ausgaben erzeugen soll. Beachten Sie bitte, dass dies kein \n"
        "Übersetzungsdienst ist und nur die Mitteilungen betrifft, die Tidy produziert.\n"
        "\n"
        "Wenn -language auf der Kommandozeile verwendet wird, muss die Option anderen \n"
        "Optionen, die Ausgaben bewirken, vorausgehen; anderenfalls erzeugt Tidy \n"
        "Ausgaben, bevor feststeht, in welcher Sprache dies geschehen soll.\n"
        "\n"
        "Abgesehen von den standard POSIX Sprachencodes kann Tidy veraltete\n"
        "Windows Sprachencodes verstehen. Beachten Sie bitte, dass diese Liste\n"
        "die Codes enthält, die Tidy versteht und nichts darüber ausssagt, ob\n"
        "die Sprache augenblicklich installiert ist.\n"
        "\n"
        "Die äußere rechte Spalte zeigt, wie Tidy den alten Windows Namen\n"
        "versteht.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,                            0,        
        "\n"
        "Die nachfolgend genannten Sprachen sind momentan in Tidy installiert. \n"
        "Bitte beachten Sie, dass ihre Vollständigkeit nicht garantiert ist;\n"
        "lediglich hat ein Entwickler damit begonnen, die betreffende Sprache\n"
        "hinzuzufügen.\n"
        "\n"
        "Wo nötig, wird bei fehlenden Übersetzungen auf \"en\" zurückgegriffen. \n"
        "Melden Sie bitte inkorrekte Meldungen an das Tidy Team.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,                            0,        
        "\n"
        "Wenn Tidy in der Lage ist, Ihre Regionaleinstellungen zu ermitteln,\n"
        "wird es automatisch die zugeornete Sprache verwenden. Unix-ähnliche \n"
        "Systeme zum Beispiel, besitzen eine Umgebungsvariable $LANG und/oder\n"
        "$LC_ALL. Entnehmen Sie weitere Informationen der Dokumentation Ihres\n"
        "Betriebssystems.\n"
        "\n"
        "Im Augenblick verwendet Tidy das Locale %s. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,                        0, NULL
    }

}};


#endif /* language_de_h */
