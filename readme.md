# Hello AOSP (`hello_aosp`)

`hello_aosp` is a native C++ demonstration binary for the Android Open Source Project (AOSP). It initializes the Android base logging system (`logd`), prints device information using the `lib_device_info` shared library, and outputs a diagnostic log message directly to Logcat.

> **Tested Environment:** This module has been tested and verified on an AOSP **Goldfish** emulator (`aosp_cf_x86_64_phone` / `sdk_phone_x86_64`).

## Prerequisites & Dependencies

1. **AOSP Source Tree**: A properly initialized and synchronized AOSP build environment.
2. **`lib_device_info` Dependency**:
   * This binary dynamically links against `lib_device_info` (`shared_libs: ["lib_device_info"]`).
   * The repository providing `lib_device_info` must be present and configured in your AOSP tree so the build system can resolve the header (`<lib_device_info.h>`) and the shared library at build time.

## Installation & Placement

Clone this repository into the `system/extras` directory relative to your AOSP root:

```bash
# Navigate to your AOSP root directory
cd /path/to/aosp/root

# Clone the repository into system/extras/hello_aosp
git clone <repository-url> system/extras/hello_aosp
```

> **Note:** The target installation path depends on the build definition:
> * Without `vendor: true`, the binary is installed into `/system/bin/hello_aosp`.
> * If `vendor: true` is enabled in `Android.bp`, it will be installed into `/vendor/bin/hello_aosp`.

---

## Build Instructions

### Option 1: Standalone / Targeted Build

1. **Set up the AOSP build environment:**
   ```bash
   source build/envsetup.sh
   ```

2. **Select your target product and variant:**
   ```bash
   lunch <target_product>-<build_variant>
   # Example for Goldfish / emulator:
   # lunch sdk_phone_x86_64-userdebug
   ```

3. **Compile the binary:**
   * **Targeted build (from any directory):**
     ```bash
     m hello_aosp
     ```
   * **Module-level build (from the module directory):**
     ```bash
     cd system/extras/hello_aosp
     mm
     ```

---

### Option 2: Automatic Inclusion in the System Image (`system.img`)

To have `hello_aosp` automatically built and bundled into the `system.img` whenever you build the target image, add the module to the product packages list:

1. Open the system configuration makefile:
   ```text
   build/make/target/product/handheld_system.mk
   ```

2. Append `hello_aosp` (and `lib_device_info` if not already included) to the `PRODUCT_PACKAGES` list:
   ```make
   PRODUCT_PACKAGES += \
       hello_aosp \
       lib_device_info
   ```

3. Rebuild the system image from the AOSP root:
   ```bash
   m
   ```

---

## Running on Target / Emulator

### A. If pushed manually via ADB:

```bash
# Ensure ADB has root access and filesystem is writable
adb root
adb remount
adb push $ANDROID_PRODUCT_OUT/system/bin/hello_aosp /system/bin/

# Ensure execution permissions
adb shell chmod +x /system/bin/hello_aosp

# Run executable
adb shell /system/bin/hello_aosp
```

### B. If built into the system image:

Simply boot your Goldfish emulator:
```bash
emulator
```
And execute the binary directly:
```bash
adb shell hello_aosp
```

### Viewing Logs

To see the output sent through Android's `LOG(INFO)`:
```bash
adb logcat -s hello_aosp:*
```