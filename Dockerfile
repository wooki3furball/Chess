# Start from the latest Ubuntu image
FROM ubuntu:latest

# Set environment variables to non-interactive (this prevents some prompts)
ENV DEBIAN_FRONTEND=noninteractive

# Run package updates and install packages
RUN apt-get update \
    && apt-get install -y \
    locales \
    gcc \
    g++ \
    busybox \
    make \
    libncurses5-dev \
    libncursesw5-dev \
    vim \
    neovim

# Generate en_US.UTF-8 locale
RUN locale-gen en_US.UTF-8

# Set environment variables for Unicode
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Change prompt, this isn't working like a normal prompt update.
RUN echo 'export PS1="Ubuntu@\h:\w\$ "' >> /etc/bash.bashrc

# Optional: Set the working directory
WORKDIR /workspace

