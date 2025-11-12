# Instalação

## Debian e derivados

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build micropython micropython-mpremote pkg-config gcc-arm-none-eabi
cd
git clone --recursive --depth=1 https://github.com/raspberrypi/pico-sdk.git
export PICO_SDK_PATH=~/pico-sdk
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.zshrc
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.bashrc
git clone --depth=1 https://github.com/raspberrypi/picotool.git
cd picotool
cmake .
sudo make install
sudo cp udev/60-picotool.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

## ArchLinux e derivados

```bash
yay -S arm-none-eadbi-gcc make cmake micropython mpremote picotool
cd
git clone --recursive --depth=1 https://github.com/raspberrypi/pico-sdk.git
export PICO_SDK_PATH=~/pico-sdk
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.zshrc
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.bashrc
```

## MacOS

```bash
brew install gcc-arm-embedded libusb make cmake git
cd
git clone --recursive --depth=1 https://github.com/raspberrypi/pico-sdk.git
export PICO_SDK_PATH=~/pico-sdk
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.zshrc
echo "export PICO_SDK_PATH=~/pico-sdk" >> ~/.bashrc
git clone --depth=1 https://github.com/raspberrypi/picotool.git
cd picotool
cmake .
sudo make install
```