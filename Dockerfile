FROM ubuntu:22.04 AS builder

RUN apt update -y \
    && apt upgrade -y \
    && apt install -y cmake clang git zlib1g zlib1g-dev libcurl4 libcurl4-openssl-dev \
    && mkdir -p /srv/pdf/build

COPY . /srv/pdf

RUN cd /srv/pdf/build && cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ..
RUN cd /srv/pdf/build && make pdfservice
RUN cd /srv/pdf/build && make install

FROM alpine:latest AS runtime

FROM builder AS b1
COPY /lib /lib

FROM builder AS b2
COPY /usr/local/bin /bin
