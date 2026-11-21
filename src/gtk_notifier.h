// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CLOUD_CORE_LINUX_GTK_NOTIFIER_H
#define CLOUD_CORE_LINUX_GTK_NOTIFIER_H
#include "gtk_notifier_shared.h"
#include "notifier.h"

class GtkNotifier : public INotifier, GtkNotifierShared
{
public:
    void notify(std::int16_t code) override;
    void notify(std::int16_t code, const std::string& data) override;
    void notify(std::int16_t code, const nlohmann::json& data) override;
};

#endif // CLOUD_CORE_LINUX_GTK_NOTIFIER_H
