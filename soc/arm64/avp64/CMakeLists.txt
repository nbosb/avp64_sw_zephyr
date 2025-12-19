 ##############################################################################
 #                                                                            #
 # Copyright (C) 2025 Nils Bosbach                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

zephyr_library_sources_ifdef(CONFIG_ARM_MMU mmu_regions.c)
zephyr_library_sources(soc.c)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm64/scripts/linker.ld CACHE INTERNAL "")
