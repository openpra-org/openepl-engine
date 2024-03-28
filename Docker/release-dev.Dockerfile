# Stage builder
FROM movesrwth/storm:travis as baseimage
RUN apt update && apt upgrade -y

# Storm build dependencies
ENV STORM_BUILD_DEPENDENCIES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake \
                             libglpk-dev libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev doxygen

# Debugging dependencies
ENV DEBUG_DEPENDENCIES gdb gdbserver ccache python3

RUN apt install -y $STORM_BUILD_DEPENDENCIES $DEBUG_DEPENDENCIES

ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash debugger
USER debugger
