// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CLOUD_CORE_LINUX_QT_NETWORK_PROVIDER_H
#define CLOUD_CORE_LINUX_QT_NETWORK_PROVIDER_H

#include "network_provider.h"
#include "qt_network_provider_shared.h"

// Split from GtkNetworkProvider because a completion must run on that toolkit's main thread.
// Qt uses QNetworkAccessManager, which already delivers results on the Qt thread, so this type does not use Beast.
class QtNetworkProvider : public INetworkProvider, public QtNetworkProviderShared
{
protected:
    void get_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void post_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void post_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const nlohmann::json& body,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void put_file_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const std::string& file_path,
        const nlohmann::json& task_info,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void download_file_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const std::string& file_path,
        const nlohmann::json& task_info,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void patch_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const nlohmann::json& body,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void put_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const nlohmann::json& body,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
    void destroy_impl(
        const std::string& url,
        const std::map<std::string, std::string>& headers,
        const std::function<void(const amqhi::HttpResponse& response)>& on_response,
        const std::function<void(std::int16_t error_code, const std::string& data)>& on_failure) override;
};

#endif // CLOUD_CORE_LINUX_QT_NETWORK_PROVIDER_H
