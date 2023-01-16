NTSTATUS BlImgLoadPEImageEx(
        ULONG64 BootDeviceId,
        INT MemoryType,
        PCWSTR PathStr,
        ULONG64 *BootImageBase,
        DWORD *BootImageSize,
        DWORD *UnknownBuffer,
        UINT *UnknownBufferSize,
        DWORD *a8,
        INT a9,
        INT a10,
        INT a11,
        UINT Unknown,
        UNICODE_STRING *a13,
        UNICODE_STRING *VendorMaybe)
{
  UINT Flags;
  NTSTATUS Status;
  
  INT nLength = 0;
  
  CHAR DevicePath[32];
  ZeroMemory(DevicePath, sizeof(DevicePath));
  
  if (BootImageBase && PathStr && ((Flags = Unknown, (Unknown & 4) == 0) || *BootImageBase && BootImageSize)) {
    Status = ImgpOpenFile(BootDeviceId, PathStr, 0, DevicePath);
    if (Status >= 0)
      Status = ImgpLoadPEImage(
                   DevicePath,
                   MemoryType,
                   BootImageBase,
                   BootImageSize,
                   UnknownBuffer,
                   UnknownBufferSize,
                   a8,
                   a9,
                   a10,
                   a11,
                   Flags,
                   &nLength,
                   VendorMaybe,
                   0i64,
                   0i64);
  } else {
    Status = STATUS_INVALID_PARAMETER;                     
  }
  
  if(a13)
    a13->Length = nLength;
	
  if((DevicePath[0] & 1) != 0)
    ImgpCloseFile(DevicePath);

  return Status;
}