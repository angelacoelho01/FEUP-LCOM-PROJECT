PROG=proj

SRCS = proj.c modules/video/video.c modules/keyboard/keyboard.c modules/mouse/mouse.c modules/timer/timer.c utils/utils.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
