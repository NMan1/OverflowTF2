#include <windows.h>
#include "c_key_values.hpp"
#include "..\..\utils\memory\memory.hpp"
#include "..\..\utils\memory\memory.hpp"

bool key_values::load_from_buffer(key_values* kv, char const* resourceName, const char* pBuffer, IBaseFileSystem* pFileSystem, const char* pPathID) {
	typedef int(__thiscall* LoadFromBufferFn)(key_values* kv, char const*, const char*, IBaseFileSystem*, const char*);
	static LoadFromBufferFn Load = (LoadFromBufferFn)memory::find_pattern("engine.dll", "55 8B EC 83 EC 38 53 8B 5D 0C");
	return Load(kv, resourceName, pBuffer, pFileSystem, pPathID);
}

key_values* key_values::init(key_values* kv, const char* name) {
	typedef key_values* (__thiscall* InitializeFn)(key_values*, const char*);
	static InitializeFn Init = (InitializeFn)(memory::find_pattern("engine.dll", "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6") - 0x42);
	return Init(kv, name); 
}
