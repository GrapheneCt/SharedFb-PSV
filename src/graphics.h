#define DISPLAY_WIDTH				960
#define DISPLAY_HEIGHT				544
#define DISPLAY_STRIDE_IN_PIXELS	960
#define MAX_PENDING_SWAPS			1

typedef struct SceSharedFbInfo { // size is 0x58
	void* base1;		// cdram base
	int memsize;
	void* base2;		// cdram base
	int unk_0C;
	void *unk_10;
	int unk_14;
	int unk_18;
	int unk_1C;
	int unk_20;
	int unk_24;		// 960
	int unk_28;		// 960
	int unk_2C;		// 544
	int unk_30;
	int curbuf;
	int unk_38;
	int unk_3C;
	int unk_40;
	int unk_44;
	int vsync;
	int unk_4C;
	int unk_50;
	int unk_54;
} SceSharedFbInfo;

//sceGxmInitializeInternalForVsh
extern int SceGxmInternalForVsh_A04F5FAC(const SceGxmInitializeParams *);

//Init GXM, SharedFb
int initGraphics( void );

//Draw display
int drawDisplay();

//Draw object
void drawObject(void *address, const int x, const int y, const int halfSize, const int color);

//SharedFb
SceUID _sceSharedFbOpen(int a1, int sysver);
int sceSharedFbClose(SceUID shared_fb_id);
int sceSharedFbBegin(SceUID shared_fb_id, SceSharedFbInfo *info);
int sceSharedFbEnd(SceUID shared_fb_id);
int sceSharedFbGetInfo(SceUID shared_fb_id, SceSharedFbInfo *info);
