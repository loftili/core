![image](https://cloud.githubusercontent.com/assets/1545348/9281871/67cd0c22-4296-11e5-8c14-72e7754e8ea1.png)

The loftili core (LFTCE) is the c++ application that is run on core devices, and is responsible for managing the device's audio output, as well as maintaining an open channel of communication with the [api](https://github.com/loftili/api). It is through this channel that the api will send the device commands (i.e `CMD audio:start`). Upon receiving one of these commands, the core library is then responsible for querying the api for information related to it's perscribed state; for audio commands this could mean the url of the track that it should be playing.

## compiling/installing

Instructions for installing can be found in the [INSTALLING.md](https://github.com/loftili/core/blob/master/INSTALLING.md) file. Please see this file for information on getting your system ready to compile the source.

## contributing

Contributions are very welcome, and anyone interested in contributing to LFTAPI should follow the guide published by [github](https://guides.github.com/activities/contributing-to-open-source/), and [create an issue](https://github.com/loftili/core/issues), or just fork the repository, make your change, and open a [pull request](https://github.com/loftili/api/pulls).


## license

Please see [LICENSE.txt](https://github.com/loftili/api/blob/master/LICENSE.txt)
