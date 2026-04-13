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

os.environ["PATH"] += f":{SRC_PATH}"
print(os.environ["PATH"])
os.environ["PATH"] = f"{os.path.join(ROOT_PATH, 'src')}:{os.environ['PATH']}"

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

    while len(classes) != 0:
        PBuilder = classes.pop()
        build_deps(classes, objs, ctx, PBuilder)
        pbuilder = PBuilder(ctx)
        pbuilder.build()
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
            
            
