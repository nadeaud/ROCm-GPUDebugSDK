//==============================================================================
// Copyright (c) 2015 Advanced Micro Devices, Inc. All rights reserved.
//
/// \author AMD Developer Tools
/// \file
/// \brief Header for RunAgentCommandLoop
//==============================================================================
#ifndef COMMANDLOOP_H_
#define COMMANDLOOP_H_

#include "CommunicationControl.h"

namespace HwDbgAgent
{
/// Struct to pass parameters to the DBE Thread
typedef struct
{
    /// This might be needed by the DBE thread to stop the dispatch
    /// first and then itself to signal GDB
    pid_t m_dispatchPID;

    /// This is got from the predispatch callback argument and passed to the DebugThread
    AgentContext* m_pHsailAgentContext;

} DebugEventThreadParams ;

/// Read the FIFO and check for any new packets
void RunFifoCommandLoop(AgentContext* pActiveContext);

/// Read the FIFO and check for any new packets multiple times
void RunFifoCommandLoop(AgentContext* pActiveContext, unsigned int runCount);

HsailAgentStatus WaitForDebugThreadCompletion();

HsailAgentStatus CreateDebugEventThread(DebugEventThreadParams* pArgs);

} // End Namespace HwDbgAgent

/// GDB will install a breakpoint on this function that will be used when
/// a GPU kernel breakpoint is hit.
/// It is defined as extern C to facilitate the name lookup by GDB. This
/// could be changed to use exported symbol referring to locations
/// as it is done in the in-process agent library.
///
extern "C"
{
    void __attribute__((optimize("O0"))) TriggerGPUBreakpointStop(void);
}

#endif // COMMANDLOOP_H_
