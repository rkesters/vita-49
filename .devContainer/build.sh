#!/bin/sh
DOCKER_CLI_EXPERIMENTAL=enabled docker build   -t mamba/cppbase -f ./baseDockerfile .
DOCKER_CLI_EXPERIMENTAL=enabled docker build  -t  mamba/cppvcpkg -f ./vcpkDockerfile .

DOCKER_CLI_EXPERIMENTAL=enabled docker build  -t mamba/cpp -f ./Dockerfile .
