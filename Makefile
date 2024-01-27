all: clean server client


client:
	cd src && cd client && mkdir build && cd build && cmake .. && make && cd ../../..

server:
	cd src && cd server && mkdir build && cd build && cmake .. && make && cd ../../..

clean:
	rm -rf src/client/build src/server/build client_run server_run

.PHONY: client server clean	
