//*********************************************************************  
// �ļ�����:  GridCtrlEx.h 
// ����˵��:  GridCtr��չ��
//*********************************************************************
#pragma once
#include "GridCtrl.h"

class CGridCtrlEx: public CGridCtrl
{
public:
    CGridCtrlEx();

public:
    // ����
    BOOL SwapRow(int nRow1, int nRow2);
    // �Զ������п�
    BOOL AutoGridColWidth(LPCTSTR lpFmt = NULL, ...);
};