"""
Module dedicated to the communication encryption between the client and the server.
"""

# The 32bit login key, generated and sent by the server
LOGIN_KEY = 0

# Initial communication (handshake) is plain (no encryption)
USE_XTEA_ENCRYPTION = False

# The different type of keys
XTEA_KEY_INVALID	= -1 # Invalid key, 
XTEA_KEY_PONG		= 0  # Pong key, which changes at any connection (or should)
XTEA_KEY_LOGIN		= 1  # Login key, always the same (static)

# Invalid key set as default since the connection should not be encrypted
XTEA_KEY_TYPE		= XTEA_KEY_INVALID