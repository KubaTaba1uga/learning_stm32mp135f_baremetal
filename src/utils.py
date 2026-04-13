import importlib.util
import os
import subprocess

def command_exists(command):
    try:
        subprocess.run(
            ["which", command], stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        return True
    except Exception:
        return False


def pr_info(message: str):
    """
    Print an informational message in blue color.

    Args:
        message (str): The message to print.

    Usage:
        pr_info("This is an info message.")
    """
    print(f"\033[94m[INFO] {message}\033[0m")


def pr_warn(message: str):
    """
    Print a warning message in yellow color.

    Args:
        message (str): The message to print.

    Usage:
        pr_warn("This is a warning message.")
    """
    print(f"\033[93m[WARN] {message}\033[0m")


def pr_debug(message: str):
    """
    Print a debug message in cyan color.

    Args:
        message (str): The message to print.

    Usage:
        pr_debug("This is a debug message.")
    """
    print(f"\033[96m[DEBUG] {message}\033[0m")


def pr_error(message: str):
    """
    Print an error message in red color.

    Args:
        message (str): The message to print.

    Usage:
        pr_error("This is an error message.")
    """
    print(f"\033[91m[ERROR] {message}\033[0m")


def run_make(ctx, command, env):
    ctx.run(
        f"make {command} " + " ".join([f"{arg}={env[arg]}" for arg in env]),
        env=env,
    )

def import_builder_modules(root_dir):
    for current_path, dirnames, filenames in os.walk(root_dir):
        # Filter out directories starting with . or _
        dirnames[:] = [d for d in dirnames if not d.startswith(('.', '_'))]

        if "builder.py" in filenames:
            file_path = os.path.join(current_path, "builder.py")
            
            module_name = os.path.relpath(file_path, root_dir) \
                .replace(os.sep, ".") \
                .rstrip(".py")

            try:
                spec = importlib.util.spec_from_file_location(module_name, file_path)
                module = importlib.util.module_from_spec(spec)
                spec.loader.exec_module(module)

                pr_debug(f"Imported: {module_name}")

            except Exception as e:
                pr_warn(f"Failed to import {file_path}: {e}")
    
