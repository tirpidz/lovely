FROM ubuntu:20.10

ENV DEBIAN_FRONTEND=noninteractive
ENV GCC_MAX_CONCURRENT_PROCESS=8

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
    build-essential \
    cmake \
    git \
    gcc-10 g++-9 \
    libssl-dev
