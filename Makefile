ROOT_PATH=$(shell pwd)

SOURCE_PATH=${ROOT_PATH}/src
TEST_PATH=${ROOT_PATH}/test

BUILD_PATH=${ROOT_PATH}/build
OUTPUT_PATH=${BUILD_PATH}/zerombq
OUTPUT_TEST_PATH=${BUILD_PATH}/test

.PHONY: build
build:
	mkdir -p ${OUTPUT_PATH}
	cd ${OUTPUT_PATH} && cmake ${SOURCE_PATH} && $(MAKE)

.PHONY: test
test: build_unittests
	cd ${OUTPUT_TEST_PATH} && ctest

.PHONY: unittests
unittests: build_unittests
	cd ${OUTPUT_TEST_PATH} && ./ZeroMBQTest

.PHONY: build_unittests
build_unittests:
	mkdir -p ${OUTPUT_TEST_PATH}
	cd ${OUTPUT_TEST_PATH} && cmake ${TEST_PATH} && $(MAKE)

.PHONY: clean
clean:
	rm -rf ${BUILD_PATH}