# Stage builder
FROM movesrwth/storm:travis-debug as base

ENV DEBIAN_FRONTEND=noninteractive
# Storm build dependencies
ENV BUILD_PACKAGES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake libglpk-dev \
                   libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev doxygen doxygen-doc graphviz

RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    apt update && \
    apt install -y --no-install-recommends $BUILD_PACKAGES

FROM base AS debugger
ENV DEBUGGER_PACKAGES gdb linux-tools-generic systemtap-sdt-dev gdb gdbserver ccache python3
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    rm -f /etc/apt/apt.conf.d/docker-clean && \
    apt install -y --no-install-recommends $DEBUGGER_PACKAGES

#RUN echo kernel.perf_event_paranoid=1 >> /etc/sysctl.d/99-perf.conf && \
#    echo kernel.kptr_restrict=0 >> /etc/sysctl.d/99-perf.conf && \
#    sysctl --system
#
#RUN rm /usr/bin/perf && \
#    ln -s /usr/lib/linux-tools/5.19.0-46-generic/perf /usr/bin/perf

ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash debugger
USER debugger
ENTRYPOINT ["/bin/bash"]

FROM base AS binary
ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug"
ARG BUILD_DIR="/build"
ARG SRC_DIR="/source"

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
