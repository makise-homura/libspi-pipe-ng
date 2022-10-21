A library for sending requests and get replies from spidev

# Build

## General build flow

```
meson build
cd build
ninja
ninja install
```

## Options

* You may specify `-Dprefix=<PREFIX>` to override default install prefix. Resulting binary will be installed to `<PREFIX>/lib/libspi-pipe-ng.so` and/or `<PREFIX>/lib/libspi-pipe-ng.a`, and  `<PREFIX>/include/libspi-pipe-ng.h`.
* You may specify `-Ddefault_library=both` if you wish to build static library in addition to shared one.
* You may specify `-Ddefault_library=static` if you do wish to build static library only.

# Usage

## Project requirements

Use the following include file:
```
#include <libspi-pipe-ng.h>
```

Link your code with `-llibspi-pipe-ng`.

If your project is built with meson, you may use included `libspi-pipe-ng.wrap` file, and add the following line into your `meson.build` to automatically download this dependency:
```
libspipipeng_dep = dependency('libspi-pipe-ng', fallback : ['libspi-pipe-ng', 'libspipipeng_dep'])
```
Then you may use `libspipipeng_dep` as dependency in any of your targets.

## Function call

```
int spipipeng_transfer(int fd, const void *tx_buf, uint32_t tx_len, void *rx_buf, uint32_t rx_len, uint32_t speed_hz);
```
where:
* `fd`: file descriptor of `/dev/spidevX.Y` device. Obtain it with `open(path, O_RDWR)` call, don't forget to `close()` it afterwards.
* `tx_buf`: buffer to transfer to SPI slave. Shall not be `NULL`.
* `tx_len`: length of `tx_buf`. Shall not be zero.
* `rx_buf`: buffer to transfer from SPI slave. Shall not be `NULL` if `rx_len` is nonzero.
* `rx_len`: length of `rx_buf`, or zero if no read after write is required.
* `speed_hz`: communication speed, or zero to use default one (for now, 12.5 MHz).

## Return value

* `0` on success (and `rx_buf` is filled with SPI slave reply if `rx_len > 0`).
* `-1` on failure, and `errno` is set appropriately: `EINVAL` if any of input parameters is invalid, or the same value `ioctl()` call has set if it has failed.
