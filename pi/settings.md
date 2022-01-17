### change wifi
    sudo nano /etc/wpa_supplicant/wpa_supplicant.conf

### crontab
    @reboot sudo chmod 666 /dev/ttyS0 && /usr/bin/python3 main.py
    @reboot /usr/bin/python3 post_requester.py
