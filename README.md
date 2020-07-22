# POC for using cairomm and pangomm in docker

This contains some C++ example programs that uses cairomm and pangomm and run in a Linux docker image.

# Build and run
## Mac
### Build and run docker image
Run the Dockerfile to build the docker image so that we can compile and run the C++ examples in it.
```
docker build --tag image-lib-poc:1.0 .

docker run -it --name image-lib-poc-test03 -v /path/to/your-local-folder:/path/to/folder-of-this-repo image-lib-poc:1.0 /bin/bash
```

Here are some examples to run the image in docker:
```
docker run -it --name image-lib-poc-test03 -v /users/<user>/examples/pangomm:/home/pangomm image-lib-poc:1.0 /bin/bash

docker run -it --name image-lib-poc-test04 -v /Users/wuzhanglin/Sources/POC/image-lib-on-docker-poc:/home/pangomm image-lib-poc:3.0 /bin/bash
```

### Install libraries for navigating through third party sources
Install the dependencies using brew so that we can navigate through source code of third party libraries.
```
brew install pangomm
brew install pkgconfig
```