TARGET= mixatron
UDP = udp
PUMP = pump
PROJECT_NAME=node
UTILS = utils

SOURCES= main.c ${UDP}/${UDP}.c ${PUMP}/${PUMP}.c ${UTILS}/${UTILS}.c

PUBDIR = $(HOME)/cmpt433/public/myApps
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L 


# -pg for supporting gprof profiling.
#CFLAGS += -pg

all: mixatron deploy node_install

mixatron:
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread -pthread 

clean:
	rm -f $(OUTDIR)/$(TARGET)
	rm -rf $(PUBDIR)/node/
	rm $(PUBDIR)/DO_NOT_EDIT-FILES_COPIED.txt
	rm $(PUBDIR)/package-lock.json

deploy:
	@echo 'COPYING THE NODE.JS FILES TO $(PUBDIR)'
	@echo ''
	mkdir -p $(PUBDIR)
	chmod a+rwx $(PUBDIR)
	cp -r node $(PUBDIR)
	@echo 'Do not edit any files in this folder; they are copied!' > $(PUBDIR)/DO_NOT_EDIT-FILES_COPIED.txt
	@echo ''
	@echo 'NOTE: On the host, in $(PUBDIR), it is best to run: npm install'
	@echo '      Or, just run the node_install target in this makefile.'

node_install:
	@echo ''
	@echo ''
	@echo 'INSTALLING REQUIRED NODE PACKAGES'
	@echo '(This may take some time)'
	@echo ''
	cd $(PUBDIR) && npm install
