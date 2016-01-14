CC = g++
EXECUTABLE = compiler
BUILD_DIR = build
SRC_DIR = src
CXXFLAGS = -Wall -std=c++11 -I${SRC_DIR}

_OBJS = interpreter.o cradle.o io.o main.o
OBJS = $(patsubst %, ${BUILD_DIR}/%, ${_OBJS})

_DEPS = interpreter.h cradle.h reporter.h input.h output.h
DEPS = $(patsubst %, ${SRC_DIR}/%, ${_DEPS})

.PHONY: all

all: run

compile: ${EXECUTABLE}

${EXECUTABLE}: ${OBJS}
	${CC} -o $@ $^ ${CXXFLAGS}

${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp ${DEPS} ${BUILD_DIR}
	${CC} -c -o $@ $< ${CXXFLAGS}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

run: ${EXECUTABLE}
	-./${EXECUTABLE}

.PHONY: clean

clean:
	-rm -r ${BUILD_DIR} ${EXECUTABLE}
