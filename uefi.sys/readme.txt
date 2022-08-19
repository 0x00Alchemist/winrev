Fully decompiled and slightly cleaned up functions from uefi.sys windows driver.

Structure:
uefi.sys <- we here!
		Dispatchers
			- UefiDispatchForwardIrp.c
			- UefiDispatchPnp.c
			- UefiDispatchPower.c
			- UefiDispatchWmi.c
		Uefi Esrt Functions
			- UefiEsrtGetDriverCatalogName.c
			- UefiEsrtGetFirmwareVersionString.c
			- UefiEsrtInitialize.c
			- UefiEsrtOpenFirmwareResourcesKey.c
			- UefiEsrtQueryFirmwareResources.c
			- UefiEsrtQueryId.c
			- UefiEsrtRetryFirmwareUpdate.c
			- UefiEsrtStartDevice.c
			- UefiEsrtTraceLog.c
		Uefi Registry Functions
			- UefiCreateRegistryKey.c
			- UefiOpenDeviceClassRegistryKey.c
			- UefiOpenRegistryKey.c
			- UefiQueryRegistryValue.c
	DriverEntry.c
	UefiAddDevice.c
	UefiDriverUnload.c
	UefiQueryDeviceRelations.c
	UefiStartDevice.c
	UefiTraceInitialize.c
	readme.txt
uefi.sys end

I have not added Guard functions, Rtl-functions and a few more functions from the CRT, I hope it is obvious why.
