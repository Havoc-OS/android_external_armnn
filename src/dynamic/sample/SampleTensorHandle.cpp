//
// Copyright © 2020 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "SampleTensorHandle.hpp"

namespace armnn
{

SampleTensorHandle::SampleTensorHandle(const TensorInfo &tensorInfo,
                                       std::shared_ptr<SampleMemoryManager> &memoryManager)
    : m_TensorInfo(tensorInfo),
      m_MemoryManager(memoryManager),
      m_Pool(nullptr),
      m_UnmanagedMemory(nullptr),
      m_ImportFlags(static_cast<MemorySourceFlags>(MemorySource::Undefined)),
      m_Imported(false)
{

}

SampleTensorHandle::SampleTensorHandle(const TensorInfo& tensorInfo,
                                       MemorySourceFlags importFlags)
    : m_TensorInfo(tensorInfo),
      m_MemoryManager(nullptr),
      m_Pool(nullptr),
      m_UnmanagedMemory(nullptr),
      m_ImportFlags(importFlags),
      m_Imported(true)
{

}

SampleTensorHandle::~SampleTensorHandle()
{
    if (!m_Pool)
    {
        // unmanaged
        if (!m_Imported)
        {
            ::operator delete(m_UnmanagedMemory);
        }
    }
}

void SampleTensorHandle::Manage()
{
    m_Pool = m_MemoryManager->Manage(m_TensorInfo.GetNumBytes());
}

void SampleTensorHandle::Allocate()
{
    if (!m_UnmanagedMemory)
    {
        if (!m_Pool)
        {
            // unmanaged
            m_UnmanagedMemory = ::operator new(m_TensorInfo.GetNumBytes());
        }
        else
        {
            m_MemoryManager->Allocate(m_Pool);
        }
    }
    else
    {
        throw InvalidArgumentException("SampleTensorHandle::Allocate Trying to allocate a SampleTensorHandle"
                                       "that already has allocated memory.");
    }
}

const void* SampleTensorHandle::Map(bool /*unused*/) const
{
    return GetPointer();
}

void* SampleTensorHandle::GetPointer() const
{
    if (m_UnmanagedMemory)
    {
        return m_UnmanagedMemory;
    }
    else
    {
        return m_MemoryManager->GetPointer(m_Pool);
    }
}

bool SampleTensorHandle::Import(void* memory, MemorySource source)
{

    if (m_ImportFlags & static_cast<MemorySourceFlags>(source))
    {
        if (source == MemorySource::Malloc)
        {
            // Check memory alignment
            constexpr uintptr_t alignment = sizeof(size_t);
            if (reinterpret_cast<uintptr_t>(memory) % alignment)
            {
                if (m_Imported)
                {
                    m_Imported = false;
                    m_UnmanagedMemory = nullptr;
                }

                return false;
            }

            // m_UnmanagedMemory not yet allocated.
            if (!m_Imported && !m_UnmanagedMemory)
            {
                m_UnmanagedMemory = memory;
                m_Imported = true;
                return true;
            }

            // m_UnmanagedMemory initially allocated with Allocate().
            if (!m_Imported && m_UnmanagedMemory)
            {
                return false;
            }

            // m_UnmanagedMemory previously imported.
            if (m_Imported)
            {
                m_UnmanagedMemory = memory;
                return true;
            }
        }
    }

    return false;
}

void SampleTensorHandle::CopyOutTo(void* dest) const
{
    const void *src = GetPointer();
    ARMNN_ASSERT(src);
    memcpy(dest, src, m_TensorInfo.GetNumBytes());
}

void SampleTensorHandle::CopyInFrom(const void* src)
{
    void *dest = GetPointer();
    ARMNN_ASSERT(dest);
    memcpy(dest, src, m_TensorInfo.GetNumBytes());
}

}
