// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gtk_network_provider.h"

#include <algorithm>

#include <glib.h>

namespace {
struct CallerCallback
{
    GtkNetworkProvider* provider;
    unsigned int source_id;
    std::function<void()> callback;
};
}

GtkNetworkProvider::~GtkNetworkProvider()
{
    std::vector<unsigned int> source_ids;
    {
        std::lock_guard lock(m_caller_mutex);
        m_is_shutting_down = true;
        source_ids.swap(m_pending_caller_sources);
    }

    for (const unsigned int source_id : source_ids)
    {
        g_source_remove(source_id);
    }
}

void GtkNetworkProvider::post_to_caller(std::function<void()> callback)
{
    if (!callback)
    {
        return;
    }

    auto* caller_callback = new CallerCallback{this, 0, std::move(callback)};
    std::lock_guard lock(m_caller_mutex);
    if (m_is_shutting_down)
    {
        delete caller_callback;
        return;
    }

    caller_callback->source_id = g_idle_add_full(
        G_PRIORITY_DEFAULT,
        on_caller_source,
        caller_callback,
        destroy_caller_source);
    m_pending_caller_sources.push_back(caller_callback->source_id);
}

void GtkNetworkProvider::remove_pending_caller_source(unsigned int source_id)
{
    std::lock_guard lock(m_caller_mutex);
    const auto it = std::find(m_pending_caller_sources.begin(), m_pending_caller_sources.end(), source_id);
    if (it != m_pending_caller_sources.end())
    {
        m_pending_caller_sources.erase(it);
    }
}

int GtkNetworkProvider::on_caller_source(void* data)
{
    auto* caller_callback = static_cast<CallerCallback*>(data);
    caller_callback->provider->remove_pending_caller_source(caller_callback->source_id);
    auto callback = std::move(caller_callback->callback);
    callback();
    return G_SOURCE_REMOVE;
}

void GtkNetworkProvider::destroy_caller_source(void* data)
{
    delete static_cast<CallerCallback*>(data);
}

void GtkNetworkProvider::get_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    get_shared(url, headers, on_response, on_failure);
}

void GtkNetworkProvider::post_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    post_shared(url, headers, on_response, on_failure);
}

void GtkNetworkProvider::post_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const nlohmann::json& body,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    post_shared(url, headers, body, on_response, on_failure);
}

void GtkNetworkProvider::put_file_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::string& file_path,
    const nlohmann::json& task_info,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    put_file_shared(url, headers, file_path, task_info, on_response, on_failure);
}

void GtkNetworkProvider::download_file_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::string& file_path,
    const nlohmann::json& task_info,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    download_file_shared(url, headers, file_path, task_info, on_response, on_failure);
}

void GtkNetworkProvider::patch_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const nlohmann::json& body,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    patch_shared(url, headers, body, on_response, on_failure);
}

void GtkNetworkProvider::put_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const nlohmann::json& body,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    put_shared(url, headers, body, on_response, on_failure);
}

void GtkNetworkProvider::destroy_impl(
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::function<void(const amqhi::HttpResponse&)>& on_response,
    const std::function<void(std::int16_t, const std::string&)>& on_failure)
{
    destroy_shared(url, headers, on_response, on_failure);
}
