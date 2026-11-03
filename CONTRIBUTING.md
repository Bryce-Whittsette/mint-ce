# Contributing

Thanks for helping improve Mint CE.

## Build

Install the CE C/C++ Toolchain, ensure `cedev-config` is on your `PATH`, and run:

```sh
make
```

The program should build to `bin/MINTCE.8xp` without new compiler warnings. Do not replace `release/MINTCE.8xp` unless the source build succeeds and the binary is intentionally prepared for a release.

## Calculator validation

For hardware-facing changes, report the calculator model and OS version, transfer method, and launcher used. Check all four launcher directions, open and close every view, hold Enter and Clear to check key-release handling, move through terminal previews, and return cleanly to the calculator OS.

## Pull requests

Keep simulated features clearly labeled; the terminal and file list do not execute Linux commands or enumerate calculator variables. Prefer small patches, describe visual or control changes, include build and hardware-test evidence, update the README for user-visible behavior, and add a concise entry under **Unreleased** in `CHANGELOG.md`.
