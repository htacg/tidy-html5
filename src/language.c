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
    return NULL;
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
    ctmbstr testCode;

    for (i = 0; tidyLanguages.languages[i]; ++i)
    {
        testLang = tidyLanguages.languages[i];
        testEntry = (*testLang)[0];
        testCode = testEntry.value;

        if (testCode == languageCode)
        {
            tidyLanguages.currentLanguage = testLang;
            return yes;
        }
    }

    return no;
}


