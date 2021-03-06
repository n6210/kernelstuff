ADAMTX
======

A simple framebuffer driver for large Adafruit/HUB75 LED matrix panels on Raspberry PI 3

# Compiling

Assuming you have kernel headers and build tools installed compiling is pretty straight forward:

1. Switch to the **parent** directory of this directory
2. Run ```make```


# Installation

Installation should be pretty easy, too:

1. Ensure you are still in the **parent**  directory of this directory
2. Copy ```dummyfb/dummyfb.ko``` and ```adafruit-matrix-rpi/adamtx.ko``` to you kernel module directory (most likely ```/usr/lib/modules/$YOUR_KERNEL_VERSION/```)
3. Run ```depmod -a```


# Configuration

The driver is configured through a device tree overlay. The file ```adamtx.dts``` contains a basic configuration for running a 64 px x 64 px display directly from a Raspberry PI.
To use the device tree overlay it needs to be compiled. This is done with the device tree compiler dtc. Your distribution of Linux will most likely offer a prebuilt dtc package.
To compile the device tree file run ```dtc adamtx.dts -O dtb -o adamtx.dtbo```. Ideally your distribution provides the binary ```/opt/vc/bin/dtoverlay```. If it does the overlay
can be loaded at runtime by executing ```/opt/vc/bin/dtoverlay adamtx.dtbo```. This should load both, the dummy framebuffer and the adamtx driver. If your distribution doesn't
come with with the dtoverlay tool you can still load the overlay at boot. To do so move the compiled overlay to ```/boot/overlays/``` and add the line ```dtoverlay=adamtx``` to
```/boot/config.txt```. After the next reboot the driver should be loaded and configured.

## DMA

This module supports DMA to offload clocking out data to the DMA engine of the BCM2835 peripheral controller. This method is not as fast as the default, cpu intensive tight loop
IO access but reduces CPU load significantly. Take a look at ```adamtx_dma.dts``` for an example configuration using DMA.

# Using it

This driver uses dummyfb to provide a framebuffer device. Thus a lot of applications like mplayer and even Xorg can use this driver to output to the LED panel.
