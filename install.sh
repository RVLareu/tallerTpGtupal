# Bin
sudo cp client /usr/bin/quantum-chess-client
sudo cp server /usr/bin/quantum-chess-server

# Config
sudo mkdir /etc/quantum-chess
sudo cp config.yaml /etc/quantum-chess

# Assets
sudo mkdir /var/quantum-chess
sudo cp -r ./assets /var/quantum-chess