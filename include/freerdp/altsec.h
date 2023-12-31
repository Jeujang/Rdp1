/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Alternate Secondary Drawing Orders Interface API
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FREERDP_UPDATE_ALTSEC_H
#define FREERDP_UPDATE_ALTSEC_H

#include <freerdp/types.h>

#define DSDNG_STRETCH 0x00000001
#define DSDNG_TILE 0x00000002
#define DSDNG_PERPIXELALPHA 0x00000004
#define DSDNG_TRANSPARENT 0x00000008
#define DSDNG_MUSTFLIP 0x00000010
#define DSDNG_TRUESIZE 0x00000020

#define FRAME_START 0x00000000
#define FRAME_END 0x00000001

#define STREAM_BITMAP_END 0x01
#define STREAM_BITMAP_COMPRESSED 0x02
#define STREAM_BITMAP_V2 0x04

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		UINT32 sIndices;
		UINT32 cIndices;
		UINT16* indices;
	} OFFSCREEN_DELETE_LIST;

	typedef struct
	{
		UINT32 id;
		UINT32 cx;
		UINT32 cy;
		OFFSCREEN_DELETE_LIST deleteList;
	} CREATE_OFFSCREEN_BITMAP_ORDER;

	typedef struct
	{
		UINT32 bitmapId;
	} SWITCH_SURFACE_ORDER;

	typedef struct
	{
		UINT32 flFlags;
		UINT32 ulLeftWidth;
		UINT32 ulRightWidth;
		UINT32 ulTopHeight;
		UINT32 ulBottomHeight;
		UINT32 crTransparent;
	} NINE_GRID_BITMAP_INFO;

	typedef struct
	{
		UINT32 bitmapBpp;
		UINT32 bitmapId;
		UINT32 cx;
		UINT32 cy;
		NINE_GRID_BITMAP_INFO nineGridInfo;
	} CREATE_NINE_GRID_BITMAP_ORDER;

	typedef struct
	{
		UINT32 action;
	} FRAME_MARKER_ORDER;

	typedef struct
	{
		UINT32 bitmapFlags;
		UINT32 bitmapBpp;
		UINT32 bitmapType;
		UINT32 bitmapWidth;
		UINT32 bitmapHeight;
		UINT32 bitmapSize;
		UINT32 bitmapBlockSize;
		BYTE* bitmapBlock;
	} STREAM_BITMAP_FIRST_ORDER;

	typedef struct
	{
		UINT32 bitmapFlags;
		UINT32 bitmapType;
		UINT32 bitmapBlockSize;
		BYTE* bitmapBlock;
	} STREAM_BITMAP_NEXT_ORDER;

	typedef struct
	{
		UINT32 cbSize;
		UINT32 cbTotalSize;
		UINT32 cbTotalEmfSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_FIRST_ORDER;

	typedef struct
	{
		UINT32 cbSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_NEXT_ORDER;

	typedef struct
	{
		UINT32 cbSize;
		UINT32 cbTotalSize;
		UINT32 cbTotalEmfSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_END_ORDER;

	typedef struct
	{
		UINT32 flags;
		UINT32 cacheType;
		UINT32 cacheIndex;
		UINT32 cbSize;
		UINT32 cbTotalSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_CACHE_FIRST_ORDER;

	typedef struct
	{
		UINT32 flags;
		UINT32 cacheType;
		UINT32 cacheIndex;
		UINT32 cbSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_CACHE_NEXT_ORDER;

	typedef struct
	{
		UINT32 flags;
		UINT32 cacheType;
		UINT32 cacheIndex;
		UINT32 cbSize;
		UINT32 cbTotalSize;
		BYTE* emfRecords;
	} DRAW_GDIPLUS_CACHE_END_ORDER;

	typedef BOOL (*pCreateOffscreenBitmap)(
	    rdpContext* context, const CREATE_OFFSCREEN_BITMAP_ORDER* create_offscreen_bitmap);
	typedef BOOL (*pSwitchSurface)(rdpContext* context, const SWITCH_SURFACE_ORDER* switch_surface);
	typedef BOOL (*pCreateNineGridBitmap)(
	    rdpContext* context, const CREATE_NINE_GRID_BITMAP_ORDER* create_nine_grid_bitmap);
	typedef BOOL (*pFrameMarker)(rdpContext* context, const FRAME_MARKER_ORDER* frame_marker);
	typedef BOOL (*pStreamBitmapFirst)(rdpContext* context,
	                                   const STREAM_BITMAP_FIRST_ORDER* stream_bitmap_first);
	typedef BOOL (*pStreamBitmapNext)(rdpContext* context,
	                                  const STREAM_BITMAP_NEXT_ORDER* stream_bitmap_next);
	typedef BOOL (*pDrawGdiPlusFirst)(rdpContext* context,
	                                  const DRAW_GDIPLUS_FIRST_ORDER* draw_gdiplus_first);
	typedef BOOL (*pDrawGdiPlusNext)(rdpContext* context,
	                                 const DRAW_GDIPLUS_NEXT_ORDER* draw_gdiplus_next);
	typedef BOOL (*pDrawGdiPlusEnd)(rdpContext* context,
	                                const DRAW_GDIPLUS_END_ORDER* draw_gdiplus_end);
	typedef BOOL (*pDrawGdiPlusCacheFirst)(
	    rdpContext* context, const DRAW_GDIPLUS_CACHE_FIRST_ORDER* draw_gdiplus_cache_first);
	typedef BOOL (*pDrawGdiPlusCacheNext)(
	    rdpContext* context, const DRAW_GDIPLUS_CACHE_NEXT_ORDER* draw_gdiplus_cache_next);
	typedef BOOL (*pDrawGdiPlusCacheEnd)(
	    rdpContext* context, const DRAW_GDIPLUS_CACHE_END_ORDER* draw_gdiplus_cache_end);
	typedef BOOL (*pDrawOrderInfo)(rdpContext* context, UINT8 orderType, const char* orderName);

	struct rdp_altsec_update
	{
		rdpContext* context;     /* 0 */
		UINT32 paddingA[16 - 1]; /* 1 */

		pCreateOffscreenBitmap CreateOffscreenBitmap; /* 16 */
		pSwitchSurface SwitchSurface;                 /* 17 */
		pCreateNineGridBitmap CreateNineGridBitmap;   /* 18 */
		pFrameMarker FrameMarker;                     /* 19 */
		pStreamBitmapFirst StreamBitmapFirst;         /* 20 */
		pStreamBitmapNext StreamBitmapNext;           /* 21 */
		pDrawGdiPlusFirst DrawGdiPlusFirst;           /* 22 */
		pDrawGdiPlusNext DrawGdiPlusNext;             /* 23 */
		pDrawGdiPlusEnd DrawGdiPlusEnd;               /* 24 */
		pDrawGdiPlusCacheFirst DrawGdiPlusCacheFirst; /* 25 */
		pDrawGdiPlusCacheNext DrawGdiPlusCacheNext;   /* 26 */
		pDrawGdiPlusCacheEnd DrawGdiPlusCacheEnd;     /* 27 */
		/* Statistics callback */
		pDrawOrderInfo DrawOrderInfo; /* 28 */
		UINT32 paddingB[32 - 29];     /* 29 */
	};
	typedef struct rdp_altsec_update rdpAltSecUpdate;

#ifdef __cplusplus
}
#endif

#endif /* FREERDP_UPDATE_ALTSEC_H */
