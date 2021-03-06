//*****************************************************************************
//
// OBJECTS.H
//
// Digital switch emulator program
//
// Written 04/23/94
//
//*****************************************************************************

//////////////////////////////////////////////////////////////////
// Call completion request

typedef struct _tagCOMPLETIONREQ
{               
	WORD wAddressID;
	WORD wComplType;
	DWORD dwTimeout;
	char szAddress[ADDRESS_SIZE+1];
	
} COMPLETIONREQ;

//////////////////////////////////////////////////////////////////
// Park request

typedef struct _tagPARKREQ
{
	char szParkAddress[ADDRESS_SIZE+1];
	char szOrigAddress[ADDRESS_SIZE+1];
	char szOrigName[OWNER_SIZE+1];

} PARKREQ;

//////////////////////////////////////////////////////////////////
// Lamp object

class CLampWnd : public CWnd
{
// Class variables
public:
    enum Direction { Left  = 0, Right = 1 };
    Direction m_Direction;   // Direction to draw arrow
    int       m_iState;      // Current indicator state
    BOOL      m_fDrawn;      // Whether we drew on last paint
    int       m_iCounter;    // Internal paint counter
    int       m_iDrawState;  // Current drawing state

// Constructor
public:
    CLampWnd();
    ~CLampWnd();
    
// State modifiers
public:
    void SetState(int iState);
    void DoTimer () { OnTimer(0); }

// Implementation
protected:
    virtual WNDPROC* GetSuperWndProcAddr();
    //{{AFX_MSG(CLampWnd)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// CEmulButton class

class CEmulButton : public CButton
{
// Class data
public:
    int         m_iButtonFunction;      // Button function
    int         m_iLampButtonID;        // Button lamp id
    CLampWnd*   m_pLampWnd;             // Lamp pointer for this button.

// Constructor
public:
    CEmulButton();    
    ~CEmulButton();
    void SetLampState(int iState);
};

///////////////////////////////////////////////////////////////////////////////
// CAddrCall class

class CAddrCall : public CObject
{ 
// Class data
public:
    BOOL        m_fIncoming;            // TRUE if call is incoming
    CString     m_strDestName;          // Name of connected party
    CString     m_strDestNumber;        // Number of connected party
    int         m_iState;               // Current address state (ADDRESSSTATE_xxx)
    int         m_iStateInfo;           // State information
    int         m_iLastState;           // Last known state
    DWORD       m_dwMediaModes;         // Media mode types supported by this call

// Constructor / destructor
public:
    CAddrCall();
    ~CAddrCall();
    const CAddrCall& operator=(const CAddrCall& src);
// Members
public:
    BOOL IsActive() const;
};

///////////////////////////////////////////////////////////////////////////////
// CAddrAppearance class

class CAddressAppearance : public CObject
{
// Class data
public:
    WORD        m_wAddressID;           // Address ID (0 - Total calls-1)
    CString     m_strNumber;            // Dialable number for this address
    int         m_iButtonIndex;         // Owner button's index (0 - BUTTON_COUNT-1)
    int         m_iRingCount;           // Ring count for this address
    CAddrCall   m_Call;                 // Current call info.
    CAddrCall   m_ConsultationCall;     // Current consulation call info.
    CStringList m_lstConf;				// Conference addresses added

public:
    // Constructor / destructor
    CAddressAppearance();
    ~CAddressAppearance();
    BOOL SetState (int iNewState, int iStateInfo=0);
};
