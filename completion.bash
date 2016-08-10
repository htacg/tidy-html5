# BASH completion for Tidy
# Copyright (c) 2012, Craig Barnes
# Licensed under the W3C license

_tidy() {
    local cur="${COMP_WORDS[COMP_CWORD]}"
    local prev="${COMP_WORDS[COMP_CWORD-1]}"

    local doctypes="html5 omit auto strict transitional user"

    local encodings="raw ascii latin0 latin1 utf8 iso2022 mac win1252 ibm858
        utf16le utf16be utf16 big5 shiftjis"

    local languages="aa ab af am ar as ay az ba be bg bh bi bn bo br ca co
        cs cy da de dz el en eo es et eu fa fi fj fo fr fy ga gd gl gn gu ha
        he hi hr hu hy ia id ie ik is it iu ja jw ka kk kl km kn ko ks ku ky
        la ln lo lt lv mg mi mk ml mn mo mr ms mt my na ne nl no oc om or pa
        pl ps pt qu rm rn ro ru rw sa sd sg sh si sk sl sm sn so sq sr ss st
        su sv sw ta te tg th ti tk tl tn to tr ts tt tw ug uk ur uz vi vo wo
        xh yi yo za zh zu"

    local boolflags="--add-xml-decl --add-xml-space --anchor-as-name
        --assume-xml-procins --bare --clean --coerce-endtags
        --decorate-inferred-ul --drop-empty-elements --drop-empty-paras
        --drop-font-tags --drop-proprietary-attributes --enclose-block-text
        --enclose-text --escape-cdata --fix-backslash --fix-bad-comments
        --fix-uri --gdoc --hide-comments --hide-endtags --indent-cdata
        --input-xml --join-classes --join-styles --literal-attributes
        --logical-emphasis --lower-literals --merge-emphasis --ncr
        --numeric-entities --omit-optional-tags --output-html --output-xhtml
        --output-xml --preserve-entities --quote-ampersand --quote-marks
        --quote-nbsp --replace-color --uppercase-attributes --uppercase-tags
        --word-2000 --show-info --show-warnings --break-before-br --indent
        --indent-attributes --markup --punctuation-wrap --vertical-space
        --wrap-asp --wrap-attributes --wrap-jste --wrap-php --split
        --wrap-script-literals --wrap-sections --ascii-chars --force-output
        --gnu-emacs --keep-time --quiet --tidy-mark --write-back"

    local stringflags="--alt-text --css-prefix --language --error-file
        --gnu-emacs-file --output-file --slide-style --new-pre-tags
        --new-blocklevel-tags --new-empty-tags --new-inline-tags"

    local intflags="--show-errors --indent-spaces --tab-size --wrap"

    local shortflags="-output -config -file -modify -indent -upper -clean
        -bare -gdoc -wrap -numeric -errors -quiet -omit -xml -asxml -asxhtml
        -ashtml -access -raw -ascii -latin0 -latin1 -iso2022 -mac -win1252
        -ibm858 -utf16le -utf16be -utf16 -big5 -shiftjis -language -version
        -help -xml-help -help-config -xml-config -show-config -utf8"

    local longflags="$boolflags $stringflags $intflags
        --char-encoding --input-encoding --output-encoding --doctype
        --sort-attributes --repeated-attributes --newline --indent
        --merge-divs --merge-spans --show-body-only --output-bom
        --accessibility-check"

    case $prev in
    --char-encoding|--input-encoding|--output-encoding)
        COMPREPLY=($(compgen -W "$encodings" -- $cur))
        return;;
    --doctype)
        COMPREPLY=($(compgen -W "$doctypes" -- $cur))
        return;;
    -language|--language)
        COMPREPLY=($(compgen -W "$languages" -- $cur))
        return;;
    --repeated-attributes)
        COMPREPLY=($(compgen -W "keep-first keep-last" -- $cur))
        return;;
    --accessibility-check)
        COMPREPLY=($(compgen -W "0 1 2 3" -- $cur))
        return;;
    --newline)
        COMPREPLY=($(compgen -W "LF CRLF CR" -- $cur))
        return;;
    --sort-attributes)
        COMPREPLY=($(compgen -W "none alpha" -- $cur))
        return;;
    # "AutoBool" flags
    --indent|--merge-divs|--merge-spans|--show-body-only|--output-bom)
        COMPREPLY=($(compgen -W "auto yes no true false 1 0" -- $cur))
        return;;
    esac

    for flag in $boolflags; do
        if [[ $flag == $prev ]]; then
            COMPREPLY=($(compgen -W "yes no true false 1 0" -- $cur))
            return
        fi
    done

    for flag in $stringflags $intflags; do
        if [[ $flag == $prev ]]; then
            # Just return an empty list to prevent default
            COMPREPLY=()
            return
        fi
    done

    case $cur in
    --*) COMPREPLY=($(compgen -W "$longflags" -- $cur)); return;;
    -*)  COMPREPLY=($(compgen -W "$shortflags" -- $cur)); return;;
    esac

    # If nothing matches, default to filename completion
    COMPREPLY=($(compgen -f ${COMP_WORDS[COMP_CWORD]}))
}

complete -F _tidy tidy
