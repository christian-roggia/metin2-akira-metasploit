#ifndef EXPLOIT_H
#define EXPLOIT_H

#include <memory.h>
#include <string.h>
#include "tea.h"
#include "sequence.h"

#define _CRT_SECURE_NO_WARNINGS 1

extern unsigned int s_encrypt_key[4];
extern unsigned int s_decrypt_key[4];
extern unsigned int s_pong_key[4];

extern unsigned char g_buffer[2048];

int MCP_HandShake(unsigned int nHandshake, unsigned int nTime, unsigned int nDelta);
int MCP_Auth(char *szUsername, char *szPassword);
int MCP_Login(char *szUsername, unsigned int nKey);
int MCP_EnterGame(void);
int MCP_SelectCharacter(unsigned char nIndex);
int MCP_ItemDrop(unsigned int nYang, unsigned char nSlot);
int MCP_Move(unsigned char nMoveType, unsigned char nUnk, unsigned char nRotation, unsigned int nX, unsigned int nY, unsigned int nClientTime);
int MCP_ItemDrop2(unsigned int nYang, unsigned char nSlot, unsigned char nAmount);
int MCP_ScriptAnswer(unsigned char nAnswer);
int MCP_ScriptSelectItem(unsigned int nItem);
int MCP_Target(unsigned int nTarget);
int MCP_PasspodAnswer(char *szAnswer);
int MCP_Pong(void);
int MCP_Version(char *szLauncherName, char *szVersion);
int MCP_Chat(char *szMessage);
int MCP_HackDetect(char *szHackDetected);
int MCP_QuestInputString(char *szString);
int MCP_Shop(unsigned char nType, unsigned char nSlot);
int MCP_Guild(unsigned char nType, int nUnk);
int MCP_Empire(unsigned char nEmpire);
int MCP_NewCharacter(char *szName, unsigned char nPos, unsigned char nJob, unsigned char nShape);
int MCP_MarkCRCList(void);
int MCP_MarkLogin(void);
int MCP_MarkIdxList(void);
int MCP_ChangeName(unsigned char nIndex, char *szName);

void MCP_SetPongKey(unsigned int *vKey);
void MCP_SetEncryptKey(unsigned int *vKey);
void MCP_SetDecryptKey(unsigned int *vKey);

#endif // EXPLOIT_H
