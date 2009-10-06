##############################################################################
#--------------------------------------------------------------------------
#Copyright (c) 2009, Code Aurora Forum. All rights reserved.

#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of Code Aurora nor
#      the names of its contributors may be used to endorse or promote
#      products derived from this software without specific prior written
#      permission.

#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#--------------------------------------------------------------------------
##############################################################################

vpath %.c $(SRCDIR)/omxcore/src/$(MM_CORE_TARGET) $(SRCDIR)/omxcore/src/common
vpath %.cpp $(SRCDIR)/omxcore/src/common

CFLAGS := $(QCT_CFLAGS)
CPPFLAGS := $(QCT_CPPFLAGS)
CPPFLAGS += -I$(SRCDIR)/omxcore/inc
CPPFLAGS += -I$(SRCDIR)/omxcore/src/common
CPPFLAGS += -D_ENABLE_QC_MSG_LOG_

SRCS := qc_omx_core.c
SRCS += qc_registry_table.c
SRCS += omx_core_cmp.cpp

all: libmm-omxcore.so.$(LIBVER)

libmm-omxcore.so.$(LIBVER): $(SRCS)
	$(CC) $(CPPFLAGS) $(QCT_CFLAGS_SO) $(QCT_LDFLAGS_SO) -Wl,-soname,libmm-omxcore.so.$(LIBMAJOR) -o $@ $^ -lpthread -lrt
