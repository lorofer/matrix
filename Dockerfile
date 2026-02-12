FROM mcr.microsoft.com/devcontainers/base:debian

RUN apt-get update && apt-get install -y \
    gcc \
    pkg-config \
    check \
    valgrind \
    cmake \
    clang-format