//*********************************************************************  
// 文件名称:  GridCtrlEx.h 
// 功能说明:  GridCtr扩展类
//*********************************************************************
#pragma once
#include "GridCtrl.h"

class CGridCtrlEx: public CGridCtrl
{
public:
    CGridCtrlEx();

public:
    // 换行
    BOOL SwapRow(int nRow1, int nRow2);
    // 自动调整列宽
    BOOL AutoGridColWidth(LPCTSTR lpFmt = NULL, ...);
};