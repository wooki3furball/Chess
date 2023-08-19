#!/usr/bin/perl

# Author: Michael Bopp
# Filename: modock.pl
# Description: Perl script to convert between Fedora or Ubuntu container generation from a Dockerfile.
# Date Created: 08/19/23
# Last Modified: 08/19/23
# Dependency: To run on Windows use Strawberry Perl or Perl on a Unix like system including WSL (Windows Subsystem for Linux).

use strict;
use warnings;

print "Do you want to create a Fedora (F) or Ubuntu (U) Dockerfile? ";
my $response = <STDIN>;
chomp $response;

if (uc($response) eq 'F') {
    open my $fh, '>', 'Dockerfile' or die "Could not open file: $!";
    print $fh <<'EOF';
# Start from the latest Fedora image
FROM fedora:latest

# Run package updates and install packages
RUN dnf -y update \
    && dnf -y install \
    glibc-langpack-en \
    gcc \
    gcc-c++ \
    busybox \
    make \
    ncurses-devel \
    vim \
    neovim

# Set environment variables for Unicode
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Change prompt
RUN echo 'export PS1="Fedora@\\h:\\w\\$ "' >> /etc/bashrc

# Optional: Set the working directory
WORKDIR /workspace

EOF
    close $fh;
    print "Fedora Dockerfile created.\n";
}
elsif (uc($response) eq 'U') {
    open my $fh, '>', 'Dockerfile' or die "Could not open file: $!";
    print $fh <<'EOF';
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

EOF
    close $fh;
    print "Ubuntu Dockerfile created.\n";
}