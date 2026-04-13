###############################################
#                Imports                      #
###############################################
import os

from invoke import task

from src.common import PackageBuilder, PackageCtx
from src.utils import pr_debug, pr_error, pr_info, pr_warn, import_builder_modules

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
SRC_PATH = os.path.join(ROOT_PATH, "src")


@task
def install(c):
    pr_info("Installing Dependencies...")

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
            pr_info("Dependencies installed successfully.")
        else:
            pr_error("Unable to install dependencies.")
    except Exception as e:
        pr_error(f"Error installing dependencies: {e}")


@task
def build(c):
    import_builder_modules(SRC_PATH)

    c.run(f"mkdir -p {BUILD_PATH}")

    ctx = PackageCtx(
        c, ROOT_PATH, THIRD_PARTY_PATH, BUILD_PATH, TOOLCHAIN_PATH, SRC_PATH
    )

    classes = list(set(PackageBuilder.__subclasses__()))
    objs = list()
    
    configs = load_config(classes)
    
    while len(classes) != 0:
        PBuilder = classes.pop()
        kwargs = configs[PBuilder]
        print(f"{PBuilder.__module__=}")
        build_deps(classes, objs, ctx, PBuilder)
        pbuilder = PBuilder(ctx)
        pbuilder.build(**kwargs)
        objs.append(pbuilder)

    for pbuilder in objs:
        deps = [obj for obj in objs if obj.__class__ in pbuilder.dependencies]
        pbuilder.install(deps)


def build_deps(classes, objs, ctx, pbuilder):
    for dep_class in pbuilder.dependencies:
        if dep_class in classes:
            build_deps(classes, objs, ctx, dep_class)
            dep_obj = dep_class(ctx)
            dep_obj.build()
            objs.append(dep_obj)
            classes.remove(dep_class)

def load_config(classes):
    config = {}

    with open("config", "r") as fp:
        txt = fp.readlines()

    for class_ in classes:
        module_name = f"{class_.__module__}".split(".")[1]
        config[class_] = class_config = {}        
        
        for line in txt:
            key, value = line.split("=")
            key, value = key.lower(), value.rstrip('\n')
            
            if key.startswith(module_name):
                class_config[key.replace(f"{module_name}_", "")] = value

    print(f"{config=}")
    return config

            
@task
def deploy_sdcard(c, dev="sda"):
    if not os.path.exists("/dev/disk/by-partlabel/fsbl1"):
        raise ValueError("No /dev/disk/by-partlabel/fsbl1")

    if not os.path.exists("/dev/disk/by-partlabel/fsbl2"):
        raise ValueError("No /dev/disk/by-partlabel/fsbl2")

    if not os.path.exists("/dev/disk/by-partlabel/fip"):
        raise ValueError("No /dev/disk/by-partlabel/fip")

    with c.cd(BUILD_PATH):
        c.run(
            "sudo dd if=tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl1 bs=1K conv=fsync"
        )
        c.run(
            "sudo dd if=tf-a-stm32mp135f-dk.stm32 of=/dev/disk/by-partlabel/fsbl2 bs=1K conv=fsync"
        )
        c.run("sudo dd if=fip.bin of=/dev/disk/by-partlabel/fip bs=1K conv=fsync")
    c.run("sudo sync")
