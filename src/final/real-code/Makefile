#------------------------------------------------------------------------------#
# Wave propagation 
#
# Makefile ./
#------------------------------------------------------------------------------#

DIST_DIR=serial-code-lad

# Build and install
#------------------------------------------------------------------------------#

default:
	make -C src

install:
	make -C src install

# Cleaning
#------------------------------------------------------------------------------#

# List of all subderectories
SUBDIRS=`find -mindepth 1 -maxdepth 1 -type d -not -name ${DIST_DIR}`

# Files to be removed from this directory at cleaning
CLEAN_FILES= *~

# Files to be removed from this directory at distribution cleaning
DISTCLEAN_FILES= ${CLEAN_FILES} .*.sw?

.PHONY: clean
clean:
	-@ rm -vf  ${CLEAN_FILES}
	-@ rm -rvf ${DIST_DIR} 
	-@ for D in ${SUBDIRS} ; do   \
	  make -C $$D clean ;      \
	done

.PHONY: distclean
distclean: 
	-@ rm -vf ${DISTCLEAN_FILES}
	-@ rm -rvf ${DIST_DIR} 
	-@ for D in ${SUBDIRS}; do        \
	  make -C $$D distclean ;      \
	done

# Distribution
#------------------------------------------------------------------------------#

DIST_DATE=`date +'%Y%m%d'`
DIST_ZIP=${DIST_DIR}-${DIST_DATE}.zip

DIST_FILES=bin src tests Makefile README.md

.PHONY: dist
dist: distclean
	mkdir -p ${DIST_DIR}
	cp -r ${DIST_FILES} ${DIST_DIR}
	zip -r9 ${DIST_ZIP} ${DIST_DIR}

#------------------------------------------------------------------------------#
