import os
from typing import Any, List
from dataclasses import dataclass

@dataclass
class PackageCtx:
    c: Any
    root_path: str
    third_party_path: str
    build_path: str
    toolchain_path: str
    src_path: str


class PackageBuilder:
    dependencies: List = [] # List[PackageBuilder]

    def __init__(self, ctx: PackageCtx):
        self.ctx = ctx

    def build(self):
        raise NotImplementedError()

    def install(self, runetime_deps: List):
        raise NotImplementedError()


class PackageCopyInstaller:
    copy_paths: List[str] = []
    ctx: PackageCtx

    def install(self, runetime_deps: List):
        for path in self.copy_paths:
            if not os.path.exists(path):
                raise RuntimeError(f"No file to install {path}")
            self.ctx.c.run(f"cp {path} {self.ctx.build_path}")
        
