import time
import random
import datetime
import telepot
import subprocess
import requests



def handle(msg):
    chat_id = msg['chat']['id']
    command = msg['text']

    print 'Got command: %s' % command

    if command == '/ssh_start':
        subprocess.Popen(["nohup", "/opt/stonut/start-ngrok.sh"])
        bot.sendMessage(chat_id, 'Starting tunnel....')
        time.sleep(10)
        r = requests.get('http://localhost:4040/api/tunnels')
        reply = "Your tunnel address is " + str(r.json()['tunnels'][0]['public_url'])
        bot.sendMessage(chat_id, reply)
    elif command == '/ssh_stop':
        subprocess.Popen(["nohup", "/opt/stonut/stop-ngrok.sh"])
        bot.sendMessage(chat_id, 'Tunnel Killed')
    elif command == '/ssh_addr':
		try:
			r = requests.get('http://localhost:4040/api/tunnels')
			reply = "Your tunnel address is " + str(r.json()['tunnels'][0]['public_url'])
			bot.sendMessage(chat_id, reply)
		
		except requests.exceptions.RequestException as e:
			bot.sendMessage(chat_id, 'An error occur. Probably tunnel isn\'t running.')
    
    elif command == '/time':
        bot.sendMessage(chat_id, str(datetime.datetime.now()))
    else :
        bot.sendMessage(chat_id, 'Unknown Command')

bot = telepot.Bot(telegram_token)
bot.message_loop(handle)
print 'I am listening ...'
time.sleep(5)

while 1:
    time.sleep(10)

