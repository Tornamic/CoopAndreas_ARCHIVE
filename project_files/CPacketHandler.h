#pragma once
class CPacketHandler
{
public:
	static void PlayerConnected__Handle(void* data, int size);
	static void PlayerDisconnected__Handle(void* data, int size);
	static CPackets::PlayerOnFoot* PlayerOnFoot__Collect();
	static void PlayerOnFoot__Handle(void* data, int size);
};

