#------------------------------------------------------------------------------#
# Wave propagation 
#
# Makefile ./src/cli
#------------------------------------------------------------------------------#

# Build and install
#------------------------------------------------------------------------------#

TARGET=cli.out

INST_DIR=../../bin

default: ${TARGET}

install: default
	cp ${TARGET} ${INST_DIR}

CFLAGS= -O2 -I../libs
LDFLAGS= -larmadillo
LIBS= ../libs/interface.o ../libs/velocity.o ../libs/_2DWave.o

${TARGET}: cli-main.cpp ../libs/_2DWave.o
	g++ ${CFLAGS} ${LDFLAGS} cli-main.cpp ${LIBS} -o ${TARGET}

../libs/_2DWave.o:
	make -C ../libs

# Cleaning
#------------------------------------------------------------------------------#

# Files to be removed from this directory at cleaning
CLEAN_FILES= *~ *.o *.a 

# Files to be removed from this directory at distribution cleaning
DISTCLEAN_FILES= ${CLEAN_FILES} .*sw?

.PHONY: clean
clean:
	-@ rm -vf ${CLEAN_FILES}


.PHONY: distclean
distclean: 
	-@ rm -vf ${DISTCLEAN_FILES}

#------------------------------------------------------------------------------#
