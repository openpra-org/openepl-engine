# Build Instructions using Docker
Execute the following command from the project root directory `ads-idac-engine`: 

## Debug
```shell
DOCKER_BUILDKIT=1 COMPOSE_DOCKER_CLI_BUILD=1 docker build -t ads-idac-engine:debug -f Docker/build/Dockerfile \
--build-arg CMAKE_BUILD_TYPE="Debug" .
```

## Release
```shell
DOCKER_BUILDKIT=1 COMPOSE_DOCKER_CLI_BUILD=1 docker build -t ads-idac-engine:release -f Docker/build/Dockerfile \
--build-arg CMAKE_BUILD_TYPE="Release" .
```

### Optional Build Arguments with defaults:
```dockerfile
ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug" | "Release"
ARG BUILD_DIR="/scratch/build"
ARG SRC_DIR="/scratch"
```

# Run Instructions using Docker, with Volume Mount
In it's current stage, `adsidac` requires input files to be provided in the project directory. This is a pain, and will
be changed in the near future. However, in order to run `adsidac` with relative ease, we have provided a volume mount
option on the `/data` directory. Here is how you use it:

Using a build variant of your choice, run the volume-mounted container like so:
```shell
   docker run -v "$(pwd)/tests/BV_Indeck_ADS_OSU_scenario_4:/data" --rm -it ads-idac-engine:release
```

