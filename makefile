# ----------------------------
# MINTCE - Linux Mint inspired desktop shell for TI-84 Plus CE
# ----------------------------

NAME = MINTCE
DESCRIPTION = "Mint-style desktop shell for arTIfiCE"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

include $(shell cedev-config --makefile)
