// Copyright (c) 2015 Vijos Dev Team. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WINC_CORE_JOB_OBJECT_H_
#define WINC_CORE_JOB_OBJECT_H_

#include <Windows.h>

#include <winc_types.h>
#include <winc/util.h>

namespace winc {

class JobObjectSharedResource;
class Target;

class JobObject {
public:
  ResultCode Init();
  ResultCode AssignProcess(HANDLE process);
  ResultCode GetBasicLimit(JOBOBJECT_EXTENDED_LIMIT_INFORMATION *limit);
  ResultCode SetBasicLimit(const JOBOBJECT_EXTENDED_LIMIT_INFORMATION &limit);
  ResultCode GetUILimit(JOBOBJECT_BASIC_UI_RESTRICTIONS *ui_limit);
  ResultCode SetUILimit(const JOBOBJECT_BASIC_UI_RESTRICTIONS &ui_limit);
  ResultCode GetAccountInfo(JOBOBJECT_BASIC_ACCOUNTING_INFORMATION *info);
  ResultCode Terminate(UINT exit_code);

private:
  static DWORD WINAPI MessageThread(PVOID param);

private:
  friend class JobObjectSharedResource;
  friend class Target;
  ResultCode AssociateCompletionPort(Target *target);
  static void DeassociateCompletionPort(Target *target);

private:
  unique_handle job_;
};

}

#endif
