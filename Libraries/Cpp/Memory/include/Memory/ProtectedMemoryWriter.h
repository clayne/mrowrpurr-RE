#pragma once

#include <Windows.h>

#include <cstdint>
#include <vector>

#include "Memory/Bytes.h"

namespace Memory {

    class ProtectedMemoryWriter {
        uintptr_t _address;

    public:
        ProtectedMemoryWriter(uintptr_t address) : _address(address) {}
        ProtectedMemoryWriter() : _address(0) {}

        void      SetAddress(uintptr_t address) { _address = address; }
        uintptr_t GetAddress() const { return _address; }

        template <typename T>
        void Write(T value, uintptr_t offset) const {
            DWORD oldProtect;
            VirtualProtect(
                (LPVOID)(GetAddress() + offset), sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect
            );
            *(T*)(GetAddress() + offset) = value;
            VirtualProtect((LPVOID)(GetAddress() + offset), sizeof(T), oldProtect, &oldProtect);
        }

        template <typename T>
        void Write(T value) const {
            Write<T>(value, 0);
        }

        void WriteByte(uint8_t byte) const { Write<uint8_t>(byte); }
        void Write8(uint8_t byte) const { WriteByte(byte); }

        void WriteWord(uint16_t word) const { Write<uint16_t>(word); }
        void Write16(uint16_t word) const { WriteWord(word); }

        void WriteDword(uint32_t dword) const { Write<uint32_t>(dword); }
        void Write32(uint32_t dword) const { WriteDword(dword); }

        void WriteQword(uint64_t qword) const { Write<uint64_t>(qword); }
        void Write64(uint64_t qword) const { WriteQword(qword); }

        void WriteBytes(const std::vector<uint8_t>& bytes) const {
            for (size_t i = 0; i < bytes.size(); i++) Write<uint8_t>(bytes[i], i);
        }
        void WriteBytes(const Bytes& bytes) const {
            for (size_t i = 0; i < bytes.GetSize(); i++) Write<uint8_t>(bytes[i], i);
        }
    };
}
