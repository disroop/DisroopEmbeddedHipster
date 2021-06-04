################################################################################################################################################################
# Base Image  ###################################################################################################################################
#
# the base images contains all tools required in the platform. This is the image that must be uses for ci builds.
################################################################################################################################################################
FROM disroop/embedded-hipster-dev:0.6.1@sha256:f18874124d623b5db50fe282db033993bc1aff8ec3c6a131f30f78a964241f60
# see also https://hub.docker.com/u/disroop or https://github.com/disroop/DisroopConanPackages/blob/master/docker/Dockerfile

RUN apt-get update && apt-get install  --no-install-recommends -y \
    ssh=1:8.2p1-4ubuntu0.2 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
