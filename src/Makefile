all: clean server client


client:
	cd client && mkdir build && cd build && cmake .. && make && cd ../..

server:
	cd server && mkdir build && cd build && cmake .. && make && cd ../..

clean:
	rm -rf client/build server/build client_run server_run

.PHONY: client server clean	
