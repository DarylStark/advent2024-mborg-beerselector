#ifndef __APPLICATION_H__
#define __APPLICATION_H__

namespace ds
{
    class Application
    {
        // Interface for a application.
    public:
        virtual void setup() = 0;
        virtual void loop() = 0;
    };
}  // namespace ds

#endif /* __APPLICATION_H__ */