# loftili - core

This repo holds the web application that runs on a device providing a web api for controlling audio playback.


## System Config

Because this application relies on the portaudio audio api, there is a pretty specfific set of system pre-requisites designed to make this application as portable as possbile.

**Ubuntu/Linux**
```
sudo apt-get install libsndfile1-dev libncurses5-dev -y
sudo apt-get install xmlto -y
sudo apt-get install libasound-dev
wget ftp://ftp.alsa-project.org/pub/lib/alsa-lib-1.0.27.2.tar.bz2
wget ftp://ftp.alsa-project.org/pub/utils/alsa-utils-1.0.27.2.tar.bz2
wget ftp://ftp.alsa-project.org/pub/tools/alsa-tools-1.0.27.tar.bz2
wget ftp://ftp.alsa-project.org/pub/oss-lib/alsa-oss-1.0.25.tar.bz2

tar xjf alsa-lib-1.0.27.2.tar.bz2
cd alsa-lib-1.0.27.2
./configure
make
sudo make install
cd ..


tar xjf alsa-utils-1.0.27.2.tar.bz2
cd alsa-utils-1.0.27.2
./configure
make
sudo make install
cd ..

tar xjf alsa-tools-1.0.27.tar.bz2
cd alsa-tools-1.0.27
./configure
make
sudo make install
cd ..

tar xjf alsa-oss-1.0.25.tar.bz2
cd alsa-oss-1.0.25
./configure
make
sudo make install
cd ..

wget http://www.portaudio.com/archives/pa_stable_v19_20140130.tgz
tar xvzf pa_stable_v19_20140130.tgz
cd pa_stable_v19_20140130
sudo ldconfig
./configure --enable-debug-output
make
sudo make install
```
