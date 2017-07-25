#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include "payload.h"
#include "hid.h"

#define PAYLOAD_MAX_SIZE 0x80000
#define BOOTONCE_PATH "/bootonce.firm"

off_t load_firm_to_buf(const char* path, void* buf) {
    FILE* fp = fopen(path, "rb");
    off_t fsize = 0;
    if (fp) {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        if (fsize && (fsize <= PAYLOAD_MAX_SIZE)) {
            fseek(fp, 0, SEEK_SET);
            fread(buf, 1, fsize, fp);
        } else fsize = 0;
        fclose(fp);
    }
    return fsize;
}

void copy_buf_to_path(const char* path, void* buf, off_t bsize) {
    FILE* fp = fopen(path, "wb");
    fseek(fp, 0, SEEK_SET);
    fwrite(buf, 1, bsize, fp);
    fclose(fp);
}

int main () {
    const char* payload_paths[] = { PAYLOAD_PATHS };
    u8* buf = (u8*) malloc(PAYLOAD_MAX_SIZE);
    off_t bsize = 0;
    
    // initialize services
	srvInit();
	aptInit();
    acInit();
    
    // try all provided paths
    for (u32 i = 0; i < (sizeof(payload_paths)/sizeof(const char*)); i++) {
        if ((bsize = load_firm_to_buf(payload_paths[i], buf))) {
            copy_buf_to_path(BOOTONCE_PATH, buf, bsize);
            break;
        }
    }
    
    // free buffer, reboot if applicable
    free(buf);
    if (bsize) APT_HardwareResetAsync(); // reboot
    else { // failed if we arrive here
        hidInit();
        gfxInitDefault();
        gfxSwapBuffers(); 
        gfxSet3D(false);
        consoleInit(GFX_TOP, NULL);
        
        // output error to console
        printf("[+] %s\n\n", PAYLOAD_NAME);
        printf("[-] %s payload not found in:\n", PAYLOAD_NAME);
        for (u32 i = 0; i < (sizeof(payload_paths)/sizeof(const char*)); i++)
            printf("[-] %s\n", payload_paths[i]);
        wait_any_key();
        
        gfxExit();
        hidExit();
    }
    
    // deinitialize services
    acExit();
    aptExit();
    srvExit();
    return 0;
}
