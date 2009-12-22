/*--------------------------------------------------------------------------
Copyright (c) 2009, Code Aurora Forum. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Code Aurora nor
      the names of its contributors may be used to endorse or promote
      products derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------*/
#ifndef __OMX_QCOM_EXTENSIONS_H__
#define __OMX_QCOM_EXTENSIONS_H__

/*============================================================================
*//** @file OMX_QCOMExtns.h
  This header contains constants and type definitions that specify the
  extensions added to the OpenMAX Vendor specific APIs.

*//*========================================================================*/


//////////////////////////////////////////////////////////////////////////////
//                             Include Files
//////////////////////////////////////////////////////////////////////////////
#include "OMX_Core.h"
#include "OMX_Video.h"

/**
 * This extension is used to register mapping of a virtual
 * address to a physical address. This extension is a parameter
 * which can be set using the OMX_SetParameter macro. The data
 * pointer corresponding to this extension is
 * OMX_QCOM_MemMapEntry. This parameter is a 'write only'
 * parameter (Current value cannot be queried using
 * OMX_GetParameter macro).
 */
#define OMX_QCOM_EXTN_REGISTER_MMAP     "OMX.QCOM.index.param.register_mmap"

/**
 * This structure describes the data pointer corresponding to
 * the OMX_QCOM_MMAP_REGISTER_EXTN extension. This parameter
 * must be set only 'after' populating a port with a buffer
 * using OMX_UseBuffer, wherein the data pointer of the buffer
 * corresponds to the virtual address as specified in this
 * structure.
 */
struct OMX_QCOM_PARAM_MEMMAPENTRYTYPE
{
    OMX_U32 nSize;              /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /**< OMX specification version information */
    OMX_U32 nPortIndex;         /**< Port number the structure applies to */

    /**
     * The virtual address of memory block
     */
    OMX_U64 nVirtualAddress;

    /**
     * The physical address corresponding to the virtual address. The physical
     * address is contiguous for the entire valid range of the virtual
     * address.
     */
    OMX_U64 nPhysicalAddress;
};

#define OMX_QCOM_PORTDEFN_EXTN   "OMX.QCOM.index.param.portdefn"
/* Allowed APIs on the above Index: OMX_GetParameter() and OMX_SetParameter() */

typedef enum OMX_QCOMMemoryRegion
{
    OMX_QCOM_MemRegionInvalid,
    OMX_QCOM_MemRegionEBI1,
    OMX_QCOM_MemRegionSMI,
    OMX_QCOM_MemRegionMax = 0X7FFFFFFF
} OMX_QCOMMemoryRegion;

typedef enum OMX_QCOMCacheAttr
{
    OMX_QCOM_CacheAttrNone,
    OMX_QCOM_CacheAttrWriteBack,
    OMX_QCOM_CacheAttrWriteThrough,
    OMX_QCOM_CacheAttrMAX = 0X7FFFFFFF
} OMX_QCOMCacheAttr;

typedef struct OMX_QCOMRectangle
{
   OMX_S32 x;
   OMX_S32 y;
   OMX_S32 dx;
   OMX_S32 dy;
} OMX_QCOMRectangle;

/** OMX_QCOMFramePackingFormat
  * Input or output buffer format
  */
typedef enum OMX_QCOMFramePackingFormat
{
  /* 0 - unspecified
   */
  OMX_QCOM_FramePacking_Unspecified,

  /*  1 - Partial frames may be present OMX IL 1.1.1 Figure 2-10:
   *  Case 1??Each Buffer Filled In Whole or In Part
   */
  OMX_QCOM_FramePacking_Arbitrary,

  /*  2 - Multiple complete frames per buffer (integer number)
   *  OMX IL 1.1.1 Figure 2-11: Case 2—Each Buffer Filled with
   *  Only Complete Frames of Data
   */
  OMX_QCOM_FramePacking_CompleteFrames,

  /*  3 - Only one complete frame per buffer, no partial frame
   *  OMX IL 1.1.1 Figure 2-12: Case 3—Each Buffer Filled with
   *  Only One Frame of Compressed Data. Usually at least one
   *  complete unit of data will be delivered in a buffer for
   *  uncompressed data formats.
   */
  OMX_QCOM_FramePacking_OnlyOneCompleteFrame,

  /*  4 - Only one complete subframe per buffer, no partial subframe
   *  Example: In H264, one complete NAL per buffer, where one frame
   *  can contatin multiple NAL
   */
  OMX_QCOM_FramePacking_OnlyOneCompleteSubFrame,

  OMX_QCOM_FramePacking_MAX = 0X7FFFFFFF
} OMX_QCOMFramePackingFormat;

typedef struct OMX_QCOM_PARAM_PORTDEFINITIONTYPE {
 OMX_U32 nSize;           /** Size of the structure in bytes */
 OMX_VERSIONTYPE nVersion;/** OMX specification version information */
 OMX_U32 nPortIndex;    /** Portindex which is extended by this structure */

 /** Platform specific memory region EBI1, SMI, etc.,*/
 OMX_QCOMMemoryRegion nMemRegion;

 OMX_QCOMCacheAttr nCacheAttr; /** Cache attributes */

 /** Input or output buffer format */
 OMX_U32 nFramePackingFormat;

} OMX_QCOM_PARAM_PORTDEFINITIONTYPE;

#define OMX_QCOM_PLATFORMPVT_EXTN   "OMX.QCOM.index.param.platformprivate"
/** Allowed APIs on the above Index: OMX_SetParameter() */

typedef enum OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE
{
    /** Enum for PMEM information */
    OMX_QCOM_PLATFORM_PRIVATE_PMEM = 0x1
} OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE;

/** IL client will set the following structure. A failure
 *  code will be returned if component does not support the
 *  value provided for 'type'.
 */
struct OMX_QCOM_PLATFORMPRIVATE_EXTN
{
    OMX_U32 nSize;        /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /** OMX spec version information */
    OMX_U32 nPortIndex;  /** Port number on which usebuffer extn is applied */

    /** Type of extensions should match an entry from
     OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE
    */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE type;
};

typedef struct OMX_QCOM_PLATFORM_PRIVATE_PMEM_INFO
{
    /** pmem file descriptor */
    OMX_U32 pmem_fd;
    /** Offset from pmem device base address */
    OMX_U32 offset;
}OMX_QCOM_PLATFORM_PRIVATE_PMEM_INFO;

typedef struct OMX_QCOM_PLATFORM_PRIVATE_ENTRY
{
    /** Entry type */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE type;

    /** Pointer to platform specific entry */
    void* entry;
}OMX_QCOM_PLATFORM_PRIVATE_ENTRY;

typedef struct OMX_QCOM_PLATFORM_PRIVATE_LIST
{
    /** Number of entries */
    OMX_U32 nEntries;

    /** Pointer to array of platform specific entries *
     * Contiguous block of OMX_QCOM_PLATFORM_PRIVATE_ENTRY element
    */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY* entryList;
}OMX_QCOM_PLATFORM_PRIVATE_LIST;

#define OMX_QCOM_FRAME_PACKING_FORMAT   "OMX.QCOM.index.param.framepackfmt"
/* Allowed API call: OMX_GetParameter() */
/* IL client can use this index to rerieve the list of frame formats *
 * supported by the component */

typedef struct OMX_QCOM_FRAME_PACKINGFORMAT_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nIndex;
    OMX_QCOMFramePackingFormat eframePackingFormat;
} OMX_QCOM_FRAME_PACKINGFORMAT_TYPE;


/**
 * Following is the enum for color formats supported on Qualcomm
 * MSMs YVU420SemiPlanar color format is not defined in OpenMAX
 * 1.1.1 and prior versions of OpenMAX specification.
 */

enum OMX_QCOM_COLOR_FORMATTYPE
{

/** YVU420SemiPlanar: YVU planar format, organized with a first
 *  plane containing Y pixels, and a second plane containing
 *  interleaved V and U pixels. V and U pixels are sub-sampled
 *  by a factor of two both horizontally and vertically.
 */
    OMX_QCOM_COLOR_FormatYVU420SemiPlanar = 0x7FA30C00
};

enum OMX_QCOM_VIDEO_CODINGTYPE
{
/** Codecs support by qualcomm which are not listed in OMX 1.1.x
 *  spec
 *   */
    OMX_QCOM_VIDEO_CodingVC1  = 0x7FA30C00 ,
    OMX_QCOM_VIDEO_CodingWMV9 = 0x7FA30C01
};

enum OMX_QCOM_EXTN_INDEXTYPE
{
    /** Qcom proprietary extension index list */

    /* "OMX.QCOM.index.param.register_mmap" */
    OMX_QcomIndexRegmmap = 0x7F000000,

    /* "OMX.QCOM.index.param.platformprivate" */
    OMX_QcomIndexPlatformPvt = 0x7F000001,

    /* "OMX.QCOM.index.param.portdefn" */
    OMX_QcomIndexPortDefn = 0x7F000002,

    /* "OMX.QCOM.index.param.framepackingformat" */
    OMX_QcomIndexPortFramePackFmt = 0x7F000003,

    /*"OMX.QCOM.index.param.Interlaced */
    OMX_QcomIndexParamInterlaced = 0x7F000004,

    /*"OMX.QCOM.index.config.interlaceformat */
    OMX_QcomIndexConfigInterlaced = 0x7F000005,

   /* "OMX.QCOM.index.param.syntaxhdr" */
    OMX_QcomIndexParamVideoSyntaxHdr = 0x7F000006,

    /* "OMX.QCOM.index.config.intraperiod" */
    OMX_QcomIndexConfigVideoIntraperiod = 0x7F000007,

    /*"OMX.QCOM.index.config.ulbufferOccupancy" */
    OMX_QcomIndexConfigVideoUlbufferOccupancy = 0x7F000008,

    /* "OMX.QCOM.index.config.randomIntrarefresh" */
    OMX_QcomIndexConfigVideoRandomIntrarefresh = 0x7F000009,

	/* "OMX.QCOM.index.config.QPRange" */
    OMX_QcomIndexConfigVideoQPRange = 0x7F00000A
};

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_PARAM_SYNTAXHDRTYPE extension. This parameter can be queried
 * during the loaded state.
 */
typedef struct OMX_QCOM_VIDEO_PARAM_SYNTAXHDRTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;    /** Portindex which is extended by this structure */

   OMX_U8* pBuff;         /** Buffer to store the header information */
   OMX_U32 nBuffLen;      /** The buffer length in bytes */
   OMX_U32 nFilledLen;    /** The number of bytes filled in to the buffer */
} OMX_QCOM_VIDEO_PARAM_SYNTAXHDRTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_INTRAPERIODTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid.  This is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_INTRAPERIODTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nPFrames;        /** The number of "p" frames between two "I" frames */
} OMX_QCOM_VIDEO_CONFIG_INTRAPERIODTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is used for the buffer negotiation
 * with other clients.  This is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE
{
   OMX_U32 nSize;            /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion; /** OMX specification version information */
   OMX_U32 nPortIndex;       /** Portindex which is extended by this structure */
   OMX_U32 nBufferOccupancy; /** The number of bytes to be set for the buffer occupancy */
} OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is primarily used for the dynamic/random
 * intrarefresh.  This is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nRirMBs;         /** The number of MBs to be set for intrarefresh */
} OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE;


/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_QPRANGE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is primarily
 * used for the min/max QP to be set from the application.  This
 * is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_QPRANGE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nMinQP;          /** The number for minimum quantization parameter */
   OMX_U32 nMaxQP;          /** The number for maximum quantization parameter */
} OMX_QCOM_VIDEO_CONFIG_QPRANGE;


typedef struct OMX_VENDOR_EXTRADATATYPE  {
    OMX_U32 nPortIndex;
    OMX_U32 nDataSize;
    OMX_U8  *pData;     // cdata (codec_data/extradata)
} OMX_VENDOR_EXTRADATATYPE;

typedef enum OMX_INDEXVENDORTYPE {
    OMX_IndexVendorFileReadInputFilename = 0xFF000001,
    OMX_IndexVendorParser3gpInputFilename = 0xFF000002,
    OMX_IndexVendorVideoExtraData = 0xFF000003,
    OMX_IndexVendorAudioExtraData = 0xFF000004
} OMX_INDEXVENDORTYPE;

typedef enum OMX_QCOM_VC1RESOLUTIONTYPE
{
   OMX_QCOM_VC1_PICTURE_RES_1x1,
   OMX_QCOM_VC1_PICTURE_RES_2x1,
   OMX_QCOM_VC1_PICTURE_RES_1x2,
   OMX_QCOM_VC1_PICTURE_RES_2x2
} OMX_QCOM_VC1RESOLUTIONTYPE;

typedef enum OMX_QCOM_INTERLACETYPE
{
    OMX_QCOM_InterlaceFrameProgressive,
    OMX_QCOM_InterlaceInterleaveFrameTopFieldFirst,
    OMX_QCOM_InterlaceInterleaveFrameBottomFieldFirst,
    OMX_QCOM_InterlaceFrameTopFieldFirst,
    OMX_QCOM_InterlaceFrameBottomFieldFirst,
    OMX_QCOM_InterlaceFieldTop,
    OMX_QCOM_InterlaceFieldBottom
}OMX_QCOM_INTERLACETYPE;

typedef struct OMX_QCOM_PARAM_VIDEO_INTERLACETYPE
{
    OMX_U32 nSize;           /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;/** OMX specification version information */
    OMX_U32 nPortIndex;    /** Portindex which is extended by this structure */
    OMX_BOOL bInterlace;  /** Interlace content **/
};

typedef struct OMX_QCOM_CONFIG_INTERLACETYPE
{
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nIndex;
    OMX_QCOM_INTERLACETYPE eInterlaceType;
}OMX_QCOM_CONFIG_INTERLACETYPE;

#define MAX_PAN_SCAN_WINDOWS 4

typedef struct OMX_QCOM_PANSCAN
{
   OMX_U32 numWindows;
   OMX_QCOMRectangle window[MAX_PAN_SCAN_WINDOWS];
} OMX_QCOM_PANSCAN;

typedef struct OMX_QCOM_EXTRADATA_FRAMEINFO
{
   // common frame meta data. interlace related info removed
   OMX_VIDEO_PICTURETYPE  ePicType;
   OMX_QCOM_INTERLACETYPE interlaceType;
   OMX_QCOM_PANSCAN       panScan;
   OMX_U32                nConcealedMacroblocks;
} OMX_QCOM_EXTRADATA_FRAMEINFO;

typedef struct OMX_QCOM_H264EXTRADATA
{
   OMX_U64 seiTimeStamp;
} OMX_QCOM_H264EXTRADATA;

typedef struct OMX_QCOM_VC1EXTRADATA
{
   OMX_U32                     nVC1RangeY;
   OMX_U32                     nVC1RangeUV;
   OMX_QCOM_VC1RESOLUTIONTYPE eVC1PicResolution;
} OMX_QCOM_VC1EXTRADATA;

typedef union OMX_QCOM_EXTRADATA_CODEC_DATA
{
   OMX_QCOM_H264EXTRADATA h264ExtraData;
   OMX_QCOM_VC1EXTRADATA vc1ExtraData;
} OMX_QCOM_EXTRADATA_CODEC_DATA;

typedef enum OMX_QCOM_EXTRADATATYPE
{
   OMX_ExtraDataFrameInfo = 0x7F000001,
   OMX_ExtraDataH264 = 0x7F000002,
   OMX_ExtraDataVC1 = 0x7F000003,
} OMX_QCOM_EXTRADATATYPE;


#define OMX_EXTRADATA_HEADER_SIZE 20

#endif /* __OMX_QCOM_EXTENSIONS_H__ */
