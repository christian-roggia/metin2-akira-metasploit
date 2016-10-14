
#define MAX_PACKET_LENGTH		1024

#define OUT_AUTH_HEADER         (unsigned char)0x6F
#define OUT_LOGIN_HEADER        (unsigned char)0x6D

#define PHASE_LEN               2
#define HANDSHAKE_LEN           13

#define HEADER_HANDSHAKE        (unsigned char)0xFF
#define HEADER_PHASE            (unsigned char)0xFD
#define HEADER_AUTH_SUCCESS     (unsigned char)0x96
#define HEADER_AUTH_FAILURE     (unsigned char)0x07
#define HEADER_LOGIN_SUCCESS    (unsigned char)0x5A

#define HANDSHAKE_PHASE         1
#define LOGIN_PHASE             2
#define AUTH_PHASE              10

#define INIT_BUF(n)			int nb = 0; memset(g_buffer, 0, n);
#define SET_HEADER(h)		{ g_buffer[nb] = h; nb++; }
#define SET_BYTE(n)			{ g_buffer[nb] = n; nb++; }
#define SET_DWORD(n)		{ memcpy(&g_buffer[nb], &n, sizeof(unsigned int)); nb += sizeof(unsigned int); }
#define SET_KEY(k)			{ memcpy(&g_buffer[nb], k, 4 * sizeof(unsigned int)); nb += 4 * sizeof(unsigned int); }
#define SET_SEQ()			{ g_buffer[nb] = gc_abSequence[inc_seq_counter()]; nb++; }
#define SET_STRING(s, n)	{ strncpy((char *)&g_buffer[nb], s, n); nb += n; }
#define ENCRYPT_BUF(n, k)	{ TEA::Encrypt((char *)g_buffer, n, k); }

#define GET_XTEA_LENGTH(n)	(((n) - ((n) % 8)) + 8)