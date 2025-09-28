### Vendoring TF-A via `git subtree` (no submodules)

```bash
# 0) From your repo root, pick a target folder
mkdir -p third_party

# 1) Add TF-A remote
git remote add tf-a https://review.trustedfirmware.org/TF-A/trusted-firmware-a.git
git fetch tf-a

# 2) Import into your tree (squashed history)
git subtree add --prefix=third_party/tf-a tf-a master --squash

# 3) Update later
git fetch tf-a
git subtree pull --prefix=third_party/tf-a tf-a master --squash

# 4) (optional) If you modify TF-A locally and want to upstream your changes
git subtree push --prefix=third_party/tf-a tf-a my-tfa-branch
```

Notes:

* `--prefix` is where TF-A lives inside your repo.
* Use `--squash` to keep your history compact; drop it if you want full upstream history.
