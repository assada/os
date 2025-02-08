FROM ubuntu:22.04

ARG BINUTILS_VERSION=2.44
ARG GCC_VERSION=14.2.0

RUN apt-get update && apt-get install -y \
                              build-essential \
                              bison \
                              flex \
                              grub-pc-bin \
                              grub-efi-amd64-bin \
                              mtools qemu-system-x86 \
                              grub2 \
                              libgmp3-dev \
                              libmpc-dev \
                              libmpfr-dev \
                              libisl-dev \
                              libelf-dev \
                              wget

# Set environment variables
ENV PREFIX=/usr/local/opt/cross
ENV TARGET=i686-elf
ENV PATH="$PREFIX/bin:$PATH"

# Create build directory
WORKDIR /build

# Download and extract sources
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz && \
    wget https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz && \
    tar -xzf binutils-${BINUTILS_VERSION}.tar.gz && \
    tar -xzf gcc-${GCC_VERSION}.tar.gz

RUN mkdir -p $PREFIX

# Build Binutils
RUN mkdir binutils-build && \
    cd binutils-build && \
    ../binutils-${BINUTILS_VERSION}/configure --target=${TARGET} --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
    make && \
    make install

# Build GCC
RUN mkdir gcc-build && \
    cd gcc-build && \
    ../gcc-${GCC_VERSION}/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx && \
    make all-gcc && \
    make all-target-libgcc && \
    make install-gcc && \
    make install-target-libgcc

# Clean up
RUN rm -rf /build

# Check if the installation is successful
RUN $PREFIX/bin/$TARGET-gcc --version

RUN apt-get install -y xorriso

VOLUME /var/lib/deados

WORKDIR /var/lib/deados
