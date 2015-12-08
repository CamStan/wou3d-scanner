# The paths used here assume you have used the Intel Edison installer which
# installed Eclipse and the necessary tools for you
PROG   = Scanner

# choose 64 or 32 bit for your platform
WINVER = x86_64-pokysdk-mingw32
#WINVER = i686-pokysdk-mingw32

MACVER = i386-pokysdk-darwin

LINUXVER = x86_64-pokysdk-linux
#LINUXVER = i686-pokysdk-linux

# Set path to toolchain depending on OS
ifeq ($(OS),Windows_NT)
	DEVKIT_HOME = C:\Intel\iotdk-ide-win\devkit-x86\sysroots
	TOOLCHAINDIR = $(DEVKIT_HOME)\$(WINVER)\usr\bin\i586-poky-linux
	SYSDIR = $(DEVKIT_HOME)\i586-poky-linux
	MRAADIR = $(DEVKIT_HOME)\i586-poky-linux\usr\include\mraa
	UPMDIR = $(DEVKIT_HOME)\i586-poky-linux\usr\include\upm
else
	ifeq ($(shell uname), Darwin)
		DEVKIT_HOME = /Applications/iotdk-ide-mac/devkit-x86/sysroots
		TOOLCHAINDIR = $(DEVKIT_HOME)/$(MACVER)/usr/bin/i586-poky-linux
		SYSDIR = $(DEVKIT_HOME)/i586-poky-linux
		MRAADIR = $(DEVKIT_HOME)/i586-poky-linux/usr/include/mraa
		UPMDIR = $(DEVKIT_HOME)/i586-poky-linux/usr/include/upm
	else ifeq ($(shell uname), Linux)
		DEVKIT_HOME = /opt/poky-edison/1.6.1/sysroots
		TOOLCHAINDIR = $(DEVKIT_HOME)/$(LINUXVER)/usr/bin/i586-poky-linux
		SYSDIR = $(DEVKIT_HOME)/i586-poky-linux
		MRAADIR = $(DEVKIT_HOME)/i586-poky-linux/usr/include/mraa
		UPMDIR = $(DEVKIT_HOME)/i586-poky-linux/usr/include/upm
	#else
		# might need other case here for other versions of unix
	endif
endif

CC     = $(TOOLCHAINDIR)/i586-poky-linux-g++
LD     = $(TOOLCHAINDIR)/i586-poky-linux-g++
# Compiler flags go here, including include (-I) directives
CFLAGS = -g3 -O0 -Wall -c -fmessage-length=0 \
		 -I$(MRAADIR) -I$(UPMDIR) \
		 --sysroot=$(SYSDIR) -m32 -march=i586 -ffunction-sections -fdata-sections

# Linker flags
LDFLAGS = -lm --sysroot=$(SYSDIR) -lmraa -lrt -pthread

RM = rm -f

SRCDIR = src
OBJDIR = build
BINDIR = bin

# find all source files, object file names
SRCS_C    := $(shell find $(SRCDIR) -name '*.c')
SRCS_CPP  := $(shell find $(SRCDIR) -name '*.cpp')
SRCS_ALL = $(SRCS_C) $(SRCS_CPP)
SRCDIRS  = src
#:= $(shell find . -name '*.cpp' -exec dirname {} \; | uniq)
OBJS    := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_CPP))
OBJS    += $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_C))

# silently create needed directories when compiling files in src
# (see: http://stackoverflow.com/questions/1950926/create-directories-using-make-file)
dir_guard=@mkdir -p $(@D)

# Doxygen command
DOXYGEN=doxygen
DOXYGEN_SCRIPT=Doxyfile

# top-level rule, to compile everything.
all: $(PROG)

info:
	@echo $(SRCS_ALL)
	@echo $(SRCDIRS)
	@echo $(OBJS)
	@echo $(DEVKIT_HOME)
	@echo $(CC)
	@echo $(LD)
	@echo $(OS)

# build Doxygen documentation
docs: Doxyfile $(PROG)
	$(DOXYGEN) $(DOXYGEN_SCRIPT)

# rule to link the program
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(BINDIR)/$(PROG)

# meta-rule for compiling any "C" source file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

# meta-rule for compiling any "C++" source file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

# rule for cleaning re-compilable files
clean:
	$(RM) $(OBJS) $(BINDIR)/$(PROG)

# resolve dependencies using compiler flag MM
depend: .depend

.depend: $(SRCS_ALL)
	$(RM) .depend
	$(CC) $(CFLAGS) -MM $^ -MF  .depend;

include .depend
