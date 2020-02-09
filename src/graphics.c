#include <string.h>

#include <psp2/gxm.h> 
#include <psp2/appmgr.h>

#include "graphics.h"

static SceUID shfb_id;
static SceSharedFbInfo info;
static int oy = 0;
static int size = 0;
static int color = 0xff00ff00;

static void* bufferData[2];
static int bufferIndex = 0;

int initGraphics()
{
	//Initialize GXM
	SceGxmInitializeParams gxm_init_params_internal;
	memset(&gxm_init_params_internal, 0, sizeof(gxm_init_params_internal));
	gxm_init_params_internal.flags = 0x0A; //Flag to disable callback?
	gxm_init_params_internal.displayQueueMaxPendingCount = MAX_PENDING_SWAPS;
	//Since we use sharedfb, callback is not required
	gxm_init_params_internal.parameterBufferSize = 0x200000;

	int ret = SceGxmInternalForVsh_A04F5FAC(&gxm_init_params_internal);
	if (ret < 0)
		color = 0xff000ff0;

	//Wait for sharedfb to be ready
	while (1){
	shfb_id = _sceSharedFbOpen(1, 0x03600000);
	memset(&info, 0, sizeof(info));
	sceSharedFbGetInfo(shfb_id, &info);
	if (info.curbuf == 1)
		sceSharedFbClose(shfb_id);
	else
		break;
	}

	bufferData[0] = info.base1; //Additional cdram can be mapped using sceGxmMapMemory
	bufferData[1] = info.base2;

	return 0;
}

int drawDisplay()
{
	//Get buffer state
	memset(&info, 0, sizeof(info));
	sceSharedFbGetInfo(shfb_id, &info);

	if (info.curbuf == 1)
		bufferIndex = 0;
	else
		bufferIndex = 1;

	//Draw animation
	drawObject(bufferData[bufferIndex], 480, oy, size, color);
	if (oy < 400)
		oy = oy + 1;
	else
		oy = 0;
	if (size < 100)
		size = size + 1;
	else
		size = 0;

	//Set new buffer
	info.base2 = bufferData[bufferIndex];

	sceSharedFbBegin(shfb_id, &info);
	sceSharedFbEnd(shfb_id);

	return 0;
}

void drawObject(void *address, const int x, const int y, const int halfSize, const int color)
{
	int i = 0, j = 0;
	int *pixel;
	pixel = address;

	for (i = -halfSize; i < halfSize; i++) {
		for (j = -halfSize; j < halfSize; j++) {
			if (0 <= (x + i) && (x + i) < DISPLAY_STRIDE_IN_PIXELS && 0 <= (y + j) && (y + j) < DISPLAY_HEIGHT) {
				pixel[(x + i) + DISPLAY_STRIDE_IN_PIXELS * (y + j)] = color;
			}
		}
	}
}
