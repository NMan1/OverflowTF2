#pragma once

//big mess

class convar;
class i_convar;
class CCommand;
class ConCommand;
class ConCommandBase;
class color;

class i_convar {
public:
	virtual void SetValue(const char* pValue) = 0;
	virtual void SetValue(float flValue) = 0;
	virtual void SetValue(int nValue) = 0;
	virtual const char* GetName(void)const = 0;
	virtual bool IsFlagSet(int nFlag) const = 0;
};

typedef void(*FnChangeCallback_t)(i_convar* var, const char* pOldValue, float flOldValue);

class IConCommandBaseAccessor {
public:
	virtual bool RegisterConCommandBase(ConCommandBase* pVar) = 0;
};

void ConVar_Register(int nCVarFlag, IConCommandBaseAccessor* pAccessor = nullptr);

class ConCommandBase {
public:
	ConCommandBase(void);
	ConCommandBase(const char* pName, const char* pHelpString = 0, int flags = 0);

	virtual						~ConCommandBase(void);
	virtual	bool				IsCommand(void) const;
	virtual bool					IsFlagSet(int flag) const;
	virtual void					AddFlags(int flags);
	virtual void					RemoveFlags(int flags);
	virtual int					GetFlags() const;
	virtual const char* GetName(void) const;
	virtual const char* GetHelpText(void) const;
	virtual bool					IsRegistered(void) const;
	virtual int					GetDLLIdentifier() const;
	virtual void					Create(const char* pName, const char* pHelpString = 0, int flags = 0);
	virtual void					Init();

public:
	ConCommandBase* m_pNext;
	bool							m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int								m_nFlags;

public:
	static ConCommandBase* s_pConCommandBases;
	static IConCommandBaseAccessor* s_pAccessor;
};

class convar : public ConCommandBase, public i_convar {
public:

	typedef ConCommandBase BaseClass;

	convar(const char* pName, const char* pDefaultValue, int flags = 0);

	convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString);
	convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax);
	convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, FnChangeCallback_t callback);
	convar(const char* pName, const char* pDefaultValue, int flags, const char* pHelpString, bool bMin, float fMin, bool bMax, float fMax, FnChangeCallback_t callback);

	virtual						~convar(void);

	virtual bool					IsFlagSet(int flag) const;
	virtual const char* GetHelpText(void) const;
	virtual bool					IsRegistered(void) const;
	virtual const char* GetName(void) const;
	virtual const char* GetBaseName(void) const;
	virtual int						GetSplitScreenPlayerSlot() const;
	DWORD GetColor(void) const;
	virtual void					AddFlags(int flags);
	virtual int						GetFlags() const;
	virtual	bool					IsCommand(void) const;
	virtual void					set_value(const char* value);
	virtual void					set_value(float value);
	virtual void					set_value(int value);
	virtual void					set_value(DWORD value);
	virtual void					InternalSetValue(const char* value);
	virtual void					InternalSetFloatValue(float fNewValue);
	virtual void					InternalSetIntValue(int nValue);
	virtual void					InternalSetColorValue(DWORD value);
	virtual bool					ClampValue(float& value);
	virtual void					ChangeStringValue(const char* tempVal, float flOldValue);
	virtual void					Create(const char* pName, const char* pDefaultValue, int flags = 0,
		const char* pHelpString = 0, bool bMin = false, float fMin = 0.0,
		bool bMax = false, float fMax = false, FnChangeCallback_t callback = 0);


	//----------------------------
	// Non-virtual helper methods
	//----------------------------
	float					get_float(void) const;
	int						GetInt(void) const;
	//DWORD					GetColor(void) const;
	const char* GetString(void) const;
	const char* GetDefault(void) const;

	void InstallChangeCallback(FnChangeCallback_t callback);

	// Value
	struct CVValue_t
	{
		char* m_pszString;
		int		m_StringLength;
		float	m_fValue;
		int		m_nValue;
	};

	convar* m_pParent;
	const char* m_pszDefaultValue;
	CVValue_t				m_Value;
	bool						m_bHasMin;
	float					m_fMinVal;
	bool						m_bHasMax;
	float					m_fMaxVal;
	FnChangeCallback_t		m_fnChangeCallback;

	char pad_0x0000[0x4]; //0x0000
	convar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	convar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 
};

class IAppSystem {
public:
	virtual bool Connect(void* factory) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* pInterfaceName) = 0;
	virtual int Init() = 0;
	virtual void Shutdown(char* reason) = 0;
};

class i_cvar : public IAppSystem {
public:
	virtual int AllocateDLLIdentifier() = 0;
	virtual void RegisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommand(ConCommandBase* pCommandBase) = 0;
	virtual void UnregisterConCommands(int id) = 0;
	virtual const char* GetCommandLineValue(const char* pVariableName) = 0;
	virtual ConCommandBase* FindCommandBase(const char* name) = 0;
	virtual const ConCommandBase* FindCommandBase(const char* name) const = 0;
	virtual convar* find_var(const char* var_name) = 0;
	virtual const convar* find_var(const char* var_name) const = 0;
	virtual ConCommand* FindCommand(const char* name) = 0;
	virtual const ConCommand* FindCommand(const char* name) const = 0;
	virtual ConCommandBase* GetCommands(void) = 0;
	virtual const ConCommandBase* GetCommands(void) const = 0;
	virtual void InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void CallGlobalChangeCallbacks(convar* var, const char* pOldString, float flOldValue) = 0;
	virtual void InstallConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const color& clr, const char* pFormat, ...) const = 0;
	virtual void ConsolePrintf(const char* pFormat, ...) const = 0;
	virtual void ConsoleDPrintf(const char* pFormat, ...) const = 0;
	virtual void RevertFlaggedConVars(int nFlag) = 0;
	virtual void InstallCVarQuery(void* pQuery) = 0;
	virtual bool IsMaterialThreadSetAllowed() const = 0;
	virtual void QueueMaterialThreadSetValue(convar* pConVar, const char* pValue) = 0;
	virtual void QueueMaterialThreadSetValue(convar* pConVar, int nValue) = 0;
	virtual void QueueMaterialThreadSetValue(convar* pConVar, float flValue) = 0;
	virtual bool HasQueuedMaterialThreadConVarSets() const = 0;
	virtual int	 ProcessQueuedMaterialThreadConVarSets() = 0;

protected:
	class ICVarIteratorInternal;

public:
	class Iterator {
	public:
		inline Iterator(i_cvar* icvar);
		inline ~Iterator(void);
		inline void		SetFirst(void);
		inline void		Next(void);
		inline bool		IsValid(void);
		inline ConCommandBase* Get(void);
	private:
		ICVarIteratorInternal* m_pIter;
	};

protected:
	class ICVarIteratorInternal {
	public:
		virtual ~ICVarIteratorInternal() {}
		virtual void		SetFirst(void) = 0;
		virtual void		Next(void) = 0;
		virtual	bool		IsValid(void) = 0;
		virtual ConCommandBase* Get(void) = 0;
	};

	virtual ICVarIteratorInternal* FactoryInternalIterator(void) = 0;
	friend class Iterator;
};
