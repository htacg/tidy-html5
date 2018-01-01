#ifndef language_pt_br_h
#define language_pt_br_h
/*
 * language_pt_br.h
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
 *     language (and maybe region) "pt_br". The source of
 *     these strings is a gettext PO file in Tidy's source, probably called 
 *     "language_pt_br.po".
 *
 * [ ] THIS FILE WAS HAND MODIFIED. Translators, please feel to edit this file
 *     directly (and check this box). If you prefer to edit PO files then use
 *     `poconvert.rb msgunfmt language_pt_br.h` (our own
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
static uint whichPluralForm_pt_br(uint n) {
    /* Plural-Forms: nplurals=2; */
    return (n > 1);
}


/**
 *  This structure specifies all of the strings needed by Tidy for a
 *  single language. Static definition in a header file makes it
 *  easy to include and exclude languages without tinkering with
 *  the build system.
 */
static languageDefinition language_pt_br = { whichPluralForm_pt_br, {
    /***************************************
     ** This MUST be present and first. 
     ** Specify the code for this language.
     ***************************************/
    {/* Specify the ll or ll_cc language code here. */
      TIDY_LANGUAGE,                                 0, "pt_br"
    },
    { TidyAccessibilityCheckLevel,                   0,        
        "Esta opção especifica o nível de verificação de acessibilidade, se houver, "
        "que Tidy deve executar. <br/>Nível <var>0 (Tidy Classic)</var> é equivalente "
        "à verificação de acessibilidade do Tidy Classic.<br/> Para obter mais "
        "informações sobre a verificação de acessibilidade do Tidy, visite <a href=\""
        "http://www.html-tidy.org/accessibility/\"> Página de acessibilidade do "
        "Tidy</a>. "
    },
    { TidyAltText,                                   0,        
        "Esta opção especifica o texto padrão <code>alt=</code> que o Tidy usa para "
        "atributos <code>&lt;img&gt;</code> quando o atributo <code>alt=</code> está "
        "faltando. <br/>Use com cuidado, pois é sua responsabilidade tornar seus "
        "documentos acessíveis para pessoas que não conseguem ver as imagens. "
    },
    { TidyAnchorAsName,                              0,        
        "Esta opção controla a exclusão ou adição do atributo <code>name</code> em "
        "elementos onde ele pode servir como âncora. <br/>Se configurado para "
        "<var>yes</var>, um atributo <code>name</code>, se não já existir, é "
        "adicionado ao longo de um atributo <code>id</code> existente se o DTD o "
        "permitir. <br/>Se configurado para <var>no</var> qualquer atributo de nome "
        "existente é removido se um atributo <code>id</code> existir ou tenha sido "
        "adicionado. "
    },
    { TidyAsciiChars,                                0,        
        "Pode ser usado para modificar o comportamento da opção <code>clean</code> "
        "quando configurado para <var>yes</var>. <br/>Se configurado para "
        "<var>yes</var> ao usar <code>clean</code>, <code>&amp;emdash;</code>, "
        "<code>&amp;rdquo;</code>, e outras entidades de caracteres nomeadas são "
        "rebaixadas para os equivalentes ASCII mais próximos. "
    },
    { TidyBlockTags,                                 0,        
        "Esta opção especifica novas tags de nível de bloco. Esta opção possui uma "
        "lista separada por vírgulas ou espaço de nomes de tags. <br/>A menos que "
        "você declare novas tags, o Tidy se recusará a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Note que você não "
        "pode alterar o modelo de conteúdo para elementos como "
        "<code>&lt;table&gt;</code>, <code>&lt;ul&gt;</code>, <code>&lt;ol&gt;</code> "
        "e <code>&lt;dl&gt;</code>. <br/>Esta opção é ignorada no modo XML. "
    },
    { TidyBodyOnly,                                  0,        
        "Esta opção especifica se o Tidy deve imprimir apenas o conteúdo da tag body "
        "como um fragmento HTML. <br/>Se configurado para <var>auto</var>, isso é "
        "realizado somente se a tag body tiver sido inferida. <br/>Útil para "
        "incorporar páginas inteiras existentes como uma porção de outra página. <br/>"
        "Esta opção não tem efeito se a saída XML for solicitada. "
    },
    { TidyBreakBeforeBR,                             0,        
        "Esta opção especifica se o Tidy deve emitir uma quebra de linha antes de "
        "cada elemento <code>&lt;br&gt;</code>. "
    },
    { TidyCharEncoding,                              0,        
        "Esta opção especifica a codificação de caracteres que o Tidy usa tanto para "
        "a entrada como para a saída. <br/>Para <var>ascii</var>, o Tidy aceitará "
        "valores de caracteres Latin-1 (ISO-8859-1), mas usará entidades para todos "
        "os caracteres cujo valor seja &gt;127. <br/>Para <var>raw</var>, o Tidy "
        "emitirá valores acima de 127 sem traduzi-los em entidades. <br/>Para "
        "<var>latin1</var>, os caracteres acima de 255 serão escritos como entidades. "
        "<br/>Para <var>utf8</var>, Tidy presume que tanto a entrada como a saída são "
        "codificadas como UTF-8. <br/>Você pode usar <var>iso2022</var> para arquivos "
        "codificados usando a família de codificações ISO-2022, p.ex. ISO-2022-JP. "
        "<br/> Para <var>mac</var> e <var>win1252</var>, o Tidy aceitará valores de "
        "caracteres específicos do fornecedor, mas usará entidades para todos os "
        "caracteres cujo valor seja &gt;127. <br/>Para codificações sem suporte, use "
        "um utilitário externo para converter de e para UTF-8. "
    },
    { TidyCoerceEndTags,                             0,        
        "Esta opção especifica se o Tidy deve coagir uma tag de início em uma tag de "
        "fim nos casos em que parece que uma tag de fim provavelmente foi projetada; "
        "por exemplo, dado <br/><code>&lt;span&gt;foo &lt;b&gt;bar&lt;b&gt; "
        "baz&lt;/span&gt;</code>, <br/>Tidy vai emitir <br/><code>&lt;span&gt;foo "
        "&lt;b&gt;bar&lt;/b&gt; baz&lt;/span&gt;</code> "
    },
    { TidyCSSPrefix,                                 0,        
        "Esta opção especifica o prefixo que o Tidy usa para regras de estilo. <br/>Por padrão, <var>c</"
        "var> será usado. "
    },
    { TidyDecorateInferredUL,                        0,        
        "Esta opção especifica se o Tidy deve decorar elementos inferidos "
        "<code>&lt;ul&gt;</code> com algumas marcações CSS para evitar recuo para a "
        "direita. "
    },
    { TidyDoctype,                                   0,        
        "Esta opção especifica a declaração DOCTYPE gerada pelo Tidy. <br/>Se "
        "configurado para <var>omit</var>, a saída não conterá uma declaração "
        "DOCTYPE. Note que isso também implica que <code>numeric-entity</code> esteja "
        "definido para <var>yes</var>. <br/>Se configurado para <var>html5</var>, o "
        "DOCTYPE é configurado para <code>&lt;!DOCTYPE html&gt;</code>. <br/>Se "
        "configurado para <var>auto</var> (o padrão), Tidy usará um palpite educado "
        "com base no conteúdo do documento. <br/>Se configurado para <var>strict</var>"
        ", o Tidy configurará o DOCTYPE para o DTD estrito HTML4 ou XHTML1. <br/>Se "
        "configurado para <var>loose</var>, o DOCTYPE é definido como o DTD loose "
        "(transicional) HTML4 ou XHTML1. <br/>Alternativamente, você pode fornecer "
        "uma string para o identificador público formal (FPI). <br/>Por exemplo: "
        "<br/><code>doctype: \"-//ACME//DTD HTML 3.14159//EN\"</code><br/>Se você "
        "especificar o FPI para um documento XHTML, o Tidy irá definir o "
        "identificador do sistema em uma string vazia. Para um documento HTML, a Tidy "
        "adiciona um identificador de sistema somente se um já estivesse presente "
        "para preservar o modo de processamento de alguns navegadores. Tidy deixa o "
        "DOCTYPE para documentos genéricos XML inalterados. <br/>Esta opção não "
        "oferece uma validação da conformidade do documento. "
    },
    { TidyDropEmptyElems,                            0, "Esta opção especifica se Tidy deve descartar elementos vazios. "                                 },
    { TidyDropEmptyParas,                            0, "Esta opção especifica se Tidy deve descartar parágrafos vazios. "                                },
    { TidyDropPropAttrs,                             0,        
        "Esta opção especifica se o Tidy deve remover os atributos de propriedade, "
        "como os atributos de ligação de dados da Microsoft. Além disso, os atributos "
        "que não são permitidos na versão de saída do HTML serão descartados se "
        "usados com <code>strict-tags-attributes</code>. "
    },
    { TidyDuplicateAttrs,                            0,        
        "Esta opção especifica se o Tidy deve manter o primeiro ou último atributo, "
        "se um atributo estiver repetido, p.ex. possui dois atributos "
        "<code>align</code>. "
    },
    { TidyEmacs,                                     0,        
        "Esta opção especifica se o Tidy deve alterar o formato para relatar erros e "
        "avisos para um formato que é analisado mais facilmente pelo GNU Emacs. "
    },
    { TidyEmptyTags,                                 0,        
        "Esta opção especifica novas tags em-linha vazias. Esta opção possui uma "
        "lista separada por espaço ou vírgulas de nomes de tags. <br/>A menos que "
        "você declare novas tags, o Tidy se recusará a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Lembre-se de declarar "
        "tags vazias como em linha ou bloqueio. <br/>Esta opção é ignorada no modo "
        "XML. "
    },
    { TidyEncloseBlockText,                          0,        
        "Esta opção especifica se Tidy deve inserir um elemento <code>&lt;p&gt;</code>"
        " para incluir qualquer texto que encontre em qualquer elemento que permita o "
        "conteúdo misto para HTML transicional mas não HTML estrito. "
    },
    { TidyEncloseBodyText,                           0,        
        "Esta opção especifica se o Tidy deve incluir qualquer texto encontrado no "
        "elemento do corpo dentro de um elemento <code>&lt;p&gt;</code>. <br/>Isso é "
        "útil quando você deseja usar o HTML existente e usá-lo com uma folha de "
        "estilo. "
    },
    { TidyErrFile,                                   0,        
        "Esta opção especifica o arquivo de erro que o Tidy usa para erros e avisos. "
        "Normalmente, erros e avisos são emitidos para <code>stderr</code>. "
    },
    { TidyEscapeCdata,                               0,        
        "Esta opção especifica se o Tidy deve converter seções "
        "<code>&lt;![CDATA[]]&gt;</code> em texto normal. "
    },
    { TidyEscapeScripts,                             0,        
        "Esta opção faz com que itens que se parecem com tags de fechamento, como <code>&lt;/g</code> "
        "sejam escapadas para <code>&lt;\\/g</code>. Defina esta opção para <var>no</var> se você não "
        "deseja isso."
    },
    { TidyFixBackslash,                              0,        
        "Esta opção especifica se o Tidy deve substituir caracteres de barra "
        "invertida <code>\\</code> em URLs com barras <code>/</code>. "
    },
    { TidyFixComments,                               0,        
        "Esta opção especifica se Tidy deve substituir hífenes inesperados com "
        "caracteres <code>=</code> quando se trata de hífenes adjacentes. <br/>O "
        "padrão é <var>yes</var>. <br/>Esta opção é fornecida para usuários do Cold "
        "Fusion que usam a sintaxe do comentário: <code>&lt;!--- ---&gt;</code>. "
    },
    { TidyFixUri,                                    0,        
        "Esta opção especifica se o Tidy deve verificar valores de atributos que "
        "carregam URIs para caracteres ilegais e, se tal for encontrado, escapa-os "
        "conforme o HTML4 recomenda. "
    },
    { TidyForceOutput,                               0,        
        "Esta opção especifica se o Tidy deve produzir saída, mesmo se forem "
        "encontrados erros. <br/>Use esta opção com cuidado; Se o Tidy relatar um "
        "erro, significa que o Tidy não conseguiu corrigir o erro (ou não sabe como), "
        "então a saída resultante pode não refletir sua intenção. "
    },
    { TidyGDocClean,                                 0,        
        "Esta opção especifica se o Tidy deve habilitar comportamento específico para "
        "limpeza de HTML exportado do Google Docs. "
    },
    { TidyHideComments,                              0, "Esta opção especifica se Tidy deve imprimir os comentários. "                                    },
    { TidyHtmlOut,                                   0,        
        "Esta opção especifica se o Tidy deve gerar uma impressão amigável, "
        "escrevendo como HTML. "
    },
    { TidyInCharEncoding,                            0,        
        "Esta opção especifica a codificação de caracteres que o Tidy usa para a "
        "entrada. Veja <code>char-encoding</code> para mais informações. "
    },
    { TidyIndentAttributes,                          0,        
        "Esta opção especifica se o Tidy deve começar cada atributo em uma nova "
        "linha. "
    },
    { TidyIndentCdata,                               0,        
        "Esta opção especifica se o Tidy deve aplicar recuo nas seções "
        "<code>&lt;![CDATA[]]&gt;</code>. "
    },
    { TidyIndentContent,                             0,        
        "Esta opção especifica se Tidy deve aplicar recuo nas tags de nível de bloco. "
        "<br/>Se configurado para <var>auto</var>, Tidy decidirá se aplica ou não "
        "recuo no conteúdo das tags, como <code>&lt;title&gt;</code>, "
        "<code>&lt;h1&gt;</code>-<code>&lt;h6&gt;</code>, <code>&lt;li&gt;</code>, "
        "<code>&lt;td&gt;</code> ou <code>&lt;p&gt;</code> com base no conteúdo, "
        "incluindo um elemento de nível de bloco. <br/>Configurar <code>indent</code> "
        "para <var>yes</var> pode expor erros de layout em alguns navegadores. <br/>"
        "Use a opção <code>indent-spaces</code> para controlar o número de espaços ou "
        "tabulações de saída por nível de recuo e <code>indent-with-tabs</code> para "
        "especificar se espaços ou tabulações são usados. "
    },
    { TidyIndentSpaces,                              0,        
        "Esta opção especifica o número de espaços ou guias que o Tidy usa para "
        "recuar o conteúdo quando <code>indent</code> está habilitado. <br/>Note que "
        "o valor padrão para esta opção depende do valor de <code>indent-with-"
        "tabs</code> (veja também). "
    },
    { TidyInlineTags,                                0,        
        "Esta opção especifica novas tags em-linha não vazias. Esta opção possui uma "
        "lista separada por espaço ou vírgulas de nomes de tags. <br/>A menos que "
        "você declare novas tags, o Tidy se recusará a gerar um arquivo arrumado se a "
        "entrada incluir tags anteriormente desconhecidas. <br/>Esta opção é ignorada "
        "no modo XML. "
    },
    { TidyJoinClasses,                               0,        
        "Esta opção especifica se o Tidy deve combinar os nomes das classes para "
        "gerar um nome de classe único e novo se várias atribuições de classe forem "
        "detectadas em um elemento. "
    },
    { TidyJoinStyles,                                0,        
        "Esta opção especifica se o Tidy deve combinar os estilos para gerar um "
        "estilo único e novo se vários valores de estilo forem detectados em um "
        "elemento. "
    },
    { TidyKeepFileTimes,                             0,        
        "Esta opção especifica se o Tidy deve manter o tempo de modificação original "
        "dos arquivos que o Tidy modifica no local. <br/>Configurar a opção para "
        "<var>yes</var> permite arrumar arquivos sem alterar a data de modificação do "
        "arquivo, o que pode ser útil com determinadas ferramentas que usam a data de "
        "modificação para coisas como a implantação automática do servidor. <br/>Note "
        "que não há suporte a este recurso em algumas plataformas. "
    },
    { TidyLiteralAttribs,                            0,        
        "Esta opção especifica como o Tidy lida com caracteres de espaço em branco "
        "dentro de valores de atributos. <br/>Se o valor for <var>no</var>, Tidy "
        "normaliza os valores dos atributos substituindo qualquer nova linha ou "
        "tabulação por um único espaço, além de substituir qualquer espaço contíguo "
        "em espaço único. <br/>Para forçar o Tidy a preservar os valores literais "
        "originais de todos os atributos e garantir que os espaços em branco dentro "
        "dos valores de atributo sejam passados inalterados através, defina esta "
        "opção como <var>yes</var>. "
    },
    { TidyLogicalEmphasis,                           0,        
        "Esta opção especifica se o Tidy deve substitui qualquer ocorrência de "
        "<code>&lt;i&gt;</code> com <code>&lt;em&gt;</code> e qualquer ocorrência de "
        "<code>&lt;b&gt;</code> com <code>&lt;strong&gt;</code>. Quaisquer atributos "
        "são preservados inalterados. <br/>Esta opção pode ser definida "
        "independentemente da opção <code>clean</code>. "
    },
    { TidyLowerLiterals,                             0,        
        "Esta opção especifica se o Tidy deve converter o valor de um atributo que "
        "leva uma lista de valores predefinidos para minúsculas. <br/>Isto é "
        "necessário para documentos XHTML. "
    },
    { TidyMakeBare,                                  0,        
        "Esta opção especifica se o Tidy deve retirar o HTML específico da Microsoft "
        "de documentos do Word 2000 e exibir espaços em vez de espaços rígidos (nbsp) "
        "nos quais eles existam na entrada. "
    },
    { TidyMakeClean,                                 0,        
        "Esta opção especifica se o Tidy deve executar a limpeza de algumas tags de "
        "apresentação legadas (atualmente <code>&lt;i&gt;</code>, "
        "<code>&lt;b&gt;</code>, <code>&lt;center&gt;</code> quando incluídas nas "
        "tags em-linha apropriadas e <code>&lt;font&gt;</code>). Se configurado para "
        "<var>yes</var>, as tags legadas serão substituídas por tags CSS "
        "<code>&lt;style&gt;</code> e marcação estrutural conforme apropriado. "
    },
    { TidyMark,                                      0,        
        "Esta opção especifica se o Tidy deve adicionar um elemento <code>meta</code> "
        "ao cabeçalho do documento para indicar que o documento foi arrumado. <br/>"
        "Tidy não adicionará um elemento meta se um já estiver presente. "
    },
    { TidyMergeDivs,                                 0,        
        "Esta opção pode ser usada para modificar o comportamento de "
        "<code>clean</code> quando configurado para <var>yes</var>. <br/>Esta opção "
        "especifica se o Tidy deve mesclar <code>&lt;div&gt;</code> aninhados, como "
        "<code>&lt;div&gt;&lt;div&gt;...&lt;/div&gt;&lt;/div&gt;</code>. <br/>Se "
        "configurado para <var>auto</var>, os atributos do <code>&lt;div&gt;</code> "
        "internos são movidos para o externo. <code>&lt;div&gt;</code> aninhados com "
        "os atributos <code>id</code> <em>não</em> são mesclados. <br/>Se configurado "
        "para <var>yes</var>, os atributos de <code>&lt;div&gt;</code> interno são "
        "descartados com a exceção de <code>class</code> e <code>style</code>. "
    },
    { TidyMergeEmphasis,                             0,        
        "Esta opção especifica se o Tidy deve mesclar elementos <code>&lt;b&gt;</code>"
        " e <code>&lt;i&gt;</code> aninhados; por exemplo, para o caso de "
        "<br/><code>&lt;b class=\"rtop-2\"&gt;foo &lt;b class=\"r2-2\""
        "&gt;bar&lt;/b&gt; baz&lt;/b&gt;</code>, <br/>Tidy vai emitir <code>&lt;b "
        "class=\"rtop-2\"&gt;foo bar baz&lt;/b&gt;</code>. "
    },
    { TidyMergeSpans,                                0,        
        "Esta opção pode ser usada para modificar o comportamento de "
        "<code>clean</code> quando configurado para <var>yes</var>. <br/>Esta opção "
        "especifica se o Tidy deve mesclar <code>&lt;span&gt;</code> aninhados como "
        "<code>&lt;span&gt;&lt;span&gt;...&lt;/span&gt;&lt;/span&gt;</code>. <br/>O "
        "algoritmo é idêntico àquele usado por <code>merge-divs</code>. "
    },
    { TidyNCR,                                       0,        
        "Esta opção especifica se o Tidy deve permitir referências de caracteres "
        "numéricos. "
    },
    { TidyNewline,                                   0,        
        "O padrão é apropriado para a plataforma atual. <br/>Geralmente, CRLF no PC-"
        "DOS, Windows e OS/2; CR no Mac OS Clássico; e LF nos demais (Linux, Mac OS X "
        "e Unix). "
    },
    { TidyNumEntities,                               0,        
        "Esta opção especifica se o Tidy deve produzir entidades diferentes das "
        "entidades HTML integradas (<code>&amp;amp;</code>, <code>&amp;lt;</code>, "
        "<code>&amp;gt;</code> e <code>&amp;quot;</code>) no formulário numérico em "
        "vez do formulário nomeado. <br/>Somente são usadas entidades compatíveis com "
        "a declaração DOCTYPE gerada. <br/>As entidades que podem ser representadas "
        "na codificação de saída são traduzidas correspondentemente. "
    },
    { TidyOmitOptionalTags,                          0,        
        "Esta opção especifica se o Tidy deve omitir tags de início e de fim "
        "opcionais ao gerar saída. <br/>Configurar essa opção causa todas as tags "
        "para os elementos <code>&lt;html&gt;</code>, <code>&lt;head&gt;</code> e "
        "<code>&lt;body&gt;</code> serem omitidos da saída, assim como tags de saída "
        "como <code>&lt;/p&gt;</code>, <code>&lt;/li&gt;</code>, "
        "<code>&lt;/dt&gt;</code>, <code>&lt;/dd&gt;</code>, "
        "<code>&lt;/option&gt;</code>, <code>&lt;/tr&gt;</code>, "
        "<code>&lt;/td&gt;</code> e <code>&lt;/th&gt;</code>. <br/>Essa opção é "
        "ignorada para saída XML. "
    },
    { TidyOutCharEncoding,                           0,        
        "Esta opção especifica a codificação de caracteres que o Tidy usa para a saída. <br/>Note que "
        "isso só pode ser diferente de <code>input-encoding</code> para codificações latinas "
        "(<var>ascii</var>, <var>latin0</var>, <var>latin1</var>, <var>mac</var>, <var>win1252</var>, "
        "<var>ibm858</var>). <br/>Veja <code>char-encoding</code> para mais informações"
    },
    { TidyOutFile,                                   0,        
        "Essa opção especifica o arquivo de saída que o Tidy usa para marcação. "
        "Normalmente, a marcação é escrita para <code>stdout</code>. "
    },
    { TidyOutputBOM,                                 0,        
        "Esta opção especifica se o Tidy deve escrever um caractere Unicode de marca "
        "de ordem de byte (BOM, também conhecido como Zero Width No Break Break, tem "
        "valor de U+FEFF) no início da saída, e aplica-se apenas a codificações de "
        "saída UTF-8 e UTF-16. <br/>Se configurado para <var>auto</var>, esta opção "
        "faz com que Tidy escreva um BOM para a saída somente se um BOM estiver "
        "presente no início da entrada. <br/>Um BOM está sempre escrita para saída "
        "XML/XHTML usando codificações de saída UTF-16. "
    },
    { TidyPPrintTabs,                                0,        
        "Esta opção especifica se o Tidy deve aplicar recuo com tabulações em vez de "
        "espaços, presumindo que <code>indent</code> seja <var>yes</var>. <br/>Defina-"
        "o para <var>yes</var> para recuar usando tabulações em vez dos espaços "
        "padrão. <br/>Use a opção <code>indent-spaces</code> para controlar o número "
        "de saídas de tabulação por nível de recuo. Note que quando <code>indent-with-"
        "tabs</code> está habilitado, o valor padrão de <code>indent-spaces</code> é "
        "reiniciado para <var>1</var>. <br/>Note que <code>tab-size</code> controla a "
        "conversão de tabulações de entrada em espaços. Coloque-o em zero para reter "
        "as tabulações de entrada. "
    },
    { TidyPreserveEntities,                          0,        
        "Esta opção especifica se o Tidy deve preservar entidades bem-formadas como "
        "localizado na entrada. "
    },
    { TidyPreTags,                                   0,        
        "Esta opção especifica novas tags que devem ser processadas exatamente da "
        "mesma forma que o elemento <code>&lt;pre&gt;</code> de HTML. Esta opção "
        "possui uma lista separada por vírgulas ou espaços de nomes de tag. <br/>A "
        "menos que você declare novas tags, o Tidy se recusará a gerar um arquivo "
        "arrumado se a entrada incluir tags anteriormente desconhecidas. <br/>Note "
        "que você ainda não pode adicionar novos elementos CDATA. <br/>Esta opção é "
        "ignorada no modo XML. "
    },
    { TidyPunctWrap,                                 0,        
        "Essa opção especifica se o Tidy deve quebrar linha após alguns Unicode ou "
        "caracteres de pontuação chineses. "
    },
    { TidyQuiet,                                     0,        
        "Essa opção especifica se o Tidy deve emitir o resumo dos números de erros e "
        "avisos, ou as mensagens de boas-vidas ou informacionais. "
    },
    { TidyQuoteAmpersand,                            0,        
        "Essa opção especifica se o Tidy deve emitir caracteres <code>&amp;</code> "
        "sem adornos como <code>&amp;amp;</code>. "
    },
    { TidyQuoteMarks,                                0,        
        "Esta opção especifica se o Tidy deve enviar caracteres <code>&quot;</code> "
        "como <code>&quot;</code> como é preferido por alguns ambientes de edição. "
        "<br/>O caractere do apóstrofe <code>'</code> é escrito como "
        "<code>&amp;#39;</code> porque muitos navegadores web ainda não oferecem "
        "suporte a <code>&amp;apos;</code>. "
    },
    { TidyQuoteNbsp,                                 0,        
        "Esta opção especifica se o Tidy deve produzir caracteres de espaço rígido "
        "como entidades, em vez de como o caractere Unicode de valor 160 (decimal). "
    },
    { TidyReplaceColor,                              0,        
        "Esta opção especifica se o Tidy deve substituir os valores numéricos nos atributos de cor com "
        "nomes de cor HTML/XHTML onde definido, p.ex. substituir <code>#ffffff</code> com <code>white</"
        "code>. "
    },
    { TidyShowErrors,                                0,        
        "Esta opção especifica o número que o Tidy usa para determinar se outros "
        "erros devem ser exibidos. Se configurado para <var>0</var>, nenhum erro será "
        "mostrado. "
    },
    { TidyShowInfo,                                  0,        
        "Esta opção especifica se o Tidy deve exibir mensagens de nível "
        "informacional. "
    },
    { TidyShowMarkup,                                0,        
        "Esta opção especifica se o Tidy deve gerar uma versão de impressão amigável "
        "da marcação. Note que o Tidy não gerará uma versão de impressão amigável se "
        "encontrar erros significativos (veja <code>force-output</code>). "
    },
    { TidyShowWarnings,                              0,        
        "Esta opção especifica se o Tidy deve suprimir avisos. Isso pode ser útil "
        "quando alguns erros estão ocultos em uma agitação de avisos. "
    },
    { TidySkipNested,                                0,        
        "Esta opção especifica que o Tidy deve pular tags aninhadas ao analisar "
        "script e dados de estilo. "
    },
    { TidySortAttributes,                            0,        
        "Esta opção especifica que o Tidy deve ordenar atributos dentro de um "
        "elemento usando o algoritmo de ordenação especificado. Se configurado para "
        "<var>alpha</var>, o algoritmo é uma ordenação alfabética ascendente. "
    },
    { TidyStrictTagsAttr,                            0,        
        "Esta opção garante que tags e atributos sejam aplicáveis à versão do HTML "
        "que o Tidy emite. Quando definido para <var>yes</var> e o tipo de documento "
        "de saída é um doctype estrito, então o Tidy informará os erros. Se o tipo de "
        "documento de saída for um tipo de documento loose ou transicional, o Tidy "
        "informará os avisos. <br/>Além disso, se <code>drop-proprietary-"
        "attributes</code> estiver habilitado, os atributos não aplicáveis também "
        "serão descartados. <br/>Quando configurado para <var>no</var>, essas "
        "verificações não são executadas. "
    },
    { TidyTabSize,                                   0,        
        "Esta opção especifica o número de colunas que o Tidy usa entre paradas de "
        "tabulação sucessivas. Ela é usada para mapear tabulações para espaços ao ler "
        "a entrada. "
    },
    { TidyUpperCaseAttrs,                            0,        
        "Esta opção especifica se o Tidy deve produzir nomes de atributo em "
        "maiúsculo. <br/>Quando configurado para <var>no</var>, os nomes dos "
        "atributos serão escritos em minúsculas. Especificar <var>yes</var> exibirá "
        "nomes de atributos em maiúsculas e <var>preserve</var> pode ser usado para "
        "deixar nomes de atributos intactos. <br/>Ao usar a entrada XML, o "
        "maiusculização original é sempre preservada. "
    },
    { TidyUpperCaseTags,                             0,        
        "Esta opção especifica se o Tidy deve emitir nomes de tags em maiúsculo. <br/>"
        "O padrão é <var>no</var>, o que resulta em nomes de tags minúsculos, exceto "
        "para entrada XML na qual a maiusculização original é preservada. "
    },
    { TidyUseCustomTags,                             0,        
        "Esta opção permite o uso de tags para elementos personalizados autônomos, "
        "p.ex. &lt;flag-icon&gt; com Tidy. As tags personalizadas são desativadas se "
        "esse valor for <var>no</var>. Outras configurações - <var>blocklevel</var>, "
        "<var>empty</var>, <var>inline</var> e <var>pre</var> tratarão <em>todas</em> "
        "as tags personalizadas detectadas em conformidade. <br/>O uso de <code>new-"
        "blocklevel-tags</code>, <code>new-empty-tags</code>, <code>new-inline-"
        "tags</code> ou <code>new-pre-tags</code> substituirá o tratamento de tags "
        "personalizadas por esta opção de configuração. Isso pode ser útil se você "
        "tiver diferentes tipos de tags personalizadas. <br/>Quando habilitado, essas "
        "tags são determinadas durante o processamento do documento usando tags de "
        "abertura; As tags de fechamento de correspondência serão reconhecidas de "
        "acordo, e as tags de fechamento desconhecidas serão descartadas. "
    },
    { TidyVertSpace,                                 0,        
        "Esta opção especifica se o Tidy deve adicionar algumas linhas vazias extras para legibilidade. "
        "<br/>O padrão é <var>no</var>. <br/>Se configurado para <var>auto</var>, Tidy vai eliminar "
        "quase todos os caracteres de nova linha."
    },
    { TidyWarnPropAttrs,                             0, "Essa opção especifica se o Tidy deve avisar sobre atributos proprietários."                      },
    { TidyWord2000,                                  0,        
        "Esta opção especifica se o Tidy deve se esforçar duro para tirar todas as "
        "coisas excedentes que o Microsoft Word 2000 insere quando você salva os "
        "documentos do Word como \"páginas web\". Não manipula imagens embutidas ou "
        "VML. <br/>Você deve considerar usar o Word \"Salvar Como: Página da Web, "
        "Filtrada\". "
    },
    { TidyWrapAsp,                                   0,        
        "Essa opção especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do ASP, que se parecem com: <code>&lt;% ... %&gt;</code>. "
    },
    { TidyWrapAttVals,                               0,        
        "Esta opção especifica se Tidy deve incluir valores de atributos de linha, o "
        "que significa que, se o valor de um atributo faz com que uma linha exceda a "
        "largura especificada por <code>wrap</code>, Tidy irá adicionar uma ou mais "
        "quebras de linha ao valor, fazendo com que ele seja embrulhado em várias "
        "linhas. <br/>Note que esta opção pode ser definida independentemente de <code"
        ">wrap-script-literals</code>. Por padrão, o Tidy substitui qualquer nova "
        "linha ou tabulação com um único espaço e substitui qualquer sequência de "
        "espaços em branco com um único espaço. <br/>Para forçar a Tidy a preservar "
        "os valores literais originais de todos os atributos e garantir que os "
        "caracteres de espaço em branco nos valores de atributos sejam passados "
        "através de alterações, configure <code>literal-attributes</code> para "
        "<var>yes</var>. "
    },
    { TidyWrapJste,                                  0,        
        "Essa opção especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do JSTE, que se parecem com: <code>&lt;# ... #&gt;</code>. "
    },
    { TidyWrapLen,                                   0,        
        "Esta opção especifica a margem direita que o Tidy usa para quebra de linha. "
        "<br/>Tidy tenta quebrar linhas para que não excedam esse comprimento. <br/>"
        "Defina <code>wrap</code> para <var>0</var> (zero) se desejar desativar a "
        "quebra de linha. "
    },
    { TidyWrapPhp,                                   0,        
        "Essa opção especifica se o Tidy deve quebrar linha de textos contidos em "
        "pseudoelementos do PHP, que se parecem com: <code>&lt;?php ... ?&gt;</code>. "
    },
    { TidyWrapScriptlets,                            0,        
        "Esta opção especifica se Tidy deve efetuar quebra de linha em string "
        "literais que aparecem em atributos de script. <br/>Tidy efetua essa quebra "
        "em string literais de scripts longos inserindo um caractere de barra "
        "invertida antes da quebra de linha. "
    },
    { TidyWrapSection,                               0,        
        "Essa opção especifica se o Tidy deve efetuar quebra de linha de textos "
        "contidos em tags de seção <code>&lt;![ ... ]&gt;</code>. "
    },
    { TidyWriteBack,                                 0,        
        "Esta opção especifica se o Tidy deve escrever novamente a marcação arrumada "
        "para o mesmo arquivo que lê. <br/> É aconselhável manter cópias de arquivos "
        "importantes antes de ordená-los, como em ocasiões raras, o resultado pode "
        "não ser o que você espera. "
    },
    { TidyXhtmlOut,                                  0,        
        "Esta opção especifica se o Tidy deve gerar uma impressão amigável, "
        "escrevendo como HTML extensível. <br/>Esta opção faz com que o Tidy "
        "configure o DOCTYPE e o espaço de nomes padrão conforme apropriado para "
        "XHTML e use o valor corrigido no resultado, independentemente de outras "
        "fontes. <br/> Para XHTML, as entidades podem ser escritas como entidades "
        "nomeadas ou numéricas de acordo com a configuração de <code>numeric-"
        "entities</code>. <br/>A maiusculização original de tags e atributos será "
        "preservada, independentemente de outras opções. "
    },
    { TidyXmlDecl,                                   0,        
        "Esta opção especifica se o Tidy deve adicionar a declaração XML ao enviar "
        "XML ou XHTML. <br/>Note que, se a entrada já incluir uma declaração "
        "<code>&lt;?xml ... ?&gt;</code>, esta opção será ignorada. <br/>Se a "
        "codificação para a saída for diferente de <var>ascii</var>, uma das "
        "codificações <var>utf*</var> ou de <var>raw</var>, então a declaração é "
        "sempre adicionado conforme exigido pelo padrão XML. "
    },
    { TidyXmlOut,                                    0,        
        "Esta opção especifica se o Tidy deve emitir impressão amigável, escrevendo-o "
        "como XML bem formado. <br/>Todas as entidades não definidas no XML 1.0 serão "
        "escritas como entidades numéricas para permitir que elas sejam analisadas "
        "por um analisador XML. <br/>A maiusculização original de tags e atributos "
        "será preservada, independentemente de outras opções. "
    },
    { TidyXmlPIs,                                    0,        
        "Esta opção especifica se o Tidy deve alterar a análise das instruções de "
        "processamento para exigir <code>?&gt;</code> como o terminador, em vez de "
        "<code>&gt;</code>. <br/>Esta opção é configurada automaticamente se a "
        "entrada for um XML. "
    },
    { TidyXmlSpace,                                  0,        
        "Esta opção especifica se o Tidy deve adicionar <code>xml:space=\"preserve\"</code> para "
        "elementos tais como <code>&lt;pre&gt;</code>, <code>&lt;style&gt;</code> e <code>&lt;script&gt;"
        "</code> ao gerar o XML. <br/>Isso é necessário se o espaço em branco em tais elementos deve ser "
        "analisado apropriadamente sem ter acesso ao DTD. "
    },
    { TidyXmlTags,                                   0,        
        "Esta opção especifica se o Tidy deve usar o analisador XML em vez do "
        "analisador HTML de correção de erro. "
    },
    { TidyMetaCharset,                               0,        
        "Esta opção, quando ativada, adiciona um elemento <code>&lt;meta&gt;</code> e "
        "define o atributo <code>charset</code> para a codificação do documento. "
        "Configure esta opção para <var>yes</var> para habilitá-lo. "
    },
    { TidyShowMetaChange,                            0,        
        "Esta opção habilita uma mensagem sempre que o Tidy alterar o atributo "
        "<code>content</code> de uma declaração de meta conjunto de caracteres para "
        "coincidir com a codificação do documento. Defina esta opção para "
        "<var>yes</var> para habilitá-lo. "
    },
    { TidyStyleTags,                                 0,        
        "Esta opção especifica se o Tidy deve mover todas as tags de estilo para o "
        "cabeçalho do documento. "
    },
    { TidyWarning,                                   0, "Acesso: "                                                                                        },
    { TidyAccess,                                    0, "Acesso: "                                                                                        },
    { TidyError,                                     0, "Erro: "                                                                                          },
    { TidyBadDocument,                               0, "Documento: "                                                                                     },
    { TidyFatal,                                     0, "Pânico: "                                                                                        },
    { TidyDialogueSummary,                           0, "Resumo: "                                                                                        },
    { TidyDialogueInfo,                              0, "Informação: "                                                                                    },
    { TidyDialogueFootnote,                          0, "Nota de rodapé: "                                                                                },
    { LINE_COLUMN_STRING,                            0, "linha %d coluna %d - "                                                                           },
    { STRING_DISCARDING,                             0, "descartando"                                                                                     },
    { STRING_ERROR_COUNT_ERROR,                      0, "erro"                                                                                            },
    { STRING_ERROR_COUNT_ERROR,                      1, "erros"                                                                                           },
    { STRING_ERROR_COUNT_WARNING,                    0, "aviso"                                                                                           },
    { STRING_ERROR_COUNT_WARNING,                    1, "avisos"                                                                                          },
    { STRING_HELLO_ACCESS,                           0,        
        "\n"
        "Verificações de acessibilidade:\n"
    },
    { STRING_HTML_PROPRIETARY,                       0, "Proprietário HTML"                                                                               },
    { STRING_XML_DECLARATION,                        0, "declaração XML"                                                                                  },
    { STRING_PLAIN_TEXT,                             0, "texto simples"                                                                                   },
    { STRING_REPLACING,                              0, "substituindo"                                                                                    },
    { STRING_SPECIFIED,                              0, "especificada"                                                                                    },
    { TIDYCUSTOMNO_STRING,                           0, "não"                                                                                             },
    { TIDYCUSTOMBLOCKLEVEL_STRING,                   0, "nível de bloco"                                                                                  },
    { TIDYCUSTOMEMPTY_STRING,                        0, "vazio"                                                                                           },
    { TIDYCUSTOMINLINE_STRING,                       0, "em-linha"                                                                                        },
    { TIDYCUSTOMPRE_STRING,                          0, "pré"                                                                                             },
    { TEXT_HTML_T_ALGORITHM,                         0,        
        "\n"
        "      - Primeiro, pesquisa à esquerda da posição da célula para\n"
        "        localizar células de cabeçalho de linha.\n"
        "      - Então, pesquisa para cima para localizar células de cabeçalho\n"
        "        de coluna.\n"
        "      - A pesquisa em uma direção dada interrompe quando a borda da\n"
        "        tabela é atingida ou quando uma célula de dados é localizada\n"
        "        após uma célula de cabeçalho.\n"
        "      - Cabeçalhos de linha são inseridas em uma linha na ordem que\n"
        "        elas aparecem na tabela.\n"
        "      - Para tabelas esquerda-para-direita, cabeçalhos são inseridas\n"
        "        da esquerda para direita.\n"
        "      - Cabeçalhos de coluna são inseridas após cabeçalhos de linha,\n"
        "        na ordem que elas aparecem na tabela, de cima para baixo.\n"
        "      - Se uma célula de cabeçalho tem atributo de cabeçalhos configurado,\n"
        "        então os cabeçalhos referenciados por este atributo são inseridos\n"
        "        na lisa e a pesquisa interrompe para a direção atual.\n"
        "        células TD que configuram o atributo de eixo também são tratadas\n"
        "        com células de cabeçalho.\n"
    },
    { TEXT_VENDOR_CHARS,                             0,        
        "É improvável que as codificações dependentes do sistema específicas\n"
        "do fornecedor funcionem amplamente na World Wide Web; você deve\n"
        "evitar o uso da codificação de caracteres %s; em vez disso,\n"
        "recomenda-se que você use entidades nomeadas, p.ex. &trade;.\n"
    },
    { TEXT_SGML_CHARS,                               0,        
        "Os códigos de caracteres 128 a 159 (U+0080 a U+009F)\n"
        "não são aceitos no HTML; mesmo se eles fossem, eles\n"
        "provavelmente seriam caracteres de controle não imprimíveis.\n"
        "Tidy presumiu que você queria se referir a um caractere\n"
        "com o mesmo valor de bytes na codificação %s e substituiu\n"
        "aquela referência com o equivalente Unicode.\n"
    },
    { TEXT_INVALID_UTF8,                             0,        
        "Os códigos de caracteres para UTF-8 devem estar dentro\n"
        "do intervalo: U+0000 a U+10FFFF. A definição de UTF-8\n"
        "no Anexo D do ISO/IEC 10646-1:2000 também permite para\n"
        "o uso de sequências de cinco e seis bytes para codificar\n"
        "caracteres que estão fora do intervalo do conjunto de\n"
        "caracteres do Unicode; aquelas sequências de cinco e\n"
        "seis bytes são ilegais para o uso de UTF-8 como uma\n"
        "transformação de caracteres Unicode. ISO/IEC 10646 não\n"
        "permite mapeamento de substitutos não pareados, nem\n"
        "U+FFFE e U+FFFF (mas permite outros não caracteres).\n"
        "Para mais informações, veja http://www.unicode.org/ e\n"
        "http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_UTF16,                            0,        
        "Os códigos de caracteres para UTF-16 devem estar dentro\n"
        "do intervalo: U+0000 a U+10FFFF. A definição de UTF-16\n"
        "no Anexo C da ISO/IEC 10646-1:2000 não permite o mapeamento\n"
        "de substitutos não pareados. Para mais informações,\n"
        "por favor veja http://www.unicode.org/ e\n"
        "http://www.cl.cam.ac.uk/~mgk25/unicode.html\n"
    },
    { TEXT_INVALID_URI,                              0,        
        "URIs devem ser devidamente escapadas, elas não devem\n"
        "conter caracteres não elaborados abaixo de U+0021,\n"
        "incluindo o caractere de espaço e não acima de U+007E.\n"
        "Tidy escapa a URI para você conforme recomendado pelo\n"
        "HTML 4.01 seção B.2.1 e XML 1.0 seção 4.2.2. Alguns\n"
        "agentes de usuários usam outro algoritmo para escapar\n"
        "tais URIs e alguns scripts de servidor dependem disso.\n"
        "Se você quiser depender disso, você deve escapar a URI\n"
        "por conta própria. Para mais informações, consulte\n"
        "http://www.w3.org/International/O-URL-and-ident.html\n"
    },
    { TEXT_BAD_FORM,                                 0,        
        "Talvez seja necessário mover uma ou ambas as tags <form>\n"
        "e </form>. Os elementos HTML devem estar adequadamente\n"
        "aninhados e os elementos de formulário não são uma exceção.\n"
        "Por exemplo, você não deve colocar o <form> em uma célula\n"
        "de tabela e </form> em outra. Se o <form> for colocado\n"
        "antes de uma tabela, o </form> não pode ser colocado dentro\n"
        "da tabela! Note que um formulário não pode ser aninhado\n"
        "dentro de outro!\n"
    },
    { TEXT_BAD_MAIN,                                 0,        
        "Apenas um elemento <main> é permitido em um documento.\n"
        "Elementos <main> subsequentes foram descartados, o que\n"
        "pode tornar o documento inválido.\n"
    },
    { TEXT_M_SUMMARY,                                0,        
        "O atributo de resumo da tabela deve ser usado para\n"
        "descrever a estrutura da tabela. É muito útil para\n"
        "pessoas que usam navegadores não visuais. Os atributos\n"
        "de escopo e cabeçalho para células de tabela são\n"
        "úteis para especificar quais cabeçalhos se aplicam\n"
        "a cada célula de tabela, permitindo que navegadores\n"
        "não visuais forneçam um contexto significativo para\n"
        "cada célula.\n"
    },
    { TEXT_M_IMAGE_ALT,                              0,        
        "O atributo alt deve ser usado para dar uma breve descrição\n"
        "de uma imagem; descrições mais longas devem ser fornecidas\n"
        "com o atributo longdesc que leva uma URL vinculada à\n"
        "descrição. Essas medidas são necessárias para pessoas que\n"
        "usam navegadores não-gráficos.\n"
    },
    { TEXT_M_IMAGE_MAP,                              0,        
        "Use os mapas de imagens do lado do cliente de preferência\n"
        "aos mapas de imagens do lado do servidor, pois estes são\n"
        "inacessíveis para pessoas que usam navegadores não gráficos.\n"
        "Além disso, os mapas do lado do cliente são mais fáceis\n"
        "de configurar e fornecer feedback imediato aos usuários.\n"
    },
    { TEXT_M_LINK_ALT,                               0,        
        "Para links de hipertexto definidos usando um mapa de imagem\n"
        "do lado do cliente, você precisa usar o atributo alt para\n"
        "fornecer uma descrição textual do link para pessoas que usam\n"
        "navegadores não gráficos.\n"
    },
    { TEXT_USING_FRAMES,                             0,        
        "Páginas desenhadas usando quadros apresentam problemas\n"
        "para pessoas que são cegas ou que usam um navegador que\n"
        "não oferece suporte a quadros. Uma página baseada em\n"
        "quadros deve sempre incluir um layout alternativo dentro\n"
        "de um elemento NOFRAMES.\n"
    },
    { TEXT_ACCESS_ADVICE1,                           0,        
        "Para mais conselhos sobre como tornar suas páginas\n"
        "acessíveis, veja http://www.w3.org/WAI/GL."
    },
    { TEXT_ACCESS_ADVICE2,                           0,        
        "Para mais conselhos sobre como tornar suas páginas\n"
        "acessíveis, veja http://www.w3.org/WAI/GL e\n"
        "http://www.html-tidy.org/accessibility/."
    },
    { TEXT_USING_LAYER,                              0,        
        "O mecanismo de posicionamento do Cascading Style\n"
        "Sheets (CSS) é recomendado em preferência ao\n"
        "elemento proprietário <LAYER> devido ao suporte\n"
        "de fornecedor limitado a LAYER.\n"
    },
    { TEXT_USING_SPACER,                             0,        
        "É recomendável usar CSS para controlar o espaço em\n"
        "branco (p.ex., para recuo, margens e espaçamento\n"
        "entre linhas). O elemento proprietário <SPACER>\n"
        "possui suporte limitado para fornecedores.\n"
    },
    { TEXT_USING_FONT,                               0,        
        "É recomendável usar o CSS para especificar a fonte e\n"
        "as propriedades, como seu tamanho e cor. Isso reduzirá\n"
        "o tamanho dos arquivos HTML e facilitando a manutenção\n"
        "em comparação com o uso de elementos <FONT>.\n"
    },
    { TEXT_USING_NOBR,                               0,        
        "É recomendável usar CSS para controlar a quebra de linha.\n"
        "Use \"white-space: nowrap\" para inibir a quebra em vez\n"
        "de inserir <NOBR>...</NOBR> na marcação.\n"
    },
    { TEXT_USING_BODY,                               0, "É recomendável usar CSS para especificar cores de página e link"                                 },
    { STRING_CONTENT_LOOKS,                          0, "O conteúdo do documento se parece com %s"                                                        },
    { STRING_DOCTYPE_GIVEN,                          0, "Doctype dado é \"%s\""                                                                           },
    { STRING_ERROR_COUNT,                            0, "Tidy encontrou %u %s e %u %s!\n"                                                                 },
    { STRING_NEEDS_INTERVENTION,                     0,        
        "Esse documento possui erros que devem ser corrigidos\n"
        "antes de usar HTML Tidy para gerar uma versão arrumada.\n"
    },
    { STRING_NO_ERRORS,                              0, "Nenhum aviso ou erro foi localizado.\n"                                                          },
    { STRING_NO_SYSID,                               0, "Nenhum identificado de sistema no doctype emitido"                                               },
    { STRING_NOT_ALL_SHOWN,                          0, "Tidy encontrou %u %s e %u %s! Nem todos avisos/erros foram mostrados.\n"                         },
    { TEXT_GENERAL_INFO,                             0,        
        "Sobre o HTML Tidy: https://github.com/htacg/tidy-html5\n"
        "Relatórios de erro e comentários: https://github.com/htacg/tidy-html5/"
        "issues\n"
        "Lista de discussão: https://lists.w3.org/Archives/Public/public-htacg/\n"
        "Especificação HTML mais recente: http://dev.w3.org/html5/spec-author-view/\n"
        "Valide seus documentos HTML: http://validator.w3.org/nu/\n"
        "Incentive sua empresa a se juntar à W3C: http://www.w3.org/Consortium\n"
    },
    { TEXT_GENERAL_INFO_PLEA,                        0,        
        "Você fala um idioma diferente do português brasileiro, ou uma variante \n"
        "diferente do português? Considere em ajudar a traduzir o HTML Tidy. \n"
        "Para mais detalhes, por favor veja: \n"
        "https://github.com/htacg/tidy-html5/blob/master/README/LOCALIZE.md"
    },
    { ADDED_MISSING_CHARSET,                         0, "Adicionado o <meta charset=...> apropriado em falta ao %s"                                       },
    { ANCHOR_NOT_UNIQUE,                             0, "âncora de %s \"%s\" já está definido"                                                            },
    { APOS_UNDEFINED,                                0, "a entidade declarada &apos; só definida em XML/XHTML"                                            },
    { ATTR_VALUE_NOT_LCASE,                          0, "valor do atributo de %s \"%s\" deve ser minúsculo para XHTML"                                    },
    { ATTRIBUTE_IS_NOT_ALLOWED,                      0, "atributo de %s \"is\" não permitido para tags personalizadas autônomas."                         },
    { ATTRIBUTE_VALUE_REPLACED,                      0, "atributo %s \"%s\", valor incorreto \"%s\" substituído"                                          },
    { BACKSLASH_IN_URI,                              0, "referência da URI %s contém barra invertida. Erro de escrita?"                                   },
    { BAD_ATTRIBUTE_VALUE_REPLACED,                  0, "atributo %s \"%s\" tinha valor inválido \"%s\" e foi substituído"                                },
    { BAD_ATTRIBUTE_VALUE,                           0, "atributo %s \"%s\" possui valor inválido \"%s\""                                                 },
    { BAD_CDATA_CONTENT,                             0, "'<' + '/' + letra não permitido aqui"                                                            },
    { BAD_SUMMARY_HTML5,                             0, "O atributo de resumo no elemento %s é obsoleto no HTML5"                                         },
    { BAD_SURROGATE_LEAD,                            0,        
        "Par substituto ao final (baixo) U+%04X, com nenhuma entidade precedente "
        "(Alta), substituído por U+FFFD."
    },
    { BAD_SURROGATE_PAIR,                            0,        
        "Possui par substituto U+%04X:U+%04X fora do intervalo, substituído pelo "
        "valor U+FFFD."
    },
    { BAD_SURROGATE_TAIL,                            0,        
        "Par substituto precedente (alto) U+%04X, com nenhuma entidade ao final "
        "(Baixo), substituído por U+FFFD."
    },
    { CANT_BE_NESTED,                                0, "%s não pode ser aninhado"                                                                        },
    { COERCE_TO_ENDTAG,                              0, "<%s> provavelmente deveria ser </%s>"                                                            },
    { CONTENT_AFTER_BODY,                            0, "o conteúdo ocorre após o fim do corpo"                                                           },
    { CUSTOM_TAG_DETECTED,                           0, "tag personalizada autônoma %s detectada; será tratada como %s"                                   },
    { DISCARDING_UNEXPECTED,                         0, "descartando %s inesperado"                                                                       },
    { DOCTYPE_AFTER_TAGS,                            0, "<!DOCTYPE> não é permitido após elementos"                                                       },
    { DUPLICATE_FRAMESET,                            0, "elemento FRAMESET repetido"                                                                      },
    { ELEMENT_NOT_EMPTY,                             0, "%s elemento não vazio ou não fechado"                                                            },
    { ELEMENT_VERS_MISMATCH_ERROR,                   0, "%s elemento não disponível na %s"                                                                },
    { ELEMENT_VERS_MISMATCH_WARN,                    0, "%s elemento não disponível na %s"                                                                },
    { ENCODING_MISMATCH,                             0,        
        "a codificação de entrada especificada (%s) não corresponde à codificação de "
        "entrada atual (%s)"
    },
    { ESCAPED_ILLEGAL_URI,                           0, "%s escapando referência de URI malformada"                                                       },
    { FILE_CANT_OPEN,                                0, "Não foi possível abrir \"%s\"\n"                                                                 },
    { FILE_CANT_OPEN_CFG,                            0, "Não foi possível abrir o arquivo de configuração \"%s\"\n"                                       },
    { FILE_NOT_FILE,                                 0, "\"%s\" não é um arquivo!\n"                                                                      },
    { FIXED_BACKSLASH,                               0, "%s convertendo barra invertida em URI para barra"                                                },
    { FOUND_STYLE_IN_BODY,                           0, "encontrada tag <style> em <body>! fix-style-tags: yes para mover."                               },
    { ID_NAME_MISMATCH,                              0, "%s valores dos atributos id e name incompatíveis"                                                },
    { ILLEGAL_NESTING,                               0, "%s não devem ser aninhados"                                                                      },
    { ILLEGAL_URI_CODEPOINT,                         0, "%s caracteres ilegais localizados na URI"                                                        },
    { ILLEGAL_URI_REFERENCE,                         0, "referência de URI %s inadequadamente escapada"                                                   },
    { INSERTING_AUTO_ATTRIBUTE,                      0, "%s inserindo atributo \"%s\" usando valor \"%s\""                                                },
    { INSERTING_TAG,                                 0, "inserindo <%s> implícita"                                                                        },
    { INVALID_ATTRIBUTE,                             0, "nome do atributo de %s \"%s\" (valor=\"%s\") é inválido"                                         },
    { INVALID_NCR,                                   0, "%s referência de caractere numérico %s"                                                          },
    { INVALID_SGML_CHARS,                            0, "%s código de caracteres inválido %s"                                                             },
    { INVALID_UTF8,                                  0, "%s bytes de UTF-8 inválido (código de caracteres %s)"                                            },
    { INVALID_UTF16,                                 0, "%s par de substituto de UTF-16 inválido (código de caracteres %s)"                               },
    { INVALID_XML_ID,                                0, "%s não pôde copiar atributo de nome para id"                                                     },
    { JOINING_ATTRIBUTE,                             0, "%s juntando valores de atributo repetido \"%s\""                                                 },
    { MALFORMED_COMMENT,                             0, "hífenes adjacentes dentro de comentário"                                                         },
    { MALFORMED_DOCTYPE,                             0, "descartando <!DOCTYPE> malformado"                                                               },
    { MISMATCHED_ATTRIBUTE_ERROR,                    0, "atributo de %s \"%s\" não permitido para %s"                                                     },
    { MISMATCHED_ATTRIBUTE_WARN,                     0, "atributo de %s \"%s\" não permitido para %s"                                                     },
    { MISSING_ATTR_VALUE,                            0, "atributo de %s \"%s\" carece de valor"                                                           },
    { MISSING_ATTRIBUTE,                             0, "%s carece de atributo \"%s\""                                                                    },
    { MISSING_DOCTYPE,                               0, "faltando declaração <!DOCTYPE>"                                                                  },
    { MISSING_ENDTAG_BEFORE,                         0, "faltando </%s> antes de %s"                                                                      },
    { MISSING_ENDTAG_FOR,                            0, "faltando </%s>"                                                                                  },
    { MISSING_IMAGEMAP,                              0, "%s deve usar mapa de imagem no lado de cliente"                                                  },
    { MISSING_QUOTEMARK,                             0, "atributo de %s faltando aspas ao final"                                                          },
    { MISSING_SEMICOLON_NCR,                         0, "referência de caractere numérico \"%s\" não termina em ';'"                                      },
    { MISSING_SEMICOLON,                             0, "entidade \"%s\" não termina em ';'"                                                              },
    { MISSING_STARTTAG,                              0, "faltando <%s>"                                                                                   },
    { MISSING_TITLE_ELEMENT,                         0, "inserindo elemento faltante 'title'"                                                             },
    { MOVED_STYLE_TO_HEAD,                           0, "tag <style> movida para <head>! fix-style-tags: no para evitar."                                 },
    { NESTED_EMPHASIS,                               0, "ênfase aninhada %s"                                                                              },
    { NESTED_QUOTATION,                              0, "elementos q aninhados, possível erro de escrita."                                                },
    { NEWLINE_IN_URI,                                0, "%s descartando nova linha na referência de URI"                                                  },
    { NOFRAMES_CONTENT,                              0, "%s não dentre de elemento 'noframes'"                                                            },
    { NON_MATCHING_ENDTAG,                           0, "substituindo %s inesperada por </%s>"                                                            },
    { OBSOLETE_ELEMENT,                              0, "substituindo elemento obsoleto %s por %s"                                                        },
    { PREVIOUS_LOCATION,                             0, "<%s> anteriormente mencionada"                                                                   },
    { PROPRIETARY_ATTR_VALUE,                        0, "atributo proprietário %s com valor \"%s\""                                                       },
    { PROPRIETARY_ATTRIBUTE,                         0, "atributo proprietário %s \"%s\""                                                                 },
    { PROPRIETARY_ELEMENT,                           0, "%s não é aprovado pela W3C"                                                                      },
    { REMOVED_HTML5,                                 0, "elemento %s removido do HTML5"                                                                   },
    { REPEATED_ATTRIBUTE,                            0, "%s descartando valor \"%s\" para atributo repetido \"%s\""                                       },
    { REPLACING_ELEMENT,                             0, "substituindo %s por %s"                                                                          },
    { REPLACING_UNEX_ELEMENT,                        0, "substituindo %s inesperada por %s"                                                               },
    { SPACE_PRECEDING_XMLDECL,                       0, "removendo espaço em branco precedendo a declaração XML"                                          },
    { STRING_MISSING_MALFORMED,                      0, "argumento faltando ou malformado para opção: %s"                                                 },
    { STRING_UNKNOWN_OPTION,                         0, "opção desconhecida: %s"                                                                          },
    { SUSPECTED_MISSING_QUOTE,                       0, "faltando aspas para o valor de atributo"                                                         },
    { TAG_NOT_ALLOWED_IN,                            0, "%s não é permitido em elementos <%s>"                                                            },
    { TOO_MANY_ELEMENTS_IN,                          0, "número excessivo de elementos %s em <%s>"                                                        },
    { TOO_MANY_ELEMENTS,                             0, "número excessivo de elementos %s"                                                                },
    { TRIM_EMPTY_ELEMENT,                            0, "aparando %s vazio"                                                                               },
    { UNESCAPED_AMPERSAND,                           0, "& não escapado que deve ser escrito como &amp;"                                                  },
    { UNEXPECTED_END_OF_FILE_ATTR,                   0, "%s fim de arquivo enquanto analisava atributos"                                                  },
    { UNEXPECTED_END_OF_FILE,                        0, "fim do arquivo %s inesperado"                                                                    },
    { UNEXPECTED_ENDTAG_ERR,                         0, "</%s> inesperada"                                                                                },
    { UNEXPECTED_ENDTAG_IN,                          0, "</%s> inesperada em <%s>"                                                                        },
    { UNEXPECTED_ENDTAG,                             0, "</%s> inesperada"                                                                                },
    { UNEXPECTED_EQUALSIGN,                          0, "%s inesperado '=', esperava nome de atributo"                                                    },
    { UNEXPECTED_GT,                                 0, "%s carece de '>' para o fim da tag"                                                              },
    { UNEXPECTED_QUOTEMARK,                          0, "%s aspas inesperadas ou duplicadas"                                                              },
    { UNKNOWN_ELEMENT_LOOKS_CUSTOM,                  0, "%s não é reconhecido! Você queria habilitar a opção custom-tags?"                                },
    { UNKNOWN_ELEMENT,                               0, "%s não é reconhecido!"                                                                           },
    { UNKNOWN_ENTITY,                                0, "& não escapado ou entidade desconhecida \"%s\""                                                  },
    { USING_BR_INPLACE_OF,                           0, "usando <br> no lugar de %s"                                                                      },
    { VENDOR_SPECIFIC_CHARS,                         0, "%s código de caractere inválido %s"                                                              },
    { WHITE_IN_URI,                                  0, "%s descartando espaço em branco na referência de URI"                                            },
    { XML_DECLARATION_DETECTED,                      0, "Uma declaração XML foi detectada. Você queria usar input-xml?"                                   },
    { XML_ID_SYNTAX,                                 0, "%s ID \"%s\" usa sintaxe de ID de XML"                                                           },
    { IMG_MISSING_ALT,                               0, "[1.1.1.1]: <img> carece de texto 'alt'."                                                         },
    { IMG_ALT_SUSPICIOUS_FILENAME,                   0, "[1.1.1.2]: texto 'alt' suspeito (nome de arquivo)."                                              },
    { IMG_ALT_SUSPICIOUS_FILE_SIZE,                  0, "[1.1.1.3]: texto 'alt' suspeito (tamanho de arquivo)."                                           },
    { IMG_ALT_SUSPICIOUS_PLACEHOLDER,                0, "[1.1.1.4]: texto 'alt' suspeito (espaço reservado)."                                             },
    { IMG_ALT_SUSPICIOUS_TOO_LONG,                   0, "[1.1.1.10]: texto 'alt' suspeito (longo demais)."                                                },
    { IMG_MISSING_LONGDESC_DLINK,                    0, "[1.1.2.1]: <img> carece de 'longdesc' e d-link."                                                 },
    { IMG_MISSING_DLINK,                             0, "[1.1.2.2]: <img> carece de d-link."                                                              },
    { IMG_MISSING_LONGDESC,                          0, "[1.1.2.3]: <img> carece de 'longdesc'."                                                          },
    { IMG_BUTTON_MISSING_ALT,                        0, "[1.1.3.1]: <img> (botão) carece de texto 'alt'."                                                 },
    { APPLET_MISSING_ALT,                            0, "[1.1.4.1]: <applet> carece de conteúdo alternativo."                                             },
    { OBJECT_MISSING_ALT,                            0, "[1.1.5.1]: <object> carece de conteúdo alternativo."                                             },
    { AUDIO_MISSING_TEXT_WAV,                        0, "[1.1.6.1]: áudio carece de transcrição de texto (wav)."                                          },
    { AUDIO_MISSING_TEXT_AU,                         0, "[1.1.6.2]: áudio carece de transcrição de texto (au)."                                           },
    { AUDIO_MISSING_TEXT_AIFF,                       0, "[1.1.6.3]: áudio carece de transcrição de texto (aiff)."                                         },
    { AUDIO_MISSING_TEXT_SND,                        0, "[1.1.6.4]: áudio carece de transcrição de texto (snd)."                                          },
    { AUDIO_MISSING_TEXT_RA,                         0, "[1.1.6.5]: áudio carece de transcrição de texto (ra)."                                           },
    { AUDIO_MISSING_TEXT_RM,                         0, "[1.1.6.6]: áudio carece de transcrição de texto (rm)."                                           },
    { FRAME_MISSING_LONGDESC,                        0, "[1.1.8.1]: <frame> pode exigir 'longdesc'."                                                      },
    { AREA_MISSING_ALT,                              0, "[1.1.9.1]: <area> carece de texto 'alt'."                                                        },
    { SCRIPT_MISSING_NOSCRIPT,                       0, "[1.1.10.1]: <script> carece de seção <noscript>."                                                },
    { ASCII_REQUIRES_DESCRIPTION,                    0, "[1.1.12.1]: arte em ascii exige descrição."                                                      },
    { IMG_MAP_SERVER_REQUIRES_TEXT_LINKS,            0, "[1.2.1.1]: mapa de imagem (lado do servidor) exige links de texto."                              },
    { MULTIMEDIA_REQUIRES_TEXT,                      0, "[1.4.1.1]: multimídia exibe equivalentes de texto sincronizado."                                 },
    { IMG_MAP_CLIENT_MISSING_TEXT_LINKS,             0, "[1.5.1.1]: mapa da imagem (lado do cliente) carece de links de texto."                           },
    { INFORMATION_NOT_CONVEYED_IMAGE,                0, "[2.1.1.1]: certificar de que as informações não sejam transmitidas apenas por cores (imagem)."   },
    { INFORMATION_NOT_CONVEYED_APPLET,               0, "[2.1.1.2]: certificar de que as informações não sejam transmitidas apenas por cores (applet)."   },
    { INFORMATION_NOT_CONVEYED_OBJECT,               0, "[2.1.1.3]: certificar de que as informações não sejam transmitidas apenas por cores (objeto)."   },
    { INFORMATION_NOT_CONVEYED_SCRIPT,               0, "[2.1.1.4]: certificar de que as informações não sejam transmitidas apenas por cores (script)."   },
    { INFORMATION_NOT_CONVEYED_INPUT,                0,        
        "[2.1.1.5]: certificar de que as informações não sejam transmitidas apenas por cores "
        "(entrada)."
    },
    { COLOR_CONTRAST_TEXT,                           0, "[2.2.1.1]: contraste de cores ruim (texto)."                                                     },
    { COLOR_CONTRAST_LINK,                           0, "[2.2.1.2]: contraste de cores ruim (link)."                                                      },
    { COLOR_CONTRAST_ACTIVE_LINK,                    0, "[2.2.1.3]: contraste de cores ruim (link ativo)."                                                },
    { COLOR_CONTRAST_VISITED_LINK,                   0, "[2.2.1.4]: contraste de cores ruim (link visitado)."                                             },
    { DOCTYPE_MISSING,                               0, "[3.2.1.1]: faltando <doctype>."                                                                  },
    { STYLE_SHEET_CONTROL_PRESENTATION,              0, "[3.3.1.1]: use folhas de estilo para controlar apresentação."                                    },
    { HEADERS_IMPROPERLY_NESTED,                     0, "[3.5.1.1]: cabeçalhos aninhados incorretamente."                                                 },
    { POTENTIAL_HEADER_BOLD,                         0, "[3.5.2.1]: cabeçalho potencial (negrito)."                                                       },
    { POTENTIAL_HEADER_ITALICS,                      0, "[3.5.2.2]: cabeçalho potencial (itálico)."                                                       },
    { POTENTIAL_HEADER_UNDERLINE,                    0, "[3.5.2.3]: cabeçalho potencial (sublinhado)."                                                    },
    { HEADER_USED_FORMAT_TEXT,                       0, "[3.5.3.1]: cabeçalho usado para formatar o texto."                                               },
    { LIST_USAGE_INVALID_UL,                         0, "[3.6.1.1]: uso de lista inválido <ul>."                                                          },
    { LIST_USAGE_INVALID_OL,                         0, "[3.6.1.2]: uso de lista inválido <ol>."                                                          },
    { LIST_USAGE_INVALID_LI,                         0, "[3.6.1.4]: uso de lista inválido <li>."                                                          },
    { LANGUAGE_NOT_IDENTIFIED,                       0, "[4.3.1.1]: idioma não identificado."                                                             },
    { LANGUAGE_INVALID,                              0, "[4.3.1.2]: atributo de idioma inválido."                                                         },
    { DATA_TABLE_MISSING_HEADERS,                    0, "[5.1.2.1]: <table> de dados carece de cabeçalhos de linha/coluna (todos)."                       },
    { DATA_TABLE_MISSING_HEADERS_COLUMN,             0, "[5.1.2.2]: <table> de dados carece de cabeçalhos de linha/coluna (1 col)."                       },
    { DATA_TABLE_MISSING_HEADERS_ROW,                0, "[5.1.2.3]: <table> de dados carece de cabeçalhos de linha/coluna (1 lin)."                       },
    { DATA_TABLE_REQUIRE_MARKUP_COLUMN_HEADERS,      0, "[5.2.1.1]: <table> pode exigir marcação (cabeçalhos de coluna)."                                 },
    { DATA_TABLE_REQUIRE_MARKUP_ROW_HEADERS,         0, "[5.2.1.2]: <table> pode exigir marcação (cabeçalhos de linha)."                                  },
    { LAYOUT_TABLES_LINEARIZE_PROPERLY,              0, "[5.3.1.1]: verifique se tabelas de layout linearizaram corretamente."                            },
    { LAYOUT_TABLE_INVALID_MARKUP,                   0, "[5.4.1.1]: marcação inválida usada em <table> de layout."                                        },
    { TABLE_MISSING_SUMMARY,                         0, "[5.5.1.1]: <table> carece de sumário."                                                           },
    { TABLE_SUMMARY_INVALID_NULL,                    0, "[5.5.1.2]: resumo da <table> inválido (nulo)."                                                   },
    { TABLE_SUMMARY_INVALID_SPACES,                  0, "[5.5.1.3]: resumo da <table> inválido (espaços)."                                                },
    { TABLE_SUMMARY_INVALID_PLACEHOLDER,             0, "[5.5.1.6]: resumo da <table> inválido (texto de espaço reservado)."                              },
    { TABLE_MISSING_CAPTION,                         0, "[5.5.2.1]: <table> carece de <caption>."                                                         },
    { TABLE_MAY_REQUIRE_HEADER_ABBR,                 0, "[5.6.1.1]: <table> pode exigir abreviações de cabeçalho."                                        },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_NULL,            0, "[5.6.1.2]: abreviações de cabeçalho de <table> inválidas (nula)."                                },
    { TABLE_MAY_REQUIRE_HEADER_ABBR_SPACES,          0, "[5.6.1.3]: abreviações de cabeçalho de <table> inválidas (espaços)."                             },
    { STYLESHEETS_REQUIRE_TESTING_LINK,              0, "[6.1.1.1]: folhas de estilo exigem teste (link)."                                                },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ELEMENT,     0, "[6.1.1.2]: folhas de estilo exigem teste (elemento de estilo)."                                  },
    { STYLESHEETS_REQUIRE_TESTING_STYLE_ATTR,        0, "[6.1.1.3]: folhas de estilo exigem teste (atributo de estilo)."                                  },
    { FRAME_SRC_INVALID,                             0, "[6.2.1.1]: fonte de <frame> inválida."                                                           },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_APPLET,      0, "[6.2.2.1]: equivalentes de texto exigem atualização (applet)."                                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_SCRIPT,      0, "[6.2.2.2]: equivalentes de texto exigem atualização (script)."                                   },
    { TEXT_EQUIVALENTS_REQUIRE_UPDATING_OBJECT,      0, "[6.2.2.3]: equivalentes de texto exigem atualização (object)."                                   },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_SCRIPT,   0, "[6.3.1.1]: objetos programáticos exigem teste (script)."                                         },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_OBJECT,   0, "[6.3.1.2]: objetos programáticos exigem teste (object)."                                         },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_EMBED,    0, "[6.3.1.3]: objetos programáticos exigem teste (embed)."                                          },
    { PROGRAMMATIC_OBJECTS_REQUIRE_TESTING_APPLET,   0, "[6.3.1.4]: objetos programáticos exigem teste (applet)."                                         },
    { FRAME_MISSING_NOFRAMES,                        0, "[6.5.1.1]: <frameset> carece de seção <noframes>."                                               },
    { NOFRAMES_INVALID_NO_VALUE,                     0, "[6.5.1.2]: seção <noframes> inválida (sem valor)."                                               },
    { NOFRAMES_INVALID_CONTENT,                      0, "[6.5.1.3]: seção <noframes> inválida (conteúdo)."                                                },
    { NOFRAMES_INVALID_LINK,                         0, "[6.5.1.4]: seção <noframes> inválida (link)."                                                    },
    { REMOVE_FLICKER_SCRIPT,                         0, "[7.1.1.1]: remoção de cintilação (script)."                                                      },
    { REMOVE_FLICKER_OBJECT,                         0, "[7.1.1.2]: remoção de cintilação (object)."                                                      },
    { REMOVE_FLICKER_EMBED,                          0, "[7.1.1.3]: remoção de cintilação (embed)."                                                       },
    { REMOVE_FLICKER_APPLET,                         0, "[7.1.1.4]: remoção de cintilação (applet)."                                                      },
    { REMOVE_FLICKER_ANIMATED_GIF,                   0, "[7.1.1.5]: remoção de cintilação (gif animado)."                                                 },
    { REMOVE_BLINK_MARQUEE,                          0, "[7.2.1.1]: remoção de blink/marquee."                                                            },
    { REMOVE_AUTO_REFRESH,                           0, "[7.4.1.1]: remoção de autorrenovação."                                                           },
    { REMOVE_AUTO_REDIRECT,                          0, "[7.5.1.1]: remoção de autorredirecionamento."                                                    },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_SCRIPT, 0, "[8.1.1.1]: certifique-se que objetos programáticos sejam acessíveis (script)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_OBJECT, 0, "[8.1.1.2]: certifique-se que objetos programáticos sejam acessíveis (object)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_APPLET, 0, "[8.1.1.3]: certifique-se que objetos programáticos sejam acessíveis (applet)."                   },
    { ENSURE_PROGRAMMATIC_OBJECTS_ACCESSIBLE_EMBED,  0, "[8.1.1.43]: certifique-se que objetos programáticos sejam acessíveis (embed)."                   },
    { IMAGE_MAP_SERVER_SIDE_REQUIRES_CONVERSION,     0, "[9.1.1.1]: mapa de imagem (lado do servidor) exige conversão."                                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_DOWN,  0, "[9.3.1.1]: <script> não é acessível por teclado (onMouseDown)."                                  },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_UP,    0, "[9.3.1.2]: <script> não é acessível por teclado (onMouseUp)."                                    },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_CLICK,       0, "[9.3.1.3]: <script> não é acessível por teclado (onClick)."                                      },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OVER,  0, "[9.3.1.4]: <script> não é acessível por teclado (onMouseOver)."                                  },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_OUT,   0, "[9.3.1.5]: <script> não é acessível por teclado (onMouseOut)."                                   },
    { SCRIPT_NOT_KEYBOARD_ACCESSIBLE_ON_MOUSE_MOVE,  0, "[9.3.1.6]: <script> não é acessível por teclado (onMouseMove)."                                  },
    { NEW_WINDOWS_REQUIRE_WARNING_NEW,               0, "[10.1.1.1]: novas janelas exigem aviso (_new)."                                                  },
    { NEW_WINDOWS_REQUIRE_WARNING_BLANK,             0, "[10.1.1.2]: novas janelas exigem aviso (_blank)."                                                },
    { REPLACE_DEPRECATED_HTML_APPLET,                0, "[11.2.1.1]: substituir o elemento html obsoleto <applet>."                                       },
    { REPLACE_DEPRECATED_HTML_BASEFONT,              0, "[11.2.1.2]: substituir o elemento html obsoleto <basefont>."                                     },
    { REPLACE_DEPRECATED_HTML_CENTER,                0, "[11.2.1.3]: substituir o elemento html obsoleto <center>."                                       },
    { REPLACE_DEPRECATED_HTML_DIR,                   0, "[11.2.1.4]: substituir o elemento html obsoleto <dir>."                                          },
    { REPLACE_DEPRECATED_HTML_FONT,                  0, "[11.2.1.5]: substituir o elemento html obsoleto <font>."                                         },
    { REPLACE_DEPRECATED_HTML_ISINDEX,               0, "[11.2.1.6]: substituir o elemento html obsoleto <isindex>."                                      },
    { REPLACE_DEPRECATED_HTML_MENU,                  0, "[11.2.1.7]: substituir o elemento html obsoleto <menu>."                                         },
    { REPLACE_DEPRECATED_HTML_S,                     0, "[11.2.1.8]: substituir o elemento html obsoleto <s>."                                            },
    { REPLACE_DEPRECATED_HTML_STRIKE,                0, "[11.2.1.9]: substituir o elemento html obsoleto <strike>."                                       },
    { REPLACE_DEPRECATED_HTML_U,                     0, "[11.2.1.10]: substituir o elemento html obsoleto <u>."                                           },
    { FRAME_MISSING_TITLE,                           0, "[12.1.1.1]: <frame> carece de título."                                                           },
    { FRAME_TITLE_INVALID_NULL,                      0, "[12.1.1.2]: título de <frame> inválido (nulo)."                                                  },
    { FRAME_TITLE_INVALID_SPACES,                    0, "[12.1.1.3]: título de <frame> inválido (espaços)."                                               },
    { ASSOCIATE_LABELS_EXPLICITLY,                   0, "[12.4.1.1]: associar rótulos explicitamente com controles de formulário."                        },
    { ASSOCIATE_LABELS_EXPLICITLY_FOR,               0,        
        "[12.4.1.2]: associar rótulos explicitamente com controles de formulário "
        "(for)."
    },
    { ASSOCIATE_LABELS_EXPLICITLY_ID,                0, "[12.4.1.3]: associar rótulos explicitamente com controles de formulário (id)."                   },
    { LINK_TEXT_NOT_MEANINGFUL,                      0, "[13.1.1.1]: texto de link não significativo."                                                    },
    { LINK_TEXT_MISSING,                             0, "[13.1.1.2]: faltando texto de link."                                                             },
    { LINK_TEXT_TOO_LONG,                            0, "[13.1.1.3]: texto de link longo demais."                                                         },
    { LINK_TEXT_NOT_MEANINGFUL_CLICK_HERE,           0, "[13.1.1.4]: texto de link não significativo (clique aqui)."                                      },
    { METADATA_MISSING,                              0, "[13.2.1.1]: faltando metadados."                                                                 },
    { METADATA_MISSING_REDIRECT_AUTOREFRESH,         0, "[13.2.1.3]: faltando metadados (redirecionamento/autorrenovação)."                               },
    { SKIPOVER_ASCII_ART,                            0, "[13.10.1.1]: pular arte em ascii."                                                               },

#if SUPPORT_CONSOLE_APP
    { TC_LABEL_COL,                                  0, "coluna"                                                                                          },
    { TC_LABEL_FILE,                                 0, "arquivo"                                                                                         },
    { TC_LABEL_LANG,                                 0, "idioma"                                                                                          },
    { TC_LABEL_LEVL,                                 0, "nível"                                                                                           },
    { TC_LABEL_OPT,                                  0, "opção"                                                                                           },
    { TC_MAIN_ERROR_LOAD_CONFIG,                     0, "Falha ao carregar o arquivo de config \"%s\", err = %d"                                          },
    { TC_OPT_ACCESS,                                 0,        
        " faz verificações adicionais de acessibilidade (<nível> = 0, 1, 2, 3). 0 é "
        "presumido se <nível> estiver faltando."
    },
    { TC_OPT_ASCII,                                  0, "usa ISO-8859-1 para entrada, US-ASCII para saída"                                                },
    { TC_OPT_ASHTML,                                 0, "força XHTML para HTML bem formatado"                                                             },
    { TC_OPT_ASXML,                                  0, "converte HTML para XHTML bem formatado"                                                          },
    { TC_OPT_BARE,                                   0, "retira aspas inteligentes, travessões etc."                                                      },
    { TC_OPT_BIG5,                                   0, "usa Big5 para tanto entrada quanto saída"                                                        },
    { TC_OPT_CLEAN,                                  0, "substitui tags FONT, NOBR e CENTER com CSS"                                                      },
    { TC_OPT_CONFIG,                                 0, "define opções de configuração a partir do <arquivo> especificado"                                },
    { TC_OPT_ERRORS,                                 0, "mostra apenas erros e avisos"                                                                    },
    { TC_OPT_FILE,                                   0, "escreve erros e avisos para o <arquivo> especificado"                                            },
    { TC_OPT_GDOC,                                   0, "produz versão limpa do html exportado pelo Google Docs"                                          },
    { TC_OPT_HELP,                                   0, "lista as opções de linha de comando"                                                             },
    { TC_OPT_HELPCFG,                                0, "lista todas as opções de configuração"                                                           },
    { TC_OPT_HELPOPT,                                0, "  mostra uma descrição da <opção>"                                                               },
    { TC_OPT_IBM858,                                 0, "usa IBM-858 (CP850+Euro) para entrada, US-ASCII para saída"                                      },
    { TC_OPT_INDENT,                                 0, "recua o conteúdo do elemento"                                                                    },
    { TC_OPT_ISO2022,                                0, "usa ISO-2022 para tanto entrada quanto saída"                                                    },
    { TC_OPT_LANGUAGE,                               0,        
        "define o idioma de saída do Tidy para <idioma>. Especifique '-language help' "
        "para mais ajuda. Use antes de argumentos que gerem saída para garantir que o "
        "idioma surta efeitos, p.ex.:\n"
        "`tidy -lang es -lang help`."
    },
    { TC_OPT_LATIN0,                                 0, "usa ISO-8859-15 para entrada, US-ASCII para saída"                                               },
    { TC_OPT_LATIN1,                                 0, "usa ISO-8859-1 para tanto entrada quanto saída"                                                  },
    { TC_OPT_MAC,                                    0, "usa MacRoman para entrada, US-ASCII para saída"                                                  },
    { TC_OPT_MODIFY,                                 0, "modifica os arquivos de entrada originais"                                                       },
    { TC_OPT_NUMERIC,                                0, "emite entidades numéricas em vez de nomeadas"                                                    },
    { TC_OPT_OMIT,                                   0, "omite tags opcionais de início e de fim"                                                         },
    { TC_OPT_OUTPUT,                                 0, "escreve a saída para o <arquivo> especificado"                                                   },
    { TC_OPT_QUIET,                                  0, "suprime saída não essencial"                                                                     },
    { TC_OPT_RAW,                                    0, "emite valores acima de 127 sem conversão para entidades"                                         },
    { TC_OPT_SHIFTJIS,                               0, "usa Shift_JIS para tanto entrada quanto saída"                                                   },
    { TC_OPT_SHOWCFG,                                0, "lista as definições da configuração atual"                                                       },
    { TC_OPT_UPPER,                                  0, "força tags para maiúsculo"                                                                       },
    { TC_OPT_UTF16,                                  0, "usa UTF-16 para tanto entrada quanto saída"                                                      },
    { TC_OPT_UTF16BE,                                0, "usa UTF-16BE para tanto entrada quanto saída"                                                    },
    { TC_OPT_UTF16LE,                                0, "usa UTF-16LE para tanto entrada quanto saída"                                                    },
    { TC_OPT_UTF8,                                   0, "usa UTF-8 para tanto entrada quanto saída"                                                       },
    { TC_OPT_VERSION,                                0, "mostra a versão do Tidy"                                                                         },
    { TC_OPT_WIN1252,                                0, "usa Windows--1252 para entrada, US-ASCII para saída"                                             },
    { TC_OPT_WRAP,                                   0,        
        "efetua quebra de texto na <coluna> especificada, 0 é presumido se <coluna> "
        "estiver faltando. Quando esta opção é omitida, o padrão da opção da "
        "configuração 'wrap' é aplicado."
    },
    { TC_OPT_XML,                                    0, "especifica a entrada é XML bem formatado"                                                        },
    { TC_OPT_XMLCFG,                                 0, "lista todas as opções de configuração no formato XML"                                            },
    { TC_OPT_XMLHELP,                                0, "lista as opções de linha de comando no formato XML"                                              },
    { TC_OPT_XMLSTRG,                                0, "emite todas as strings do Tidy no formato XML"                                                   },
    { TC_OPT_XMLERRS,                                0, "emite constantes de erro e strings no formato XML"                                               },
    { TC_OPT_XMLOPTS,                                0, "emite descrições de opção no formato XML"                                                        },
    { TC_STRING_CONF_HEADER,                         0, "Definições do arquivo de configuração:"                                                          },
    { TC_STRING_CONF_NAME,                           0, "Nome"                                                                                            },
    { TC_STRING_CONF_TYPE,                           0, "Tipo"                                                                                            },
    { TC_STRING_CONF_VALUE,                          0, "Valor atual"                                                                                     },
    { TC_STRING_OPT_NOT_DOCUMENTED,                  0, "Aviso: a opção '%s' não está documentada."                                                       },
    { TC_STRING_OUT_OF_MEMORY,                       0, "Memória insuficiente. Saindo."                                                                   },
    { TC_STRING_FATAL_ERROR,                         0, "Erro fatal: valor impossível para id='%d'."                                                      },
    { TC_STRING_FILE_MANIP,                          0, "Manipulação de arquivo"                                                                          },
    { TC_STRING_PROCESS_DIRECTIVES,                  0, "Diretivas de processamento"                                                                      },
    { TC_STRING_CHAR_ENCODING,                       0, "Codificações de caracteres"                                                                      },
    { TC_STRING_LANG_MUST_SPECIFY,                   0, "Uma localidade POSIX ou Windows deve ser especificada."                                          },
    { TC_STRING_LANG_NOT_FOUND,                      0, "Tidy não possui o idioma '%s'; em vez desta, usará '%s'."                                        },
    { TC_STRING_MISC,                                0, "Diversos"                                                                                        },
    { TC_STRING_XML,                                 0, "XML"                                                                                             },
    { TC_STRING_MUST_SPECIFY,                        0, "Um nome de opção Tidy deve ser especificado."                                                    },
    { TC_STRING_UNKNOWN_OPTION,                      0, "HTML Tidy: opção desconhecida: %c"                                                               },
    { TC_STRING_UNKNOWN_OPTION_B,                    0, "HTML Tidy: opção desconhecida."                                                                  },
    { TC_STRING_VERS_A,                              0, "HTML Tidy para %s versão %s"                                                                     },
    { TC_STRING_VERS_B,                              0, "HTML Tidy versão %s"                                                                             },
    { TC_TXT_HELP_1,                                 0,        
        "\n"
        "%s [opções...] [arquivo...] [opções...] [arquivo...]\n"
        "Utilitário para limpar e melhor imprimir HTML/XHTML/XML.\n"
        "\n"
        "Essa é o HTML Tidy moderno versão %s.\n"
        "\n"
    },
    { TC_TXT_HELP_2A,                                0, "Os argumentos de linha de comando para HTML Tidy para %s:"                                       },
    { TC_TXT_HELP_2B,                                0, "Os argumentos de linha de comando para HTML Tidy:"                                               },
    { TC_TXT_HELP_3,                                 0,        
        "\n"
        "Opções de configuração do Tidy\n"
        "==========================\n"
        "Use as opções de configuração do Tidy como argumentos de linha de comando\n"
        "no forma de \"--alguma-opcao <valor>\", por exemplo \"--indent-with-tabs "
        "yes\".\n"
        "\n"
        "Para uma lista de todas as opções de configuração, use \"-help-config\" ou\n"
        "veja a página man (se seu SO tiver uma).\n"
        "\n"
        "Se seu ambiente tem uma variável $HTML_TIDY definida, aponte para um "
        "arquivo\n"
        "de configuração Tidy e, então, Tidy vai tentar usá-la.\n"
        "\n"
        "Em algumas plataformas, Tidy também vai tentar usar uma configuração\n"
        "especificada no /etc/tidy.conf ou ~/.tidy.conf.\n"
        "\n"
        "Outro\n"
        "=====\n"
        "Entrada/Saída usa, por padrão, stdin/stdout respectivamente.\n"
        "\n"
        "Opções de uma só letra, com exceção de -f, podem ser combinadas\n"
        "como em: tidy -f errs.txt -imu foo.html\n"
        "\n"
        "Informação\n"
        "===========\n"
        "Para mais informações sobre HTML Tidy, veja\n"
        "  http://www.html-tidy.org/\n"
        "\n"
        "Para mais informações sobre HTML, veja o seguinte:\n"
        "\n"
        "  HTML: Edition for Web Authors (the latest HTML specification)\n"
        "  http://dev.w3.org/html5/spec-author-view\n"
        "\n"
        "  HTML: The Markup Language (an HTML language reference)\n"
        "  http://dev.w3.org/html5/markup/\n"
        "\n"
        "Preencha relatórios de erros em https://github.com/htacg/tidy-html5/issues/\n"
        "ou envie perguntas e comentários para public-htacg@w3.org.\n"
        "\n"
        "Valide seus documentos HTML usando Nu, o validador de marcação da W3C:\n"
        "  http://validator.w3.org/nu/\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG,                            0,        
        "\n"
        "Definições de configuração do HTML Tidy\n"
        "\n"
        "Dentro de um arquivo, use a forma:\n"
        "\n"
        "wrap: 72\n"
        "indent: no\n"
        "\n"
        "Quando especificado na linha de comando, use a forma:\n"
        "\n"
        "--wrap 72 --indent no\n"
        "\n"
    },
    { TC_TXT_HELP_CONFIG_NAME,                       0, "Nome"                                                                                            },
    { TC_TXT_HELP_CONFIG_TYPE,                       0, "Tipo"                                                                                            },
    { TC_TXT_HELP_CONFIG_ALLW,                       0, "Valores permitidos"                                                                              },
    { TC_TXT_HELP_LANG_1,                            0,        
        "\n"
        "A opção -language (ou -lang) indica qual idioma o Tidy deve usar\n"
        "para comunicar sua saída. Por favor, note que este não é um serviço\n"
        "de tradução de documentos e afeta apenas as mensagens com as quais\n"
        "o Tidy se comunica com você.\n"
        "\n"
        "Quando usado a partir da linha de comando, o argumento -language\n"
        "deve ser usado antes de qualquer argumento que resulte em saída; do\n"
        "contrário, o Tidy produzirá saída antes de saber qual idioma usar.\n"
        "\n"
        "Além dos códigos de idioma POSIX padrão, o Tidy é capaz de entender\n"
        "os códigos legados de idioma do Windows. Por favor, note que esta\n"
        "lista indica códigos Tidy entende e não indica que o idioma esteja\n"
        "instalado no momento.\n"
        "\n"
        "A coluna mais à direita indica como o Tidy vai entender o nome do\n"
        "Windows legado.\n"
        "\n"
    },
    { TC_TXT_HELP_LANG_2,                            0,        
        "\n"
        "Os seguintes idiomas estão atualmente instalados em Tidy. Por favor, \n"
        "note que não há garantia de que eles estejam completos; apenas que \n"
        "esse desenvolvedor ou outro começou a adicionar o idioma indicado. \n"
        "\n"
        "As localizações incompletas serão padrão para \"en\" quando necessário. \n"
        "Informe as instâncias de strings incorretas para a equipe do Tidy. \n"
        "\n"
    },
    { TC_TXT_HELP_LANG_3,                            0,        
        "\n"
        "Se o Tidy for capaz de determinar sua localidade, o Tidy usará \n"
        "o idioma da localidade automaticamente. Por exemplo, os sistemas \n"
        "tipo Unix usam uma variável de ambiente $LANG e/ou $LC_ALL. \n"
        "Consulte a documentação de seu sistema operacional para obter \n"
        "mais informações. \n"
        "\n"
        "Tidy está usando a localidade %s. \n"
        "\n"
    },
#endif /* SUPPORT_CONSOLE_APP */

    {/* This MUST be present and last. */
      TIDY_MESSAGE_TYPE_LAST,                        0, NULL
    }

}};


#endif /* language_pt_br_h */

