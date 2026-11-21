// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CLOUD_CORE_LINUX_GTK_NETWORK_PROVIDER_H
#define CLOUD_CORE_LINUX_GTK_NETWORK_PROVIDER_H

#include <mutex>
#include <vector>

#include "beast_network_provider_shared.h"
#include "network_provider.h"

// Split from QtNetworkProvider because a completion must run on that toolkit's main thread.
// GTK has no HTTP client here, so Beast performs the request and post_to_caller uses g_idle_add.
// Qt uses QNetworkAccessManager instead of Beast.
class GtkNetworkProvider : public INetworkProvider, public BeastNetworkProviderShared
{
public:
    ~GtkNetworkProvider() override;

protected:
    // Post callback onto the GTK main loop with g_idle_add and return immediately.
    void post_to_caller(std::function<void()> callback) override;

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

private:
    void remove_pending_caller_source(unsigned int source_id);
    static int on_caller_source(void* data);
    static void destroy_caller_source(void* data);

    std::mutex m_caller_mutex;
    bool m_is_shutting_down = false;
    std::vector<unsigned int> m_pending_caller_sources;
};

#endif // CLOUD_CORE_LINUX_GTK_NETWORK_PROVIDER_H
