 ##############################################################################
 #                                                                            #
 # Copyright (C) 2025 Nils Bosbach                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

add_subdirectory(drivers)

zephyr_syscall_include_directories(include)
zephyr_include_directories(include)
