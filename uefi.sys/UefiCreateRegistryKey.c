NTSTATUS __fastcall UefiCreateRegistryKey(
        void *DirHandle,
        struct _UNICODE_STRING *UefiObjectName,
        __int64 a3,
        __int64 a4,
        ULONG *Disposition,
        PHANDLE KeyHandle)
{
  struct _OBJECT_ATTRIBUTES UefiKeyObjectAttributes; 

  UefiKeyObjectAttributes.RootDirectory = DirHandle;
  UefiKeyObjectAttributes.ObjectName = UefiObjectName;
  *&UefiKeyObjectAttributes.Length = 48i64;
  *&UefiKeyObjectAttributes.Attributes = 576i64;
  *&UefiKeyObjectAttributes.SecurityDescriptor = 0i64;
  
  return ZwCreateKey(KeyHandle, 0xF003Fu, &UefiKeyObjectAttributes, 0, 0i64, 0, Disposition);
}