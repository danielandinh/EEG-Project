'''
	Created:    November 13, 2023
	Modified:   December 13, 2023
	Version:    1.0
	GitHub: https://github.com/danielandinh/EEG-Project
	
	Description:
	Implementation of analog data sampler.
	Recieves serial data from nano and saves it to text file;
	
	Modification History:
	- Version 1.0 (November 13, 2023): Initial commit
	- 
'''

import serial

def process_packet(packet: str) -> list[int]:
	"""
	Processes packet read from arduino

	:param packet: Packet of data with format = value, time.
	:type packet: str
	:return: 2 item list that containing [value, time].
	:rtype: List[int]
	"""
	packet = packet.decode()						# decode into utf-8
	packet = packet.strip()							# remove whitespace
	packet = packet.split(', ')						# split numbers into list
	data = [int(i) for i in packet if i.strip()]	# convert list items to integers
	
	return data

def validate_data(data: list[int], prev: list[int]) -> bool:
	"""
	Validates transmitted data 

	:param data: 2 item list storing [value, time].
	:type data: List[int]
	:param prev: 2 item list storing previous packet of data.
	:type prev: List[int]
	:return: True if data is valid, False otherwise.
	:rtype: bool
	"""
	# check if data contains 2 values
	if len(data) != 2:
		return False
	# check if time for n	ext data point are in order 
	if data[1] <= prev[1]:
		return False
	# check if time difference is between tolerance
	if data[1] > prev[1] + 30: # 30 works as a decent tolerance for error.
		return False

	# else: data is valid
	return True
	
def write_to_file(data, filepath):
	"""
	Writes validated data to text file

	:param data: 2 item list containing [value, time].
	:type data: List[int]
	:param filepath: name of file to write data to
	:type filepath: str
	"""
	# Code for writing/storing data to a file
	with open(filepath, 'a') as output_file:
		output_file.write(f'{data[0]}, {data[1]}\n')

def main():
	BTSerial = serial.Serial('COM11', 38400)	# select port with Arduino Nano
	filepath = 'data.txt'
	prev = [0, 0]
	
	# clear file
	with open(filepath, 'w'):
		pass
	
	while True:
		if BTSerial.in_waiting:
			packet = BTSerial.readline()
			data = process_packet(packet)

			if validate_data(data, prev):   
				write_to_file(data, filepath)	# save data
				prev = data		# save data packet
				print(data)		# for debugging

if __name__ == "__main__":
	main()