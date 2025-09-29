# Where find third party repos

Good starting point is optee manifest https://github.com/OP-TEE/manifest/tree/master. Current version of optee manifest used by this project is v4.6.0.

## How to add a third-party repo in-tree (using `git subtree`)

```bash
# 0) From your repo root, pick a target folder
mkdir -p third_party

# 1) Make sure your working tree is clean
git status

# If you have changes:
git add . && git commit -m "WIP"    # or stash them: git stash push -m "temp"

# 2) Add the remote of the third-party project
git remote add tf-a https://review.trustedfirmware.org/TF-A/trusted-firmware-a.git
git fetch tf-a

# 3) Import the code (squashed history)
git subtree add --prefix=third_party/tf-a tf-a v2.9 --squash

# 4) Update later when upstream changes
git fetch tf-a
git subtree pull --prefix=third_party/tf-a tf-a v2.10 --squash
```
