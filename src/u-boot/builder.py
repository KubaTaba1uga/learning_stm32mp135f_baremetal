import os
import tempfile

from src.utils import pr_error, pr_info, run_make
from src.common import PackageBuilder, PackageCopyInstaller


class UbootPackageBuilder(PackageCopyInstaller, PackageBuilder):
    def build(self):
        pr_info("Building uboot...")

        env = {
            "CROSS_COMPILE": self.ctx.toolchain_path,
            "DEVICE_TREE": "stm32mp135f-dk",
        }
        config = {}
        uboot_env = {}

        UBOOT_PATH = os.path.join(self.ctx.third_party_path, "u-boot")

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

                with self.ctx.c.cd(UBOOT_PATH):
                    run_make(self.ctx.c, "stm32mp13_defconfig", env)

                    for key, value in config.items():
                        if value is True:
                            self.ctx.c.run(f"scripts/config --enable {key}")
                        elif value is False:
                            self.ctx.c.run(f"scripts/config --disable {key}")
                        elif isinstance(value, str):
                            self.ctx.c.run(f'scripts/config --set-str {key} "{value}"')
                        else:
                            raise ValueError("Unsupported %s:%s" % (key, value))

                    run_make(self.ctx.c, "-j 4 all", env)

                self.copy_paths = [
                    os.path.join(UBOOT_PATH, "u-boot-nodtb.bin"),
                    os.path.join(UBOOT_PATH, "u-boot.dtb"),
                ]

        except Exception as err:
            print(err)
            pr_error("Building uboot failed")
            raise err

        pr_info("Building uboot completed")
