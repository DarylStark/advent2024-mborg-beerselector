#ifndef __STATE_H__
#define __STATE_H__

namespace ds
{
    class State
    {
        // Interface for the application state.
    public:
        virtual void loop() = 0;
    };
}  // namespace ds

#endif /* __STATE_H__ */