import akira
import const

PASSPOD_ATTACK	= False
PASSODING		= False

PASSPOD_ANSWER	= "PASSPODA"

def AuthPhaseExploitHandle():
	if PASSPOD_ATTACK == True:
		PASSODING = True
		print('[+] Passpod attack enabled')

def AuthSuccessExploitHandle():
	if PASSODING == True and PASSPOD_ATTACK == True:
		const.SOCKET.send(akira.PasspodAnswer(PASSPOD_ANSWER))
		print('[+] Sent passpod answer')
