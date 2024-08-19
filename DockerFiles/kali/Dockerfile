# Get Kali and install
FROM kalilinux/kali-rolling
RUN apt-get update && apt-get upgrade -y

# Tools
RUN apt-get install -y \
    net-tools \
    iputils-ping \
    dnsutils \
    gobuster \
    nmap \
    metasploit-framework \
    john \
    hydra \
    nikto \
    sqlmap \
    aircrack-ng \
    wireshark \
    openvpn \
    nano \
    curl \
    wget \
    git \
    python3-pip \
    neofetch \
    htop

# Set the default command to start an interactive bash shell
CMD ["/bin/bash"]
