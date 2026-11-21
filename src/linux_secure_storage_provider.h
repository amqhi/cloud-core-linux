// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CLOUD_CORE_LINUX_SECURE_STORAGE_PROVIDER_H
#define CLOUD_CORE_LINUX_SECURE_STORAGE_PROVIDER_H

#include "linux_secure_storage_provider_shared.h"
#include "secure_storage_provider.h"

#include <string>

class LinuxSecureStorageProvider : public ISecureStorageProvider, public LinuxSecureStorageProviderShared
{
public:
    bool set_secure_string(const std::string_view& key, const std::string& value) override;
    std::string get_secure_string(const std::string_view& key, const std::string& default_value) override;
    void remove_secure_string(const std::string_view& key) override;
};

#endif // CLOUD_CORE_LINUX_SECURE_STORAGE_PROVIDER_H
