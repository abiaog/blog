# tcpdump

	sudo tcpdump -vv -s 0 -w ~/tmp/tcpdump.pcap -i wlan0 port 25

# wireshark

	wireshark ~/tmp/tcpdump.pcap
