# SharedFb-PSV

This sample demonstrates how to use shared framebuffer and initialize GXM in PS Vita applications running in system mode.

If you have been using NoSharedFb plugin, unistall it before using this application.

It draws squares moving from top to bottom of the screen. Color of the squares will be green if GXM was initialized successfully and red if initialization failed.

# How to Build

Use vitasdk to build application. After building, boot params for executable must be set manually. Refer to the precompiled version for the values.

# Known Issues

Conflict with SceShell overlay
