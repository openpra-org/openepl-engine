# Stage builder
FROM movesrwth/storm:travis-debug as baseimage
RUN apt update && apt upgrade -y

# Storm build dependencies
ENV STORM_BUILD_DEPENDENCIES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake \
                             libglpk-dev libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev

RUN apt install -y $STORM_BUILD_DEPENDENCIES

# Create working directory and copy-over the src
ENV SOURCE_PATH /errorpro-engine-src
RUN mkdir -p $SOURCE_PATH/build
WORKDIR $SOURCE_PATH/build
COPY . $SOURCE_PATH

RUN cmake -DSTORM_DEVELOPER=ON -DSTORM_USE_INTELTBB=OFF ..