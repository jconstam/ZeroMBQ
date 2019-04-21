ROOT_PATH=$(shell pwd)

SOURCE_PATH=${ROOT_PATH}/src
BUILD_PATH=${ROOT_PATH}/build
TARGET_PATH=${BUILD_PATH}/zerombq
TEST_PATH=${BUILD_PATH}/test

.PHONY: build
build:
	mkdir -p ${TARGET_PATH}
	cd ${TARGET_PATH} && cmake ${SOURCE_PATH} && make

.PHONY: clean
clean:
	rm -rf ${BUILD_PATH}