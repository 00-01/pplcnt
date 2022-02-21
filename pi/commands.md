### change wifi
    sudo nano /etc/wpa_supplicant/wpa_supplicant.conf

### crontab [website](https://crontab.guru/)
    @reboot sudo chmod 666 /dev/ttyS0 && /usr/bin/python3 main.py
    @reboot /usr/bin/python3 post_requester.py

    # every 5 minutes from 7 to 10  
    */5 7-10 * * * python3 main.py && python3 poster.py



### scp
     scp -r ~/data/* z@192.168.0.16:/media/z/e9503728-f419-4a14-9fc0-21e2947af50c/DATA/gappi
### scp with pw
     sudo sshpass -p 1234qwer scp ~/data/* z@192.168.0.16:/media/z/e9503728-f419-4a14-9fc0-21e2947af50c/DATA/gappi
