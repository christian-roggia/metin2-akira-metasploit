def DumpPacketData(data):
	print('[!] An unknown packet has been received:')
	print('[!]    Length     : ', len(data))
	print('[!]    Header     : ', data[0])
	print('[!]    Packet Nr. : ', PACKET_NR)
	
	pf = open("dump_%d (%d)" % (PACKET_NR, data[0]), "wb")
	pf.write(data)
	pf.close()