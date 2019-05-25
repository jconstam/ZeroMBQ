TRAVIS_BUILD_NUMBER ?= 0

ROOT_PATH=$(shell pwd)

SOURCE_PATH=${ROOT_PATH}/src
INCLUDE_PATH=${ROOT_PATH}/include
TEST_PATH=${ROOT_PATH}/test

BUILD_PATH=${ROOT_PATH}/build
OUTPUT_PATH=${BUILD_PATH}/zerombq
OUTPUT_TEST_PATH=${BUILD_PATH}/test
OUTPUT_UNITTEST_PATH=${OUTPUT_TEST_PATH}/unittests
OUTPUT_DOXYGEN_PATH=${BUILD_PATH}/doxygen

DOXYFILE_PATH=${ROOT_PATH}/doc/doxygen/doxyfile

.PHONY: build
build:
	mkdir -p ${OUTPUT_PATH}
	cd ${OUTPUT_PATH} && cmake ${SOURCE_PATH} && $(MAKE) $(MAKEFLAGS)

.PHONY: test
test: build_unittests
	cd ${OUTPUT_TEST_PATH} && ctest --output-on-failure

.PHONY: unittests
unittests: build_unittests
	cd ${OUTPUT_UNITTEST_PATH} && ./ZeroMBQTest

.PHONY: build_unittests
build_unittests:
	mkdir -p ${OUTPUT_TEST_PATH}
	cd ${OUTPUT_TEST_PATH} && cmake ${TEST_PATH} && $(MAKE) $(MAKEFLAGS)

.PHONY: clean
clean:
	rm -rf ${BUILD_PATH}

.PHONY: doxygen
doxygen:
	mkdir -p ${OUTPUT_DOXYGEN_PATH}
	cd ${OUTPUT_DOXYGEN_PATH} && ( cat ${DOXYFILE_PATH} ; echo "INPUT=${SOURCE_PATH} ${INCLUDE_PATH} ${DOXYFILE_PATH}"; echo "PROJECT_NUMBER=${TRAVIS_BUILD_NUMBER}" ) | doxygen -