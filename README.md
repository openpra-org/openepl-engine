# OpenErrorPro Engine
C++ implementation of the DEPM algorithm, built on the C++ [Storm](https://www.stormchecker.org) API.

1. TOC
{:toc}


# Build Instructions using Docker
Execute the following command from the project root directory `openerrorpro-engine`:

## Debug
```shell
docker build -t openerror-pro-engine:Debug -f Dockerfile-build --build-arg CMAKE_BUILD_TYPE="Debug" .
```

## Release
```shell
docker build -t openerror-pro-engine:Release -f Dockerfile-build --build-arg CMAKE_BUILD_TYPE="Release" .
```

### Optional Build Arguments with defaults:
```dockerfile
ARG MAKEFLAGS=-j$(nproc)
ARG CMAKE_BUILD_TYPE="Debug" | "Release"
ARG BUILD_DIR="/build"
ARG SRC_DIR="/src"
```

## Development
<iframe src="Docker/Dockerfile-dev" frameborder="0" allowfullscreen="true"></iframe>