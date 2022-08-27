Cleaned up ntosext.sys driver.
This driver is responsible for updating vendor (Intel, AMD) processor microcode, it detects which CPU you have and then loads the required dynamic library (mcupdate_GenuineIntel.dll or mcupdate_AuthenticAMD.dll) for further work. 
This driver is unloaded to the OS at the "early-boot" stage (after winload.efi)

Structure:
ntosext.sys <- we here!
		+ Locks
			- ExpAcquireMicrocodeUpdateLock.c
			- ExpInitializeMicrocodeUpdateLock.c
			- ExpReleaceMicrocodeUpdateLock.c
		+ Microcode update control facilities
			- ExpGetMicrocodeImageFileName.c
			- ExpLoadMicrocodeImage.c
			- ExpMicrocodeInformationLoad.c
			- ExpMicrocodeInformationUnload.c
			- ExpMicrocodeInitialization.c
			- ExpUnloadMicrocodeImage.c
	- DllUnload.c
	- DriverEntry.c
	- ExpMicrocodePowerStateCallback.c
	- ExpWorkMicrocode.c
	- readme.txt
