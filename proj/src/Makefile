PROG=proj

.PATH: ${.CURDIR}/modules/keyboard ${.CURDIR}/modules/mouse ${.CURDIR}/modules/timer ${.CURDIR}/modules/video ${.CURDIR}/utils ${.CURDIR}/modules/game ${.CURDIR}/modules/graphics

SRCS += proj.c keyboard.c mouse.c timer.c video.c utils.c game.c graphics.c

# LCOM_OPTIMIZED disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D LCOM_OPTIMIZED

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
