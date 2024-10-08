#
# Copyright (c) 2016 Nest Labs, Inc.
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/ipc-dbus \
	-I$(top_srcdir)/src/util \
	-I$(top_srcdir)/src/wpantund \
	-I$(top_srcdir)/third_party/fgetln \
	-I$(top_srcdir)/third_party/assert-macros \
	$(NULL)

include $(top_srcdir)/pre.am

DISTCLEANFILES = .deps Makefile

if !ENABLE_FUZZ_TARGETS
bin_PROGRAMS = wpanctl
endif

wpanctl_SOURCES = \
	wpanctl.c \
	wpanctl-cmds.h \
	../util/config-file.c \
	../util/string-utils.c \
	../wpantund/wpan-error.c \
	wpanctl-utils.c \
	commissioner-utils.c \
	tool-cmd-scan.c \
	tool-cmd-join.c \
	tool-cmd-form.c \
	tool-cmd-mfg.c \
	tool-cmd-leave.c \
	tool-cmd-permit-join.c \
	tool-cmd-linkmetrics.c \
	tool-cmd-mlr.c \
	tool-cmd-bbr.c \
	tool-cmd-list.c \
	tool-cmd-status.c \
	tool-cmd-resume.c \
	tool-cmd-reset.c \
	tool-cmd-getprop.c \
	tool-cmd-setprop.c \
	tool-cmd-insertprop.c \
	tool-cmd-removeprop.c \
	tool-cmd-begin-low-power.c \
	tool-cmd-begin-net-wake.c \
	tool-cmd-cd.c \
	tool-cmd-poll.c \
	tool-cmd-config-gateway.c \
	tool-cmd-add-prefix.c \
	tool-cmd-remove-prefix.c \
	tool-cmd-host-did-wake.c \
	tool-cmd-add-route.c \
	tool-cmd-remove-route.c \
	tool-updateprop.c \
	wpanctl-utils.h \
	commissioner-utils.h \
	tool-cmd-scan.h \
	tool-cmd-join.h \
	tool-cmd-form.h \
	tool-cmd-leave.h \
	tool-cmd-mfg.h \
	tool-cmd-permit-join.h \
	tool-cmd-linkmetrics.h \
	tool-cmd-mlr.h \
	tool-cmd-bbr.h \
	tool-cmd-list.h \
	tool-cmd-status.h \
	tool-cmd-resume.h \
	tool-cmd-reset.h \
	tool-cmd-getprop.h \
	tool-cmd-setprop.h \
	tool-cmd-insertprop.h \
	tool-cmd-removeprop.h \
	tool-cmd-begin-low-power.h \
	tool-cmd-begin-net-wake.h \
	tool-cmd-cd.h \
	tool-cmd-poll.h \
	tool-cmd-config-gateway.h \
	tool-cmd-add-prefix.h \
	tool-cmd-remove-prefix.h \
	tool-cmd-host-did-wake.h \
	tool-cmd-add-route.h \
	tool-cmd-remove-route.h \
	tool-cmd-pcap.h \
	tool-cmd-pcap.c \
	tool-cmd-peek.h \
	tool-cmd-peek.c \
	tool-cmd-poke.h \
	tool-cmd-poke.c \
	tool-cmd-commr.h \
	tool-cmd-commr.c \
	tool-cmd-commissioner.h \
	tool-cmd-commissioner.c \
	tool-cmd-joiner.h \
	tool-cmd-joiner.c \
	tool-cmd-dataset.h \
	tool-cmd-dataset.c \
	tool-cmd-add-service.h \
	tool-cmd-add-service.c \
	tool-cmd-remove-service.h \
	tool-cmd-remove-service.c \
	tool-updateprop.h \
	tool-cmd-request-sleep.h \
	tool-cmd-request-sleep.c \
	$(NULL)

wpanctl_LDADD = \
	$(DBUS_LIBS) \
	$(LIBREADLINE_LIBS) \
	$(NULL)

wpanctl_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(DBUS_CFLAGS) \
	$(LIBREADLINE_CPPFLAGS) \
	$(NULL)


SOURCE_VERSION=$(shell git describe --dirty --always --match "[0-9].*" 2> /dev/null)
BUILT_SOURCES  = $(top_builddir)/$(subdir)/version.c
CLEANFILES = $(top_builddir)/$(subdir)/version.c
.INTERMEDIATE: wpanctl-version.$(OBJEXT)
$(top_builddir)/$(subdir)/version.c: ../version.c.in Makefile
	sed 's/SOURCE_VERSION/"$(SOURCE_VERSION)"/' < $< > $@
wpanctl_SOURCES += $(top_builddir)/$(subdir)/version.c
