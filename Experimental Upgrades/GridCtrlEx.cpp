#include "stdafx.h"
#include <algorithm>
#include <numeric>
#include <map>
#include "GridCtrlEx.h"

CGridCtrlEx::CGridCtrlEx()
{
    SetBkColor(RGB(255, 255, 255));
}

BOOL CGridCtrlEx::SwapRow(int nRow1, int nRow2)
{   
    std::swap(m_RowData[nRow1], m_RowData[nRow2]);

    return 0;
}

// �Զ������п�
BOOL CGridCtrlEx::AutoGridColWidth(LPCTSTR lpFmt, ...)
{
    if (GetSafeHwnd() == NULL || GetColumnCount() == 0)
        return false;

    va_list argList;
    va_start(argList, lpFmt);

    // 1.�ֽ��ʽ���б�(��)
    std::vector<std::string> vecString;
    if (lpFmt != NULL)
    {
        vecString = StringUtil::split(lpFmt, "%");
        // vecString.erase(vecString.begin());
    }

    // 2.��ȡ����ʵ��ֵ(�п�)
    std::vector<int> vecGridWid;
    for (size_t i = 0; i < vecString.size(); i++)
    {
        int nWid = va_arg(argList, int);
        vecGridWid.push_back(nWid);
    }
    va_end(argList);

    // 3.�������п����
    std::map<int, int> mpWid;
    for (size_t i = 0; i < vecString.size(); i++)
        mpWid.insert(std::pair<int, int>(atoi(vecString[i].c_str()), vecGridWid[i]));

    // 4.����Grid���
    CRect rect;
    GetClientRect(&rect);
    int nGridWidth = rect.Width();

    // �������趨������ܺ�,��������򷵻�
    int nFixWid = std::accumulate(vecGridWid.begin(), vecGridWid.end(), 0);
    if (nFixWid > nGridWidth)
        return false;

    // 5.�趨��Ԫ����
    // ƽ�����(�ܿ��-���趨�п�/δ�趨����)
    int nNoSetColCount = GetColumnCount() - vecGridWid.size();// δ�趨����
    int dAveWid = 0;
    if (nNoSetColCount > 0)// ȫ���ж������趨
        dAveWid = (rect.Width() - nFixWid) / nNoSetColCount;

    // �趨ÿ�п��
    int nSetWid = 0;	// �Ѿ�ָ������ܺ�, ���һ����Ҫ���ܿ��-�Ѿ�ָ�����
    for (int i = 0; i < GetColumnCount(); i++)
    {
        // �������һ�п��, ƽ�����������ܻ���ʧ���־���,�����һ���ֲ�
        if (i == GetColumnCount() - 1)
        {
            SetColumnWidth(i, nGridWidth - nSetWid);
        }
        else
        {
            std::map<int, int>::iterator it = mpWid.find(i);
            if (it == mpWid.end())
            {
                SetColumnWidth(i, dAveWid);
                nSetWid += dAveWid;
            }
            else
            {
                SetColumnWidth(i, it->second);
                nSetWid += it->second;
            }
        }
    }
    Invalidate();

    return TRUE;
}
