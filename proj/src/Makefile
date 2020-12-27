PROG=proj

.PATH: ${.CURDIR}/modules/keyboard ${.CURDIR}/modules/mouse ${.CURDIR}/modules/timer ${.CURDIR}/modules/video ${.CURDIR}/utils ${.CURDIR}/modules/game ${.CURDIR}/modules/graphics ${.CURDIR}/modules/game/player ${.CURDIR}/modules/game/collision ${.CURDIR}/modules/graphics/plataform ${.CURDIR}/modules/graphics/numbers ${.CURDIR}/modules/graphics/labels ${.CURDIR}/modules/graphics/hearts ${.CURDIR}/modules/graphics/blocks ${.CURDIR}/modules/graphics/ball ${.CURDIR}/modules/graphics/clock ${.CURDIR}/modules/graphics/menus ${.CURDIR}/xpm

SRCS += proj.c keyboard.c mouse.c timer.c video.c utils.c game.c graphics.c player.c collision.c graphics_plataform.c graphics_numbers.c graphics_labels.c graphics_hearts.c graphics_blocks.c graphics_ball.c graphics_clock.c graphics_menus.c load_xpms.c

# LCOM_OPTIMIZED disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D LCOM_OPTIMIZED

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
