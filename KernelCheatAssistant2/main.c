#include "kca.h"


/// <summary>
/// ������� ע������
/// </summary>
/// <param name="DriverObject">��������</param>
/// <param name="RegistryPath">ע��·��y</param>
/// <returns>NTSTATUS</returns>
NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT DriverObject, 
	IN PUNICODE_STRING RegistryPath
)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS Status = STATUS_SUCCESS;



	return Status;
}