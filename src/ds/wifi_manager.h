#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

namespace ds {
    class WifiManager
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}

#endif /* WIFI_MANAGER_H */