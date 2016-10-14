import sys
import akira
import const
import socket
import packet
import encryption
import config
import phase
import dump

LIST_INCOMING_PACKET = {
	b'\xff': packet.Handshake,
	b'\xfd': packet.ChangePhase,
	b'\x96': packet.AuthSuccess,
	b'\x07': packet.AuthFailure,
	b'\x5a': packet.LoginSucces,
	b'\xf2': packet.UnkPacket,
	b'\x09': packet.CrationSuccess,
	b'\x11': packet.EnteringGame,
	b'\x03': packet.UnkPacket2,
}

def HandlePacket(data):
	# If packet is encrypted, decrypt it only once
	if encryption.USE_XTEA_ENCRYPTION == True:
		data = akira.XTEA_Decrypt(data, encryption.XTEA_KEY_TYPE)
	
	while 1:
		# Close the connection if requested
		if const.CLOSE_CONNECTION == True:
			print("[-] HandlePacket: Connection closed")
			FinalizeAkira()
			break
		
		# Increment packet number
		const.PACKET_NR += 1
		
		# Clean the LAST_PACKET_LENGTH before processing the data
		const.LAST_PACKET_LENGTH = 0
		
		# Process the data
		for p in LIST_INCOMING_PACKET:
			if p[0] == data[0]:
				LIST_INCOMING_PACKET[p](data)
		
		# If no data has been process, dump it
		if const.LAST_PACKET_LENGTH == 0:
			dump.DumpPacketData(data)
		
		# If encryption is enabled align the packed length (8 bytes alignment)
		if encryption.USE_XTEA_ENCRYPTION == True:
			const.LAST_PACKET_LENGTH = (const.LAST_PACKET_LENGTH - (const.LAST_PACKET_LENGTH % 8)) + 8
		
		# If all the data has been processed exit the loop, otherwise process the next data
		if len(data) <= const.LAST_PACKET_LENGTH:
			break
		else:
			data = data[const.LAST_PACKET_LENGTH:]

def MainLoop():
	print("[+] Entering main loop...")
	while 1:
		if const.SOCKET == None or const.CLOSE_CONNECTION == True:
			print("[-] MainLoop: Connection closed")
			FinalizeAkira()
			break
		
		try:
			data = const.SOCKET.recv(8192)
			
			if data == b'':
				print("[-] MainLoop: Connection closed (data is NULL)")
				FinalizeAkira()
				break
			
			#print(data)
			
			HandlePacket(data)
		except:
			print("[-] MainLoop: Connection closed (exception: %s)" % sys.exc_info()[0])
			FinalizeAkira()
			break

def InitializeAkira():
	CleanAkira()
	
	if config.PONG != None:
		akira.SetPong(config.PONG[0], config.PONG[1], config.PONG[2], config.PONG[3])
	
	try:
		const.SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		const.SOCKET.connect((config.IP, config.LOGIN_PORT))
		
		print("[+] Connection opened with %s:%d" % (config.IP, config.LOGIN_PORT))
		MainLoop()
	except:
		print("[-] Impossible to connect to %s:%d" % (config.IP, config.LOGIN_PORT))

def CleanAkira():
	phase.CURRENT_PHASE = phase.INVALID_PHASE
	
	encryption.USE_XTEA_ENCRYPTION	= False
	encryption.XTEA_KEY_TYPE		= encryption.XTEA_KEY_INVALID
	encryption.LOGIN_KEY			= 0
	
	const.CLOSE_CONNECTION		= False
	const.LAST_PACKET_LENGTH	= 0
	const.PACKET_NR				= 0
	
	akira.ResetSequence()

def	FinalizeAkira():
	try:
		if const.SOCKET != None:
			const.SOCKET.close()
	except:
		pass
	
	CleanAkira()
	print("[-] Connection closed")

if __name__ == '__main__':
	InitializeAkira()
