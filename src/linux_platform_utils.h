// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CLOUD_CORE_LINUX_PLATFORM_UTILS_H
#define CLOUD_CORE_LINUX_PLATFORM_UTILS_H
#include "linux_platform_utils_shared.h"
#include "platform_utils.h"

class LinuxPlatformUtils : public IPlatformUtils, public LinuxPlatformUtilsShared
{
public:
    std::string get_device_name() const override;
    std::string get_file_sha256_checksum(const std::string& file_path) const override;
};

#endif // CLOUD_CORE_LINUX_PLATFORM_UTILS_H
