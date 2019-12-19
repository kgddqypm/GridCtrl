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

// 自动调整列宽
BOOL CGridCtrlEx::AutoGridColWidth(LPCTSTR lpFmt, ...)
{
    if (GetSafeHwnd() == NULL || GetColumnCount() == 0)
        return false;

    va_list argList;
    va_start(argList, lpFmt);

    // 1.分解格式化列表(列)
    std::vector<std::string> vecString;
    if (lpFmt != NULL)
    {
        vecString = StringUtil::split(lpFmt, "%");
        // vecString.erase(vecString.begin());
    }

    // 2.读取参数实际值(列宽)
    std::vector<int> vecGridWid;
    for (size_t i = 0; i < vecString.size(); i++)
    {
        int nWid = va_arg(argList, int);
        vecGridWid.push_back(nWid);
    }
    va_end(argList);

    // 3.将列与列宽关联
    std::map<int, int> mpWid;
    for (size_t i = 0; i < vecString.size(); i++)
        mpWid.insert(std::pair<int, int>(atoi(vecString[i].c_str()), vecGridWid[i]));

    // 4.计算Grid宽度
    CRect rect;
    GetClientRect(&rect);
    int nGridWidth = rect.Width();

    // 计算已设定宽度列总和,如果超出则返回
    int nFixWid = std::accumulate(vecGridWid.begin(), vecGridWid.end(), 0);
    if (nFixWid > nGridWidth)
        return false;

    // 5.设定单元格宽度
    // 平均宽度(总宽度-已设定列宽/未设定列数)
    int nNoSetColCount = GetColumnCount() - vecGridWid.size();// 未设定列数
    int dAveWid = 0;
    if (nNoSetColCount > 0)// 全部列都己被设定
        dAveWid = (rect.Width() - nFixWid) / nNoSetColCount;

    // 设定每列宽度
    int nSetWid = 0;	// 已经指定宽度总和, 最后一列需要用总宽度-已经指定宽度
    for (int i = 0; i < GetColumnCount(); i++)
    {
        // 设置最后一列宽度, 平均宽度算出可能会损失部分精度,用最后一列弥补
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
