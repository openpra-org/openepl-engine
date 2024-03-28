# Stage builder
FROM movesrwth/storm:travis-debug as baseimage
ARG DEBIAN_FRONTEND=noninteractive

# Storm build dependencies
ENV STORM_BUILD_DEPENDENCIES build-essential git cmake libboost-all-dev libcln-dev libgmp-dev libginac-dev automake \
                             libglpk-dev libhwloc-dev libz3-dev libxerces-c-dev libeigen3-dev doxygen

# Debugging dependencies
ENV DEBUG_DEPENDENCIES gdb gdbserver ccache python3

# SSH dependencies
ENV SSH_DEPENDENCIES openssh-server sudo rsync

RUN apt update && apt install -y $STORM_BUILD_DEPENDENCIES $DEBUG_DEPENDENCIES $SSH_DEPENDENCIES

RUN mkdir /var/run/sshd && \
    echo 'root:debugger' | chpasswd && \
    echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config && \
    sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

EXPOSE 22

CMD ["/usr/sbin/sshd","-D"]
