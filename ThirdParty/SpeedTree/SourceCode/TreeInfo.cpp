///////////////////////////////////////////////////////////////////////  
//         Name: TreeInfo.cpp
//
//  *** INTERACTIVE DATA VISUALIZATION (IDV) PROPRIETARY INFORMATION ***
//
//      Copyright (c) 2001-2004 IDV, Inc.
//      All Rights Reserved.
//
//      IDV, Inc.
//      1233 Washington St. Suite 610
//      Columbia, SC 29201
//      Voice: (803) 799-1699
//      Fax:   (803) 931-0320
//      Web:   http://www.idvinc.com
//
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Interactive Data Visualization and may not 
//  be copied or disclosed except in accordance with the terms of that 
//  agreement.

#include "Debug.h"
#include "TreeEngine.h"


///////////////////////////////////////////////////////////////////////  
//  SIdvTreeInfo::SIdvTreeInfo definition
//

SIdvTreeInfo::SIdvTreeInfo( ) :
    m_fFar(1100.0f),
    m_fNear(100.0f),
    m_nSeed(1200),
    m_fSize(50.0f),
    m_fSizeVariance(0.0f),
    m_nFlareSeed(444)
{
}
