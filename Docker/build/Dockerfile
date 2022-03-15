FROM intel/oneapi-hpckit:latest as baseimage
RUN apt update && apt upgrade -y

ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug"
ARG BUILD_DIR="/scratch/build"
ARG SRC_DIR="/scratch"

# Create working directory
RUN mkdir -p ${BUILD_DIR}
WORKDIR ${BUILD_DIR}

# Copy codebase into docker container
COPY . /scratch

ENV MAKEFLAGS=${MAKEFLAGS}
RUN export MAKEFLAGS=${MAKEFLAGS}

RUN cmake -B${BUILD_DIR} -H${SRC_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
                                      -DCMAKE_CXX_COMPILER=icpc \
                                      -DCMAKE_C_COMPILER=icc \
                                      -DCMAKE_Fortran_COMPILER=ifort
RUN make

FROM debian:stable-slim as executor
ARG BUILD_DIR="/scratch/build"
ENV DATA_DIR="/data"
COPY --from=baseimage ${BUILD_DIR}/bin/adsidac /usr/bin/adsidac
COPY --from=baseimage ${BUILD_DIR}/bin/tpfh2onew /usr/bin/tpfh2onew
COPY --from=baseimage ${BUILD_DIR}/bin/tpfh2o /usr/bin/tpfh2o
COPY --from=baseimage ${BUILD_DIR}/bin/tpfd2o /usr/bin/tpfd2o
COPY --from=baseimage /opt/intel/oneapi/compiler/latest/linux/compiler/lib/* /usr/lib/

RUN mkdir -p $DATA_DIR && touch $DATA_DIR/not-mounted
VOLUME $DATA_DIR

COPY ./docker-entrypoint.sh /
RUN  chmod +x /docker-entrypoint.sh
ENTRYPOINT ["/docker-entrypoint.sh"]
