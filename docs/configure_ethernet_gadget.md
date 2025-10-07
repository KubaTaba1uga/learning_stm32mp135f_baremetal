# 🧩 Configure Ethernet Gadget

This guide describes how to enable and connect the **Ethernet Gadget** interface on the board.

---

## 1. Build the Image

Run the build command to generate the image with Ethernet gadget support:

```bash
❯ inv build
```

---

## 2. Connect the Board

Use a **USB-C cable** to connect the **CN7 port** on the board to your **host PC**.

Once the board boots, it should register as a USB Ethernet device. You can verify this using:

```bash
❯ sudo dmesg -w
```

Example output:

```text
[18240.420615] usb 3-7.4.2: new high-speed USB device number 37 using xhci_hcd
[18240.533651] usb 3-7.4.2: New USB device found, idVendor=0483, idProduct=5720, bcdDevice= 3.27
[18240.533675] usb 3-7.4.2: Product: Ethernet Gadget
[18240.533680] usb 3-7.4.2: Manufacturer: STMicroelectronics
[18240.542854] cdc_ether 3-7.4.2:1.0 eth0: register 'cdc_ether' at usb-0000:00:14.0-7.4.2, CDC Ethernet Device, f8:dc:7a:00:00:01
[18240.564333] cdc_ether 3-7.4.2:1.0 enxf8dc7a000001: renamed from eth0
```

---

## 3. Configure Host Network Interface

Assign a **static IP** to the Ethernet gadget interface on the host.
Edit `/etc/network/interfaces` and add:
```ini
allow-hotplug enxf8dc7a000001
iface enxf8dc7a000001 inet static
    address 192.168.7.1/24
    gateway 192.168.7.1
    hwaddress ether f8:dc:7a:00:00:01	
```

Then restart the networking service to apply the changes:

```bash
❯ sudo systemctl restart networking
```

---

## 4. Verify the Connection

After the board boots, the host should recognize it as an Ethernet device:

```bash
❯ ip addr
```

Example output:

```text
10: enxf8dc7a000001: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UNKNOWN group default qlen 1000
    link/ether f8:dc:7a:00:00:01 brd ff:ff:ff:ff:ff:ff
    inet 192.168.7.1/24 brd 192.168.7.255 scope global enxf8dc7a000001
       valid_lft forever preferred_lft forever
    inet6 fe80::fadc:7aff:fe00:1/64 scope link
       valid_lft forever preferred_lft forever
```

---

✅ **At this point, the Ethernet gadget interface is active and ready for communication.**

---
