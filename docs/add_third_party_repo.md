# 📦 Managing Third-Party Repositories

This document explains how to locate and integrate third-party repositories (e.g., OP-TEE, TF-A) directly into your project using `git subtree`.

---

## 🔍 Where to Find Third-Party Repositories

A good starting point is the official **OP-TEE manifest**:
➡️ [https://github.com/OP-TEE/manifest/tree/master](https://github.com/OP-TEE/manifest/tree/master)

The current version used in this project is:

```text
v4.6.0
```

---

## 🧩 Adding a Third-Party Repository In-Tree (via `git subtree`)

Follow these steps to import and manage a third-party project inside your repo.

```bash
# 0) From your repository root, create a target folder
mkdir -p third_party

# 1) Ensure your working tree is clean
git status

# If you have uncommitted changes:
git add . && git commit -m "WIP"
# or stash them temporarily:
git stash push -m "temp"

# 2) Add the remote of the third-party project
git remote add tf-a https://review.trustedfirmware.org/TF-A/trusted-firmware-a.git
git fetch tf-a

# 3) Import the repository (squashed history)
git subtree add --prefix=third_party/tf-a tf-a v2.9 --squash

# 4) Update later when upstream changes
git fetch tf-a
git subtree pull --prefix=third_party/tf-a tf-a v2.10 --squash
```

---

✅ **Result:**
The third-party code is now available under `third_party/tf-a`, fully integrated but isolated for easy updates.

---
