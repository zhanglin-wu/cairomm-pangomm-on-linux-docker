# POC for Using Cairomm and Pangomm in Docker

This contains some C++ example programs that use cairomm and pangomm. These programs run in a Linux docker image.

## What does the examples do?

1. Cairomm examples can render circle, line, and reactagle into png and svg, and PDF.
2. Pangomm examples can render unicode text like Latin letters, Chinese, Japanese, Emoji, and measure pixel size of text.

## Build and run

### Mac

#### Use VS Code to build and debug C++ program in docker

##### Prerequisites

- [Docker](https://docs.docker.com/get-docker/)
- [Visual Studio Code](https://code.visualstudio.com/)

- [VS Code Extension: Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers), for connecting with a docker container
- [VS Code Extension: C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools), for editing and debugging C++ code

##### Build and debug C++ program in docker

1. In VS Code, go to "View > Command Palette...", enter "Remote-Containers: OpenFolder in Container..." and execute the command.
2. Navigate to the folder of this repository in your local disk, and open it.
3. Now wait for VS Code to finish building the docker image, it will take a while. (Note if VS Code asks about how to build the docker image, just choose to use the Dockerfile.)
4. Go to "View > Extentions" to install the "C/C++" extention in the docker container by clicking the "Install in Dev Container: Existing Dockerfile" button. We must reload VS Code after installing this extention, we can just click the "Reload Required" button.
5. Go to "View > Terminal" to open the Terminal, and use the commands from section "[Build and run C++ examples in docker](https://github.com/zhanglin-wu/image-lib-on-docker-poc#build-and-run-c-examples-in-docker)" to build the program.
6. Go to "View > Run" to open the debugger, select "measure-text-pdf", and then launch the program to start debugging.

#### Optional: Use Terminal to build and run C++ program in docker

##### Build and run docker image

Run the Dockerfile to build the docker image so that we can compile and run the C++ example programs in it:

```
docker build --tag image-lib-docker-poc:1.0 .

docker run -it --name image-lib-docker-poc-test -v /path/to/your-local-folder:/path/to/folder-in-docker-image image-lib-docker-poc:1.0 /bin/bash
```

Here are some example command lines to run the image in docker:

```
docker run -it --name image-lib-docker-poc-test03 -v /users/<user>/image-lib-docker-poc:/workspaces/image-lib-docker-poc image-lib-docker-poc:1.0 /bin/bash

docker run -it --name image-lib-docker-poc-test04 -v /Users/wuzhanglin/Sources/POC/image-lib-on-docker-poc:/workspaces/image-lib-docker-poc image-lib-poc:3.0 /bin/bash
```

##### Build and run C++ examples in docker

```
cd /workspaces/image-lib-docker-poc/examples/pangomm
mkdir build
cd build

g++ -g -Wall -o measure-text-pdf `pkg-config --cflags cairomm-1.0 pangomm-1.4` ../measure-text-pdf.cpp `pkg-config --libs cairomm-1.0 pangomm-1.4`

./measure-text-pdf "../measure-text-pdf-test-data.txt"
```

##### Optional: Install third party libraries on Mac for source navigation

This is just for improving developers' productivity on Mac writing C++ code in VS Code.

Install the dependencies using brew so that we can navigate through the source code of the third party libraries.

```
brew install pangomm
brew install pkgconfig
```

## Questions

### Docker image

2. No need to install source code editing tools in production environment?

### Fonts

1. Which fonts we should install by default?
2. There are too many fonts in the example here, we should remove the unuseful ones?

## References

- [Cairomm: A C++ wrapper for the cairo graphics library](https://www.cairographics.org/documentation/cairomm/reference/index.html)
- [Pangomm: The official C++ interface for the Pango font layout library](https://developer.gnome.org/pangomm/2.42/)
- [Docker: Build and run your image](https://docs.docker.com/get-started/part2/)
- [VS Code: Developing inside a Container](https://code.visualstudio.com/docs/remote/containers)
- [VS Code: Example of debugging C++ code in docker containers](https://github.com/microsoft/vscode-remote-try-cpp)

