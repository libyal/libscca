#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="log2timeline/plaso";
TEST_DATA_PATH="test_data/winprefetch";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="CMD.EXE-087B4001.pf PING.EXE-B29F6629.pf TASKHOST.EXE-3AE259FC.pf WUAUCLT.EXE-830BCC14.pf";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

