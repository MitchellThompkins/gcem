# CI build environment for gcem.
# Contains all Linux compiler variants: gcc-9/10/11/12/13 and clang-11/12/13/14/16.
#
# ubuntu:20.04 (focal) is required — Ubuntu 22.04 dropped clang-11 and clang-12
# from apt.llvm.org. The ubuntu-toolchain-r PPA provides gcc-11 through gcc-13
# on focal.
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        ca-certificates \
        gnupg \
        software-properties-common \
        wget \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor \
       > /usr/share/keyrings/llvm-archive-keyring.gpg \
    && for V in 11 12 13 14 16; do \
         echo "deb [signed-by=/usr/share/keyrings/llvm-archive-keyring.gpg] \
           http://apt.llvm.org/focal/ llvm-toolchain-focal-${V} main" \
           >> /etc/apt/sources.list.d/llvm.list; \
       done \
    && apt-get update && apt-get install -y --no-install-recommends \
        curl \
        git \
        make \
        gcc-9  g++-9  \
        gcc-10 g++-10 \
        gcc-11 g++-11 \
        gcc-12 g++-12 \
        gcc-13 g++-13 \
        clang-11 clang-12 clang-13 clang-14 clang-16 \
        lcov \
    && rm -rf /var/lib/apt/lists/*
