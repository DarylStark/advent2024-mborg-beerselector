#ifndef SERVICE_H
#define SERVICE_H

namespace ds
{
    class Service
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}  // namespace ds

#endif /* SERVICE_H */
