#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <process.h>
#include "../KernelCheatAssistan3/Packet.h"
#pragma comment(lib, "Ws2_32")


int main()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	SOCKADDR_IN address{ };

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(server_ip);
	address.sin_port = htons(server_port);

	SOCKET connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connection == INVALID_SOCKET)
		return INVALID_SOCKET;

	if (connect(connection, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		closesocket(connection);
		//return INVALID_SOCKET;
	}

	Packet packet{ };

	packet.header.verify_code = verify_code;
	packet.header.type = PacketType::packet_get_target_process_status;

	/*auto& data = packet.data.get_base_address;
	data.process_id = process_id;*/

	uint64_t result = 0;
	if (send(connection, (char *)&packet, sizeof(Packet), 0));
		//return result;
	NTSTATUS status;
	recv(connection, (char*)&status, sizeof(status), 0);

	recv(connection, (char *)&packet, sizeof(Packet), 0);

	//return 0;

	system("pause");
	return 0;
}

