#ifndef _KHMIBASEHEAD_H__
#define _KHMIBASEHEAD_H__
#include "KCWindow.h"
#include "KCButton.h"
#include "KCTextCtrl.h"
#include "KCCheckBox.h"
#include "KCListBox.h"
#include "KCSlideCtrl.h"
#include "KCProgressCtrl.h"
#include "KCImageCtrl.h"
#include "KDialogBase.h"

// Add.hzf.2006.05.18
// 安全删除一个需调用delete释放的对象
#define SAFE_DELETE(pObject) if((pObject) != NULL) {delete (pObject); (pObject) = NULL;}
// 安全删除一组需调用delete[]释放的对象
#define SAFE_DELETE_GROUP(pObject) if((pObject) != NULL) {delete[] (pObject); (pObject) = NULL;}

enum {KMB_OK, KMB_QUESTION, KMB_ERROR, KMB_RIGHT};


enum _PICTYPE
{
	PIC_NONE = 0,		//无图片
	PIC_BMP,			//BMP图片
	PIC_JPG				//JPG图片
};

typedef unsigned char byte;
typedef struct tagID3INFO
{
	int   nUnicodeType;
	char* title;
	int   nTitleLen;
	char* artist;
	int   nArtistLen;
	char* album;
	int   nAlbumLen;
	void* pic;
	long  picSize;
	byte  picType;
	tagID3INFO()
	{
		nUnicodeType = 0;
		nTitleLen = 0;
		nAlbumLen = 0;
		nArtistLen = 0;
		title = NULL;
		artist = NULL;
		album = NULL;
		pic = NULL;
		picSize = 0;
		picType = PIC_NONE;
	}
	~tagID3INFO()
	{
		SAFE_DELETE(title);
		SAFE_DELETE(artist);
		SAFE_DELETE(album);
		SAFE_DELETE(pic);
	}
}ID3INFO;


// 键盘按键定义
extern unsigned short KVK_LEFT;
extern unsigned short KVK_RIGHT;
extern unsigned short KVK_UP;
extern unsigned short KVK_DOWN;
extern unsigned short KVK_OK;
extern unsigned short KVK_CANCEL;
extern unsigned short KVK_RETURN;
extern unsigned short KVK_ZOOMIN;
extern unsigned short KVK_ZOOMOUT;

UICORE_DLL_API HCScreen* GetScreen();
//获得屏幕的IReSurface
UICORE_DLL_API IReSurface* GetScreenSurf();
//获得屏幕的宽度
UICORE_DLL_API HINT GetScreenWidth();
//获得屏幕的高度
UICORE_DLL_API HINT GetScreenHeight();
//是否允许屏幕进行绘制
UICORE_DLL_API void EnableScreenDraw(HBOOL bEnable);
UICORE_DLL_API HBOOL IsCanScreenDraw();
//对屏幕的给定区域进行上屏操作
UICORE_DLL_API void FlipScreenRect(HINT x, HINT y, HINT width, HINT height);

UICORE_DLL_API int KNMessageBox(HString str, HINT type = KMB_OK, HINT nDelayTime = 5);
UICORE_DLL_API bool KNPlayVoice(int iVoiceID);
UICORE_DLL_API HString GetHMIPath(const HString &name);
UICORE_DLL_API void* GetID3FromFile(const char* sFile);

class UICORE_DLL_API CMsgDlg : public HCWindow
{
public:
    CMsgDlg();
    virtual ~CMsgDlg();

    //消息处理函数，各子类都要重载
    HINT Create(int x, int y, int w, int h, HCScreen* pScreen, HWORD type, HString& str, HINT nDelayTime);

    void Draw(IReSurface* pSurface);

    static void OnBtnOK(void* p, void*);
    void OnBtnOK();

    static void OnBtnCancel(void* p, void*);
    void OnBtnCancel();

    static void OnTimer(void* p, void*);
    void OnTimer();

    HINT  OnInit();

protected:
    HCButton m_btnOK;
    HCButton m_btnCancel;
    HString m_strMsg;
    HString m_strTitle;
    CTimer m_timer;
    HINT m_nStrRow;
    HINT m_nStrWidth;
};

#endif //_KHMIBASEHEAD_H__