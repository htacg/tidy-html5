#!/usr/bin/env bash
# Set snap version according to various factors
# 林博仁(Buo-ren, Lin) © 2018

set \
    -o errexit \
    -o errtrace \
    -o nounset \
    -o pipefail

init(){
    set \
        -o errexit \
        -o nounset

    local \
        upstream_version \
        upstream_git_revision

    upstream_version="$(
        head \
            --lines=1 \
            parts/tidy/src/version.txt
    )"

    upstream_git_revision="$(
        git \
            -C parts/tidy/src \
            describe \
            --always \
            --dirty \
            --match nothing \
        | sed s/^v//
    )"

    printf \
        -- \
        '%s' \
        "${upstream_version}-g${upstream_git_revision}"

    exit 0
}

init "${@}"
