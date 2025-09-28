## Install deps on debian

```bash
sudo apt-get install -y build-essential device-tree-compiler

sudo apt-get update && sudo apt-get install -y \
  gcc-arm-none-eabi \
  g++ \
  clang \
  device-tree-compiler \
  make \
  libmbedtls-dev \
  nodejs \
  libssl-dev \
  python3-poetry \
  python3-sphinx \
  python3-pip
```

## Download cross compilation toolchain from arm

https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
