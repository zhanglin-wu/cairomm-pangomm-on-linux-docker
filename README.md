# POC for using cairomm and pangomm in docker

This contains some C++ example programs that uses cairomm and pangomm and run in a Linux docker image.

# Build and run
## Mac
### Build and run docker image
Run the Dockerfile to build the docker image so that we can compile and run the C++ examples in it.
```
docker build --tag image-lib-docker-poc:1.0 .

docker run -it --name image-lib-docker-poc-test -v /path/to/your-local-folder:/path/to/folder-in-docker-image image-lib-docker-poc:1.0 /bin/bash
```

Here are some examples to run the image in docker:
```
docker run -it --name image-lib-docker-poc-test03 -v /users/<user>/image-lib-docker-poc:/home/image-lib-docker-poc image-lib-docker-poc:1.0 /bin/bash

docker run -it --name image-lib-docker-poc-test04 -v /Users/wuzhanglin/Sources/POC/image-lib-on-docker-poc:/home/image-lib-docker-poc image-lib-poc:3.0 /bin/bash
```

### Install libraries for navigating through third party sources
Install the dependencies using brew so that we can navigate through source code of third party libraries.
```
brew install pangomm
brew install pkgconfig
```

### Build and run C++ examples
```
cd /home/image-lib-docker-poc/examples/pangomm
mkdir build
cd build

g++ -g -Wall -o measure-text-pdf `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../measure-text-pdf.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4`

./measure-text-pdf "../measure-text-pdf-test-data.txt"
```