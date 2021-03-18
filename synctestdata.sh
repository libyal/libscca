#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20161009

TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="CMD.EXE-087B4001.pf PING.EXE-B29F6629.pf TASKHOST.EXE-3AE259FC.pf WUAUCLT.EXE-830BCC14.pf";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://github.com/log2timeline/plaso/blob/main/test_data/${TEST_FILE}?raw=true";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

