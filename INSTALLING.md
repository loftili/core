# Rasbian install

```
# setup a new sudo user 
sudo apt-get install vim -y
sudo useradd -s /bin/bash -d /home/s3studios s3studios
sudo usermod -a -G audio s3studios
sudo passwd s3studios
sudo vim /etc/sudoers
sudo mkdir /home/s3studios
sudo chown -R s3studios.s3studios /home/s3studios

# relogin as s3studios
mkdir ~/src
cd ~/src

sudo apt-get update
sudo apt-get install build-essential -y
sudo apt-get install autoconf -y
sudo apt-get install automake -y
sudo apt-get install libtool -y

wget http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/libmicrohttpd-0.9.37.tar.gz
tar xvzf libmicrohttpd-0.9.37.tar.gz
cd libmicrohttpd-0.9.37/
./configure
make
sudo make install
cd ..

sudo apt-get install libasound2-dev

wget http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/alsa-lib-1.0.27.2.tar.bz2
tar xjf alsa-lib-1.0.27.2.tar.bz2
cd alsa-lib-1.0.27.2/
./configure
make
sudo make install
cd ..

wget http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/pa_stable_v19_20140130.tgz
tar xvzf pa_stable_v19_20140130.tgz
cd pa_stable_v19_20140130
./configure
make
sudo make install
cd ..

wget http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/mpg123-1.20.1.tar.bz2
tar xjvf mpg123-1.20.1.tar.bz2
cd mpg123-1.20.1
./configure
make
sudo make install
cd ..

git clone git@github.com:loftili/core.git
cd core
./bootstrap && ./configure
make
```
