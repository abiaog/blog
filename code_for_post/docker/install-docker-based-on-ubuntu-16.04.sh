#!/bin/bash
# refer to https://docs.docker.com/engine/installation/linux/docker-ce/ubuntu/#install-using-the-repository

set -x # for debug

# Uninstall old versions
sudo apt-get remove docker docker-engine docker.io

# Install Docker CE --- Install using the repository

# SET UP THE REPOSITORY

## Update the apt package index:

sudo apt-get update

sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    software-properties-common



## Add Docker’s official GPG key:

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -


# Verify that you now have the key with the fingerprint 9DC8 5822 9FC7 DD38 854A E2D8 8D81 803C 0EBF CD88, by searching for the last 8 characters of the fingerprint.
sudo apt-key fingerprint 0EBFCD88



## For amd64 architecture
sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"



## INSTALL DOCKER CE

### Update the apt package index.

sudo apt-get update

## Install the latest version of Docker CE, or go to the next step to install a specific version. Any existing installation of Docker is replaced.

sudo apt-get install docker-ce


## Verify that Docker CE is installed correctly by running the hello-world image.

sudo docker run hello-world


#### Output ####
#### peter@peter-VirtualBox:~/work/src$ sudo docker run hello-world
#### Unable to find image 'hello-world:latest' locally
#### latest: Pulling from library/hello-world
#### 5b0f327be733: Pull complete
#### Digest: sha256:1f1404e9ea1a6665e3664626c5d2cda76cf90a4df50cfee16aab1a78f58a3f95
#### Status: Downloaded newer image for hello-world:latest
#### 
#### Hello from Docker!
#### This message shows that your installation appears to be working correctly.
#### 
#### To generate this message, Docker took the following steps:
####  1. The Docker client contacted the Docker daemon.
####  2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
####  3. The Docker daemon created a new container from that image which runs the
####     executable that produces the output you are currently reading.
####  4. The Docker daemon streamed that output to the Docker client, which sent it
####     to your terminal.
#### 
#### To try something more ambitious, you can run an Ubuntu container with:
####  $ docker run -it ubuntu bash
#### 
#### Share images, automate workflows, and more with a free Docker ID:
####  https://cloud.docker.com/
#### 
#### For more examples and ideas, visit:
####  https://docs.docker.com/engine/userguide/





