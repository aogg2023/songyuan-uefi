# songyuan-uefi

Mu-Silicium platform package for the Redmi K90 Pro Max (**songyuan**, SM8850 / Canoe),
derived from the OnePlus 15 package (`astonPkg`, the same SoC) so the device can be
started with `fastboot boot` instead of flashing anything.

## What is here

| Path | Purpose |
|---|---|
| `Platforms/Xiaomi/songyuanPkg/` | the Mu-Silicium platform package: `DeviceBuild.py`, `.dsc/.fdf/.dec`, `Include/*.inc` driver lists, `Library/MemoryMapLib` and `Library/ConfigurationMapLib` |
| `Resources/Configs/songyuan.toml` | UEFI FD base/size (`0xA7100000` + `0x300000`) and the boot image shape (`header_version = 0`, gzip kernel, DTB appended) |
| `.github/workflows/build.yml` | clones Mu-Silicium, overlays this package, and builds `Build/songyuanPkg/RELEASE_CLANGPDB/FV/SILICIUM_UEFI.fd` on Linux |

## How it is used

`unixnu build firmware --uefi <this checkout>` in UniXNU overlays the package into a
Mu-Silicium tree and produces the firmware volume that `unixnu bootimg` wraps together
with BootShim and the device tree. The resulting `boot.img` is started with `fastboot
boot`; nothing is written to the phone.

## Status

Builds with the upstream Mu-Silicium `astonPkg` files renamed. The memory map is the
aston one, which already matches this SoC family; it still has to be reconciled with
the reserved regions of the songyuan device tree before the first boot
(`/memory` ranges and 48 `reserved-memory` nodes are recorded in
`UniXNU-songyuan/reference/songyuan-fdt.dtb` on the development machine).

The OnePlus 15 ACPI tables (`Silicium-ACPI/Platforms/OnePlus/aston`) are reused because
both boards are SM8850; per-device ACPI can come later.

## License

BSD-2-Clause-Patent.
