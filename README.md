
Installation of supla-server
============================

    git clone https://github.com/IoTAqua/supla-core.git
    cd supla-server

    ./build.sh
    sudo cp Release/supla-server /usr/sbin/
    sudo cp supla-server-init /etc/init.d/supla-server
    sudo update-rc.d supla-server defaults

    vi supla.cfg
    * set "password=" to <mysql-supla-password>
    sudo mkdir /etc/supla-server
    sudo cp supla.cfg /etc/supla-server/
    openssl req -new -newkey rsa:2048 -days 3650 -sha256 -nodes -x509 -keyout private.key -out cert.crt
    sudo mv private.key cert.crt /etc/supla-server/
    sudo adduser --system --no-create-home --group supla
    sudo chown root:supla /etc/supla-server/*
    sudo chmod 640 /etc/supla-server/*
