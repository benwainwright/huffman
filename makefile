######################################################################
############################## Settings ##############################
######################################################################

# GCC warning flags
CFLAGS= -pedantic -Wall -Wextra -Wfloat-equal -std=c89

# GCC library flags
LIBS= -lm

# If source files are in the current dir, change to ./ on its own
SOURCEDIR=./src

# Name of the binary file to build. Ensure to suffix outputdir with a trailing slash if it is not blank
OUTPUTDIR=
OUTPUT=huffman

# Junk files to be removed via make clean
JUNK= *.gch *.c~ *.c~~ *.h~ .fuse_hidden*

# Directories to remove the above files from in make clean. Use . for the current dir
JUNKDIRS=src test .

######################################################################
######################################################################

# Generated varibles
SOURCE=$(wildcard $(SOURCEDIR)/*.c)
ZIPNAME=$(OUTPUT).zip
JUNKFILES=$(foreach JUNKDIR,$(JUNKDIRS),$(foreach JUNKFILE,$(JUNK),$(wildcard $(JUNKDIR)/$(JUNKFILE))))
JUNKSPACE=$(foreach JUNKDIR,$(JUNKDIRS),$(foreach JUNKFILE,$(JUNK),))

all:
	@make build --silent;

clean: $(JUNKFILES)
	@if [ -f ./$(OUTPUTDIR)$(OUTPUT) ]; then echo Binaries removed; rm ./$(OUTPUTDIR)$(OUTPUT) >/dev/null 2>&1; else echo No binaries to clean...; fi;
	@if [ -f ./$(ZIPNAME) ]; then echo Zip files removed...; rm ./$(ZIPNAME) >/dev/null 2>&1; else echo No zip files to clean...; fi;
ifneq ("$(JUNKFILES)","$(JUNKSPACE)")
	@rm $(JUNKFILES)
	@echo Junk files removed...
else
	@echo No junk files to clean...
endif
build: $(SOURCE)
	@make buildSource --silent

buildSource: $(SOURCE)
	@echo Cleaning house first
	@make clean --silent;
	@echo Building source...
	gcc $(SOURCE) -o $(OUTPUT) $(CFLAGS) $(LIBS) -O3
	@echo "./$(OUTPUTDIR)$(OUTPUT) built!"

debug: $(SOURCE)
	make buildDebug --silent

buildDebug: $(SOURCE)
	@echo Cleaning house first
	@make clean --silent;
	@echo Building source with -g flag
	@gcc -g $(SOURCE) -o $(OUTPUT) $(CFLAGS) $(LIBS)
	@echo "./$(OUTPUTDIR)$(OUTPUT) built!"

prepareZip:
	@make clean; zip -r $(ZIPNAME) ./ > /dev/null
	@echo Current directory packaged into $(ZIPNAME) ready for submission

prepare:
	@make prepareZip --silent;

valgrind:
	make debug;
	valgrind --leak-check=yes ./$(OUTPUT) 34words.txt < vginput.txt
