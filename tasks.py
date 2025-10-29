###############################################
#                Imports                      #
###############################################
import glob
import os
import shutil
import subprocess
import tempfile

from invoke import task

###############################################
#                Public API                   #
###############################################
ROOT_PATH = os.path.dirname(os.path.abspath(__file__))
THIRD_PARTY_PATH = os.path.join(ROOT_PATH, "third_party")
BUILD_PATH = os.path.join(ROOT_PATH, "build")
TOOLCHAIN_PATH = os.path.join(
    THIRD_PARTY_PATH,
    "arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-linux-gnueabihf",
    "bin",
    "arm-none-linux-gnueabihf-",
)
OPTEE_PATH = os.path.join(THIRD_PARTY_PATH, "optee-os")
UBOOT_PATH = os.path.join(THIRD_PARTY_PATH, "u-boot")
EXAMPLES_PATH = os.path.join(ROOT_PATH, "examples")
SHARED_PATH = os.path.join(ROOT_PATH, "shared")

@task
def install(c):
    """
    Install Ansible and sshpass on the system if they are not already installed.

    Usage:
        inv install
    """

    _pr_info("Installing Dependencies...")
    try:
        result = c.run(
            """
                  sudo apt-get update && sudo apt-get install -y \
                    build-essential device-tree-compiler \
                    g++ \
                    clang \
                    device-tree-compiler \
                    make \
                    libmbedtls-dev \
                    nodejs \
                    libssl-dev \
                    python3-poetry \
                    python3-sphinx \
                    python3-pip \
                    bison \
                    xxd   \
                    stlink-tools
            """,
            warn=True,
        )
        if result.ok:
            _pr_info("Dependencies installed successfully.")
        else:
            _pr_error("Unable to install dependencies.")
    except Exception as e:
        _pr_error(f"Error installing dependencies: {e}")


@task
def clean(c, bytecode=False, extra=""):
    """
    Clean up build and temporary files recursively.

    This task removes specified patterns of files and directories,
    including build artifacts, temporary files, and optionally Python
    bytecode files.

    Args:
        bytecode (bool, optional): If True, also removes Python bytecode files (.pyc). Defaults to False.
        extra (str, optional): Additional pattern to remove. Defaults to "".

    Usage:
        inv clean
        inv clean --bytecode
        inv clean --extra='**/*.log'
    """
    patterns = [
      "build/*",
      "*/*~*",
      "*/#*",
      "**/*~*",
      "**/*#*",
      "*~*",
      "*#*",
      "**/.#*"   
    ]
    
    if bytecode:
        patterns.append("**/*.pyc")
    if extra:
        patterns.append(extra)

    for pattern in patterns:
        _pr_info(f"Removing files matching pattern '{pattern}'")

        # Use glob to find files recursively and remove each one
        for path in glob.glob(pattern, recursive=True):
            if os.path.isfile(path) or os.path.islink(path):
                os.remove(path)
                print(f"Removed file {path}")
            elif os.path.isdir(path):
                shutil.rmtree(path)
                print(f"Removed directory {path}")
    try:
        clean_optee(c)
        clean_uboot(c)
        clean_tfa(c)
    except Exception:
        _pr_error("Cleaning failed")
        raise

    _pr_info("Clean up completed.")


@task
def build_uboot(c, is_ethernet_gadget=True):
    _pr_info("Building uboot...")

    env = {
        "CROSS_COMPILE": TOOLCHAIN_PATH,
        "DEVICE_TREE": "stm32mp135f-dk",
    }
    config = {}
    uboot_env = {}

    if is_ethernet_gadget:
        config["CONFIG_CMD_BIND"] = True
        config["CONFIG_USB_ETHER"] = True
        config["CONFIG_USB_ETH_CDC"] = True
        config["CONFIG_USB_ETH_RNDIS"] = False
        config["CONFIG_USBNET_DEV_ADDR"] = "de:ad:be:ef:00:01"
        config["CONFIG_USBNET_HOST_ADDR"] = "de:ad:be:ef:00:00"

        uboot_env["ethact"] = "usb_ether"
        uboot_env["usbnet_devaddr"] = "f8:dc:7a:00:00:02"
        uboot_env["usbnet_hostaddr"] = "f8:dc:7a:00:00:01"
        uboot_env["bootcmd"] = (
            "bind /soc/usb@49000000 usb_ether; tftp 0xC0300000 example.bin; go 0xC0300000"
        )
        uboot_env["serverip"] = "192.168.7.1"
        uboot_env["ipaddr"] = "192.168.7.2"

    try:
        with tempfile.NamedTemporaryFile(
            "w", dir=UBOOT_PATH, prefix="env", suffix=".txt", delete_on_close=False
        ) as fp:
            if len(uboot_env) > 0:
                config["CONFIG_USE_DEFAULT_ENV_FILE"] = True
                config["CONFIG_ENV_IS_DEFAULT"] = True
                config["CONFIG_ENV_IS_NOWHERE"] = True
                config["CONFIG_ENV_IS_IN_MMC"] = False
                config["CONFIG_USE_ENV_MMC_PARTITION"] = False
                config["CONFIG_DEFAULT_ENV_FILE"] = str(fp.name)
                config["CONFIG_ENV_SOURCE_FILE"] = str(fp.name)

                for key, value in uboot_env.items():
                    fp.write(f"{key}={value}\n")

            fp.close()  # This line is required to save content

            with c.cd(UBOOT_PATH):
                _run_make(c, "stm32mp13_defconfig", env)

                for key, value in config.items():
                    if value is True:
                        c.run(f"scripts/config --enable {key}")
                    elif value is False:
                        c.run(f"scripts/config --disable {key}")
                    elif isinstance(value, str):
                        c.run(f'scripts/config --set-str {key} "{value}"')
                    else:
                        raise ValueError("Unsupported %s:%s" % (key, value))

                _run_make(c, "-j 4 all", env)
                c.run(f"mkdir -p {BUILD_PATH}")
                c.run(f"cp u-boot-nodtb.bin u-boot.dtb {BUILD_PATH}")

    except Exception as err:
        print(err)
        _pr_error("Building uboot failed")
        raise err

    _pr_info("Building uboot completed")


@task
def build_optee(c, dt_file=None):
    _pr_info("Building optee os...")

    env = {
        "CROSS_COMPILE": TOOLCHAIN_PATH,
        "CROSS_COMPILE_core": TOOLCHAIN_PATH,
        "CROSS_COMPILE_ta_arm32": TOOLCHAIN_PATH,
        "CFG_USER_TA_TARGETS": "ta_arm32",
        "CFG_ARM64_core": "n",
        "PLATFORM": "stm32mp1-135F_DK",
        "CFG_TEE_CORE_LOG_LEVEL": "1",
        "DEBUG": "0",
        "CFG_IN_TREE_EARLY_TAS": "trusted_keys/f04a0fe7-1f5d-4b9b-abf7-619b85b4ce8c",
        "CFG_SCP_FIRMWARE": os.path.join(THIRD_PARTY_PATH, "scp-firmware"),
    }

    def _compile():
      try:
          with c.cd(os.path.join(THIRD_PARTY_PATH, "optee-os")):

              _run_make(c, "-j 4 all", env)
              c.run(f"mkdir -p {BUILD_PATH}")
              with c.cd(os.path.join("out", "arm-plat-stm32mp1", "core")):
                  c.run(f"cp tee.bin tee-raw.bin tee-*_v2.bin {BUILD_PATH}")

      except Exception:
          _pr_error("Building optee os failed")
          raise
    
    if dt_file:
        env["CFG_EMBED_DTB"]="y"
        env["CFG_STM32MP13"]="y"
        env["CFG_DRAM_SIZE"]="0x20000000" # Without this config optee sets 1GB ram and we crash
                                          #  cause optee expect it's code elswhere.
        env["CFG_EMBED_DTB_SOURCE_FILE"]=os.path.basename(dt_file)
        with open(dt_file, "rb") as src:
            with open(
                    os.path.join(OPTEE_PATH,"core", "arch", "arm", "dts",env["CFG_EMBED_DTB_SOURCE_FILE"]), "wb"
            ) as dst:
                dst.write(src.read())
                
        _compile()
    else:
        _compile()
    
    _pr_info("Building optee os completed")


@task
def build_tfa(c):
    _pr_info("Building tf-a...")

    env = {
        "CROSS_COMPILE": TOOLCHAIN_PATH,
        "CC": str(TOOLCHAIN_PATH) + "gcc",
        "LD": str(TOOLCHAIN_PATH) + "ld",
        "BL32": os.path.join(BUILD_PATH, "tee-header_v2.bin"),
        "BL32_EXTRA1": os.path.join(BUILD_PATH, "tee-pager_v2.bin"),
        "BL32_EXTRA2": os.path.join(BUILD_PATH, "tee-pageable_v2.bin"),
        "BL33": os.path.join(BUILD_PATH, "u-boot-nodtb.bin"),
        "BL33_CFG": os.path.join(BUILD_PATH, "u-boot.dtb"),
        "ARM_ARCH_MAJOR": "7",
        "ARCH": "aarch32",
        "PLAT": "stm32mp1",
        "DTB_FILE_NAME": "stm32mp135f-dk.dtb",
        "AARCH32_SP": "optee",
        "DEBUG": "0",
        "LOG_LEVEL": "30",
        "STM32MP15_OPTEE_RSV_SHM": "0",
        "STM32MP_EMMC": "1",
        "STM32MP_SDMMC": "1",
        "STM32MP_RAW_NAND": "0",
        "STM32MP_SPI_NAND": "0",
        "STM32MP_SPI_NOR": "0",
        "STM32MP_USB_PROGRAMMER": "1",
    }
    try:
        with c.cd(os.path.join(THIRD_PARTY_PATH, "tf-a")):
            _run_make(c, "-j 4 all fip", env)
            c.run(f"mkdir -p {BUILD_PATH}")
            c.run(f"cp build/stm32mp1/*/fip.bin {BUILD_PATH}/fip.bin")
            c.run(
                f"cp build/stm32mp1/*/tf-a-stm32mp135f-dk.stm32 {BUILD_PATH}/tf-a-stm32mp135f-dk.stm32"
            )

    except Exception:
        _pr_error("Building tf-a failed")
        raise

    _pr_info("Building tf-a completed")


@task
def build(c, examples=True, example=None, tests=True, boot=True):
    _pr_info("Building...")
    try:
        if boot:
          if os.path.exists((device_tree:=os.path.join(EXAMPLES_PATH, example, "dts", "stm32mp135f-dk-optee.dts"))):
                build_optee(c, device_tree)
          else:
                build_optee(c)
          build_uboot(c)
          build_tfa(c)
                  
        if examples:
            examples_paths = os.listdir(EXAMPLES_PATH)
            if example:
                examples_paths = [path for path in examples_paths if path==example]

            for path in examples_paths:
                _pr_info(f"Building {path}...")
                
                example_dir = os.path.join(EXAMPLES_PATH, os.path.basename(path))                
                with c.cd(example_dir):
                    build_dir = os.path.join(BUILD_PATH, os.path.basename(path))
                    c.run(f"mkdir -p {build_dir}")
                    c.run(
                        f"meson setup --wipe --cross-file {os.path.join(SHARED_PATH, 'armv7a-cross-compile-meson.txt')} {build_dir}"
                    )
                    c.run(
                        f"rm -f compile_commands.json && ln -s {os.path.join(build_dir, 'compile_commands.json')} compile_commands.json"
                    )
                    
                    
                c.run(f"meson compile -C {build_dir}")
                    
                if example is not None:
                    c.run(f"arm-none-eabi-objcopy -O binary {build_dir}/{path} {ROOT_PATH}/tftp/example.bin")
                c.run(f"chmod 777 {ROOT_PATH}/tftp/example.bin")
                    
                _pr_info(f"Building {path} completed")

        if tests:
            tests_dir = os.path.join(ROOT_PATH, "tests")
            build_dir = os.path.join(BUILD_PATH, "tests")
            _pr_info(f"Building tests...")
            
            with c.cd(tests_dir):
                c.run(
                    f"meson setup {build_dir}"
                )                
                c.run(
                    f"rm -f compile_commands.json && ln -s {os.path.join(build_dir, 'compile_commands.json')} compile_commands.json"
                )
                
            c.run(f"meson compile -C {build_dir}")            
            _pr_info(f"Building tests completed")            
            
    except Exception:
        _pr_error("Building failed")
        raise

    _pr_info("Building completed")


@task
def clean_tfa(c):
    with c.cd(os.path.join(THIRD_PARTY_PATH, "tf-a")):
        c.run("make clean")
        c.run("rm -rf build")


@task
def clean_optee(c):
    with c.cd(os.path.join(THIRD_PARTY_PATH, "optee-os")):
        c.run("make clean")
        c.run("rm -rf out")


@task
def clean_uboot(c):
    with c.cd(os.path.join(THIRD_PARTY_PATH, "u-boot")):
        c.run("make clean")


@task
def deploy_via_usb(c):
    if not os.environ.get("STM32_PRG_PATH"):
        raise ValueError("set STM32_PRG_PATH to path where")

    with c.cd(BUILD_PATH):
        c.run(
            """sudo $STM32_PRG_PATH/STM32_Programmer_CLI -c port=usb1 \
                      -d tf-a-stm32mp135f-dk.stm32 0x1 -s 0x1           \
                      -d fip.bin 0x3 -s 0x3                             
        """
        )


@task
def deploy_to_sdcard(c, dev="sda"):
    with c.cd(BUILD_PATH):
        if not os.path.exists("/dev/disk/by-partlabel/fsbl1"):
            raise ValueError("No /dev/disk/by-partlabel/fsbl1")
        if not os.path.exists("/dev/disk/by-partlabel/fsbl2"):
            raise ValueError("No /dev/disk/by-partlabel/fsbl2")
        if not os.path.exists("/dev/disk/by-partlabel/fip"):
            raise ValueError("No /dev/disk/by-partlabel/fip")

        c.run(
            "sudo dd if=tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl1 bs=1K conv=fsync"
        )
        c.run(
            "sudo dd if=tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl2 bs=1K conv=fsync"
        )
        c.run("sudo dd if=fip.bin of=/dev/disk/by-partlabel/fip bs=1K conv=fsync")
        c.run("sudo sync")


@task
def test(c, test=None):
    _pr_info("Testing...")

    tests_dir = os.path.join(ROOT_PATH, "tests")
    build_dir = os.path.join(BUILD_PATH, "tests")

    with c.cd(tests_dir):
        cmd = f"meson test -C {build_dir} --verbose "
        if test is not None:
            cmd += test

        try:
            c.run(cmd)
        except:
            _pr_error("Testing failed")
            raise
    _pr_info("Testing completed")
        
###############################################
#                Private API                  #
###############################################
def _command_exists(command):
    try:
        subprocess.run(
            ["which", command], stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        return True
    except Exception:
        return False


def _pr_info(message: str):
    """
    Print an informational message in blue color.

    Args:
        message (str): The message to print.

    Usage:
        pr_info("This is an info message.")
    """
    print(f"\033[94m[INFO] {message}\033[0m")


def _pr_warn(message: str):
    """
    Print a warning message in yellow color.

    Args:
        message (str): The message to print.

    Usage:
        pr_warn("This is a warning message.")
    """
    print(f"\033[93m[WARN] {message}\033[0m")


def _pr_debug(message: str):
    """
    Print a debug message in cyan color.

    Args:
        message (str): The message to print.

    Usage:
        pr_debug("This is a debug message.")
    """
    print(f"\033[96m[DEBUG] {message}\033[0m")


def _pr_error(message: str):
    """
    Print an error message in red color.

    Args:
        message (str): The message to print.

    Usage:
        pr_error("This is an error message.")
    """
    print(f"\033[91m[ERROR] {message}\033[0m")


def _run_make(ctx, command, env):
    ctx.run(
        f"make {command} " + " ".join([f"{arg}={env[arg]}" for arg in env]),
        env=env,
    )
