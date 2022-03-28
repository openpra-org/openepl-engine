# Clion Docker Toolchain
Developing in Clion using the Docker Toolchain provides a consistent experience. The debugging environment is an 
ephemeral Docker container.

## Prerequisites
* Docker
* CLion

## Instructions

1. ### Build Docker image
    From the `$PROJECT_ROOT_DIR`, run the following commands in a shell:
    
    ```shell
    # Set the environment variables
    PROJECT_ROOT_DIR=$(pwd)
    DEV_IMAGE_TAG=openerrorpro-engine-debugger
    DEV_IMAGE_DOCKERFILE=$PROJECT_ROOT_DIR/Dockerfile-dev
    
    # Build the development image
    docker build --build-arg UID=$(id -u) -t $DEV_IMAGE_TAG $DEV_IMAGE_DOCKERFILE
    ```
2. ### [Create Docker Toolchain](https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html#create-docker-toolchain)
   1. Go to `Settings / Preferences | Build, Execution, Deployment | Toolchains`.
   2. Click `Add toolchain` and select `Docker`.
   3. Click the `screw nut icon` next to the `Docker` field to select a Docker image.
      1. You can also configure a `Docker server` in `Settings / Preferences | Build, Execution, Deployment | Docker` and then select it in the toolchain settings.
   4. Select the Docker Image `openerrorpro-engine-debugger` and wait until the tool detection finishes.
   5. Set the `C Compiler` to `gcc`
   6. Set the `C++ Compiler` to `g++`
   8. Then save the settings.

3. ### [Build, Run, Debug with a Docker Toolchain](https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html#build-run-debug-docker)
   1. After configuring a Docker toolchain, you can select it in `CMake profiles` or in `Makefile` settings. Alternatively, move the toolchain to the top of the list to make it default.
---
   **Note: The project folder will mounted to the Docker container and building, running, and debugging will be 
   performed in it. CLion will start the container and shut it down after the command is executed. The project folder 
   will be mounted into the `/tmp/openerrorpro-engine` directory in the container.**
--- 

## Troubleshooting
* ### [Improve Docker Toolchain performance on Windows](https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html#windows-performance)
  * To get better performance on Windows, we recommend using Docker with the WSL 2 backend.
    1. Set up `Docker Desktop` with the [WSL 2 backend](https://docs.docker.com/desktop/windows/wsl/).
    2. In the Docker desktop application, navigate to `Settings | Resources | WSL Integration` and enable integration 
    with your WSL distribution (for example, ubuntu-20.04).
    3. Place the project sources into the WSL filesystem (for example, \\wsl$\ubuntu-20.04\tmp\llvm), then open it in CLion and configure a Docker toolchain.
