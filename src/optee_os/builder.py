import os
# import tempfile

from src.utils import pr_error, pr_info, run_make
from src.common import PackageBuilder, PackageCopyInstaller


class OpteePackageBuilder(PackageCopyInstaller, PackageBuilder):
    def build(self, **kwargs):
        pr_info("Building optee os...")

        OPTEE_PATH = os.path.join(self.ctx.third_party_path, "optee-os")
        
        env = {
            "CROSS_COMPILE": self.ctx.toolchain_path,
            "CROSS_COMPILE_core": self.ctx.toolchain_path,
            "CROSS_COMPILE_ta_arm32": self.ctx.toolchain_path,
            "CFG_USER_TA_TARGETS": "ta_arm32",
            "CFG_ARM64_core": "n",
            "PLATFORM": "stm32mp1-135F_DK",
            "CFG_TEE_CORE_LOG_LEVEL": "2",
            "CFG_TEE_CORE_DEBUG": "y",
            "DEBUG": kwargs.get("debug") or "0",
            "CFG_IN_TREE_EARLY_TAS": "trusted_keys/f04a0fe7-1f5d-4b9b-abf7-619b85b4ce8c",
            "CFG_SCP_FIRMWARE": os.path.join(self.ctx.third_party_path, "scp-firmware"),
        }

        dt_file = kwargs.get("dt_file")
        print(f"{dt_file=}")
        if dt_file:
            env["CFG_DT"]="y"
            env["CFG_EMBED_DTB"]="y"
            env["CFG_STM32MP13"]="y"
            env["CFG_WITH_TUI"]="n"
            env["CFG_DRAM_SIZE"]="0x20000000" # Without this config optee sets 1GB ram and we crash
                                              #  cause optee expect it's code elswhere.
            env["CFG_EMBED_DTB_SOURCE_FILE"]=os.path.basename(dt_file)
            self.ctx.c.run(f"cp {dt_file} {os.path.join(OPTEE_PATH, 'core', 'arch', 'arm', 'dts',env['CFG_EMBED_DTB_SOURCE_FILE'])}")

        try:
            with self.ctx.c.cd(os.path.join(self.ctx.third_party_path, "optee-os")):
                run_make(self.ctx.c, "-j 4 all", env)
                self.ctx.c.run(f"mkdir -p {self.ctx.build_path}")

                copy_src = os.path.join(
                    self.ctx.third_party_path,
                    "optee-os",
                    "out",
                    "arm-plat-stm32mp1",
                    "core",
                )
                self.copy_paths = [
                    os.path.join(copy_src, "tee.bin"),
                    os.path.join(copy_src, "tee-raw.bin"),
                    os.path.join(copy_src, "tee-*_v2.bin"),
                ]

        except Exception:
            pr_error("Building optee os failed")
            raise

        pr_info("Building optee os completed")
