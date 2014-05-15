// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include <engextcpp.hpp>

class EXT_CLASS : public ExtExtension {
 public:
  EXT_COMMAND_METHOD(for_each_process);
};

EXT_DECLARE_GLOBALS();

EXT_COMMAND(for_each_process,
            "Executes a specified command for each process",
            "{;x;CommandString;The command to run for each process}") {
  HRESULT status;
  ULONG num_processes;
  status = m_System->GetNumberProcesses(&num_processes);

  if (FAILED(status)) {
    Out("Couldn't GetNumberProcesses\n");
    return;
  }

  ULONG original_process;
  status = m_System->GetCurrentProcessId(&original_process);
  if (FAILED(status)) {
    Out("Couldn't GetCurrentProcessId\n");
    return;
  }

  PCSTR command = GetUnnamedArgStr(0);
  for (ULONG i = 0; i < num_processes; ++i) {
    status = m_System->SetCurrentProcessId(i);
    if (FAILED(status)) {
      Out("Couldn't SetCurrentProcessId\n");
      return;
    }
    Out("Process %d: ", i);
    status = m_Control->Execute(
        DEBUG_OUTCTL_ALL_CLIENTS, command, DEBUG_EXECUTE_ECHO);
    if (FAILED(status)) {
      Out("Execute failed on %d\n", i);
      // Don't abort here in case it just didn't make sense for that process.
    }
  }

  status = m_System->SetCurrentProcessId(original_process);
  if (FAILED(status)) {
    Out("Couldn't SetCurrentProcessId\n");
    return;
  }
}

