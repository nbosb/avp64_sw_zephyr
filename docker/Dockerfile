 ##############################################################################
 #                                                                            #
 # Copyright (C) 2025 Nils Bosbach                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

FROM ubuntu:24.04
WORKDIR /app
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y --no-install-recommends \
    git \
    cmake \
    ninja-build \
    gperf \
    ccache \
    dfu-util \
    device-tree-compiler \
    wget \
    python3-dev \
    python3-pip \
    python3-setuptools \
    python3-tk \
    python3-venv \
    python3-wheel \
    xz-utils \
    file \
    make \
    gcc \
    gcc-multilib \
    g++-multilib \
    libsdl2-dev \
    libmagic1

WORKDIR /app

# download the minimal sdk
ENV SDK_VERSION=0.17.4
RUN echo "check-certificate = off" >> ~/.wgetrc
RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${SDK_VERSION}/zephyr-sdk-${SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && tar -xf zephyr-sdk-${SDK_VERSION}_linux-x86_64_minimal.tar.xz -C /app/ \
    && rm zephyr-sdk-${SDK_VERSION}_linux-x86_64_minimal.tar.xz
WORKDIR /app/zephyr-sdk-${SDK_VERSION}
RUN ./setup.sh -c -t aarch64-zephyr-elf

WORKDIR /app/project

ENTRYPOINT ["/app/entrypoint.sh"]
