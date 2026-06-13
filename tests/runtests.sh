#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libscca/.libs/libscca.1.dylib && test -f ./pyscca/.libs/pyscca.so
then
	install_name_tool -change /usr/local/lib/libscca.1.dylib ${PWD}/libscca/.libs/libscca.1.dylib ./pyscca/.libs/pyscca.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

