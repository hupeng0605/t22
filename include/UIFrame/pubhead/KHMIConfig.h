

#ifndef _KHMICONFIG_H_
#define _KHMICONFIG_H_

#include "Pubhead.h"
#include "CfgStruct.h"


// 帮助获取配置信息的工具类
class UICORE_DLL_API HUIConfig
{
public:
    HUIConfig();
    virtual ~HUIConfig();
    static HLONG Load(const HString&, HDialogProp* pDialogProp);
    static HLONG Load(const HINT iID, HDialogProp* pDialogProp);
    static HLONG LoadFile(HString &name, HDialogProp* pDialogProp);
    static HLONG Save(const HString&);
    static HLONG Save(const HINT iID);

    //二进制加载
    static HINT ReadBFileToKDlgProp(HString& filename, HDialogProp& dlg);
    static HBaseCtrlProp* CreateStructFromBinaryFile(HBYTE* CtrlInfoBuffer, HBYTE*& offsetBack, const HString& strKdsPath);
    static void ParseProp(HBaseCtrlProp* prop, HBYTE * CtrlInfoBuffer, HBYTE*& offsetBack, const HString&);

private:
    static HBaseCtrlProp* ReadCtrlStruct(int, HString strSection, const HString&);

#ifndef KOTEI_EVC
    static UINT GetProfileInt(
        const HString& strSectionName,  // section name
        const HString& strKeyName,  // key name
        HINT nDefault,       // return value if key name is not found
        const HString& strFileName) // initialization filename
    {
        return GetPrivateProfileInt(strSectionName.c_str(),
                                    strKeyName.c_str(),
                                    nDefault,
                                    strFileName.c_str());
    }

    static HULONG GetProfileString(
        const HString& strSectionName,
        const HString& strKeyName,
        const HCHAR* strDefault,
        HCHAR* pReturnedString,
        HULONG nSize,
        const HString& strFileName)
    {
        return GetPrivateProfileString(
                   strSectionName.c_str(),
                   strKeyName.c_str(),
                   strDefault,
                   pReturnedString,
                   nSize,
                   strFileName.c_str());
    }
#else
    static UINT GetProfileInt(
        const HString& ,  // section name
        const HString& ,  // key name
        HINT ,       // return value if key name is not found
        const HString&)  // initialization filename
    {
        return 0;
    }

    static HULONG GetProfileString(
        const HString& ,
        const HString& ,
        const HCHAR* ,
        HCHAR* ,
        HULONG ,
        const HString&)
    {
        return 0;
    }
#endif
};

#endif // _KHMICONFIG_H_