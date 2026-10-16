#include <android-base/logging.h>
// #include <android-base/properties.h>
#include <lib_device_info.h>
#include <iostream>

namespace ab = android::base;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    (void)argc;

    // Start android logging system
    ab::InitLogging(argv, ab::LogdLogger());

    info::PrintVersion();
    info::PrintAPI();
    info::PrintModel();
    info::PrintBrand();
    info::Notify();

    LOG(INFO) << "Message sent from Logcat Hello AOSP";

    return 0;
}