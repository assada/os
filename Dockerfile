########################
# stage 0: builder
########################
FROM ubuntu:22.04 AS builder

ARG BINUTILS_VERSION=2.44
ARG GCC_VERSION=14.2.0
ARG PREFIX=/usr/local/opt/cross
ARG TARGET=i686-elf

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential bison flex wget ca-certificates \
        libgmp3-dev libmpc-dev libmpfr-dev libisl-dev libelf-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/src
RUN wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz  && \
    wget -q https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz && \
    tar -xf binutils-${BINUTILS_VERSION}.tar.gz && \
    tar -xf gcc-${GCC_VERSION}.tar.gz

# Binutils
RUN mkdir binutils-build && \
    cd binutils-build && \
    ../binutils-${BINUTILS_VERSION}/configure          \
        --target=${TARGET} --prefix=${PREFIX}          \
        --with-sysroot --disable-nls --disable-werror  && \
    make -j$(nproc) && \
    make install-strip

# GCC
RUN mkdir gcc-build && \
    cd gcc-build && \
    ../gcc-${GCC_VERSION}/configure                    \
        --target=${TARGET} --prefix=${PREFIX}          \
        --disable-nls --disable-hosted-libstdcxx       \
        --enable-languages=c,c++ --without-headers     && \
    make all-gcc -j$(nproc)            && make install-gcc        && \
    make all-target-libgcc -j$(nproc)  && make install-strip-target-libgcc

########################
# stage 1: runtime
########################
FROM ubuntu:22.04

ARG PREFIX=/usr/local/opt/cross
ARG TARGET=i686-elf
ENV PATH=${PREFIX}/bin:$PATH

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        grub-pc-bin grub-efi-amd64-bin mtools xorriso build-essential && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder ${PREFIX} ${PREFIX}

VOLUME /var/lib/deados
WORKDIR /var/lib/deados

RUN ${TARGET}-gcc --version
