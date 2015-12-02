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
#include "tmbstr.h"


/**
 *  This structure type provides universal access to all of Tidy's strings.
 */
typedef struct {
    languageDictionary *currentLanguage;
    languageDictionary *languages[];
} tidyLanguagesType;


/**
 *  This single structure contains all localizations. Note that we preset
 *  `.currentLanguage` to language_en, which is Tidy's default language.
 */
static tidyLanguagesType tidyLanguages = {
    .currentLanguage = &language_en,
    .languages = {
        &language_en,
        &language_en_gb,
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
 *  Provides a string given `messageType` in the current
 *  localization.
 *
 *  This isn't currently highly optimized; rewriting some
 *  of infrastructure to use hash lookups is a preferred
 *  future optimization.
 */
ctmbstr tidyLocalizedString( uint messageType )
{
    uint i;
    languageDictionary *current = tidyLanguages.currentLanguage;

    for (i = 0; (*current)[i].value; ++i)
    {
        if ((*current)[i].key == messageType)
        {
            return (*current)[i].value;
        }
    }

    /* Fallback to `en` in case a string is missing. */
    current = &language_en;

    for (i = 0; (*current)[i].value; ++i)
    {
        if ((*current)[i].key == messageType)
        {
            return (*current)[i].value;
        }
    }
    return NULL;

}


/**
 *  Retrieves the POSIX components for a string. We accept
 *  POSIX names and Windows legacy names.
 */
ctmbstr tidyNormalizedLocaleName( ctmbstr locale )
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
			search = (tmbstr)localeMappings[i].POSIXName;
			break;
		}
	}
	
	/* We're going to be stupid about this and trust the
	   user, and return just the first two characters
	   if they exist and the 4th and 5th if they exist. */
	len = strlen( search );
	if ( len >= 5 )
		strncpy( result+3, search+3, 2 );
	else
		result[2] = '\0';
	
	if ( len >= 2 )
		strncpy( result, search, 2 );
	
	for ( i = 0; i < 6; i++ )
		result[i] = tolower(result[i]);
	
	return result;
}

/**
 *  Tells Tidy to use a different language for output. The
 *  parameter `languageCode` must match the TIDY_LANGUAGE for
 *  an included language. The result indicates the success of
 *  this setting.
 */
Bool tidySetLanguage( ctmbstr languageCode )
{
    uint i;
    languageDictionary *testLang;
    languageDictionaryEntry testEntry;
	ctmbstr wantCode;
    ctmbstr testCode;

	/* @todo: we want to do this twice: once to set the language,
	 * and then again to set the langage+region. This way the
	 * language will be set even when the region cannot be. */
	wantCode = tidyNormalizedLocaleName( languageCode );
    for (i = 0; tidyLanguages.languages[i]; ++i)
    {
        testLang = tidyLanguages.languages[i];
        testEntry = (*testLang)[0];
        testCode = testEntry.value;

        if ( strcmp(testCode, wantCode) == 0 )
        {
            tidyLanguages.currentLanguage = testLang;
            return yes;
        }
    }

    return no;
}


