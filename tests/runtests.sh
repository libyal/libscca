#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libscca/.libs/libscca.1.dylib" ] && [ -f ./pyscca/.libs/pyscca.so ]
then
    install_name_tool -change /usr/local/lib/libscca.1.dylib "${PWD}/libscca/.libs/libscca.1.dylib" ./pyscca/.libs/pyscca.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

