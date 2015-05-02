# The Core

Loftili's core application runs on devices connected to audio systems at home.

It is responsible for establishing a connection to the [api](https://github.com/loftili/api), receiving commands and executing them on the user's behalf. The connection between the two is pesistant, using simple `CMD type:command` messages to dictate instruction.

### Building

This codebase uses [autoconf](http://www.gnu.org/software/autoconf/) and [automake](http://www.gnu.org/software/automake/) to compile it's source:

```
$ ./bootstrap
$ ./configure
$ make
$ make install
```

### Design

```
```

### Support

Active development of the core library is currently limited to linux machines only.

### License

see [License.txt](https://github.com/loftili/core/blob/master/LICENSE.txt)

### Notes

Much of the inspiration for this code came from [James O. Coplien](http://www.amazon.com/Advanced-C-Programming-Styles-Idioms/dp/0201548550), as well as work done by [Andrei Alexandrescu](http://en.wikipedia.org/wiki/Andrei_Alexandrescu).

