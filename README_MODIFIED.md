# msquic modified

## What's changed?

* Added `void* Context` as the last field in `QUIC_REGISTRATION_CONFIG`
* Support to `dispatch` worker threads
* Break the worker thread function into multiple small pieces

## What can I do with the changed version?

1. Thread Dispatching: Run msquic worker on your thread
2. Custom Event Loop: Integrate msquic into your custom event loop

## How to use?

### 1. Thread Dispatching

A callback function for dispatching threads:

```c
QUIC_STATUS
(QUIC_API * QUIC_EVENT_LOOP_THREAD_DISPATCH_FN)(
    CXPLAT_THREAD_CONFIG* Config,
    CXPLAT_EVENTQ* EventQ,
    CXPLAT_THREAD* Thread,
    void* Context
    );
```

You can set `void* Context` in `QUIC_REGISTRATION_CONFIG`, and get the object from `Context` parameter.  
You can also retrieve the `Worker` pointer from `Config->Context`.

In the callback function, you should spawn a new thread for msquic to run on.

In the new thread, you must call `ThreadGetCur(Thread);` before calling other functions.  
And the dispatch function must not return until `ThreadGetCur(Thread)` is called.
You probably need a lock to do this.

To run the **normal** msquic worker, you should call `(Config->Callback)(Config->Context);`.

Before calling any msquic functions, you should register the dispatcher function to msquic:

```c
MsQuicSetEventLoopThreadDispatcher(fn);
```

### 2. Custom Event Loop

This is really tricky, here's the key points:

1. msquic creates an `eventQ` (e.g. epoll fd)
2. you must use the `eventQ` created by msquic in your event loop
3. your event loop and msquic will both operate the same `eventQ`
4. you should poll the `eventQ` (e.g. `epoll_wait`)
5. you should distinguish the events added by msquic from those added by your event loop
6. you should extract msquic events, and inject the events to msquic

It's recommended to read the following definitions before integrating msquic to your event loop:

* `CXPLAT_EVENTQ`: e.g. epoll fd
* `CXPLAT_SQE`: e.g. fd
* `CxPlatCqeUserData(...)`: retrieves userdata
* `CxPlatCqeType(...)`: retrieves type info from the userdata

You must ensure your event loop corresponds to msquic `CXPLAT_EVENTQ`, which means:

* epoll on linux
* kqueue on macos
* iocp on windows

From `CxPlatCqeType(...)` we can know that the userdata added into `eventQ` starts with an `uint32_t` field,
which means the type of the event.

So in order to distinguish event loop events and msquic events, you could always use the following struct as userdata:

```c
struct {
  uint32_t type;
  union {
    // ...
  };
};
```

, where the `type` for your event loop events is defined by you, and the `type`s for msquic are defined by msquic.

---

You would also need to strictly call a sequence of functions:

```
call ThreadGetCur(...) before anything else
call ThreadIsWorker(1)
call WorkerThreadInit(...)
while (true) {
    call WorkerThreadBeforePoll(...)
    poll the eventQ (e.g. epoll_wait)
    if ( call WorkerThreadAfterPoll(...) )
        break;
    handle your event loop events here
}
call WorkerThreadFinalize(...)
```

You may check the source code for definitions of the above functions.
