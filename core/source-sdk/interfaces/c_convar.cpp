#include "c_convar.hpp"
#include <windows.h>
#include "../structs/enums.hpp"
#include <winnt.h>
#include <corecrt_math.h>

ConCommandBase* ConCommandBase::s_pConCommandBases = nullptr;
static int	s_nCVarFlag = 0;
static int	s_nDLLIdentifier = -1;
static bool	s_bRegistered = false;

class CDefaultAccessor : public IConCommandBaseAccessor
{
public:
	virtual bool RegisterConCommandBase(ConCommandBase* pVar)
	{
		/*gInts.cvar->RegisterConCommand(pVar);
		return true;*/
		return false;
	}
};

static CDefaultAccessor s_DefaultAccessor;
IConCommandBaseAccessor* ConCommandBase::s_pAccessor = &s_DefaultAccessor;

void ConVar_Register(int nCVarFlag, IConCommandBaseAccessor* pAccessor)
{
	/*if (s_bRegistered)
		return;
	s_bRegistered = true;
	s_nCVarFlag = nCVarFlag;
	s_nDLLIdentifier = gInts.cvar->AllocateDLLIdentifier();
	ConCommandBase *pCur, *pNext;
	ConCommandBase::s_pAccessor = pAccessor ? pAccessor : &s_DefaultAccessor;
	pCur = ConCommandBase::s_pConCommandBases;
	while (pCur)
	{
		pNext = pCur->m_pNext;
		pCur->AddFlags(s_nCVarFlag);
		pCur->Init();
		pCur = pNext;
	}
	ConCommandBase::s_pConCommandBases = NULL;*/
}

convar::convar(const char* pName, const char* pDefaultValue, int flags)
{
	Create(pName, pDefaultValue, flags);
}

convar::convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString)
{
	Create(pName, pDefaultValue, flags, pHelpString);
}

convar::convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax)
{
	Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax);
}

convar::convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, FnChangeCallback_t callback)
{
	Create(pName, pDefaultValue, flags, pHelpString, false, 0.0, false, 0.0, callback);
}

convar::convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback)
{
	Create(pName, pDefaultValue, flags, pHelpString, bMin, fMin, bMax, fMax, callback);
}

convar::~convar(void)
{
	if (m_Value.m_pszString)
	{
		delete[] m_Value.m_pszString;
		m_Value.m_pszString = NULL;
	}
}

bool convar::IsFlagSet(int flag) const
{
	return (flag & m_pParent->m_nFlags) ? true : false;
}

const char* convar::GetHelpText(void) const
{
	return m_pParent->m_pszHelpString;
}

void convar::AddFlags(int flags)
{
	m_pParent->m_nFlags |= flags;
}

int convar::GetFlags(void) const
{
	return m_pParent->m_nFlags;
}

bool convar::IsRegistered(void) const
{
	return m_pParent->m_bRegistered;
}

bool convar::IsCommand(void) const
{
	return false;
}

const char* convar::GetName(void) const
{
	return m_pParent->m_pszName;
}

const char* convar::GetBaseName(void) const
{
	return m_pParent->m_pszName;
}

float convar::get_float(void) const
{
	return m_pParent->m_Value.m_fValue;
}

int convar::GetInt(void) const
{
	return m_pParent->m_Value.m_nValue;
}

const char* convar::GetString(void) const
{
	return m_pParent->m_Value.m_pszString;
}

int convar::GetSplitScreenPlayerSlot(void) const
{
	return 0;
}

void convar::InternalSetValue(const char* value)
{
	float fNewValue;
	char  tempVal[32];
	char* val;

	float flOldValue = m_Value.m_fValue;

	val = (char*)value;
	fNewValue = (float)atof(value);

	if (ClampValue(fNewValue))
	{
		val = tempVal;
	}

	// Redetermine value
	m_Value.m_fValue = fNewValue;
	m_Value.m_nValue = (int)(fNewValue);

	if (!(m_nFlags & (int)ConVarFlags_t::FCVAR_NEVER_AS_STRING))
	{
		ChangeStringValue(val, flOldValue);
	}
}

void convar::ChangeStringValue(const char* tempVal, float flOldValue)
{
	UNREFERENCED_PARAMETER(flOldValue);
	int len = strlen(tempVal) + 1;

	if (len > m_Value.m_StringLength)
	{
		if (m_Value.m_pszString)
		{
			delete[] m_Value.m_pszString;
		}

		m_Value.m_pszString = new char[len];
		m_Value.m_StringLength = len;
	}

	memcpy(m_Value.m_pszString, tempVal, len);

}

bool convar::ClampValue(float& value)
{
	if (m_bHasMin && (value < m_fMinVal))
	{
		value = m_fMinVal;
		return true;
	}

	if (m_bHasMax && (value > m_fMaxVal))
	{
		value = m_fMaxVal;
		return true;
	}

	return false;
}

void convar::InternalSetFloatValue(float fNewValue)
{
	if (fNewValue == m_Value.m_fValue)
		return;
	// Check bounds
	ClampValue(fNewValue);

	// Redetermine value
	float flOldValue = m_Value.m_fValue;
	m_Value.m_fValue = fNewValue;
	m_Value.m_nValue = (int)fNewValue;

	if (!(m_nFlags & (int)ConVarFlags_t::FCVAR_NEVER_AS_STRING))
	{
		char tempVal[32];
		ChangeStringValue(tempVal, flOldValue);
	}
}

void convar::InternalSetIntValue(int nValue)
{
	if (nValue == m_Value.m_nValue)
		return;

	float fValue = (float)nValue;
	if (ClampValue(fValue))
	{
		nValue = (int)(fValue);
	}

	float flOldValue = m_Value.m_fValue;
	m_Value.m_fValue = fValue;
	m_Value.m_nValue = nValue;

	if (!(m_nFlags & (int)ConVarFlags_t::FCVAR_NEVER_AS_STRING))
	{
		char tempVal[32];
		ChangeStringValue(tempVal, flOldValue);
	}
}

void convar::InternalSetColorValue(DWORD cValue)
{
	int color = (int)cValue;
	InternalSetIntValue(color);
}

void convar::Create(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback)
{
	static const char* empty_string = "";

	m_pParent = this;

	// Name should be static data
	m_pszDefaultValue = pDefaultValue ? pDefaultValue : empty_string;

	m_Value.m_StringLength = strlen(m_pszDefaultValue) + 1;
	m_Value.m_pszString = new char[m_Value.m_StringLength];
	memcpy(m_Value.m_pszString, m_pszDefaultValue, m_Value.m_StringLength);

	m_bHasMin = bMin;
	m_fMinVal = fMin;
	m_bHasMax = bMax;
	m_fMaxVal = fMax;

	m_fnChangeCallback = callback;
	m_Value.m_fValue = (float)atof(m_Value.m_pszString);
	m_Value.m_nValue = (int)m_Value.m_fValue;

	BaseClass::Create(pName, pHelpString, flags);
}

void convar::set_value(const char* value)
{
	m_pParent->InternalSetValue(value);
}

void convar::set_value(float value)
{
	m_pParent->InternalSetFloatValue(value);
}

void convar::set_value(int value)
{
	m_pParent->InternalSetIntValue(value);
}

void convar::set_value(DWORD value)
{
	m_pParent->InternalSetColorValue(value);
}

const char* convar::GetDefault(void) const
{
	return m_pParent->m_pszDefaultValue;
}

ConCommandBase::ConCommandBase(void)
{
	m_bRegistered = false;
	m_pszName = NULL;
	m_pszHelpString = NULL;

	m_nFlags = 0;
	m_pNext = NULL;
}

ConCommandBase::ConCommandBase(const char* pName, const char* pHelpString, int flags)
{
	Create(pName, pHelpString, flags);
}

ConCommandBase::~ConCommandBase(void)
{
}

bool ConCommandBase::IsCommand(void) const
{
	return true;
}

int ConCommandBase::GetDLLIdentifier() const
{
	return s_nDLLIdentifier;
}

void ConCommandBase::Create(const char* pName, const char* pHelpString, int flags)
{
	static const char* empty_string = "";

	m_bRegistered = false;

	m_pszName = pName;
	m_pszHelpString = pHelpString ? pHelpString : empty_string;

	m_nFlags = flags;

	if (!(m_nFlags & (int)ConVarFlags_t::FCVAR_UNREGISTERED))
	{
		m_pNext = s_pConCommandBases;
		s_pConCommandBases = this;
	}

	else
	{
		m_pNext = NULL;
	}

	Init();
}

void ConCommandBase::Init()
{
	if (s_pAccessor)
	{
		s_pAccessor->RegisterConCommandBase(this);
	}
}

const char* ConCommandBase::GetName(void) const
{
	return m_pszName;
}

void convar::InstallChangeCallback(FnChangeCallback_t callback)
{
	m_pParent->m_fnChangeCallback = callback;

	if (m_pParent->m_fnChangeCallback)
	{
		m_pParent->m_fnChangeCallback(this, m_Value.m_pszString, m_Value.m_fValue);
	}
}

bool ConCommandBase::IsFlagSet(int flag) const
{
	return (flag & m_nFlags) ? true : false;
}

void ConCommandBase::AddFlags(int flags)
{
	m_nFlags |= flags;
}

void ConCommandBase::RemoveFlags(int flags)
{
	m_nFlags &= ~flags;
}

int ConCommandBase::GetFlags(void) const
{
	return m_nFlags;
}

const char* ConCommandBase::GetHelpText(void) const
{
	return m_pszHelpString;
}

bool ConCommandBase::IsRegistered(void) const
{
	return m_bRegistered;
}