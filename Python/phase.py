INVALID_PHASE	= -1
MAX_PHASE		= 10

GLOBAL_PHASE_ARRAY = {
	# ----------------------------------------------------------
	0: 'CLOSE',
	# ----------------------------------------------------------
	1: 'HANDSHAKE',
	# ----------------------------------------------------------
	2: 'LOGIN',
	3: 'LOGIN',		# Duplicate entry, not used by the server
	4: 'LOGIN',		# Duplicate entry, not used by the server
	# ----------------------------------------------------------
	5: 'MAIN',		# Duplicate entry, not used by the server
	6: 'MAIN',
	# ----------------------------------------------------------
	7: 'UNUSED',	# Not used by the server
	8: 'UNUSED',	# Not used by the server
	9: 'UNUSED',	# Not used by the server
	# ----------------------------------------------------------
	10: 'AUTH',
	# ----------------------------------------------------------
	INVALID_PHASE: 'INVALID'
	# ----------------------------------------------------------
}

CURRENT_PHASE 	= INVALID_PHASE
