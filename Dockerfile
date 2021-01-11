FROM ubuntu:20.10 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV GCC_MAX_CONCURRENT_PROCESS=8
ENV LOVELY_BUILD_DIR=/usr/local/lovely
ENV LOVELY_INSTALL_DIR=/lovely
ENV LOVELY_SOURCE_DIR=/usr/src/lovely

RUN mkdir -p ${LOVELY_BUILD_DIR} ${LOVELY_INSTALL_DIR} ${LOVELY_SOURCE_DIR}

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
    build-essential \
    cmake \
    git \
    gcc-8 g++-8 \
    libssl-dev

COPY . ${LOVELY_SOURCE_DIR}

WORKDIR ${LOVELY_BUILD_DIR}
RUN cmake -DCMAKE_INSTALL_PREFIX:PATH=${LOVELY_INSTALL_DIR} ${LOVELY_SOURCE_DIR}
RUN cmake --build ${LOVELY_BUILD_DIR} --target install -- -j ${GCC_MAX_CONCURRENT_PROCESS} 

FROM ubuntu:20.10

ENV DEBIAN_FRONTEND=noninteractive
ENV LOVELY_INSTALL_DIR=/lovely

COPY --from=builder ${LOVELY_INSTALL_DIR} ${LOVELY_INSTALL_DIR}
ENTRYPOINT ["lovely/bin/main"]