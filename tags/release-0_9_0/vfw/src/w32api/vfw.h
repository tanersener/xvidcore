#ifndef _INC_VFW
#define _INC_VFW

#include <mmsystem.h>

#ifndef aviTWOCC
#define aviTWOCC(C0,C1) ((WORD)(BYTE)(C0)|((WORD)(BYTE)(C1) << 8))
#endif

#ifndef ICTYPE_VIDEO
#define ICTYPE_VIDEO mmioFOURCC('v', 'i', 'd', 'c')
#define ICTYPE_AUDIO mmioFOURCC('a', 'u', 'd', 'c')
#endif

#ifndef ICERR_OK
#define ICERR_OK 0L
#define ICERR_DONTDRAW 1L
#define ICERR_NEWPALETTE 2L
#define ICERR_GOTOKEYFRAME 3L
#define ICERR_STOPDRAWING 4L

#define ICERR_UNSUPPORTED -1L
#define ICERR_BADFORMAT -2L
#define ICERR_MEMORY -3L
#define ICERR_INTERNAL -4L
#define ICERR_BADFLAGS -5L
#define ICERR_BADPARAM -6L
#define ICERR_BADSIZE -7L
#define ICERR_BADHANDLE -8L
#define ICERR_CANTUPDATE -9L
#define ICERR_ABORT -10L
#define ICERR_ERROR -100L
#define ICERR_BADBITDEPTH -200L
#define ICERR_BADIMAGESIZE -201L

#define ICERR_CUSTOM -400L
#endif

#ifndef ICMODE_COMPRESS
#define ICMODE_COMPRESS 1
#define ICMODE_DECOMPRESS 2
#define ICMODE_FASTDECOMPRESS 3
#define ICMODE_QUERY 4
#define ICMODE_FASTCOMPRESS 5
#define ICMODE_DRAW 8
#endif

#define AVIIF_LIST 0x00000001L
#define AVIIF_TWOCC 0x00000002L
#define AVIIF_KEYFRAME 0x00000010L

#define ICCOMPRESS_KEYFRAME 0x00000001L

typedef struct {
	DWORD dwFlags;
	LPBITMAPINFOHEADER lpbiOutput;
	LPVOID lpOutput;
	LPBITMAPINFOHEADER lpbiInput;
	LPVOID lpInput;
	LPDWORD lpckid;
	LPDWORD lpdwFlags;
	LONG lFrameNum;
	DWORD dwFrameSize;
	DWORD dwQuality;
	LPBITMAPINFOHEADER lpbiPrev;
	LPVOID lpPrev;
} ICCOMPRESS;

#define ICCOMPRESSFRAMES_PADDING 0x00000001

typedef struct {
	DWORD dwFlags;
	LPBITMAPINFOHEADER lpbiOutput;
	LPARAM lOutput;
	LPBITMAPINFOHEADER lpbiInput;
	LPARAM lInput;
	LONG lStartFrame;
	LONG lFrameCount;
	LONG lQuality;
	LONG lDataRate;
	LONG lKeyRate;
	DWORD dwRate;
	DWORD dwScale;
	DWORD dwOverheadPerFrame;
	DWORD dwReserved2;
	LONG (CALLBACK *GetData)(LPARAM,LONG,LPVOID,LONG);
	LONG (CALLBACK *PutData)(LPARAM,LONG,LPVOID,LONG);
} ICCOMPRESSFRAMES;

#define ICDECOMPRESS_HURRYUP 0x80000000L
#define ICDECOMPRESS_UPDATE 0x40000000L
#define ICDECOMPRESS_PREROLL 0x20000000L
#define ICDECOMPRESS_NULLFRAME 0x10000000L
#define ICDECOMPRESS_NOTKEYFRAME 0x08000000L

typedef struct {
	DWORD dwFlags;
	LPBITMAPINFOHEADER lpbiInput;
	LPVOID lpInput;
	LPBITMAPINFOHEADER lpbiOutput;
	LPVOID lpOutput;
	DWORD ckid;
} ICDECOMPRESS;

typedef struct {
	DWORD dwSize;
	DWORD fccType;
	DWORD fccHandler;
	DWORD dwVersion;
	DWORD dwFlags;
	LRESULT dwError;
	LPVOID pV1Reserved;
	LPVOID pV2Reserved;
	DWORD dnDevNode;
} ICOPEN;

#define ICM_USER (DRV_USER+0x0000)

#define ICM_RESERVED ICM_RESERVED_LOW
#define ICM_RESERVED_LOW (DRV_USER+0x1000)
#define ICM_RESERVED_HIGH (DRV_USER+0x2000)

#define ICM_GETSTATE (ICM_RESERVED+0)
#define ICM_SETSTATE (ICM_RESERVED+1)
#define ICM_GETINFO (ICM_RESERVED+2)
#define ICM_CONFIGURE (ICM_RESERVED+10)
#define ICM_ABOUT (ICM_RESERVED+11)
#define ICM_GETERRORTEXT (ICM_RESERVED+12)
#define ICM_GETFORMATNAME (ICM_RESERVED+20)
#define ICM_ENUMFORMATS (ICM_RESERVED+21)
#define ICM_GETDEFAULTQUALITY (ICM_RESERVED+30)
#define ICM_GETQUALITY (ICM_RESERVED+31)
#define ICM_SETQUALITY (ICM_RESERVED+32)
#define ICM_SET (ICM_RESERVED+40)
#define ICM_GET (ICM_RESERVED+41)

#define ICM_FRAMERATE mmioFOURCC('F','r','m','R')
#define ICM_KEYFRAMERATE mmioFOURCC('K','e','y','R')

typedef struct {
	DWORD dwSize;
	DWORD fccType;
	DWORD fccHandler;
	DWORD dwFlags;
	DWORD dwVersion;
	DWORD dwVersionICM;
	WCHAR szName[16];
	WCHAR szDescription[128];
	WCHAR szDriver[128];
} ICINFO;

#define VIDCF_QUALITY 0x0001
#define VIDCF_CRUNCH 0x0002
#define VIDCF_TEMPORAL 0x0004
#define VIDCF_COMPRESSFRAMES 0x0008
#define VIDCF_DRAW 0x0010
#define VIDCF_FASTTEMPORALC 0x0020
#define VIDCF_FASTTEMPORALD 0x0080
#define VIDCF_QUALITYTIME 0x0040
#define VIDCF_FASTTEMPORAL (VIDCF_FASTTEMPORALC|VIDCF_FASTTEMPORALD)

#define ICVERSION 0x0104

#define ICM_COMPRESS_GET_FORMAT (ICM_USER+4)
#define ICM_COMPRESS_GET_SIZE (ICM_USER+5)
#define ICM_COMPRESS_QUERY (ICM_USER+6)
#define ICM_COMPRESS_BEGIN (ICM_USER+7)
#define ICM_COMPRESS (ICM_USER+8)
#define ICM_COMPRESS_END (ICM_USER+9)

#define ICM_DECOMPRESS_GET_FORMAT (ICM_USER+10)
#define ICM_DECOMPRESS_QUERY (ICM_USER+11)
#define ICM_DECOMPRESS_BEGIN (ICM_USER+12)
#define ICM_DECOMPRESS (ICM_USER+13)
#define ICM_DECOMPRESS_END (ICM_USER+14)
#define ICM_DECOMPRESS_SET_PALETTE (ICM_USER+29)
#define ICM_DECOMPRESS_GET_PALETTE (ICM_USER+30)

#define ICM_DRAW_QUERY (ICM_USER+31)
#define ICM_DRAW_BEGIN (ICM_USER+15)
#define ICM_DRAW_GET_PALETTE (ICM_USER+16)
#define ICM_DRAW_UPDATE (ICM_USER+17)
#define ICM_DRAW_START (ICM_USER+18)
#define ICM_DRAW_STOP (ICM_USER+19)
#define ICM_DRAW_BITS (ICM_USER+20)
#define ICM_DRAW_END (ICM_USER+21)
#define ICM_DRAW_GETTIME (ICM_USER+32)
#define ICM_DRAW (ICM_USER+33)
#define ICM_DRAW_WINDOW (ICM_USER+34)
#define ICM_DRAW_SETTIME (ICM_USER+35)
#define ICM_DRAW_REALIZE (ICM_USER+36)
#define ICM_DRAW_FLUSH (ICM_USER+37)
#define ICM_DRAW_RENDERBUFFER (ICM_USER+38)
#define ICM_DRAW_START_PLAY (ICM_USER+39)
#define ICM_DRAW_STOP_PLAY (ICM_USER+40)
#define ICM_DRAW_SUGGESTFORMAT (ICM_USER+50)
#define ICM_DRAW_CHANGEPALETTE (ICM_USER+51)
#define ICM_DRAW_IDLE (ICM_USER+52)
#define ICM_GETBUFFERSWANTED (ICM_USER+41)
#define ICM_GETDEFAULTKEYFRAMERATE (ICM_USER+42)
#define ICM_DECOMPRESSEX_BEGIN (ICM_USER+60)
#define ICM_DECOMPRESSEX_QUERY (ICM_USER+61)
#define ICM_DECOMPRESSEX (ICM_USER+62)
#define ICM_DECOMPRESSEX_END (ICM_USER+63)
#define ICM_COMPRESS_FRAMES_INFO (ICM_USER+70)
#define ICM_COMPRESS_FRAMES (ICM_USER+71)
#define ICM_SET_STATUS_PROC (ICM_USER+72)

#endif /* _INC_VFW */
