#include "Player.h"
#include <iostream>
#include <gst/gst.h>
#include <pthread.h>
#include "newPlayer.h"

using namespace std;
namespace WPEFramework
{
    namespace Plugin
    {
        newPlayer *player1 = new newPlayer;
        void *runPipeline(void *arg);
        SERVICE_REGISTRATION(Player, 1, 0);
        Player::Player() : PluginHost::JSONRPC() // REGISTERING THE METHODS IN A CONSTRUCTOR
        {
            cout << "PLAYER CONSTRUCTOR\n";
            Register<JsonObject, void>(_T("pathset"), &Player::pathset, this);
            Register<void, void>(_T("p"), &Player::p, this);
            Register<JsonObject, void>(_T("loop"), &Player::loop, this);
            //  Register<void, void>(_T("play").& Player::play, this);
        }
        Player::~Player() // DESTRUCTOR
        {
        }
        const string Player::Initialize(PluginHost::IShell *service) // INITIALIZE
        {
            // shared pointer initialized
            // initialize external library
            int argc = 0;
            char **argv = nullptr;
            std::cout << "..................THE PLAYER HAS STARTED......................\n";
            gst_init(&argc, &argv);
            return (string());
        }
        void Player::Deinitialize(PluginHost::IShell *service) // DEINITIALIZE
        {
            std::cout << "Player deinitialize\n";

            // shared pointer deinitialized
            // deinitialize external library
        }
        /* virtual */ string Player::Information() const // INFORMATION
        {
            // No additional info to report.
            std::cout << "Information part\n";
            return ((_T("The purpose of this plugin is provide ability to execute functional tests.")));
        }

        // PLAYER METHODS...
        void *runPipeline(void *arg)
        {

            /* Start playing */
            gst_element_set_state(player1->pipeline, GST_STATE_PLAYING);
            player1->bus = gst_element_get_bus(player1->pipeline);
            do
            {
                player1->msg = gst_bus_timed_pop_filtered(player1->bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

                /* Parse message */
                if (player1->msg != NULL)
                {
                    GError *err;
                    gchar *debug_info;

                    switch (GST_MESSAGE_TYPE(player1->msg))
                    {
                    case GST_MESSAGE_ERROR:
                        gst_message_parse_error(player1->msg, &err, &debug_info);
                        g_printerr("Error received from element %s: %s\n",
                                   GST_OBJECT_NAME(player1->msg->src), err->message);
                        g_printerr("Debugging information: %s\n",
                                   debug_info ? debug_info : "none");
                        g_clear_error(&err);
                        g_free(debug_info);
                        break;
                    case GST_MESSAGE_EOS:
                        g_print("End-Of-Stream reached.\n");
                        if (player1->loop == 1)
                        {
                            printf("yeah loop is 1.\n");
                            player1->seek_event = gst_event_new_seek(1.0, GST_FORMAT_TIME, (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT), GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_NONE, 0);
                            gst_element_send_event(player1->pipeline, player1->seek_event);
                            gst_element_set_state(player1->pipeline, GST_STATE_PLAYING);
                        }
                        break;
                    default:
                        /* We should not reach here because we only asked for ERRORs and EOS */
                        g_printerr("Unexpected message received.\n");
                        break;
                    }
                    gst_message_unref(player1->msg);
                }
            } while (player1->loop == 1);
            gst_object_unref(player1->bus);
            gst_element_set_state(player1->pipeline, GST_STATE_NULL);
            gst_object_unref(player1->pipeline);
            pthread_exit(NULL);
            return NULL;
        }

        uint32_t Player::pathset(const JsonObject &request)
        {

            pthread_t th1;
            string tempstr;
            tempstr = request["path"].String();
            cout << "the path is: " << tempstr << endl;
            strcpy(player1->path, tempstr.c_str());
            sprintf(player1->desc, "playbin uri=file://%s", player1->path);
            printf("The description is: %s\n", player1->desc);
            if (player1->pipeline != NULL)
            {
                gst_element_set_state(player1->pipeline, GST_STATE_NULL);
                gst_object_unref(player1->pipeline);
            }
            player1->pipeline = gst_parse_launch(player1->desc, NULL);
            pthread_create(&th1, NULL, runPipeline, NULL);

            cout << "after pthread exit\n";
            return Core::ERROR_NONE;
        }
        uint32_t Player::p()

        {
            GstState state;
            gst_element_get_state(player1->pipeline, &state, NULL, GST_CLOCK_TIME_NONE);
            printf("The current state is: %s\n", gst_element_state_get_name(state));
            if (state == GST_STATE_PLAYING)
            {
                printf("Inside p inside if\n");
                gst_element_set_state(player1->pipeline, GST_STATE_PAUSED);
            }
            else if (state == GST_STATE_PAUSED)
            {
                gst_element_set_state(player1->pipeline, GST_STATE_PLAYING);
            }
            return Core::ERROR_NONE;
        }

        uint32_t Player::loop(const JsonObject &request)
        {

            string loopstr = request["loop"].String();
            player1->loop = stoi(loopstr);
            return Core::ERROR_NONE;
        }

    } // namespace plugin
} // namespace framework
