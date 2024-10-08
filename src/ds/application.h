#ifndef APPLICATION_H
#define APPLICATION_H

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

#endif /* APPLICATION_H */