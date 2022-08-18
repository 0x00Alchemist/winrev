NTSTATUS __fastcall UefiOpenRegistryKey(
        void *DirHandle,
        struct _UNICODE_STRING *UefiObjectName,
        __int64 a3,
        void **KeyHandle)
{
  _OBJECT_ATTRIBUTES UefiKeyObjectAttributes;

  *(&UefiKeyObjectAttributes.Length + 1) = 0;
  memset(&UefiKeyObjectAttributes.Attributes + 1, 0, 20);
  UefiKeyObjectAttributes.RootDirectory = DirHandle;
  UefiKeyObjectAttributes.ObjectName = UefiObjectName;
  UefiKeyObjectAttributes.Length = 48;
  UefiKeyObjectAttributes.Attributes = 576;
  
  return ZwOpenKey(KeyHandle, 0x20019u, &UefiKeyObjectAttributes);
}