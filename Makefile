###############################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <msmith@FreeBSD.ORG> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return
###############################################################################
#
# Makefile for building the blackbox data decoder.
#
# Invoke this with 'make help' to see the list of supported targets.
#

###############################################################################
# Things that the user might override on the commandline
#

# Compile-time options
OPTIONS		?=
BLACKBOX_VERSION     ?=

prefix ?= /usr/local

# Debugger optons, must be empty or GDB
DEBUG =

###############################################################################
# Things that need to be maintained as the source changes
#

# Working directories
ROOT		 = $(dir $(lastword $(MAKEFILE_LIST)))
SRC_DIR		 = $(ROOT)/src
OBJECT_DIR	 = $(ROOT)/obj
BIN_DIR		 = $(ROOT)/obj

# Source files common to all targets
COMMON_SRC	 = parser.c tools.c platform.c stream.c decoders.c units.c blackbox_fielddefs.c
DECODER_SRC	 = $(COMMON_SRC) blackbox_decode.c gpxwriter.c imu.c battery.c stats.c
RENDERER_SRC = $(COMMON_SRC) blackbox_render.c datapoints.c embeddedfont.c expo.c imu.c
ENCODER_TESTBED_SRC = $(COMMON_SRC) encoder_testbed.c encoder_testbed_io.c

# In some cases, %.s regarded as intermediate file, which is actually not.
# This will prevent accidental deletion of startup code.
.PRECIOUS: %.s

# Search path for decoder  sources
VPATH		:= $(SRC_DIR)

###############################################################################
# Things that might need changing to use different tools
#

#
# Tool options.
#
INCLUDE_DIRS	 = $(SRC_DIR)

ifeq ($(DEBUG),GDB)
OPTIMIZE	 = -O0
LTO_FLAGS	 = $(OPTIMIZE)
DEBUG_FLAGS	 = -g3 -ggdb
else
OPTIMIZE	 = -O3
LTO_FLAGS	 = -flto $(OPTIMIZE)
DEBUG_FLAGS =
LDFLAGS += -flto # required for clang LTO linking
endif

# Setting ARCH_FLAGS=-m32 permits building on Linux x86_64 for ia32 ..
CFLAGS		= $(ARCH_FLAGS) \
		$(LTO_FLAGS) \
		$(addprefix -D,$(OPTIONS)) \
		$(addprefix -I,$(INCLUDE_DIRS)) \
		$(if $(strip $(BLACKBOX_VERSION)), -DBLACKBOX_VERSION=$(BLACKBOX_VERSION)) \
		$(DEBUG_FLAGS) \
		-pthread \
		-Wall -pedantic -Wextra -Wshadow

# Supports native builds on
# * Linux,FreeBSD (system dynamic libraries)
# * MacOS, blackbox_render is statically linked unless MACDYN is set
#   (make MACDYN=1); in which case, you need to supply cairo and
#   freetype2 and dependencies, e.g. via `homebrew`
#   MacOS blackbox_decode can be cross-compiled on Linux.
# * Windows via mingw32 hosted on Linux

SYSTGT := $(shell $(CC) -dumpmachine)
ifneq (, $(findstring darwin, $(SYSTGT)))
 ifndef MACDYN
  RENDER_LDFLAGS = -Llib/macosx -lcairo -lpixman-1 -lpng16 -lz -lfreetype -lbz2
 else
  RENDER_LDFLAGS = `pkg-config --libs cairo` `pkg-config --libs freetype2`
 endif
else ifneq (, $(findstring mingw, $(SYSTGT)))
 RENDER_LDFLAGS = -Llib/win32/ -lcairo-2 -lfontconfig-1 -lfreetype-6 -liconv-2 -llzma-5 -lpixman-1-0 -lpng15-15 -lxml2-2 -lzlib1
else
 RENDER_LDFLAGS = `pkg-config --libs cairo` `pkg-config --libs freetype2`
endif

RENDER_CFLAGS = `pkg-config --cflags cairo` `pkg-config --cflags freetype2`
LDFLAGS += -pthread -lm

###############################################################################
# No user-serviceable parts below
###############################################################################

#
# Things we will build
#

DECODER_ELF	 = $(BIN_DIR)/blackbox_decode
RENDERER_ELF = $(BIN_DIR)/blackbox_render
ENCODER_TESTBED_ELF = $(BIN_DIR)/encoder_testbed

DECODER_OBJS	 = $(addsuffix .o,$(addprefix $(OBJECT_DIR)/,$(basename $(DECODER_SRC))))
RENDERER_OBJS	 = $(addsuffix .o,$(addprefix $(OBJECT_DIR)/,$(basename $(RENDERER_SRC))))
ENCODER_TESTBED_OBJS	 = $(addsuffix .o,$(addprefix $(OBJECT_DIR)/,$(basename $(ENCODER_TESTBED_SRC))))

TARGET_MAP   = $(OBJECT_DIR)/blackbox_decode.map

all : $(DECODER_ELF) $(RENDERER_ELF) $(ENCODER_TESTBED_ELF)

ifneq ($(BLACKBOX_VERSION),)
 $(info **INFO** Setting VERSION to $(BLACKBOX_VERSION))
else
 $(info **INFO* *Using src/version.h for VERSION)
endif


$(DECODER_ELF):  $(DECODER_OBJS)
	@$(CC) $(ARCH_FLAGS) -o $@ $^ $(LDFLAGS)

$(RENDERER_ELF):  $(RENDERER_OBJS)
	@$(CC) $(ARCH_FLAGS) -o $@ $^ $(RENDER_LDFLAGS) $(LDFLAGS)

$(ENCODER_TESTBED_ELF): $(ENCODER_TESTBED_OBJS)
	@$(CC) $(ARCH_FLAGS) -o $@ $^ $(LDFLAGS)

# Compile
$(OBJECT_DIR)/%.o: %.c version.h
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CFLAGS) $<

obj/blackbox_render.o :  blackbox_render.c
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CFLAGS) $(RENDER_CFLAGS) $<

clean:
	rm -f $(RENDERER_ELF) $(DECODER_ELF) $(ENCODER_TESTBED_ELF) $(ENCODER_TESTBED_OBJS) $(RENDERER_OBJS) $(DECODER_OBJS) $(TARGET_MAP)

help:
	@echo ""
	@echo "Makefile for the INAV blackbox data decoder"
	@echo ""
	@echo "Usage:"
	@echo "        make [OPTIONS=\"<options>\"]"
	@echo ""

install: $(DECODER_ELF) $(RENDERER_ELF)
	install -d $(prefix)/bin
	install -s -m 755  $(DECODER_ELF) $(RENDERER_ELF) $(prefix)/bin/

uninstall:
	rm -f $(prefix)/bin/blackbox_decode  $(prefix)/bin/blackbox_render
