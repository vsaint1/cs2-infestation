#ifndef MUSTACHE_MEMORY_H
#define MUSTACHE_MEMORY_H

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <winternl.h>
#include <optional>
#include <vector>
#include <charconv>
#include <memory>
#include "../utils/macros.h"

struct SystemHandle {
    unsigned long m_process_id;
    uint8_t m_object_type_number;
    uint16_t m_handle;
    uint32_t m_flags;
    void *m_object;
    ACCESS_MASK m_granted_access;
};

struct SystemHandleInfo {
    unsigned long m_handle_count;
    SystemHandle m_handles[1];
};

class Pattern {
public:
    Pattern() = default;

    explicit Pattern(const uintptr_t address) : m_address(address) {}

    uintptr_t get_address() const {
        return this->m_address;
    }

    Pattern add(const ptrdiff_t offset) const {
        return Pattern(this->m_address + offset);
    }

    Pattern sub(const ptrdiff_t offset) const {
        return Pattern(this->m_address - offset);
    }

    Pattern rip(const ptrdiff_t offset = 0x03, const size_t length = 0x07) const;

    template<typename T>
    T as() const {
        return reinterpret_cast<T>(this->m_address);
    }

private:
    uintptr_t m_address;
};


class Memory {
public:

    ~Memory() {
        if (this->m_handle != nullptr)
            CloseHandle(this->m_handle);
    }

    uint32_t get_pid() {
        return this->m_pid;
    }

    bool attach();

    std::optional<uint32_t> get_process_id(const std::string_view &process_name);

    std::pair<std::optional<uintptr_t>, std::optional<uintptr_t>> get_module_info(const std::string_view &module_name);

    std::optional<Pattern> find_pattern(const std::string_view &module_name, const std::string_view &pattern);


    template<typename T>
    T readv(void *address) {
        T value;
        this->read_raw(address, &value, sizeof(T));

        return value;
    }

    template<typename T>
    T readv(uintptr_t address) noexcept {
        T buffer;
        this->read_raw(reinterpret_cast<void *>(address), &buffer, sizeof(T));
        return buffer;
    }

    bool readv(uintptr_t address, void *buffer, uintptr_t size);

    std::string read_str(uintptr_t address) noexcept;

private:
    void *m_handle;
    uint32_t m_pid;

    bool read_raw(void *address, void *buffer, const size_t size) {
        return ReadProcessMemory(this->m_handle, reinterpret_cast<void *>(address), buffer, size, nullptr);
    }

    std::optional<void *> hijack_handle();

    bool running_as_admin();

};

inline Memory memory{};

#endif //MUSTACHE_MEMORY_H