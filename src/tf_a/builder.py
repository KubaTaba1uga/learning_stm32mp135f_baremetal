import os

from src.utils import pr_error, pr_info, run_make
from src.common import PackageBuilder, PackageCopyInstaller
from src.u_boot.builder import UbootPackageBuilder
from src.optee_os.builder import OpteePackageBuilder


class TfaPackageBuilder(PackageCopyInstaller, PackageBuilder):
    dependencies = [UbootPackageBuilder, OpteePackageBuilder]

    def build(self):
        pr_info("Building tf-a...")

        env = {
            "CROSS_COMPILE": self.ctx.toolchain_path,
            "CC": str(self.ctx.toolchain_path) + "gcc",
            "LD": str(self.ctx.toolchain_path) + "ld",
            "BL32": os.path.join(self.ctx.build_path, "tee-header_v2.bin"),
            "BL32_EXTRA1": os.path.join(self.ctx.build_path, "tee-pager_v2.bin"),
            "BL32_EXTRA2": os.path.join(self.ctx.build_path, "tee-pageable_v2.bin"),
            "BL33": os.path.join(self.ctx.build_path, "u-boot-nodtb.bin"),
            "BL33_CFG": os.path.join(self.ctx.build_path, "u-boot.dtb"),
            "ARM_ARCH_MAJOR": "7",
            "ARCH": "aarch32",
            "PLAT": "stm32mp1",
            "DTB_FILE_NAME": "stm32mp135f-dk.dtb",
            "AARCH32_SP": "optee",
            "DEBUG": "1",
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
            with self.ctx.c.cd(os.path.join(self.ctx.third_party_path, "tf-a")):
                run_make(self.ctx.c, "-j 4 all fip", env)

                src_path = os.path.join(
                    self.ctx.third_party_path, "tf-a", "build", "stm32mp1", "debug"
                )
                self.copy_paths = [
                    os.path.join(src_path, "fip.bin"),
                    os.path.join(src_path, "tf-a-stm32mp135f-dk.stm32"),
                ]

        except Exception:
            pr_error("Building tf-a failed")
            raise

        pr_info("Building tf-a completed")
