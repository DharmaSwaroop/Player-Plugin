class newPlayer
{
public:
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    char path[100];
    char desc[1000];
    int eos;
    int loop;
    GstEvent *seek_event;
};