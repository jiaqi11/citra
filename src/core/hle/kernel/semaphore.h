// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string>
#include <queue>
#include "common/common_types.h"
#include "core/hle/kernel/object.h"
#include "core/hle/kernel/wait_object.h"
#include "core/hle/result.h"

namespace Kernel {

class Semaphore final : public WaitObject {
public:
    std::string GetTypeName() const override {
        return "Semaphore";
    }
    std::string GetName() const override {
        return name;
    }

    static const HandleType HANDLE_TYPE = HandleType::Semaphore;
    HandleType GetHandleType() const override {
        return HANDLE_TYPE;
    }

    s32 max_count;       ///< Maximum number of simultaneous holders the semaphore can have
    s32 available_count; ///< Number of free slots left in the semaphore
    std::string name;    ///< Name of semaphore (optional)

    bool ShouldWait(Thread* thread) const override;
    void Acquire(Thread* thread) override;

    /**
     * Releases a certain number of slots from a semaphore.
     * @param release_count The number of slots to release
     * @return The number of free slots the semaphore had before this call
     */
    ResultVal<s32> Release(s32 release_count);

private:
    explicit Semaphore(KernelSystem& kernel);
    ~Semaphore() override;

    friend class KernelSystem;
};

} // namespace Kernel
