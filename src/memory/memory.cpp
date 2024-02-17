#include "memory.hpp"

Pattern Pattern::rip(const std::ptrdiff_t offset, const size_t length) const {
    auto base = this->m_address;
    const auto rip_offset = memory.readv<std::int32_t>(base + offset);

    base += rip_offset;
    base += length;

    return Pattern(base);
}

std::optional<uint32_t> Memory::get_process_id(const std::string_view &process_name) {
    const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return {};

    PROCESSENTRY32 process_entry = {0};
    process_entry.dwSize = sizeof(process_entry);

    for (Process32First(snapshot, &process_entry); Process32Next(snapshot, &process_entry);) {
        if (std::string_view(process_entry.szExeFile) == process_name)
            return process_entry.th32ProcessID;
    }

    CloseHandle(snapshot);
    return {};
}


bool Memory::attach() {
    const auto pid = this->get_process_id(GAME_NAME);
    
    if (!pid.has_value()) {
        printf("failed to get process id for %s", GAME_NAME);
        return false;
    }

    this->m_pid = pid.value();

    const auto handle = OpenProcess(PROCESS_ALL_ACCESS,0,this->m_pid);

    if (!handle) {
        printf("failed to hijack a handle for %s", GAME_NAME);
        return false;
    }

    this->m_handle = handle;

    return this->m_handle != nullptr;
}

std::optional<Pattern> Memory::find_pattern(const std::string_view &module_name, const std::string_view &pattern) {
    constexpr auto pattern_to_bytes = [](const std::string_view &pattern) {
        std::vector<int32_t> bytes;

        for (size_t i = 0; i < pattern.size(); ++i) {
            switch (pattern[i]) {
                case '?':
                    bytes.push_back(-1);
                    break;

                case ' ':
                    break;

                default: {
                    if (i + 1 < pattern.size()) {
                        auto value{0};

                        if (const auto [ptr, ec] = std::from_chars(pattern.data() + i, pattern.data() + i + 2,
                                                                   value,
                                                                   16); ec == std::errc()) {
                            bytes.push_back(value);
                            ++i;
                        }
                    }

                    break;
                }
            }
        }

        return bytes;
    };

    const auto [module_base, module_size] = this->get_module_info(module_name);
    if (!module_base.has_value() || !module_size.has_value())
        return {};

    const auto module_data = std::make_unique<uint8_t[]>(module_size.value());
    if (!this->readv(module_base.value(), module_data.get(), module_size.value()))
        return {};

    const auto pattern_bytes = pattern_to_bytes(pattern);
    for (size_t i = 0; i < module_size.value() - pattern.size(); ++i) {
        bool found = true;


        for (size_t j = 0; j < pattern_bytes.size(); ++j) {
            if (module_data[i + j] != pattern_bytes[j] && pattern_bytes[j] != -1) {
                found = false;
                break;
            }
        }

        if (found)
            return Pattern(module_base.value() + i);
    }

    return {};
}

std::pair<std::optional<uintptr_t>, std::optional<uintptr_t>>
Memory::get_module_info(const std::string_view &module_name) {
    void *snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->m_pid);
    if (snapshot == INVALID_HANDLE_VALUE)
        return {};

    MODULEENTRY32 module_entry{
            .dwSize = sizeof(module_entry)
    };

    for (Module32First(snapshot, &module_entry); Module32Next(snapshot, &module_entry);) {

        for (Module32First(snapshot, &module_entry); Module32Next(snapshot, &module_entry);) {

            if (EQUALS_IGNORE_CASE(module_entry.szModule, module_name))
                return {reinterpret_cast<uintptr_t>(module_entry.modBaseAddr),
                        static_cast<uintptr_t>(module_entry.modBaseSize)};
        }

        return {};

    }

    return {};
}

std::string Memory::read_str(uintptr_t address) noexcept {
    char buffer[128];
    this->read_raw((void *) address, &buffer, sizeof(buffer));
    const auto &it = std::find(buffer, buffer + 64, '\0');

    if (it != buffer + 64)
        return std::string(buffer, it);

    return "unknown";
}

bool Memory::readv(uintptr_t address, void *buffer, uintptr_t size) {
    this->read_raw(reinterpret_cast<void *>(address), buffer, size);
    return true;
}
