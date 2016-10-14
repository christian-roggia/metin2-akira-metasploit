#include "Packet.h"
#include "Packet_MACRO.h"

unsigned int s_encrypt_key[4]	= {0x4B434148, 0x46204445, 0x4C20524F, 0x215A4C55};
unsigned int s_decrypt_key[4]	= {0x1B0B659D, 0x436CDA6C, 0x1DEAE8EB, 0xEAD25173};
unsigned int s_pong_key[4]		= {0x74736574, 0x74736574, 0x74736574, 0x74736574}; // testtesttesttest

unsigned char g_buffer[2048] = {};

int MCP_HandShake(unsigned int nHandshake, unsigned int nTime, unsigned int nDelta)
{
	unsigned int nDeltaTime = nTime + nDelta;

	INIT_BUF(13);

	SET_HEADER	(HEADER_HANDSHAKE);

	SET_DWORD	(nHandshake);
	SET_DWORD	(nTime);

	return 13;
}

int MCP_Auth(char *szUsername, char *szPassword)
{
	INIT_BUF(72);

	SET_HEADER	(OUT_AUTH_HEADER);

	SET_STRING	(szUsername, 31);
	SET_STRING	(szPassword, 17);
	SET_KEY		(s_encrypt_key);
	SET_SEQ		();

	ENCRYPT_BUF(72, s_pong_key);
	return 72;
}

int MCP_Login(char *szUsername, unsigned int nKey)
{
	INIT_BUF(56);
    
	SET_HEADER	(OUT_LOGIN_HEADER);
	SET_STRING	(szUsername, 31);
	SET_DWORD	(nKey);
	SET_KEY		(s_encrypt_key);
	SET_SEQ		();

    ENCRYPT_BUF(56, s_pong_key);
	return 56;
}

int MCP_EnterGame(void)
{
	INIT_BUF(8);
    
	SET_HEADER	(0x0A);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_SelectCharacter(unsigned char nIndex)
{
	INIT_BUF(8);

	SET_HEADER	(6);
	SET_BYTE	(nIndex);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_ItemDrop(unsigned int nYang, unsigned char nSlot)
{
	INIT_BUF(8);

	SET_HEADER	(12);
	SET_BYTE	(nSlot);
	SET_DWORD	(nYang);
	SET_SEQ		();

    ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_Move(unsigned char nMoveType, unsigned char nUnk, unsigned char nRotation, unsigned int nX, unsigned int nY, unsigned int nClientTime)
{
	INIT_BUF(24);

	SET_HEADER	(7);
	SET_BYTE	(nMoveType);
	SET_BYTE	(nUnk);
	SET_BYTE	(nRotation);
	SET_DWORD	(nX);
	SET_DWORD	(nY);
	SET_DWORD	(nClientTime);
	SET_SEQ		();

    ENCRYPT_BUF(24, s_encrypt_key);
	return 24;
}

int MCP_ItemDrop2(unsigned int nYang, unsigned char nSlot, unsigned char nAmount)
{
	INIT_BUF(8);

	SET_HEADER	(20);
	SET_BYTE	(nSlot);
	SET_BYTE	(nYang);
	SET_BYTE	(nAmount);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_ScriptAnswer(unsigned char nAnswer)
{
	INIT_BUF(8);

	SET_HEADER	(29);
	SET_BYTE	(nAnswer);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_ScriptSelectItem(unsigned int nItem)
{
	INIT_BUF(8);

	SET_HEADER	(114);
	SET_DWORD	(nItem);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_Target(unsigned int nTarget)
{
	INIT_BUF(8);

	SET_HEADER	(61);
	SET_DWORD	(nTarget);
	SET_SEQ		();

	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_PasspodAnswer(char *szAnswer)
{
	INIT_BUF(16);

	SET_HEADER	(202);
	SET_STRING	(szAnswer, 9);
	SET_SEQ		();

	ENCRYPT_BUF(16, s_pong_key);
	return 16;
}

int MCP_Pong(void)
{
	INIT_BUF(8);

	SET_HEADER	(254);
	SET_SEQ		();
	
	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_Version(char *szLauncherName, char *szVersion)
{
	INIT_BUF(72);
	
	SET_HEADER	(0xF1);
	SET_STRING	(szLauncherName, 33);
	SET_STRING	(szVersion, 32);
	SET_BYTE	(0x0A);
	SET_SEQ		();
	
	ENCRYPT_BUF(72, s_encrypt_key);
	return 72;
}

int MCP_Chat(char *szMessage)
{
	int nLen = GET_XTEA_LENGTH(strlen(szMessage) + 1 + 5);

	INIT_BUF(nLen);

	SET_HEADER	(3);
	SET_DWORD	(nLen);
	SET_STRING	(szMessage, strlen(szMessage));
	SET_SEQ		();
	
	ENCRYPT_BUF(nLen, s_encrypt_key);
	return nLen;
}

int MCP_HackDetect(char *szHackDetected)
{
	INIT_BUF(264);

	SET_HEADER	(0x69);
	SET_STRING	(szHackDetected, strlen(szHackDetected));
	SET_SEQ		();
	
	ENCRYPT_BUF(264, s_encrypt_key);
	return 264;
}

int MCP_QuestInputString(char *szString)
{
	INIT_BUF(72);

	SET_HEADER	(0x1E);
	SET_STRING	(szString, 65);
	SET_SEQ		();
	
	ENCRYPT_BUF(72, s_encrypt_key);
	return 72;
}

int MCP_Shop(unsigned char nType, unsigned char nSlot)
{
	INIT_BUF(8);

	SET_HEADER	(0x32);
	SET_BYTE	(nType);
	SET_BYTE	(nSlot);
	SET_SEQ		();
	
	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_Guild(unsigned char nType, int nUnk)
{
	INIT_BUF(16);

	SET_HEADER	(0x50);
	SET_BYTE	(nType);
	SET_DWORD	(nUnk);
	SET_SEQ		();
	
	ENCRYPT_BUF(16, s_encrypt_key);
	return 16;
}

int MCP_Empire(unsigned char nEmpire)
{
	INIT_BUF(8);
	
	SET_HEADER	(90);
	SET_BYTE	(nEmpire);
	SET_SEQ		();
	
	ENCRYPT_BUF(8, s_encrypt_key);
	return 8;
}

int MCP_NewCharacter(char *szName, unsigned char nPos, unsigned char nJob, unsigned char nShape)
{
	INIT_BUF(40);
	
	SET_HEADER	(4);
	SET_BYTE	(nPos);
	SET_STRING	(szName, 25);
	SET_BYTE	(nJob);
	SET_BYTE	(0);		// UNUSED
	SET_BYTE	(nShape);
	SET_BYTE	(0);		// UNUSED
	SET_BYTE	(0);		// UNUSED
	SET_BYTE	(0);		// UNUSED
	SET_BYTE	(0);		// UNUSED
	SET_SEQ		();
	
	ENCRYPT_BUF(40, s_encrypt_key);
	return 40;
}

int MCP_MarkCRCList(void)
{
	INIT_BUF(328);
	
	SET_HEADER	(101);
	
	ENCRYPT_BUF(328, s_pong_key);
	return 328;
}

int MCP_MarkLogin(void)
{
	INIT_BUF(9);

	SET_HEADER	(100);

    return 9;
}

int MCP_MarkIdxList(void)
{
	INIT_BUF(8);

	SET_HEADER	(104);
	
	ENCRYPT_BUF(8, s_pong_key);
	return 8;
}

int MCP_ChangeName(unsigned char nIndex, char *szName)
{
	INIT_BUF(32);

	SET_HEADER	(106);
	SET_BYTE	(nIndex);
	SET_STRING	(szName, 25);
	SET_SEQ		();

	ENCRYPT_BUF(32, s_encrypt_key);
	return 32;
}

void MCP_SetPongKey(unsigned int *vKey)
{
	memcpy(s_pong_key, vKey, sizeof(unsigned int) * 4);
}

void MCP_SetEncryptKey(unsigned int *vKey)
{
	memcpy(s_encrypt_key, vKey, sizeof(unsigned int) * 4);
}

void MCP_SetDecryptKey(unsigned int *vKey)
{
	memcpy(s_decrypt_key, vKey, sizeof(unsigned int) * 4);
}