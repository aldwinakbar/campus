#!/bin/bash 

install_deb_package() {
	
	
	if ! dpkg -s $1 >/dev/null 2>&1; then
		
		## Prompt the user 
		read -p "Do you want to install $1? [Y/n]: " answer
		##Set the default value if no answer was given
		answer=${answer:Y}
		
		if [[ $answer =~ [Yy] ]]; then # we can compare directly with this syntax.
			apt-get install -y $1
			echo 
		else
			echo "Exiting"
			exit 1
		fi
	fi
	
}
package_install(){
	
		if pip list | grep -F $1 &> /dev/null 2>&1; then
			pip install $1 --upgrade
		else
			pip install $1
		fi	
}

install_pip_package() {
	## Prompt the user 
	read -p "Do you want to install required python package? [Y/n]: " answer
	##Set the default value if no answer was given
	answer=${answer:Y}
	
	if [[ $answer =~ [Yy] ]]; then # we can compare directly with this syntax.
		
		package_install requests
		package_install telepot
		echo 		
	else
		echo "Continuing without installing required python package."
	fi
}

if [[ $EUID > 0 ]]; then # we can compare directly with this syntax.
  echo "Please run as root/sudo"
  exit 1
else
	
		apt-get update
		install_deb_package python-pip
		install_deb_package unzip
		install_pip_package
		
		wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-arm.zip -O temp.zip && unzip temp.zip && rm temp.zip
		
		read -p "Insert your Ngrok Authentication token: " input
		
		./ngrok authtoken $input
		mv ngrok src/
		
		read -p "Insert your Telegram Bot token: " input
				
		telegram_token="telegram_token = '$input'"
		sed -i "8i $telegram_token" src/telegram-bot.py
		
		mkdir stonut
		cp -rf src/* stonut/
		chmod +x stonut/*
		mv -f stonut /opt/
		
		crontab -l > mycron
		echo "@reboot nohup /opt/stonut/start-telegram-bot.sh > /dev/null 2>&1 &" >> mycron
		crontab mycron
		rm mycron
		
		echo "SSH Tunnel over Ngrok using Telegram successfully installed!"
fi

