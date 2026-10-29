#include <Library/MemoryMapLib.h>

//
// Memory map for the Xiaomi Redmi K90 Pro Max ("songyuan", Qualcomm SM8850
// "canoe"), reconciled with this phone's live merged device tree:
//
//   E:\songyuan\dl\live.dtb
//   sha256 443905c8dcea7e7fee7763ad6053df2784539ae2ac6837fb53a05f8797c0e088
//
// Every DDR reservation below is a /reserved-memory node of that DT; the node
// path and its reg=<base size> are on the same line. live.dtb has 64 children
// under /reserved-memory: 48 with a non-zero reg (all listed here), 14 that only
// carry size/alloc-ranges (the OS allocates them at runtime, so there is no fixed
// address to reserve) and 2 zero-length demura regions. The FDT memory
// reservation block is empty.
//
// live.dtb /memory is already a usable-RAM list (21 reg entries, one of them
// zero length; 20 non-empty ranges totalling 0x2D2645800 bytes), and it does not
// contain most /reserved-memory regions. "Inside /memory" is therefore not the
// test for a reservation; the /reserved-memory node itself is the evidence.
//
// Caching policy (DT does not describe attributes): a region that the previous
// map already covered at the same base keeps the previous attribute choice;
// otherwise no-map reservations are mapped UNCACHED_UNBUFFERED_XN and reusable
// reservations WRITE_BACK_XN.
//
// Firmware-internal DDR (the UEFI FD, stack, heaps, kernel and XNU payload
// window) is not in the DT. Those lines are marked TODO and cite the file that
// does define them (Resources/Configs/songyuan.toml, docs/BOOT-CONTRACT.md or the
// previous map); they are not DT-grounded.
//
// The only conventional (usable) DDR range is DXE_HEAP. It lies inside
// /memory <0xA6980000 0x1D450000>, overlaps no /reserved-memory node and ends
// exactly where /reserved-memory/hypervisor_extended_heap_region@0xC3DD0000
// begins.
//
STATIC
EFI_MEMORY_REGION_DESCRIPTOR
gMemoryDescriptor[] = {
  // Name, Address, Length, HobOption, ResourceType, ResourceAttribute, MemoryType, ArmAttribute

  // DDR Regions reserved by the device tree (/reserved-memory/*, 48 fixed nodes)
  {"GUNYAH_HYP_REGION",    0x80000000, 0x00E00000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/gunyah_hyp_region@80000000 reg=<0x0 0x80000000 0x0 0xE00000> no-map
  {"RESERVED_REGION",      0x80E00000, 0x00400000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/reserved_region@80e00000 reg=<0x0 0x80E00000 0x0 0x400000> no-map
  {"CPUCP_PDP_REGION",     0x81200000, 0x00200000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/cpucp_pdp_region@81200000 reg=<0x0 0x81200000 0x0 0x200000> no-map
  {"XBL_DTLOG_REGION",     0x81A00000, 0x00060000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/xbl_dtlog_region@81a00000 reg=<0x0 0x81A00000 0x0 0x60000> no-map
  {"AOP_IMAGE_REGION",     0x81C00000, 0x00060000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/aop_image_region@81c00000 reg=<0x0 0x81C00000 0x0 0x60000> no-map
  {"AOP_CMD_DB_REGION",    0x81C60000, 0x00020000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/aop_cmd_db_region@81c60000 reg=<0x0 0x81C60000 0x0 0x20000> no-map
  {"AOP_TME_UEFI_MERGED_", 0x81C80000, 0x00074000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/aop_tme_uefi_merged_region@81c80000 reg=<0x0 0x81C80000 0x0 0x74000> no-map
  {"SMEM_REGION",          0x81D00000, 0x00200000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/smem_region@81d00000 reg=<0x0 0x81D00000 0x0 0x200000> no-map
  {"PDP_NS_SHARED_REGION", 0x81F00000, 0x00100000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/pdp_ns_shared_region@81f00000 reg=<0x0 0x81F00000 0x0 0x100000> no-map
  {"CPUCP_SCANDUMP_REGIO", 0x82000000, 0x00380000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/cpucp_scandump_region@82000000 reg=<0x0 0x82000000 0x0 0x380000> no-map
  {"ADSP_MHI_REGION",      0x82380000, 0x00020000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/adsp_mhi_region@82380000 reg=<0x0 0x82380000 0x0 0x20000> no-map
  {"SOCCP_SDI_REGION",     0x823A0000, 0x00040000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/soccp_sdi_region@823a0000 reg=<0x0 0x823A0000 0x0 0x40000> no-map
  {"PMIC_MINII_DUMP_REGI", 0x823E0000, 0x00080000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/pmic_minii_dump_region@823e0000 reg=<0x0 0x823E0000 0x0 0x80000> no-map
  {"QUP_FW_REGION",        0x82460000, 0x00018000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/qup_fw_region@82460000 reg=<0x0 0x82460000 0x0 0x18000> no-map
  {"PVM_FW_REGION",        0x824A0000, 0x00100000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/pvm_fw_region@824a0000 reg=<0x0 0x824A0000 0x0 0x100000> no-map
  {"TZ_STAT_REGION",       0x82700000, 0x00100000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/tz_stat_region@82700000 reg=<0x0 0x82700000 0x0 0x100000> no-map
  {"QDSS_APPS_REGION",     0x82800000, 0x02000000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/qdss_apps_region@82800000 reg=<0x0 0x82800000 0x0 0x2000000> reusable
  {"DSM_PARTITION_1_REGI", 0x84A00000, 0x05500000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/dsm_partition_1_region@84a00000 reg=<0x0 0x84A00000 0x0 0x5500000> no-map
  {"DSM_PARTITION_2_REGI", 0x89F00000, 0x00A80000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/dsm_partition_2_region@89f00000 reg=<0x0 0x89F00000 0x0 0xA80000> no-map
  {"MPSS_REGION",          0x8AA00000, 0x0EB00000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/mpss_region@8aa00000 reg=<0x0 0x8AA00000 0x0 0xEB00000> no-map
  {"Q6_MPSS_DTB_REGION",   0x99500000, 0x00080000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/q6_mpss_dtb_region@99500000 reg=<0x0 0x99500000 0x0 0x80000> no-map
  {"IPA_FW_REGION",        0x99580000, 0x00010000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/ipa_fw_region@99580000 reg=<0x0 0x99580000 0x0 0x10000> no-map
  {"IPA_GSI_REGION",       0x99590000, 0x0000A000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/ipa_gsi_region@99590000 reg=<0x0 0x99590000 0x0 0xA000> no-map
  {"GPU_MICROCODE_REGION", 0x9959A000, 0x00002000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/gpu_microcode_region@9959a000 reg=<0x0 0x9959A000 0x0 0x2000> no-map
  {"CAMERA_REGION",        0x99600000, 0x00800000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/camera_region@99600000 reg=<0x0 0x99600000 0x0 0x800000> no-map
  {"CAMERA_2_REGION",      0x99E00000, 0x00800000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/camera_2_region@99e00000 reg=<0x0 0x99E00000 0x0 0x800000> no-map
  {"VIDEO_REGION",         0x9A600000, 0x00800000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/video_region@9a600000 reg=<0x0 0x9A600000 0x0 0x800000> no-map
  {"CVP_REGION",           0x9AE00000, 0x00700000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/cvp_region@9ae00000 reg=<0x0 0x9AE00000 0x0 0x700000> no-map
  {"CDSP_REGION",          0x9B500000, 0x01900000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/cdsp_region@9b500000 reg=<0x0 0x9B500000 0x0 0x1900000> no-map
  {"Q6_CDSP_DTB_REGION",   0x9CE00000, 0x00080000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/q6_cdsp_dtb_region@9ce00000 reg=<0x0 0x9CE00000 0x0 0x80000> no-map
  {"DCP_DTB_REGION",       0xA0050000, 0x00080000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/dcp_dtb_region@a0050000 reg=<0x0 0xA0050000 0x0 0x80000> no-map
  {"DCP_REGION",           0xA00D0000, 0x00300000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/dcp_region@a00d0000 reg=<0x0 0xA00D0000 0x0 0x300000> no-map
  {"SOCCP_REGION",         0xA03D0000, 0x00500000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/soccp_region@a03d0000 reg=<0x0 0xA03D0000 0x0 0x500000> no-map
  {"SOCCP_DTB_REGION",     0xA08D0000, 0x00040000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/soccp_dtb_region@a08d0000 reg=<0x0 0xA08D0000 0x0 0x40000> no-map
  {"Q6_ADSP_DTB_REGION",   0xA1380000, 0x00080000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/q6_adsp_dtb_region@a1380000 reg=<0x0 0xA1380000 0x0 0x80000> no-map
  {"ADSPSLPI_REGION",      0xA1400000, 0x05580000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/adspslpi_region@a1400000 reg=<0x0 0xA1400000 0x0 0x5580000> no-map
  {"HYPERVISOR_EXTENDED_", 0xC3DD0000, 0x00A30000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/hypervisor_extended_heap_region@0xc3dd0000 reg=<0x0 0xC3DD0000 0x0 0xA30000> no-map
  {"XBL_RAMDUMP_REGION",   0xD7800000, 0x00200000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/xbl_ramdump_region@d7800000 reg=<0x0 0xD7800000 0x0 0x200000> no-map
  {"GLOBAL_SYNC_REGION",   0xD7A00000, 0x00200000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/global_sync_region@d7a00000 reg=<0x0 0xD7A00000 0x0 0x200000> no-map
  {"TZ_MERGED_REGION",     0xD8000000, 0x00800000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/tz_merged_region@d8000000 reg=<0x0 0xD8000000 0x0 0x800000> no-map
  {"TRUST_UI_VM_REGION",   0xF3800000, 0x05000000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/trust_ui_vm_region@f3800000 reg=<0x0 0xF3800000 0x0 0x5000000> reusable
  {"OEM_VM_REGION",        0xF8800000, 0x03800000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/oem_vm_region@f8800000 reg=<0x0 0xF8800000 0x0 0x3800000> reusable
  {"SHM",                  0xFC200000, 0x00400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/shm@fc200000 reg=<0x0 0xFC200000 0x0 0x400000> reusable
  {"SPLASH_REGION",        0xFC800000, 0x02B00000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH_XN}, // /reserved-memory/splash_region reg=<0x0 0xFC800000 0x0 0x2B00000> label="cont_splash_region"
  {"DUMP_DISPLAY_REGION",  0xFF3FF800, 0x00000800, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/dump_display_region@ff3ff800 reg=<0x0 0xFF3FF800 0x0 0x800> no-map
  {"RAMOOPS_REGION",       0xFF400000, 0x00200000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/ramoops-region reg=<0x0 0xFF400000 0x0 0x200000> compatible="ramoops"
  {"LLCC_LPI_REGION",      0xFF800000, 0x00800000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED_XN}, // /reserved-memory/llcc_lpi_region@ff800000 reg=<0x0 0xFF800000 0x0 0x800000> no-map
  {"LCP_DARE_REGION",      0x880000000, 0x06000000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN}, // /reserved-memory/lcp_dare_region reg=<0x0 0x880000000 0x0 0x6000000> reusable

  // DDR Regions used by the firmware/loader - NOT in the device tree (TODO)
  // TODO: FD_Reserved is not a DT node; inherited from the previous songyuan-uefi map.
  {"FD_Reserved",          0xA7000000, 0x00100000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
  // TODO: FD base/size are NOT DT values; they come from Resources/Configs/songyuan.toml
  // [uefi_fd] base = 0xA7100000, size = 0x300000 (same value the BootShim is built with).
  {"UEFI_FD",              0xA7100000, 0x00300000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
  // TODO: FD_Reserved tail not in DT; inherited from the previous map.
  {"UEFI_FD_Reserved",     0xA7400000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
  // TODO: firmware-internal block 0xA7601000..0xA7FFF000 not in DT; inherited layout.
  {"Info_Blk",             0xA7601000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
  {"MMU_PageTables",       0xA7602000, 0x00003000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  {"Log_Buffer",           0xA7605000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
  {"UEFI_Stack",           0xA760D000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  {"SEC_Heap",             0xA764D000, 0x0008C000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  {"Sched_Heap",           0xA76D9000, 0x00400000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  {"FV_Region",            0xA7AD9000, 0x00400000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  {"UEFI_RESV",            0xA7ED9000, 0x00127000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
  // TODO: kernel load window is not in the DT; inherited from the previous map.
  {"Kernel",               0xA8000000, 0x10000000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
  // TODO: XNU payload window is not in the DT. Value from docs/BOOT-CONTRACT.md
  // (PAYLOAD_BASE 0xF0000000, PAYLOAD_RESERVE_SIZE 0x03800000); its end coincides
  // with /reserved-memory/trust_ui_vm_region@f3800000 in live.dtb.
  {"XNU_Payload",          0xF0000000, 0x03800000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
  // TODO: DXE heap is not in the DT. This window is inside live.dtb /memory
  // <0xA6980000 0x1D450000>, starts after the Kernel window and ends exactly at
  // /reserved-memory/hypervisor_extended_heap_region@0xC3DD0000.
  {"DXE_Heap",             0xB8000000, 0x0BDD0000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

  // Other Memory Regions
  // MMIO: unchanged from the previous map, not part of the /reserved-memory
  // reconciliation (live.dtb does carry /soc/qcom,msm-imem@14680000).
  {"IMEM Base",            0x14680000, 0x0002A000, NoHob,  MMAP_IO, INITIALIZED, Conv, NS_DEVICE},
  {"IMEM Cookie Base",     0x146AA000, 0x00016000, AddDev, MMAP_IO, INITIALIZED, Conv, NS_DEVICE},

  // Register Regions
  // MMIO windows: unchanged from the previous map (no /reserved-memory node).
  {"IPC_ROUTER_TOP",       0x00400000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"SECURITY CONTROL",     0x00780000, 0x00007000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"QUP",                  0x00800000, 0x00300000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"PRNG_CFG_PRNG",        0x010C0000, 0x0000C000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"CRYPTO0 CRYPTO",       0x01DC0000, 0x00040000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"CORE_TOP_CSR",         0x01F00000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"PERIPH_SS",            0x08800000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"USB",                  0x0A600000, 0x00200000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"AOSS",                 0x0B000000, 0x04000000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"TLMM",                 0x0F000000, 0x01000000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"SMMU",                 0x15000000, 0x00200000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE},
  {"APSS_HM",              0x17000000, 0x02000000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, NS_DEVICE}
};

VOID
GetMemoryMap (
  OUT EFI_MEMORY_REGION_DESCRIPTOR **MemoryDescriptor,
  OUT UINT8                         *MemoryDescriptorCount)
{
  // Pass Data
  *MemoryDescriptor      = gMemoryDescriptor;
  *MemoryDescriptorCount = ARRAY_SIZE (gMemoryDescriptor);
}
