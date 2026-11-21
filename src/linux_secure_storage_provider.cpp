// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "linux_secure_storage_provider.h"

bool LinuxSecureStorageProvider::set_secure_string(const std::string_view& key, const std::string& value)
{
    return set_secure_string_shared("com.amqhi.Cloud", "Amqhi Cloud " + std::string(key), key, value);
}

std::string LinuxSecureStorageProvider::get_secure_string(const std::string_view& key, const std::string& default_value)
{
    return get_secure_string_shared("com.amqhi.Cloud", key, default_value);
}

void LinuxSecureStorageProvider::remove_secure_string(const std::string_view& key)
{
    remove_secure_string_shared("com.amqhi.Cloud", key);
}

