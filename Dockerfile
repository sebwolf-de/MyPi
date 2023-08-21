FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
    bzip2 \
    cmake \
    g++ \
    gcc \
    libmpich-dev \
    && mkdir -p /usr/mypi


COPY CMakeLists.txt /usr/mypi
COPY src /usr/mypi/src

RUN cd /usr/mypi \
    && ls -la \
    && mkdir build && cd build \
    && cmake .. && make

ENTRYPOINT ["/usr/mypi/build/mypi"]

