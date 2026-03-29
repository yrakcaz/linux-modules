[![CI](https://github.com/yrakcaz/linux-modules/actions/workflows/ci.yml/badge.svg)](https://github.com/yrakcaz/linux-modules/actions/workflows/ci.yml)
[![MIT License](https://img.shields.io/github/license/yrakcaz/linux-modules?color=blue)](./LICENSE)

# linux-modules

A collection of Linux kernel modules written as learning exercises in device driver development.

## Modules

### beep_driver

A PC speaker driver implemented as a Linux platform device. Hooks into the Linux input subsystem and drives the speaker via the i8253 PIT (Programmable Interval Timer) at I/O ports `0x42`/`0x43`/`0x61`.

- Registers as a platform device and driver
- Handles `EV_SND` input events (`SND_BELL`, `SND_TONE`)
- Supports suspend and shutdown lifecycle hooks

## Requirements

Linux kernel headers matching your running kernel. On Debian/Ubuntu:

```
apt install linux-headers-$(uname -r)
```

## Build

```
make
```

## Load / Unload

```
sudo make load    # insmod beep.ko
sudo make unload  # rmmod beep
```
