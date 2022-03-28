# Build Instructions using Docker
Execute the following command from the project root directory `openerrorpro-engine`: 

## Debug
```shell
DOCKER_BUILDKIT=1 COMPOSE_DOCKER_CLI_BUILD=1 docker build -t openerror-pro-engine:Debug -f Dockerfile-build \
--build-arg CMAKE_BUILD_TYPE="Debug" .
```

## Release
```shell
DOCKER_BUILDKIT=1 COMPOSE_DOCKER_CLI_BUILD=1 docker build -t openerror-pro-engine:Release -f Dockerfile-build \
--build-arg CMAKE_BUILD_TYPE="Release" .
```

### Optional Build Arguments with defaults:
```dockerfile
ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug" | "Release"
ARG BUILD_DIR="/build"
ARG SRC_DIR="/src"
```

