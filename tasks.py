###############################################
#                Imports                      #
###############################################
import glob
import os
import shutil
import subprocess

from invoke import task

###############################################
#                Public API                   #
###############################################
ROOT_PATH = os.path.dirname(os.path.abspath(__file__))
SRC_PATH = os.path.join(ROOT_PATH, "src")
OS_PATH = os.path.join(ROOT_PATH, "os")
BUILD_PATH = os.path.join(ROOT_PATH, "build")


@task
def install(c):
    """
    Install Ansible and sshpass on the system if they are not already installed.

    Usage:
        inv install
    """

    _pr_info("Installing Dependencies...")
    try:
        if _command_exists("pip"):
            c.run(
                "pip install ansible lxml jmespath && "
                "ansible-galaxy collection install devsec.hardening l3d.git "
                "prometheus.prometheus grafana.grafana && "
                "ansible-galaxy role install geerlingguy.docker",
                warn=True,
            )
            _pr_info("Ansible installed successfully.")
        else:
            _pr_error("'pip' command not found. Unable to install Ansible.")
            return
    except Exception as e:
        _pr_error(f"Error installing Ansible: {e}")
        return


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
    patterns = ["build/*", "**/*~*", "**/*#*", "*~*", "*#*"]

    if bytecode:
        patterns.append("**/*.pyc")
    if extra:
        patterns.append(extra)

    for pattern in patterns:
        _pr_info(f"Removing files matching pattern '{pattern}'")

        # Use glob to find files recursively and remove each one
        for path in glob.glob(pattern, recursive=True):
            if os.path.isfile(path):
                os.remove(path)
                print(f"Removed file {path}")
            elif os.path.isdir(path):
                shutil.rmtree(path)
                print(f"Removed directory {path}")

    _pr_info("Clean up completed.")


###############################################
#                Private API                  #
###############################################
def _command_exists(command):
    try:
        # Attempt to run the command with '--version' or any other flag that doesn't change system state
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
