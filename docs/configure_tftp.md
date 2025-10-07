# 📡 Setting Up and Using TFTP with STM32MP135F

This guide explains how to install and configure a **TFTP server** on the host, prepare files for transfer, and fetch them from the STM32MP135F board via **U-Boot**.

---

## 🧰 1. Install the TFTP Server

Install `tftpd-hpa` (it’s often already available on Ubuntu/Debian):

```bash
❯ sudo apt install tftpd-hpa
```

To locate its configuration and service files:

```bash
❯ sudo find /etc | grep tftp
```

The main configuration file is:

```
/etc/default/tftpd-hpa
```

---

## 📁 2. Locate the TFTP Root Directory

By default, `tftpd-hpa` uses `/srv/tftp` as the TFTP root directory.
If `/var/lib/tftpboot` does not exist, verify the correct directory in `/etc/default/tftpd-hpa`.

Example entry:

```bash
TFTP_DIRECTORY="/srv/tftp"
```

You can check if the folder exists:

```bash
❯ ls /srv/tftp/
```

If missing, create it:

```bash
❯ sudo mkdir -p /srv/tftp
```

---

## 📄 3. Create a Test File

Add a small file to verify the setup:

```bash
❯ echo -e "Hello friend\n" | sudo tee /srv/tftp/textfile.txt
```

Ensure it’s readable by TFTP clients:

```bash
❯ sudo chmod 555 /srv/tftp/textfile.txt
```

Test by reading it:

```bash
❯ sudo cat /srv/tftp/textfile.txt
Hello friend
```

---

## 🚀 4. Transfer File via TFTP

Run TFTP to load the test file into RAM.
Avoid reserved memory addresses like `0x81000000` — use a safe one such as `0xC0000000`.

```bash
STM32MP> tftp 0xC0000000 textfile.txt
```

Expected output:

```
Using usb@49000000 device
TFTP from server 192.168.7.1; our IP address is 192.168.7.2
Filename 'textfile.txt'.
Load address: 0xc0000000
Loading: #
         2.9 KiB/s
done
Bytes transferred = 14 (e hex)
```

---

## 🔍 5. Verify Memory Content

Dump memory to confirm the file was received correctly:

```bash
STM32MP> md 0xC0000000
c0000000: 6c6c6548 7266206f 646e6569 e59f0a0a  Hello friend....
```

---

✅ **Result:**
TFTP is configured correctly, and the STM32MP board can download files from the host over USB Ethernet.

---
