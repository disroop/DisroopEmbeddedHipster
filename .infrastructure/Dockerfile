################################################################################################################################################################
# Base Image  ###################################################################################################################################
#
# the base images contains all tools required in the platform. This is the image that must be uses for ci builds.
################################################################################################################################################################
FROM ubuntu:20.04@sha256:bc2f7250f69267c9c6b66d7b6a81a54d3878bb85f1ebb5f951c896d13e6ba537 AS base
ENV DEBIAN_FRONTEND=noninteractive
#
#Install C++ tools
RUN apt-get update && apt-get install --no-install-recommends -y \
    python3=3.8.2-0ubuntu2 \
    python3-pip=20.0.2-5ubuntu1.4 \
    clang-10=1:10.0.0-4ubuntu1 \
    clang-format-10=1:10.0.0-4ubuntu1 \
    cmake=3.16.3-1ubuntu1\
    git=1:2.25.1-1ubuntu3 \
    make=4.2.1-1.2 \
    graphviz=2.42.2-3build2 \
    doxygen=1.8.17-0ubuntu2 \
    wget=1.20.3-1ubuntu1 \ 
    ssh=1:8.2p1-4ubuntu0.2 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
#
#Remove python it is depreacted
RUN ln -s /usr/bin/python3 /usr/bin/python
#
#Set Clang-10 as default clangg
RUN ln -s /usr/bin/clang++-10 /usr/bin/clang++ \
   && ln -s /usr/bin/clang-10 /usr/bin/clang \
   && ln -s /usr/bin/clang-format-10 /usr/bin/clang-format
#
# Install arm-none-eabi-gcc toolchain
ARG TOOLCHAIN_TARBALL_URL="https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2?revision=05382cca-1721-44e1-ae19-1e7c3dc96118&la=en&hash=D7C9D18FCA2DD9F894FD9F3C3DC9228498FA281A"
ARG TOOLCHAIN_PATH=/opt/toolchain-arm
RUN mkdir -p ${TOOLCHAIN_PATH}
RUN wget ${TOOLCHAIN_TARBALL_URL} \
	&& export TOOLCHAIN_TARBALL_FILENAME=$(basename "${TOOLCHAIN_TARBALL_URL}") \
	&& tar -xvjf ${TOOLCHAIN_TARBALL_FILENAME} -C ${TOOLCHAIN_PATH} \
	&& rm -rf ${TOOLCHAIN_PATH}/share/doc \
	&& rm ${TOOLCHAIN_TARBALL_FILENAME}
#
# Install Conan
RUN pip3 install -Iv conan==1.30.0
RUN pip3 install -Iv python-dotenv==0.15.0
#
# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*
####################
############################################################################################################################################
# Build Image  #############################################################################################################################
#
# The build is the image that must be uses for ci builds.
############################################################################################################################################
FROM base AS build
ARG USERNAME=ci-dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME
#
#Change to ci-dev user
USER ${USERNAME}
#
# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog
#
#do no change anything else here!! the build images shal just be the base image with a entrypoint
ENTRYPOINT ["python", "build.py"]

##################################################################################################################################################
# Dev Build Environment Image for Development ####################################################################################################
##################################################################################################################################################
FROM base AS development
ENV DEBIAN_FRONTEND=noninteractive
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID
#
#Install specific devtools
RUN apt-get update && apt-get install --no-install-recommends -y \
    vim=2:8.1.2269-1ubuntu5 \
    sudo=1.8.31-1ubuntu1.2\
    gdb=9.2-0ubuntu1~20.04 \
    clangd-10=1:10.0.0-4ubuntu1 \
    libncurses5 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* 
#AddJlink Debugger
ARG TMP_JLINK_TGZ=/tmp
ARG TAR_NAME=JLink_Linux_x86_64.tgz
ARG FOLDER_JLINK=/opt/segger_jlink_v692
RUN wget https://www.segger.com/downloads/jlink/${TAR_NAME} --directory-prefix=$TMP_JLINK_TGZ --post-data="accept_license_agreement=accepted"
RUN mkdir ${FOLDER_JLINK} && tar -xzvf $TMP_JLINK_TGZ/$TAR_NAME -C ${FOLDER_JLINK} --strip 1
RUN ls /opt/segger_jlink_v692
RUN rm ${FOLDER_JLINK}/JLinkConfigExe
RUN rm ${FOLDER_JLINK}/JLinkGDBServerExe
RUN rm ${FOLDER_JLINK}/JLinkGUIServerExe
RUN rm ${FOLDER_JLINK}/JLinkRemoteServer
RUN rm ${FOLDER_JLINK}/JLinkRemoteServerCLExe
RUN rm ${FOLDER_JLINK}/JLinkRemoteServerExe
RUN rm ${FOLDER_JLINK}/JLinkRTTViewerExe
RUN rm ${FOLDER_JLINK}/JLinkSWOViewerExe
RUN rm ${FOLDER_JLINK}/JLinkRegistration
RUN rm ${FOLDER_JLINK}/JLinkRegistrationExe
RUN rm ${FOLDER_JLINK}/JLinkLicenseManager
RUN rm ${FOLDER_JLINK}/JLinkLicenseManagerExe
RUN rm -rf ${FOLDER_JLINK}/Samples
ENV PATH="${FOLDER_JLINK}:${PATH}"

#
# Set Clangd-10 as default clangd
RUN ln -s /usr/bin/clangd-10 /usr/bin/clangd
#
# Install Pylint
RUN pip3 install pylint==2.6.0
#
# Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user.
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME
#
# Add sudo support for the non-root user
RUN apt-get install --no-install-recommends -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME
# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*
#Switch back to dialog
ENV DEBIAN_FRONTEND=dialog