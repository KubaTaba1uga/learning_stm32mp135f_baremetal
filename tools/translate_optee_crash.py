import argparse
import subprocess

def main():
    args = parse_args()

    with open(args.filename, "r") as fp:
        log = fp.read()

    addrs = set()

    for line in log.split("\n"):
        if line.startswith("E/TC:0 0  0x"):
            addrs.add(line.replace("E/TC:0 0  ", ""))

    print(f"{addrs=}")
    for addr in addrs:
        with subprocess.Popen(["addr2line", "-e", "third_party/optee-os/out/arm-plat-stm32mp1/core/tee.elf", addr], stdout=subprocess.PIPE) as proc:
            translation = proc.stdout.read().decode().replace("\n", "")
            log = log.replace(addr, translation)

    print(log)
    
def parse_args():
    parser = argparse.ArgumentParser(
    prog='translate_optee_crash.py',
    description='Translate memory addresses in optee crash into functions, files and line numbers.')

    parser.add_argument('filename')
    return parser.parse_args()


if __name__ == "__main__":
    main()
