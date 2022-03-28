# Stage builder
FROM movesrwth/storm:travis-debug as baseimage
RUN apt update && apt upgrade -y

# Storm build dependencies
ENV STORM_BUILD_DEPENDENCIES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake \
                             libglpk-dev libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev

RUN apt install -y $STORM_BUILD_DEPENDENCIES

ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug"
ARG BUILD_DIR="/build"
ARG SRC_DIR="/src"

# Create working directory
RUN mkdir -p ${BUILD_DIR}
WORKDIR ${BUILD_DIR}

# Copy codebase into docker container
COPY . ${SRC_DIR}

ENV MAKEFLAGS=${MAKEFLAGS}
RUN export MAKEFLAGS=${MAKEFLAGS}

RUN cmake -B${BUILD_DIR} -H${SRC_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
                                      -DSTORM_DEVELOPER=ON \
                                      -DSTORM_USE_INTELTBB=OFF
RUN make
