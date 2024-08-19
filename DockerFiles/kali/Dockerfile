# Get Kali and install updates
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

# Add the rockyou.txt wordlist
RUN apt-get install -y wordlists && \
    gunzip /usr/share/wordlists/rockyou.txt.gz

# Set the default command
CMD ["/bin/bash"]
