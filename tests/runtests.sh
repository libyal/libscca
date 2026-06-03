#!/bin/sh
# Script to run tests
#
# Version: 20260602

if test -f ${PWD}/libscca/.libs/libscca.1.dylib && test -f ./pyscca/.libs/pyscca.so
then
	install_name_tool -change /usr/local/lib/libscca.1.dylib ${PWD}/libscca/.libs/libscca.1.dylib ./pyscca/.libs/pyscca.so
fi

make check $@
RESULT=$?

if test ${RESULT} -ne 0 && test -f tests/test-suite.log
then
	cat tests/test-suite.log
fi
exit ${RESULT}

