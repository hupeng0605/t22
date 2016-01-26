
#include "RenderingEngine.h"

// enum KBRUSHTYPE
// {
//  BRUSH_CIRCL,
//      BRUSH_SQUARE
// };
//
// struct BrushBuffer
// {
//  kn_byte* byMask; //Í¸Ã÷¶ÈÑÚÂë
//  kn_int width;
//  kn_int height;
//  BrushBuffer()
//  {
//      byMask = NULL;
//      width = height = 0;
//  }
// };
// struct REBrush
// {
//  BrushBuffer* buff;
//  kn_int space;
// };
//
// struct REBrushGenerate
// {
//  REBrush* instant;
//  KBRUSHTYPE shape;
//  kn_float                  radius;
//  kn_int                    spikes;       /* 2 - 20     */
//  kn_float                  hardness;     /* 0.0 - 1.0  */
// };



class BrushManager
{
public:

    BrushManager()
    {
        InitialDefaultBrush();
    }

    ~BrushManager()
    {
        ReleaseAllBrush();
    }

    HINT AddGenBrush(REBrushGenerate* ptem)
    {
        if (ptem)
        {
            m_listBrush.push_back(ptem);
        }

        return m_listBrush.size();
    }

    void LoadBrushFromFile(REBrushGenerate& BrushGen, HString& filename)
    {

    }

    HINT  BrushSize()
    {
        return m_listBrush.size();
    }
    REBrushGenerate* CreateGenBrush(HINT ispace, HFLOAT fradius, HFLOAT fhardness, HINT ispike = 2);
    void InitialDefaultBrush();

    void   ReleaseAllBrush()
    {

        for (HINT i = 0 ; i < m_listBrush.size(); i++)
        {
            SAFE_DELETE_GROUP(m_listBrush[i]->instant->buff->byMask);
            SAFE_DELETE(m_listBrush[i]->instant->buff);
            SAFE_DELETE(m_listBrush[i]->instant);
            SAFE_DELETE(m_listBrush[i]);
        }
    }

    REBrushGenerate* GetBrush(HINT index)
    {
        if (index < m_listBrush.size())
        {
            return m_listBrush[index];
        }
        else
            return NULL;
    }
private:

    vector<REBrushGenerate*> m_listBrush;

};
