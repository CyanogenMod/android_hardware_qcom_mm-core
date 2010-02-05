vpath %.c $(SRCDIR)/omxcore/src/8250 $(SRCDIR)/omxcore/src/common
vpath %.cpp $(SRCDIR)/omxcore/src/common

CFLAGS := $(QCT_CFLAGS)
CPPFLAGS := $(QCT_CPPFLAGS)
CPPFLAGS += -I$(SRCDIR)/omxcore/inc
CPPFLAGS += -I$(SRCDIR)/omxcore/src/common
CPPFLAGS += -D_ENABLE_QC_MSG_LOG_

SRCS := qc_omx_core.c
SRCS += qc_registry_table.c
SRCS += omx_core_cmp.cpp

all: libOmxCore.so.$(LIBVER)

libOmxCore.so.$(LIBVER): $(SRCS)
	$(CC) $(CPPFLAGS) $(QCT_CFLAGS_SO) $(QCT_LDFLAGS_SO) -Wl,-soname,libOmxCore.so.$(LIBMAJOR) -o $@ $^ -lpthread -lrt
