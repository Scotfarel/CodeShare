#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} project --enable=all --error-exitcode=1 -I project/headers --suppress=missingIncludeSystem # --check-config


print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --linelength=120 --extensions=c,cpp --headers=h,hpp--filter=-runtime/references,-legal/copyright,-build/include_subdir,-whitespace/line_length project/headers/* project/src/* project/tests/*

print_header "SUCCESS"
