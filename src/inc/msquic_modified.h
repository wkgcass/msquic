#ifndef _MSQUIC_MODIFIED_H_
#define _MSQUIC_MODIFIED_H_

#include "msquic.h"

void
QUIC_API
MsQuicCxPlatWorkerThreadInit(
    _Inout_ void* CxPlatWorkerThreadLocals
    );

void
QUIC_API
MsQuicCxPlatWorkerThreadBeforePoll(
    _Inout_ void* CxPlatProcessEventLocals
    );

BOOLEAN
QUIC_API
MsQuicCxPlatWorkerThreadAfterPoll(
    _Inout_ void* CxPlatProcessEventLocals
    );

int
QUIC_API
MsQuicCxPlatWorkerThreadFinalize(
    _Inout_ void* CxPlatWorkerThreadLocals
    );

QUIC_STATUS
QUIC_API
CxPlatGetCurThread(
    _Out_ CXPLAT_THREAD* Thread
    );

QUIC_STATUS
QUIC_API
MsQuicSetEventLoopThreadDispatcher(
    _In_ QUIC_EVENT_LOOP_THREAD_DISPATCH_FN ThreadDispatcher
    );

QUIC_STATUS
QUIC_API
MsQuicGetEventLoopThreadDispatcher(
    _Out_ QUIC_EVENT_LOOP_THREAD_DISPATCH_FN* ThreadDispatcher
    );

uint8_t
QUIC_API
MsQuicIsWorker(void);

void
QUIC_API
MsQuicSetIsWorker(
    _In_ uint8_t is_worker
    );

#endif // _MSQUIC_MODIFIED_H_
