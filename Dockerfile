#
# The Dockerfile to build a docker image for compiling and running C++ examples with cairomm and
# pangomm on Linux.
#

FROM ubuntu:16.04

WORKDIR /workspaces
RUN apt-get update -y

# Install basic development tools
# Note: No need to install them in production environment.
RUN apt-get install gdb -y
# RUN apt-get install vim -y
# RUN apt-get install git -y

# Install third party libraries
# Note: Installing "pangomm" will install its dependency "cairomm" as well.
RUN apt-get install pangomm-1.4 -y

# Install fonts for unicode
# TODO: There are too many fonts installed here, how do we remove the unuseful ones?
COPY resources/fonts resources/fonts/
RUN apt-get install fontconfig -y
RUN cp -r resources/fonts/* /usr/share/fonts
RUN fc-cache -f -v
RUN rm -r -f resources