#pragma once
#include <windows.h>
#include <Psapi.h>
#include <string>
#include <memory>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

namespace memory {
	struct protect_t {
		protect_t(void* addr, uint32_t size, DWORD flags) {
			m_size = size;
			m_addr = addr;

			VirtualProtect(m_addr, m_size, flags, &m_flags);
		}

		~protect_t() { VirtualProtect(m_addr, m_size, m_flags, &m_flags); }

		DWORD m_flags = 0ul;
		uint32_t m_size = 0u;
		void* m_addr = nullptr;
	};

	struct hook_t {
		hook_t() = default;

		hook_t(uintptr_t ptr) {
			m_vtable = reinterpret_cast<uintptr_t**>(ptr);

			init();
		};

		hook_t(void* ptr) {
			m_vtable = reinterpret_cast<uintptr_t**>(ptr);

			init();
		};

		__forceinline bool init() {
			if (!m_vtable)
				return false;

			const auto protect = protect_t(m_vtable, sizeof(uintptr_t), PAGE_READWRITE);

			m_original = *m_vtable;

			for (m_table_length = 0u; m_original[m_table_length]; m_table_length++) {
				if (IS_INTRESOURCE(m_original[m_table_length]))
					break;
			}

			if (!m_table_length)
				return false;

			m_replace = std::make_unique<uintptr_t[]>(m_table_length + 1);

			std::memset(m_replace.get(), 0, m_table_length * sizeof(uintptr_t) + sizeof(uintptr_t));

			std::memcpy(&m_replace[1], m_original, m_table_length * sizeof(uintptr_t));

			std::memcpy(m_replace.get(), &m_original[-1], sizeof(uintptr_t));

			*m_vtable = &m_replace[1];

			return true;
		}

		template <typename T>
		__forceinline void hook(uint32_t index, T replace_function) {
			if (index > m_table_length) {
				return;
			}

			m_replace[index + 1u] = reinterpret_cast<uintptr_t>(replace_function);
		}

		template <typename T>
		__forceinline T get_original(uint32_t index) {
			if (index > m_table_length) {
				return nullptr;
			}

			return reinterpret_cast<T>(m_original[index]);
		}

		__forceinline void unhook(uint32_t index) {
			if (index > m_table_length) {
				return;
			}

			m_replace[index + 1u] = m_original[index];
		}

		__forceinline void unhook() {
			if (!m_original) {
				return;
			}

			const auto protect = protect_t(m_vtable, sizeof(uintptr_t), PAGE_READWRITE);

			*m_vtable = m_original;
			m_original = nullptr;
		}

		uint32_t m_table_length = 0u;
		uintptr_t** m_vtable = nullptr;
		uintptr_t* m_original = nullptr;
		std::unique_ptr<uintptr_t[]> m_replace = nullptr;
	};

	static DWORD find_pattern(std::string module_name, const std::string& pattern) {
		auto pat = pattern.c_str();
		DWORD first_match = 0;
		const auto range_start = DWORD(GetModuleHandleA(module_name.c_str()));
		MODULEINFO miModInfo;
		K32GetModuleInformation(GetCurrentProcess(), HMODULE(range_start), &miModInfo, sizeof(MODULEINFO));
		const auto range_end = range_start + miModInfo.SizeOfImage;
		for (auto p_cur = range_start; p_cur < range_end; p_cur++) {
			if (!*pat)
				return first_match;

			if (*(PBYTE)pat == '\?' || *(BYTE*)p_cur == getByte(pat)) {
				if (!first_match)
					first_match = p_cur;

				if (!pat[2])
					return first_match;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;
			}
			else
			{
				pat = pattern.c_str();
				first_match = 0;
			}
		}

		return NULL;
	}
}