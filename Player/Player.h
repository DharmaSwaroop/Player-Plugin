#pragma once

#include "Module.h"
#include <bits/stdc++.h>
#include <gst/gst.h>

namespace WPEFramework
{
    namespace Plugin
    {
        class Player : public PluginHost::IPlugin, public PluginHost::JSONRPC
        {

        private:
            Player(const Player &) = delete;
            Player &operator=(const Player &) = delete;
            // simple method const JsonObject& parameters, JsonObject& response

        public:
            Player();
            virtual ~Player();
            // IPlugin methods
            virtual const string Initialize(PluginHost::IShell *service) override;
            virtual void Deinitialize(PluginHost::IShell *service) override;
            virtual string Information() const override;
            uint32_t pathset(const JsonObject &request);
            uint32_t p();
            uint32_t loop(const JsonObject &request);

            BEGIN_INTERFACE_MAP(Player)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            END_INTERFACE_MAP
        };
    } // namespace Plugin
} // namespace WPEFramework