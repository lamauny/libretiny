# Copyright (c) Etienne Le Cousin 2024-02-08.

from os.path import join

from platformio.platform.board import PlatformBoardConfig
from SCons.Script import Builder, DefaultEnvironment, Environment

env: Environment = DefaultEnvironment()
board: PlatformBoardConfig = env.BoardConfig()
queue = env.AddLibraryQueue("lightning-ln882h")
env.ConfigureFamily()

# Flags
queue.AppendPublic(
    CCFLAGS=[
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mabi=aapcs",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
        "-fno-short-enums",
        "-Wfatal-errors",
        "-ffunction-sections",
        "-fdata-sections",
        "-fno-strict-aliasing",
        "-MD","-MP",
#        "-O1","-DNDEBUG",
    ],
    CFLAGS=[
        "-Wpointer-arith",
        "-Wno-write-strings",
        "-Wno-maybe-uninitialized",
#        "-Wall",
#        "-Wextra",
#        "-Wundef",
#        "-Wshadow",
#        "-Wredundant-decls",
#        "-Wstrict-prototypes",
#        "-Wimplicit-function-declaration",
#        "-Wmissing-prototypes",
#        "-Wdouble-promotion",
#        "-Wfloat-conversion",
#        "-Wformat=2",
    ],
    CXXFLAGS=[
#        "-Wall",
#        "-Wextra",
#        "-Wundef",
#        "-Wshadow",
#        "-Wredundant-decls",
#        "-Wmissing-prototypes",
#        "-Wdouble-promotion",
#        "-Wfloat-conversion",
    ],
    CPPDEFINES=[
        # other options
        "ARM_MATH_CM4",
        "LN882H",
        ("PLATFORM_LN882H","1"),
        ("MBEDTLS_CONFIG_FILE",r"\"mbedtls_config.h\""),
    ],
    ASFLAGS=[
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mabi=aapcs",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
        "-g",
        "-c",
    ],
    LINKFLAGS=[
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mabi=aapcs",
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16",
        "--specs=nano.specs",
        # stdio wrappers (base/port/printf.c)
        "-Wl,-wrap,ln_printf",
        "-Wl,--gc-sections",
    ],
)
queue.AppendPrivate(
    CFLAGS=[
        "-Wno-implicit-function-declaration",
        "-Wno-incompatible-pointer-types",
        "-Wno-int-conversion",
        "-Wno-pointer-sign",
        "-Wfatal-errors",
        "-ffunction-sections",
        "-fdata-sections",
        "-fno-strict-aliasing",
        "-std=gnu99",
        "-MD","-MP",
    ],
)

# Boot files - from SDK project/wifi_mcu_basic_example
"""
queue.AddLibrary(
    name="ln882h_boot",
    base_dir="$SDK_DIR/project/wifi_mcu_basic_example",
    srcs=[
        "+<startup/startup_ln882h_gcc.c>",
        ],
)
"""
# Sources
queue.AddLibrary(
    name="ln882h_sdk",
    base_dir="$SDK_DIR",
    srcs=[
        # MCU
        "+<mcu/ln882h/system_ln882h.c>"
        # Hal
        "+<mcu/driver_ln882h/hal/*.c>",
        # FreeRTOS
#        "+<components/kernel/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c>",
        "+<components/kernel/FreeRTOS_Adapter/*.c>",
        # Serial
        "+<components/serial/serial.c>",
        # Misc
        "+<components/fs/nvds/ln_nvds.c>",
        "+<components/fs/kv/kv/ln_kv.c>",
        "+<components/fs/kv/kv_port/ln_kv_port.c>",
        "+<components/utils/fifo/fifobuf.c>",
        "+<components/utils/debug/log.c>",
        "+<components/utils/debug/CmBacktrace/cm_backtrace.c>",
        "+<components/utils/system_parameter.c>",
        "+<components/utils/power_mgmt/ln_pm.c>",
        "+<components/utils/runtime/runtime.c>",
        "+<components/utils/reboot_trace/reboot_trace.c>",
        "+<components/tencent/qcloud_iot_c_sdk/external_libs/cJSON/cJSON.c>",
    ],
    includes=[
        # MCU
        "+<mcu/CMSIS_5.3.0>",
        "+<mcu/ln882h>",
        # Hal
        "+<mcu/driver_ln882h>",
        "+<mcu/driver_ln882h/reg>",
        "+<mcu/driver_ln882h/hal>",
        # Components
        "+<components>",
        # FreeRTOS
        "+<components/kernel>",
#        "+<components/kernel/FreeRTOS/Source/include>",
        "+<components/kernel/FreeRTOS/Source/portable/GCC/ARM_CM4F>",
        "+<components/kernel/FreeRTOS_Adapter>",
        "+<components/kernel/osal>",
        # Misc
        "+<components/fs/nvds>",
        "+<components/fs/kv/kv>",
        "+<components/fs/kv/kv_port>",
        "+<components/serial>",
        "+<components/utils/debug/CmBacktrace>",
        "+<components/utils/power_mgmt>",
        #"+<components/utils/runtime>",
        "+<components/utils/reboot_trace>",
        "+<components/tencent/qcloud_iot_c_sdk/external_libs/cJSON>",
    ],
    options=dict(
        CPPDEFINES=["LN882H_SDK"],
        CFLAGS=["-w"],
    ),
)

queue.AddLibrary(
    name="ln882h_net",
    base_dir="$SDK_DIR",
    srcs=[
        # WiFi
        "+<components/wifi/wifi_manager/wifi_manager.c>",
        "+<components/wifi/wifi_lib_import/wifi_port.c>",
        # DHCPD
        "+<components/net/dhcpd/*.c>",
        # Utils
        "+<components/utils/ln_misc.c>",
        "+<components/utils/ln_sha1.c>",
        "+<components/utils/ln_aes.c>",
        "+<components/utils/ln_psk_calc.c>",
    ],
    includes=[
        "+<components/wifi/wifi_manager>",
        "+<components/wifi/wifi_lib_import>",
        "+<components/wifi/wifi_lib_export>",
        "+<components/net/dhcpd>",
    ],
    options=dict(
        CPPDEFINES=["LN882H_SDK"],
        CFLAGS=["-w"],
    ),
)


# Sources - FreeRTOS
env.Replace(FREERTOS_PORT=env["FAMILY_NAME"], FREERTOS_PORT_DEFINE="LIGHTNING_LN882H")
queue.AddExternalLibrary("freertos")
queue.AddExternalLibrary("freertos-port")

# Sources - lwIP
queue.AddExternalLibrary("lwip", port="ln882h")

# Sources - mbedTLS
queue.AddLibrary(
    name="ln882h_mbedtls",
    base_dir="$SDK_DIR",
    srcs=[
        # mbedTLS from SDK
        "+<components/net/mbedtls/library/*.c>",
        # replace this with a port specific
        "-<components/net/mbedtls/library/net_sockets.c>",
        "-<components/net/mbedtls/library/platform.c>",
        "-<components/net/mbedtls/library/threading_alt.c>",
        "-<components/net/mbedtls/library/timing.c>",
        # ln port
        "+<components/net/mbedtls/port_ln/library/*.c>",
    ],
    includes=[
        "+<components/net/mbedtls/include>",
        "+<components/net/mbedtls/port_ln/include>",
    ],
    options=dict(
        CPPDEFINES=["LN882H_SDK"],
        CFLAGS=["-w"],
    ),
)

# Libs & linker config
queue.AppendPublic(
    LIBPATH=[
        # fmt: off
        join("$SDK_DIR", "lib", "gcclib"),
        # fmt: on
    ],
    LIBS=[
        "arm_cortexM4lf_math",
        "ln882h_wifi",
        "m",
        "c",
        "nosys",
        "gcc",
   ],
)

# Misc options
# env.Replace(
#     SIZEPROGREGEXP=r"^(?:\.vectors|\.text|\.rodata|\.data|\.ARM\.exidx)\s+([0-9]+).*",
#     SIZEDATAREGEXP=r"^(?:\.vectors|\.data|\.bss)\s+([0-9]+).*",
#     SIZECHECKCMD="$SIZETOOL -A -d $SOURCES",
#     SIZEPRINTCMD="$SIZETOOL -B -d $SOURCES",
# )
# Generate linker scripts with correct flash offsets
env.GenerateLinkerScript(board, board.get("build.ldscript"))

env.Append(
    BUILDERS=dict(
        BinToObj=Builder(
            action=" ".join(
                [
                    "$OBJCOPY",
                    "-I binary",
                    "-O elf32-littlearm",
                    "-B arm",
                    "$SOURCE",
                    "$TARGET",
                ],
            ),
        ),
        ObjToBin=Builder(
            action=" ".join(
                [
                    "$OBJCOPY",
                    "-I elf32-littlearm",
                    "-O binary",
                    "$SOURCE",
                    "$TARGET",
                ],
            ),
        )
    ),
)


# Build all libraries
queue.BuildLibraries()

# Main firmware outputs and actions
#env.Replace(
#    # linker command (tbd)
#    LINK="${LTCHIPTOOL} link2bin ${BOARD_JSON} '' ''",
#    # UF2OTA input list
#    UF2OTA=[
#        # same OTA images for flasher and device
#        f"{image_ota1},{image_ota2}=device:ota1,ota2;flasher:ota1,ota2",
#    ],
#)
env.Replace(
    UF2OTA=[],
)

env.Append(
    BUILDERS=dict(
        BinToFirmware=Builder(
            action=" ".join(
                [
                    "${LTPYTHONEXE}",
                    "${SDK_DIR}/tools/python_scripts/makeimage.py",
                    "--boot ${SDK_DIR}/lib/boot_ln882h.bin",
                    "--app $SOURCE",
                    "--output $TARGET",
                    "--part ${FAMILY_DIR}/base/config/flash_partition_cfg.json",
                    "--ver 1.0",
                    "--crp 0",
                ],
            ),
        ),
        FirmwareToOTA=Builder(
            action=" ".join(
                [
                    "${LTPYTHONEXE}",
                    "${SDK_DIR}/tools/python_scripts/ota_image_generator.py",
                    "$SOURCE",
                ],
            ),
        ),
    ),
)

target_bin = join("${BUILD_DIR}", "${PROGNAME}.bin")
target_elf = join("${BUILD_DIR}", "${PROGNAME}.elf")
target_fw  = join("${BUILD_DIR}", "firmware.bin")
target_uf2 = join("${BUILD_DIR}", "firmware.uf2")

AlwaysBuild(env.Alias("nobuild", target_uf2))

# Build bin from elf
env.AddPostAction(target_elf, env.ObjToBin(target_bin, target_elf))
env.Depends(target_bin, target_elf)

# Build firmware from bin
env.AddPostAction(target_bin, env.BinToFirmware(target_fw, target_bin))
env.Depends(target_fw, target_bin)

# Build OTA from firmware
target_ota = env.Alias("OTA", env.FirmwareToOTA(source=target_fw))
env.Depends(target_uf2, target_ota)

# Build UF2
env.AddPostAction(target_fw,  env.VerboseAction("cp ${BUILD_DIR}/firmware.bin ${BUILD_DIR}/firmware.uf2", "Fake UF2 generation..."))
env.Depends(target_uf2, target_fw)
