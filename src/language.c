/*
 * language.c
 * Localization support for HTML Tidy.
 *
 * (c) 2015 HTACG
 * See tidy.h and access.h for the copyright notice.
 *
 * Created by Jim Derry on 11/28/15.
 */

#include "language.h"
#include "language_en.h"
#if SUPPORT_LOCALIZATIONS
#include "language_en_gb.h"
#include "language_es.h"
#include "language_es_mx.h"
#include "language_zh_cn.h"
#endif
#include "tmbstr.h"
#include "locale.h"
#if defined(_WIN32)
#include "win_vsnprintf.h"
#define nest_(x) TY_(x)
#define printf nest_(win_printf)
#define fprint nest_(win_fprintf)
#endif


/**
 *  This structure type provides universal access to all of Tidy's strings.
 */
typedef struct {
	languageDefinition *currentLanguage;
	languageDefinition *fallbackLanguage;
	languageDefinition *languages[];
} tidyLanguagesType;


/**
 *  This single structure contains all localizations. Note that we preset
 *  `.currentLanguage` to language_en, which is Tidy's default language.
 */
static tidyLanguagesType tidyLanguages = {
	&language_en, /* current language */
	&language_en, /* first fallback language */
	{
        /* Required localization! */
        &language_en,
#if SUPPORT_LOCALIZATIONS
		/* These additional languages are installed. */
		&language_en_gb,
		&language_es,
		&language_es_mx,
        &language_zh_cn,
#endif
		NULL /* This array MUST be null terminated. */
	}
};


/**
 *  This structure maps old-fashioned Windows strings
 *  to proper POSIX names (modern Windows already uses
 *  POSIX names).
 */
static const tidyLocaleMapItem localeMappings[] = {
	{ "america",                "en_us" },
	{ "american english",       "en_us" },
	{ "american-english",       "en_us" },
	{ "american",               "en_us" },
	{ "aus",                    "en_au" },
	{ "australia",              "en_au" },
	{ "australian",             "en_au" },
	{ "austria",                "de_at" },
	{ "aut",                    "de_at" },
	{ "bel",                    "nl_be" },
	{ "belgian",                "nl_be" },
	{ "belgium",                "nl_be" },
	{ "bra",                    "pt-br" },
	{ "brazil",                 "pt-br" },
	{ "britain",                "en_gb" },
	{ "can",                    "en_ca" },
	{ "canada",                 "en_ca" },
	{ "canadian",               "en_ca" },
	{ "che",                    "de_ch" },
	{ "china",                  "zh_cn" },
	{ "chinese-simplified",     "zh"    },
	{ "chinese-traditional",    "zh_tw" },
	{ "chinese",                "zh"    },
	{ "chn",                    "zh_cn" },
	{ "chs",                    "zh"    },
	{ "cht",                    "zh_tw" },
	{ "csy",                    "cs"    },
	{ "cze",                    "cs_cz" },
	{ "czech",                  "cs_cz" },
	{ "dan",                    "da"    },
	{ "danish",                 "da"    },
	{ "dea",                    "de_at" },
	{ "denmark",                "da_dk" },
	{ "des",                    "de_ch" },
	{ "deu",                    "de"    },
	{ "dnk",                    "da_dk" },
	{ "dutch-belgian",          "nl_be" },
	{ "dutch",                  "nl"    },
	{ "ell",                    "el"    },
	{ "ena",                    "en_au" },
	{ "enc",                    "en_ca" },
	{ "eng",                    "eb_gb" },
	{ "england",                "en_gb" },
	{ "english-american",       "en_us" },
	{ "english-aus",            "en_au" },
	{ "english-can",            "en_ca" },
	{ "english-nz",             "en_nz" },
	{ "english-uk",             "eb_gb" },
	{ "english-us",             "en_us" },
	{ "english-usa",            "en_us" },
	{ "english",                "en"    },
	{ "enu",                    "en_us" },
	{ "enz",                    "en_nz" },
	{ "esm",                    "es-mx" },
	{ "esn",                    "es"    },
	{ "esp",                    "es"    },
	{ "fin",                    "fi"    },
	{ "finland",                "fi_fi" },
	{ "finnish",                "fi"    },
	{ "fra",                    "fr"    },
	{ "france",                 "fr_fr" },
	{ "frb",                    "fr_be" },
	{ "frc",                    "fr_ca" },
	{ "french-belgian",         "fr_be" },
	{ "french-canadian",        "fr_ca" },
	{ "french-swiss",           "fr_ch" },
	{ "french",                 "fr"    },
	{ "frs",                    "fr_ch" },
	{ "gbr",                    "en_gb" },
	{ "german-austrian",        "de_at" },
	{ "german-swiss",           "de_ch" },
	{ "german",                 "de"    },
	{ "germany",                "de_de" },
	{ "grc",                    "el_gr" },
	{ "great britain",          "en_gb" },
	{ "greece",                 "el_gr" },
	{ "greek",                  "el"    },
	{ "hkg",                    "zh_hk" },
	{ "holland",                "nl_nl" },
	{ "hong kong",              "zh_hk" },
	{ "hong-kong",              "zh_hk" },
	{ "hun",                    "hu"    },
	{ "hungarian",              "hu"    },
	{ "hungary",                "hu_hu" },
	{ "iceland",                "is_is" },
	{ "icelandic",              "is"    },
	{ "ireland",                "en_ie" },
	{ "irl",                    "en_ie" },
	{ "isl",                    "is"    },
	{ "ita",                    "it"    },
	{ "ita",                    "it_it" },
	{ "italian-swiss",          "it_ch" },
	{ "italian",                "it"    },
	{ "italy",                  "it_it" },
	{ "its",                    "it_ch" },
	{ "japan",                  "ja_jp" },
	{ "japanese",               "ja"    },
	{ "jpn",                    "ja"    },
	{ "kor",                    "ko"    },
	{ "korea",                  "ko_kr" },
	{ "korean",                 "ko"    },
	{ "mex",                    "es-mx" },
	{ "mexico",                 "es-mx" },
	{ "netherlands",            "nl_nl" },
	{ "new zealand",            "en_nz" },
	{ "new-zealand",            "en_nz" },
	{ "nlb",                    "nl_be" },
	{ "nld",                    "nl"    },
	{ "non",                    "nn"    },
	{ "nor",                    "nb"    },
	{ "norway",                 "no"    },
	{ "norwegian-bokmal",       "nb"    },
	{ "norwegian-nynorsk",      "nn"    },
	{ "norwegian",              "no"    },
	{ "nz",                     "en_nz" },
	{ "nzl",                    "en_nz" },
	{ "plk",                    "pl"    },
	{ "pol",                    "pl-pl" },
	{ "poland",                 "pl-pl" },
	{ "polish",                 "pl"    },
	{ "portugal",               "pt-pt" },
	{ "portuguese-brazil",      "pt-br" },
	{ "portuguese",             "pt"    },
	{ "pr china",               "zh_cn" },
	{ "pr-china",               "zh_cn" },
	{ "prt",                    "pt-pt" },
	{ "ptb",                    "pt-br" },
	{ "ptg",                    "pt"    },
	{ "rus",                    "ru"    },
	{ "russia",                 "ru-ru" },
	{ "russian",                "ru"    },
	{ "sgp",                    "zh_sg" },
	{ "singapore",              "zh_sg" },
	{ "sky",                    "sk"    },
	{ "slovak",                 "sk"    },
	{ "spain",                  "es-es" },
	{ "spanish-mexican",        "es-mx" },
	{ "spanish-modern",         "es"    },
	{ "spanish",                "es"    },
	{ "sve",                    "sv"    },
	{ "svk",                    "sk-sk" },
	{ "swe",                    "sv-se" },
	{ "sweden",                 "sv-se" },
	{ "swedish",                "sv"    },
	{ "swiss",                  "de_ch" },
	{ "switzerland",            "de_ch" },
	{ "taiwan",                 "zh_tw" },
	{ "trk",                    "tr"    },
	{ "tur",                    "tr-tr" },
	{ "turkey",                 "tr-tr" },
	{ "turkish",                "tr"    },
	{ "twn",                    "zh_tw" },
	{ "uk",                     "en_gb" },
	{ "united kingdom",         "en_gb" },
	{ "united states",          "en_us" },
	{ "united-kingdom",         "en_gb" },
	{ "united-states",          "en_us" },
	{ "us",                     "en_us" },
	{ "usa",                    "en_us" },
	
	/* MUST be last. */
	{ NULL,                     NULL    }
};


/**
 *  The real string lookup function.
 */
ctmbstr TY_(tidyLocalizedString)( uint messageType, languageDefinition *definition, uint plural )
{
	int i;
	languageDictionary *dictionary = &definition->messages;
	uint pluralForm = definition->whichPluralForm(plural);
	
	for (i = 0; (*dictionary)[i].value; ++i)
	{
		if ( (*dictionary)[i].key == messageType && (*dictionary)[i].pluralForm == pluralForm )
		{
			return (*dictionary)[i].value;
		}
	}
	return NULL;
}


/**
 *  Provides a string given `messageType` in the current
 *  localization, returning the correct plural form given
 *  `quantity`.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedStringN( uint messageType, uint quantity )
{
	ctmbstr result;
	
	result  = TY_(tidyLocalizedString)( messageType, tidyLanguages.currentLanguage, quantity);
	
	if (!result && tidyLanguages.fallbackLanguage )
	{
		result = TY_(tidyLocalizedString)( messageType, tidyLanguages.fallbackLanguage, quantity);
	}
	
	if (!result)
	{
		/* Fallback to en which is built in. */
		result = TY_(tidyLocalizedString)( messageType, &language_en, quantity);
	}
	
	if (!result)
	{
		/* Last resort: Fallback to en singular which is built in. */
		result = TY_(tidyLocalizedString)( messageType, &language_en, 1);
	}
	
	return result;
}


/**
 *  Provides a string given `messageType` in the current
 *  localization, in the non-plural form.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedString( uint messageType )
{
	return tidyLocalizedStringN( messageType, 1 );
}


/**
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  @param  result The buffer to use to return the string.
 **          Returns NULL on failure.
 **  @return The same buffer for convenience.
 */
tmbstr tidySystemLocale(tmbstr result)
{
	ctmbstr temp;
	
	/* This should set the OS locale. */
	setlocale( LC_ALL, "" );
	
	/* This should read the current locale. */
	temp = setlocale( LC_ALL, NULL);
	
	/* Make a new copy of the string, because temp
       always points to the current locale. */
	if (( result = malloc( strlen( temp ) + 1 ) ))
		strcpy(result, temp);
	
	/* This should restore the C locale. */
	setlocale( LC_ALL, "C" );
	
	return result;
}


/**
 *  Retrieves the POSIX name for a string. Result is a static char so please
 *  don't try to free it. If the name looks like a cc_ll identifier, we will
 *  return it if there's no other match.
 */
tmbstr tidyNormalizedLocaleName( ctmbstr locale )
{
	uint i;
	uint len;
	static char result[6] = "xx_yy";
	tmbstr search = strdup(locale);
	search = TY_(tmbstrtolower)(search);
	
	/* See if our string matches a Windows name. */
	for (i = 0; localeMappings[i].winName; ++i)
	{
		if ( strcmp( localeMappings[i].winName, search ) == 0 )
		{
            free(search);
            search = strdup(localeMappings[i].POSIXName);
			break;
		}
	}
	
	/* We're going to be stupid about this and trust the user, and
	 return just the first two characters if they exist and the
	 4th and 5th if they exist. The worst that can happen is a
	 junk language that doesn't exist and won't be set. */
	
	len = strlen( search );
	len = len <= 5 ? len : 5;
	
	for ( i = 0; i < len; i++ )
	{
		if ( i == 2 )
		{
			/* Either terminate the string or ensure there's an underscore */
			strncpy( result + i, strlen( search ) >= 5 ? "_" : '\0', 1 );
		}
		else
		{
			strncpy( result + i, search + i, 1);
			result[i] = tolower( result[i] );
		}
	}

    if ( search ) free( search );
	return result;
}


/**
 *  Returns the languageDefinition if the languageCode is installed in Tidy,
 *  otherwise return NULL
 */
languageDefinition *TY_(tidyTestLanguage)( ctmbstr languageCode )
{
	uint i;
	languageDefinition *testLang;
	languageDictionary *testDict;
	ctmbstr testCode;
	
	for (i = 0; tidyLanguages.languages[i]; ++i)
	{
		testLang = tidyLanguages.languages[i];
		testDict = &testLang->messages;
		testCode = (*testDict)[0].value;
		
		if ( strcmp(testCode, languageCode) == 0 )
            return testLang;
	}
	
	return NULL;
}


/**
 *  Tells Tidy to use a different language for output.
 *  @param  languageCode A Windows or POSIX language code, and must match
 *          a TIDY_LANGUAGE for an installed language.
 *  @result Indicates that a setting was applied, but not necessarily the
 *          specific request, i.e., true indicates a language and/or region
 *          was applied. If es_mx is requested but not installed, and es is
 *          installed, then es will be selected and this function will return
 *          true. However the opposite is not true; if es is requested but
 *          not present, Tidy will not try to select from the es_XX variants.
 */
Bool tidySetLanguage( ctmbstr languageCode )
{
	languageDefinition *dict1 = NULL;
	languageDefinition *dict2 = NULL;
	tmbstr wantCode = NULL;
	char lang[3] = "";
	
	if ( !languageCode || !(wantCode = tidyNormalizedLocaleName( languageCode )) )
    {
		return no;
    }

    /* We want to use the specified language as the currentLanguage, and set
     fallback language as necessary. We have either a two or five digit code,
     either or both of which might be installed. Let's test both of them:
     */

    dict1 = TY_(tidyTestLanguage( wantCode ));  /* WANTED language */

    if ( strlen( wantCode ) > 2 )
    {
        strncpy(lang, wantCode, 2);
        lang[2] = '\0';
        dict2 = TY_(tidyTestLanguage( lang ) ); /* BACKUP language? */
    }

    if ( dict1 && dict2 )
    {
        tidyLanguages.currentLanguage = dict1;
        tidyLanguages.fallbackLanguage = dict2;
    }
    if ( dict1 && !dict2 )
    {
        tidyLanguages.currentLanguage = dict1;
        tidyLanguages.fallbackLanguage = NULL;
    }
    if ( !dict1 && dict2 )
    {
        tidyLanguages.currentLanguage = dict2;
        tidyLanguages.fallbackLanguage = NULL;
    }
    if ( !dict1 && !dict2 )
    {
        /* No change. */
    }

	return dict1 || dict2;
}


/**
 *  Gets the current language used by Tidy.
 */
ctmbstr tidyGetLanguage()
{
	languageDefinition *langDef = tidyLanguages.currentLanguage;
	languageDictionary *langDict = &langDef->messages;
	return (*langDict)[0].value;
}


/**
 *  Provides a string given `messageType` in the default
 *  localization (which is `en`), for single plural form.
 */
ctmbstr tidyDefaultString( uint messageType )
{
	return TY_(tidyLocalizedString)( messageType, &language_en, 1);
}


/**
 *  Determines the true size of the `language_en` array indicating the
 *  number of items in the array, _not_ the highest index.
 */
const uint TY_(tidyStringKeyListSize)()
{
    static uint array_size = 0;
    
    if ( array_size == 0 )
    {
        do {
            array_size++;
        } while ( language_en.messages[array_size].value );
    }
    
    return array_size;
}


/*
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of localization string keys. Note that
 *  these are provided for documentation generation purposes
 *  and probably aren't useful for LibTidy implementors.
 */
TidyIterator getStringKeyList()
{
    return (TidyIterator)(size_t)1;
}

/*
 *  Provides the next key value in Tidy's list of localized
 *  strings. Note that these are provided for documentation
 *  generation purposes and probably aren't useful to
 *  libtidy implementors.
 */
uint getNextStringKey( TidyIterator* iter )
{
    uint item = 0;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyStringKeyListSize)() )
    {
        item = language_en.messages[itemIndex].key;
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyStringKeyListSize)() ? itemIndex : (size_t)0 );
    return item;
}


/**
 *  Determines the true size of the `localeMappings` array indicating the
 *  number of items in the array, _not_ the highest index.
 */
const uint TY_(tidyLanguageListSize)()
{
	static uint array_size = 0;
	
	if ( array_size == 0 )
	{
		do {
			array_size++;
		} while ( localeMappings[array_size].winName );
	}
	
	return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's structure of Windows<->POSIX local mapping.
 *  Items can be retrieved with getNextWindowsLanguage();
 */
TidyIterator getWindowsLanguageList()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next record of type `localeMapItem` in
 *  Tidy's structure of Windows<->POSIX local mapping.
 */
const tidyLocaleMapItem *getNextWindowsLanguage( TidyIterator *iter )
{
    const tidyLocaleMapItem *item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyLanguageListSize)() )
    {
        item = &localeMappings[ itemIndex -1 ];
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyLanguageListSize)() ? itemIndex : (size_t)0 );
    return item;
}


/**
 *  Determines the number of languages installed in Tidy.
 */
const uint TY_(tidyInstalledLanguageListSize)()
{
	static uint array_size = 0;
	
	if ( array_size == 0 )
	{
		do {
			array_size++;
		} while ( tidyLanguages.languages[array_size] );
	}
	
	return array_size;
}

/**
 *  Initializes the TidyIterator to point to the first item
 *  in Tidy's list of installed language codes.
 *  Items can be retrieved with getNextInstalledLanguage();
 */
TidyIterator getInstalledLanguageList()
{
    return (TidyIterator)(size_t)1;
}

/**
 *  Returns the next installed language.
 */
ctmbstr getNextInstalledLanguage( TidyIterator* iter )
{
    ctmbstr item = NULL;
    size_t itemIndex;
    assert( iter != NULL );
    
    itemIndex = (size_t)*iter;
    
    if ( itemIndex > 0 && itemIndex <= TY_(tidyInstalledLanguageListSize)() )
    {
        item = tidyLanguages.languages[itemIndex - 1]->messages[0].value;
        itemIndex++;
    }
    
    *iter = (TidyIterator)( itemIndex <= TY_(tidyInstalledLanguageListSize)() ? itemIndex : (size_t)0 );
    return item;
}
