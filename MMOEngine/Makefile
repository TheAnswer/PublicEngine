# Copyright (C) 2007 <SWGEmu>. All rights reserved.
# Distribution of this file for usage outside of Core3 is prohibited.


MACHINE_TYPE := $(shell uname -m)
DIR = 

ifeq ($(MACHINE_TYPE), x86_64)
	DIR = linux64
else
	DIR = linux32
endif
all:
	mkdir -p lib/unix
	cp -rf lib/$(DIR)/* lib/unix/
	echo java -XX:+TieredCompilation -XX:TieredStopAtLevel=1 -XX:+UseConcMarkSweepGC -XX:+CMSClassUnloadingEnabled -client -Xmx128M -cp `pwd`/bin/idlc.jar org.sr.idlc.compiler.Compiler '$$@' > bin/idlc
	chmod +x bin/idlc
	
