#------------------------------------------------------------------------------#
# Wave propagation 
#
# Makefile ./src/tools
#------------------------------------------------------------------------------#

# Files to be removed from this directory at cleaning
CLEAN_FILES= *~

# Files to be removed from this directory at distribution cleaning
DISTCLEAN_FILES= ${CLEAN_FILES} .*sw?

# Lists of tools
PYTHON_TOOLS=`find -mindepth 1 -maxdepth 1 -name '*.py'`
SHELL_TOOLS= `find -mindepth 1 -maxdepth 1 -name '*.sh'`

# Instalation prefix
PREFIX='../../'

# Build and install
#------------------------------------------------------------------------------#

default:

install:
	@ for T in ${PYTHON_TOOLS} ; do \
	  F=${PREFIX}/bin/$${T%.py} ;   \
	  cp -v $${T} $${F} ;           \
	  chmod +x $${F} ;              \
	done
	@ for T in ${SHELL_TOOLS} ; do \
	  F=${PREFIX}/bin/$${T%.sh} ;  \
	  cp -v $${T} $${F} ;          \
	  chmod +x $${F} ;             \
	done

# Cleaning
#------------------------------------------------------------------------------#

.PHONY: clean
clean:
	-@ rm -vf ${CLEAN_FILES}

.PHONY: distclean
distclean: 
	-@ rm -vf ${DISTCLEAN_FILES}

#------------------------------------------------------------------------------#
