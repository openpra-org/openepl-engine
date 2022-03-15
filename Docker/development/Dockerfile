FROM debian:stable-slim as baseimage
RUN apt update && apt upgrade -y

# Storm build dependencies
ENV STORM_BUILD_DEPENDENCIES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake \
                             libglpk-dev libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev

RUN apt install $STORM_BUILD_DEPENDENCIES

ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash debugger
USER debugger