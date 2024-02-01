all: clean tcp_server tcp_client udp_server udp_client


tcp_client:
	cd src && cd tcpip && cd client && mkdir build && cd build && cmake .. && make && cd ../../../..

tcp_server:
	cd src && cd tcpip && cd server && mkdir build && cd build && cmake .. && make && cd ../../../..

udp_client:
	cd src && cd udpip && cd client && mkdir build && cd build && cmake .. && make && cd ../../../..

udp_server:
	cd src && cd udpip && cd server && mkdir build && cd build && cmake .. && make && cd ../../../..

clean:
	rm -rf src/tcpip/client/build src/tcpip/server/build src/udpip/client/build src/udpip/server/build tcp_client_run tcp_server_run udp_client_run udp_server_run

.PHONY: tcp_client tcp_server udp_client udp_server clean	
