################################################################################################################################################################
# Base Image  ###################################################################################################################################
#
# the base images contains all tools required in the platform. This is the image that must be uses for ci builds.
################################################################################################################################################################
FROM disroop/embedded-hipster-dev:0.4.0@sha256:c290e78c471f39bd82c4ded646038376210682d00a7ac9879896f8f6138794be
# see also https://hub.docker.com/u/disroop or https://github.com/disroop/DisroopConanPackages/blob/master/docker/Dockerfile

RUN apt-get update && apt-get install  --no-install-recommends -y \
    ssh=1:8.2p1-4ubuntu0.2 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
