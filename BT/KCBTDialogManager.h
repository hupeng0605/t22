#pragma once
#include "define.h"
#include "KCBluetoothBaseDialog.h"
#include "KCBTAddressBookDialog.h"
#include "KCBTCallRecordsDialog.h"
#include "KCBTConnectionSettingDialog.h"
#include "KCBTDialDialog.h"
#include "KCBTMusicDialog.h"
#include "KCBTSerialPort.h"
#include "BTHmi.h"
class KCBTDialogManager
{
	public:
		static KCBTDialogManager* Instance();
		 static void DeleteInstance();
		virtual  ~KCBTDialogManager();
		HCBluetoothBaseDlg* GetCurrentDlg();
		void SetShow(eDIALOGTYPE InterfaceType);
		HCBluetoothBaseDlg* GetDlg( eDIALOGTYPE eDialogType );
		eDIALOGTYPE GetDlgID( HCBluetoothBaseDlg* pDialog );
		HCBluetoothBaseDlg	*	ShowDlg(eDIALOGTYPE eDialogType );
		void JumpToDlg(eDIALOGTYPE eDialogType);
		HCBluetoothBaseDlg* ShowPreDlg();
		void CreateAllBTDlg();
		eDIALOGTYPE GetCurrentDlgType(void);
		void ChangeThemeForAllDlg();
		void ChangeLangeForAllDlg(HINT nType);
		HDialogBase* ShowBTHMIDlg();
		HDialogBase* GetBTHMIDlg();
		void HideBTHMIdlg();
		bool IsBTHMIDlgShow();
		void ReleaseUncurrentSource();
		void ReleaseCurrentSource();
		void RequreCurrentSource();
		//HUINT SendData(const HBYTE *pdata,HUINT nDataLen);
	private:
		static KCBTDialogManager* s_pBTdialogManger;
		HCBluetoothBaseDlg* CreateBTDlg(eDIALOGTYPE eDialogType);
		HDialogBase* CreateBTHMIDlg();
		KCBTDialogManager();
		HCBluetoothBaseDlg*  m_pBTDialog[eMAXBTDIALOGNUM];
		HDialogBase* m_pBTHMIDlg;
		//HINT m_nCurrentLangue;
		//HCBluetoothBaseDlg* m_pBTCurrentDlg;
		eDIALOGTYPE m_eCurrentDlgType;
		eDIALOGTYPE m_ePreDlgType;
		bool m_bBTHMIDlg;
};