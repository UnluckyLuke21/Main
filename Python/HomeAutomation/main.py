import automodules
from automodules import HomeAutomationBot
from automodules import DeviceGroup
from automodules import Light
from automodules import SpotifyBot

#--------------------------------------------------------

# Initialize Devices:
bot = HomeAutomationBot()
Licht = DeviceGroup("Licht")

licht1 = Light("Regallampe")
licht2 = Light("Deckenleuchte")

music = SpotifyBot("Spotify_Bot")

Licht.add_device(licht1)
Licht.add_device(licht2)

bot.add_device(music)
bot.add_group(Licht)

# Live Controll Devices:
bot.liveConsole()
