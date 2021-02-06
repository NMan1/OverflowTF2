#pragma once

class IBaseFileSystem;

class key_values
{
public:
	static key_values* init(key_values* kv, const char* name);
	static bool load_from_buffer(key_values* kv, char const* resourceName, const char* pBuffer, IBaseFileSystem* pFileSystem = 0, const char* pPathID = 0);

	int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

	char* m_sValue;
	wchar_t* m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		unsigned char m_Color[4];
	};

	char	m_iDataType;
	char	m_bHasEscapeSequences;	// true, if while parsing this KeyValue, Escape Sequences are used (default false)
	char	m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
	char	unused[1];

	key_values* m_pPeer;	// pointer to next key in list
	key_values* m_pSub;	// pointer to Start of a new sub key list
	key_values* m_pChain;// Search here if it's not in our list
};