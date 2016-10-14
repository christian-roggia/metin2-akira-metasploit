import akira
import const
import socket
import time
import config
import encryption
import phase

def Handshake(data):
	if phase.GLOBAL_PHASE_ARRAY[phase.CURRENT_PHASE] != 'HANDSHAKE':
		print('[+] Handshake received while phase %s: %d set' % (phase.GLOBAL_PHASE_ARRAY[phase.CURRENT_PHASE], phase.CURRENT_PHASE))
		const.CLOSE_CONNECTION = True
	
	handshake, server_time, delta = akira.GetHandshake(data)
	const.LAST_PACKET_LENGTH = 13
	
	print('[+] Handshake received (handshake %d server_time %d delta %d)' % (handshake, server_time, delta))
	const.SOCKET.send(akira.Handshake(handshake, server_time+120, delta))
	
	if const.SERVER_TIME == -1:
		const.SERVER_TIME = server_time
		time.clock()

def ChangePhase(data):
	phase.CURRENT_PHASE = akira.GetPhase(data)
	const.LAST_PACKET_LENGTH = 2
	
	print('[+] Current phase changed (phase %s: %d)' % (phase.GLOBAL_PHASE_ARRAY[phase.CURRENT_PHASE], phase.CURRENT_PHASE))
	
	if phase.CURRENT_PHASE > phase.MAX_PHASE:
		print('[-] Phase is out of range (%d)' % phase.CURRENT_PHASE)
		return
	
	if phase.GLOBAL_PHASE_ARRAY[phase.CURRENT_PHASE] == 'AUTH':
		encryption.USE_XTEA_ENCRYPTION = True
		encryption.XTEA_KEY_TYPE = encryption.XTEA_KEY_PONG
		
		const.SOCKET.send(akira.Authenticate(config.USERNAME, config.PASSWORD))
		print('[+] Sent authentication %s:%s' % (config.USERNAME, config.PASSWORD))
		
	elif phase.GLOBAL_PHASE_ARRAY[phase.CURRENT_PHASE] == 'LOGIN':
		encryption.USE_XTEA_ENCRYPTION = True
		encryption.XTEA_KEY_TYPE = encryption.XTEA_KEY_LOGIN
		
		const.SOCKET.send(akira.Login(config.USERNAME, encryption.LOGIN_KEY))
		print('[+] Sent login %s:%s' % (config.USERNAME, encryption.LOGIN_KEY))

def AuthFailure(data):
	error = akira.GetAuthFailure(data)
	const.LAST_PACKET_LENGTH = len(error) + 1
	
	print('[-] Authentication failed (error %s)' % error)
	const.CLOSE_CONNECTION = True

def AuthSuccess(data):
	encryption.LOGIN_KEY, result = akira.GetAuthSuccess(data)
	const.LAST_PACKET_LENGTH = 9
	
	print('[+] Client is authenticated (result %d key %d)' % (result, encryption.LOGIN_KEY))
	
	# Reset connection
	phase.CURRENT_PHASE = phase.INVALID_PHASE
	
	encryption.USE_XTEA_ENCRYPTION	= False
	encryption.XTEA_KEY_TYPE		= encryption.XTEA_KEY_INVALID
	
	const.CLOSE_CONNECTION		= False
	const.LAST_PACKET_LENGTH	= 0
	
	akira.ResetSequence()
	
	const.SOCKET.close()
	print("[-] Connection closed")
	
	const.SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	const.SOCKET.connect((config.IP, config.GAME_PORT))
	print("[+] Connection opened with %s:%d" % (config.IP, config.GAME_PORT))

def LoginSucces(data):
	const.LAST_PACKET_LENGTH = 1
	
	print('[+] Client is logged in')

def UnkPacket(data):
	print('[+] Unk packet')
	
	const.LAST_PACKET_LENGTH = len(data)
	#const.SOCKET.send(akira.CreateCharacter("nevritza", 0, 1, 1))
	#CrationSuccess(data) # Skip
	const.SOCKET.send(akira.SelectCharacter(0))

def CrationSuccess(data):
	print('[+] Unk packet 2')
	
	#const.LAST_PACKET_LENGTH = 8
	#const.SOCKET.send(akira.SelectEmpire(1))
	#const.SOCKET.send(akira.SelectCharacter(1))

def EnteringGame(data):
	const.LAST_PACKET_LENGTH = len(data)
	
	const.SOCKET.send(akira.Version(config.VERSION_EXE, config.VERSION_NR))
	print('[+] Sent client version (%s: %s)' % (config.VERSION_EXE, config.VERSION_NR))
	
	const.X, const.Y = akira.GetXY(data)
	print('[+] Received enter game at %d:%d' % (const.X, const.Y))
	
	const.SOCKET.send(akira.EnterGame())
	print('[+] Sent enter game')
	
	const.SOCKET.send(akira.QuestInputString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"))
	print('[+] Sent QuestInputString (%s)' % ("AAAAAAAAAAAAAAA..."))
	

def UnkPacket2(data):
	#const.X += 2
	#const.SOCKET.send(akira.Move(1, 0, 0, const.X, const.Y, const.SERVER_TIME + 5000)) #  + (time.clock() * 1000)
	#print('[+] Moved to %d:%d' % (const.X, const.Y))
	
	const.SOCKET.send(akira.QuestInputString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"))
	print('[+] Sent QuestInputString (%s)' % ("AAAAAAAAAAAAAAA..."))
	