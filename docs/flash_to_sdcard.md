# 💾 Flash Image to SD Card

This guide explains how to build the image and flash it to an SD card for deployment.

---

## 🏗️ 1. Build the Image

Run the build command from your project root:

```bash
❯ inv build
```

---

## 💽 2. Prepare the SD Card

Initialize and partition the SD card.

**⚠️ Warning:** Replace `/dev/sda` with the correct device for your SD card.
Running these commands on the wrong disk may cause data loss.

```bash
❯ sudo sgdisk -o /dev/sda
❯ sudo sgdisk --resize-table=128      \
            -a 1 -n 1:34:545          \
            -c 1:fsbl1                \
            -n 2:546:1057             \
            -c 2:fsbl2                \
            -n 3:1058:9249            \
            -c 3:fip                  \
            -n 4:9250:                \
            -c 4:rootfs               \
            -A 4:set:2                \
            -p /dev/sda
```

This creates the following partitions:

| Partition | Name   | Description            |
| --------- | ------ | ---------------------- |
| 1         | fsbl1  | First-stage bootloader |
| 2         | fsbl2  | Backup bootloader      |
| 3         | fip    | Firmware Image Package |
| 4         | rootfs | Root filesystem        |

---

## 🚀 3. Flash the Image

Deploy the built image to the SD card:

```bash
❯ inv deploy-to-sdcard
```

---

✅ **Result:**
The SD card is now ready to boot the board with the freshly built image.

---
