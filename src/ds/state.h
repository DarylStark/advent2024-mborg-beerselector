#ifndef STATE_H
#define STATE_H

namespace ds
{
    class State
    {
        // Interface for the application state.
    public:
        virtual void run() = 0;
    };
}  // namespace ds

#endif /* STATE_H */