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
#include "language_en_gb.h"
#include "language_es.h"
#include "language_es_mx.h"
#include "tmbstr.h"
#include "locale.h"


/**
 *  This structure type provides universal access to all of Tidy's strings.
 */
typedef struct {
	languageDictionary *currentLanguage;
	languageDictionary *fallbackLanguage;
	languageDictionary *languages[];
} tidyLanguagesType;


/**
 *  This single structure contains all localizations. Note that we preset
 *  `.currentLanguage` to language_en, which is Tidy's default language.
 */
static tidyLanguagesType tidyLanguages = {
	.currentLanguage = &language_en,
	.fallbackLanguage = &language_en,
	.languages = {
		&language_en,
		&language_en_gb,
		&language_es,
		&language_es_mx,
		NULL /* This array MUST be null terminated. */
	}
};


/**
 *  This structure maps old-fashioned Windows strings
 *  to proper POSIX names (modern Windows already uses
 *  POSIX names).
 */
static struct _localeMap {
	ctmbstr winName;
	ctmbstr POSIXName;
} const localeMappings[] = {
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
ctmbstr TY_(tidyLocalizedString)( uint messageType, languageDictionary *dictionary )
{
	int i;
	for (i = 0; (*dictionary)[i].value; ++i)
	{
		if ((*dictionary)[i].key == messageType)
		{
			return (*dictionary)[i].value;
		}
	}
	return NULL;
}

/**
 *  Provides a string given `messageType` in the current
 *  localization.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedString( uint messageType )
{
	ctmbstr result;
	
	result  = TY_(tidyLocalizedString)( messageType, tidyLanguages.currentLanguage);
	
	if (!result && tidyLanguages.fallbackLanguage )
	{
		result = TY_(tidyLocalizedString)( messageType, tidyLanguages.fallbackLanguage);
	}
	
	if (!result)
	{
		/* Fallback to en which is built in. */
		result = TY_(tidyLocalizedString)( messageType, &language_en);
	}
	
	return result;
}


/**
 **  Determines the current locale without affecting the C locale.
 **  Tidy has always used the default C locale, and at this point
 **  in its development we're not going to tamper with that.
 **  We have to return a new string, so don't forget to free it.
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
 *  Retrieves the POSIX name for a string. Result is a
 *  static char so please don't try to free it.
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
 *  Actually sets the language with a sanitized languageCode.
 */
languageDictionary *TY_(tidySetLanguage)( ctmbstr languageCode )
{
	uint i;
	languageDictionary *testLang;
	ctmbstr testCode;
	
	for (i = 0; tidyLanguages.languages[i]; ++i)
	{
		testLang = tidyLanguages.languages[i];
		testCode = (*testLang)[0].value;
		
		if ( strcmp(testCode, languageCode) == 0 )
		{
			tidyLanguages.currentLanguage = testLang;
			if ( strlen(testCode) == 2 )
				return testLang;
		}
	}
	
	return NULL;
}


/**
 *  Tells Tidy to use a different language for output. The
 *  parameter `languageCode` must match the TIDY_LANGUAGE for
 *  an included language. The result indicates that a setting
 *  was applied, but not necessarily the specific request, i.e.,
 *  true indicates the language and/or region was applied.
 */
Bool tidySetLanguage( ctmbstr languageCode )
{
	languageDictionary *dict1 = NULL;
	languageDictionary *dict2 = NULL;
	tmbstr wantCode = NULL;
	char lang[3] = "";
	
	if ( !languageCode || !(wantCode = tidyNormalizedLocaleName( languageCode )) )
    {
		return no;
    }

	/* We should have a two or five character string at this point, so
	 we will first set with the two character ID to get the right
	 language, then try again with the five character ID to set the
	 region. If the region fails, at least the language is set.
	 */
	
	if ( strlen( wantCode ) > 2 )
	{
		strncpy(lang, wantCode, 2);
		lang[2] = '\0';
		dict1 = TY_(tidySetLanguage( lang ) );
	}
	
	dict2 = TY_(tidySetLanguage( wantCode ));
	
	/* Set a fallback dictionary if applicable. If dict1 is assigned,
	 it means we wanted a xx_yy dict, but the xx worked, making it
	 eligible as a fallback. If !dict1, then there is no eligible
	 fallback so make sure to NULL it out.
	 */
	if ( dict1 )
		tidyLanguages.fallbackLanguage = dict1;
	if ( !dict1 && dict2 )
		tidyLanguages.fallbackLanguage = NULL;

	return dict1 || dict2;
}


/**
 *  Gets the current language used by Tidy.
 */
ctmbstr tidyGetLanguage()
{
	return (*tidyLanguages.currentLanguage)[0].value;
}
