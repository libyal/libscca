#!/bin/sh
# Script that synchronizes the local test data

TESTS_INPUT_DIRECTORY="tests/input"
TEST_SET="public"
TEST_FILES="CMD.EXE-087B4001.pf PING.EXE-B29F6629.pf TASKHOST.EXE-3AE259FC.pf WUAUCLT.EXE-830BCC14.pf"

mkdir -p "${TESTS_INPUT_DIRECTORY}/${TEST_SET}"

for TEST_FILE in ${TEST_FILES}
do
	URL="https://raw.githubusercontent.com/log2timeline/plaso/refs/heads/main/test_data/winprefetch/${TEST_FILE}"

	curl -L -o "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL}
done
