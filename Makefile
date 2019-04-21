ROOT_PATH=$(shell pwd)

SOURCE_PATH=${ROOT_PATH}/src
UNITTEST_PATH=${ROOT_PATH}/test/unittests

BUILD_PATH=${ROOT_PATH}/build
OUTPUT_PATH=${BUILD_PATH}/zerombq
OUTPUT_UNITTEST_PATH=${BUILD_PATH}/unittests

.PHONY: build
build:
	mkdir -p ${OUTPUT_PATH}
	cd ${OUTPUT_PATH} && cmake ${SOURCE_PATH} && $(MAKE)

.PHONY: test
test: unittests

.PHONY: unittests
unittests:
	mkdir -p ${OUTPUT_UNITTEST_PATH}
	cd ${OUTPUT_UNITTEST_PATH} && cmake ${UNITTEST_PATH} && $(MAKE) && ctest

.PHONY: clean
clean:
	rm -rf ${BUILD_PATH}