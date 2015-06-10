# Core library installation

This guide was made to help users get the core library compiled onto their compatible device. We recommend the [raspberry pi 2](http://amzn.com/B00T2U7R7I), with the [ubuntu snappy core](http://developer.ubuntu.com/en/snappy/) os installed. For instruction on getting the operating system installed on your raspberry pi, see [this guide](http://elinux.org/RPi_Easy_SD_Card_Setup), which walks you through the process of burning an image to an SD card, which you'll use as the storage on your device. On OSX, this process looks like:

```
$ diskutil list
$ diskutil unmountDisk /dev/<disk# from diskutil>
$ sudo dd bs=1m if=<your image file>.img of=/dev/<disk# from diskutil>
```

*note: using `/dev/rdisk#` will take less time*


## Package dependencies

After getting the operating system installed on your device, you will need to install a few packages that are pre-requisites of our core library. These packages are:

1. [Git](https://git-scm.com/) (used to download the source code and vendor libraries)
2. [openssl](https://wiki.openssl.org/index.php/Libssl_API) 
3. [ao](https://www.xiph.org/ao/)
4. [mpg123](http://www.mpg123.de/)

### Installing from source

When compiling our application ourselves, we prefer using our own package versions and compiling them ourselves. We've uploaded these libraries to our ftp server as a mirror [here](http://artifacts.sizethreestudios.com/loftili/libs/). 
*note: alsa-utils-1.0.28 is not required*

compiling these packages is straightforward:

```
$ wget <artifact url>/alsa-lib-1.0.28.tar.bz2
$ tar xjf alsa-lib-1.0.28.tar.bz2
$ cd alsa-lib-1.0.28
$ ./configure
$ make
$ make install

$ wget <artifact url>/libao-1.2.0.tar.gz
$ tar xzf libao-1.2.0.tar.gz
$ cd libao-1.2.0
$ ./configure
$ make
$ make install

$ wget <artifact url>/mpg123-1.20.1.tar.bz2
$ tar xjf mpg123-1.20.1.tar.bz2
$ cd mpg123-1.20.1
$ ./configure
$ make
$ make install
```

**important: after installing these from source, you will need to update your system's `LD_LIBRARY_PATH`**
```
export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib
```

### Installing from packages

On ubuntu snappy, installing these could be done by running:

```
$ sudo apt-get install -y libao-dev libmpg123-dev libssl-dev build-essential autoconf automake libtool
```


## Downloading the source

The source code for the library can be downloaded from our github's [releases](https://github.com/loftili/core/releases) page, or it can be cloned using:

```
$ git clone https://github.com/loftili/core.git ./core
```

Once you have the source code downloaded, you'll need to copy our vendor libraries into a `vendor` director; these libraries are:

1. [spdlog](https://github.com/gabime/spdlog) - a logging library used in favor of "in-house" solution
2. [rapidjson](https://github.com/miloyip/rapidjson) - json parsing library used to get information from api requests

```
$ cd ./core
$ mkdir -p vendor
$ cd vendor
$ git clone https://github.com/miloyip/rapidjson ./rapidjson
$ git clone https://github.com/gabime/spdlog.git ./spdlog
```

## Compiling the source

Once everything is in place, compiling the source code can be done by running:

```
$ cd ./core
$ ./bootstrap
$ ./configure
$ make
```

Be sure to view the output from the `./confgure command` - it will have helpful information regarding the core library's ability to compile properly - including a check that the dependent packages were installed correctly. You should see something like:

![image](https://cloud.githubusercontent.com/assets/1545348/7918818/26f53d96-0862-11e5-9372-10d980fe2954.png)

## Running

After successfully compiling the source code, your executable can be found at `./src/loftili`. Running without any arguments should generate the following output:

![image](https://cloud.githubusercontent.com/assets/1545348/7919013/6a1700ae-0863-11e5-88df-881f39be6fcd.png)

The `serial` parameter should be the serial number assigned to you via our [account request](https://lofti.li/join) form. The rest of the arguments are optional; values default to our production api server and a default log file.
