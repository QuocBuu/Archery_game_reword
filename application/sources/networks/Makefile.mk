ifeq ($(IF_LINK_OPTION),-DIF_LINK_UART_EN)
include sources/networks/net/link/Makefile.mk
endif

ifeq ($(TASK_MBMASTER_OPTION),-DTASK_MBMASTER_EN)
include sources/networks/mbmaster-v2.9.6/Makefile.mk
endif
