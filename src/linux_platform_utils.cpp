// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "linux_platform_utils.h"

std::string LinuxPlatformUtils::get_device_name() const
{
    return get_device_name_shared();
}

std::string LinuxPlatformUtils::get_file_sha256_checksum(const std::string& file_path) const
{
    return get_file_sha256_checksum_shared(file_path);
}
