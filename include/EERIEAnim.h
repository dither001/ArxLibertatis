/*
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
///////////////////////////////////////////////////////////////////////////////
// EERIEAnim
///////////////////////////////////////////////////////////////////////////////
//
// Description:
//		Animation funcs
//
// Updates: (date) (person) (update)
//
// Code: Cyril Meynier
//
// Copyright (c) 1999 ARKANE Studios SA. All rights reserved
///////////////////////////////////////////////////////////////////////////////
#ifndef  EERIEANIM_H
#define  EERIEANIM_H

#include <string>

#include "EERIETypes.h"
#include "EERIEPoly.h"

//-----------------------------------------------------------------------------
#define HALOMAX 2000
extern long MAX_LLIGHTS;
#define MAX_ANIMATIONS 900

//-----------------------------------------------------------------------------
extern long HALOCUR ;
extern D3DTLVERTEX LATERDRAWHALO[HALOMAX*4];
extern EERIE_LIGHT * llights[32];

//-----------------------------------------------------------------------------
long EERIE_ANIMMANAGER_Count( std::string& tex, long * memsize);
void EERIE_ANIMMANAGER_ClearAll();
void llightsInit();
void Preparellights(EERIE_3D * pos);
void Insertllight(EERIE_LIGHT * el, float dist);

//-----------------------------------------------------------------------------
void ManageObjectClothes(INTERACTIVE_OBJ * io, EERIE_3DOBJ * eobj);
void PopAllTriangleList(bool);
void PopOneTriangleList(TextureContainer * _pTex, bool _bNoUpdate = true);
void PopAllTriangleListTransparency();

//-----------------------------------------------------------------------------
ARX_D3DVERTEX * PushVertexInTableCull(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TNormalTrans(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TAdditive(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TSubstractive(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TMultiplicative(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TMetal(TextureContainer *);

ARX_D3DVERTEX * PushVertexInTableCullH(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TNormalTransH(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TAdditiveH(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TSubstractiveH(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TMultiplicativeH(TextureContainer *);
ARX_D3DVERTEX * PushVertexInTableCull_TMetalH(TextureContainer *);

//-----------------------------------------------------------------------------
void PushInterBump(TextureContainer *, D3DTLVERTEX *);
void CalculateInterZMapp(EERIE_3DOBJ * _pobj3dObj, long lIdList, long * _piInd, TextureContainer * _pTex, D3DTLVERTEX * _pD3DVertex);
void EERIE_ANIMMANAGER_ReloadAll();
#endif // EERIEANIM_H
