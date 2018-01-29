#define WTOBJECT 0x00000002 //Always true for anything that can call this method
#define WTCONTAINER 0x00000004 //Set for anything that can be directly positioned: WTActor, WTCamera, WTContainer, WTGroup, WTLight, WTAudioClip3D
#define WT_2D 0x00000008 //Set for strictly two-D rendered objects: WTDrop
#define WT_3D 0x00000010 //Set for most three-D rendered objects: WTActor, WTCamera, WTGroup, WTAudioClip3D, WTLight but not WTModel
#define WTGROUP 0x00000020 //Set for WTGroup, WTAudioClip3D and WTActor (since WTAudioClip3D and WTActor both act like a group)
#define WTCAMERA 0x00000040 //Set for WTCamera
#define WTLIGHT 0x00000080 //Set for WTLight
#define WTBITMAP 0x00000100 //Set for WTBitmap
#define WTMODEL 0x00000200 //Set for WTModel but not for WTActor
#define WTSTAGE 0x00002000 //Set for WTStage
#define WTDROP 0x00004000 //Set for WTDrop
#define WTAUDIOCLIP 0x00008000 //Set for WTAudioClip
#define WTFILE 0x00020000 //Set for WTFile
#define WTACTOR 0x00040000 //Set for WTActor
#define WTAUDIOCLIP3D 0x00100000 //Set for WTAudioClip3D
#define WTSPOUT 0x00200000 //Set for WTSpout.  Must call DFV 3.0 to get the correct bit`s.
#define WTPORTAL 0x00400000 //Set for WTPortal
#define WTSTRING3D 0x00800000 //Set for WTString3D.  Must call DFV 3.0 to get the correct bit`s.
#define WTSHADOW 0x01000000 //Set for WTShadow
