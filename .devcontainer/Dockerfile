# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.241.1/containers/ubuntu/.devcontainer/base.Dockerfile

FROM devkitpro/devkitppc
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN sudo dpkg --add-architecture i386
RUN sudo apt-get update
RUN sudo apt-get install -y sudo
RUN sudo apt-get install -y python3-pip
RUN sudo apt-get install -y cmake
RUN sudo apt-get install -y ninja-build
RUN sudo apt-get install -y wget 
RUN sudo apt-get install -y lsb-release 
RUN sudo apt-get install -y software-properties-common 
RUN sudo apt-get install -y gnupg

# clang format
RUN sudo wget https://apt.llvm.org/llvm.sh
RUN sudo chmod +x llvm.sh
RUN sudo ./llvm.sh 14
RUN sudo apt install -y clang-format-14

# Install DevkitPPC
# RUN sudo ln -sf /proc/self/mounts /etc/mtab
# WORKDIR /tmp
# COPY install-devkitpro-pacman install-devkitpro-pacman
# RUN sudo chmod +x ./install-devkitpro-pacman
# RUN sudo ./install-devkitpro-pacman
# RUN sudo dkp-pacman -Syu --noconfirm
# WORKDIR /etc
# RUN sudo ln -sf /proc/self/mounts mtab
# RUN sudo dkp-pacman -S --noconfirm gamecube-dev

# Setup user
RUN groupadd --gid $USER_GID $USERNAME
RUN useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -G sudo -m $USERNAME
RUN echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME
RUN chmod 0440 /etc/sudoers.d/$USERNAME
USER vscode

RUN python3 -m pip install Pillow
