import logging
import telegram
from telegram.error import NetworkError, Unauthorized 
import time
import random
import datetime
import subprocess
import requests



update_id = None

def main():
    """Run the bot."""
    global update_id
    # Telegram Bot Authorization Token
    bot = telegram.Bot(telegram_token)

    # get the first pending update_id, this is so we can skip over it in case
    # we get an "Unauthorized" exception.
    try:
        update_id = bot.get_updates()[0].update_id
    except IndexError:
        update_id = None

    logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')

    while True:
        try:
            echo(bot)
        except NetworkError:
            time.sleep(1)
        except Unauthorized:
            # The user has removed or blocked the bot.
            update_id += 1


def echo(bot):
	"""Echo the message the user sent."""
	global update_id
    # Request updates after the last update_id
	for update in bot.get_updates(offset=update_id, timeout=10):
		update_id = update.update_id + 1

		if update.message:  # your bot can receive updates without messages
            # Reply to the message
			command = update.message.text
			if command == '/ssh_start':
				subprocess.Popen(["nohup", "/opt/stonut/start-ngrok.sh"])
				update.message.reply_text('Starting tunnel....')
				time.sleep(10)
				r = requests.get('http://localhost:4040/api/tunnels')
				reply = "Your tunnel address is " + str(r.json()['tunnels'][0]['public_url'])
				update.message.reply_text(reply)
			elif command == '/ssh_stop':
				subprocess.Popen(["nohup", "/opt/stonut/stop-ngrok.sh"])
				update.message.reply_text('Tunnel Killed')
			elif command == '/ssh_addr':
				try:
					r = requests.get('http://localhost:4040/api/tunnels')
					reply = "Your tunnel address is " + str(r.json()['tunnels'][0]['public_url'])
					update.message.reply_text(reply)
				
				except requests.exceptions.RequestException as e:
					update.message.reply_text('An error occur. Probably tunnel isn\'t running.')
			
			elif command == '/time':
				update.message.reply_text(str(datetime.datetime.now()))
			elif command == '/help':
				update.message.reply_text('/ssh_start	--- Open SSH port')
				update.message.reply_text('/ssh_stop	--- Stop SSH port')
				update.message.reply_text('/ssh_addr	--- Show SSH URL')
				update.message.reply_text('/time 		--- Show time')
			else :
				update.message.reply_text('Unknown Command')


if __name__ == '__main__':
    main()
