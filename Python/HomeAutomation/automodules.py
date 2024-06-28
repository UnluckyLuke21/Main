import spotipy
from spotipy.oauth2 import SpotifyOAuth

class HomeAutomationBot:
    def __init__(self):
        self.devices = {}
        self.groups = {}

    def add_device(self, device):
        self.devices[device.name] = device

    def add_group(self, group):
        self.groups[group.name] = group
    
    def control_device(self, device_name, action, args):

        # Search for the Device Name in List:
        if device_name in self.devices:
            device = self.devices[device_name]

            if action == "turn_on":
                device.turn_on()
            elif action == "turn_off":
                device.turn_off()
            elif action == "status":
                device.status()
            elif isinstance(device, SpotifyBot):
                if action == "play_music":
                    device.play_music()
                elif action == "pause_music":
                    device.pause_music()
                elif action == "skip_to_next":
                    device.skip_to_next()
                elif action == "skip_to_previous":
                    device.skip_to_previous()
                elif action == "set_volume":
                    device.set_volume(int(args[0]))
            else:
                print("Action not found!")

        # Control Device Groups:
        elif device_name in self.groups:
            group = self.groups[device_name]
            if action == "turn_on_all":
                group.turn_on_all()
            elif action == "turn_off_all":
                group.turn_off_all()
            elif action == "status_all":
                group.status_all()
            else:
                print("Unknown Action")

        else:
            print("Device not found!")

    def liveConsole(self):
        while True:
            print(f"The following Devices are available: ")
            for device in self.devices:
                print(device)
            for group in self.groups:
                print(group)

            user_input = input("Enter Command (format: Device_Name Action) or 'exit' to quit:")
            if user_input.lower() == 'exit':
                break
            try:
                parts = user_input.split()
                device_name = parts[0]
                action = parts[1]
                additional_params = parts[2:]
                self.control_device(device_name, action, additional_params)
            except ValueError:
                print("Invalid command format")

#-----------------------------------------------------

class Device:
    def __init__(self, name):
        self.name = name
        self.is_on = False

    def turn_on(self):
        self.is_on = True
        print(f"{self.name} turned on!")

    def turn_off(self):
        self.is_on = False
        print(f"{self.name} turned off!")

    def status(self):
        if self.is_on:
            print(f"{self.name} Status: on!")
        else:
            print(f"{self.name} Status: off!")

#------------------------------------------------------

class DeviceGroup:
    def __init__(self, name):
        self.name = name
        self.devices = []

    def add_device(self, device):
        self.devices.append(device)

    def turn_on_all(self):
        for device in self.devices:
            device.turn_on()
    
    def turn_off_all(self):
        for device in self.devices:
            device.turn_off()

    def status_all(self):
        for device in self.devices:
            device.status()

#------------------------------------------------------

class Light(Device):
    def __init__(self, name):
        super().__init__(name)

#-------------------------------------------------------

class SpotifyBot(Device):
    def __init__(self, name):
        super().__init__(name)

        # Spotify API credentials
        CLIENT_ID = '3f9b11ed0985455f836851e29f4f73fb'
        CLIENT_SECRET = '42a0f652ec61441281d533eda99d3f0f'
        REDIRECT_URI = 'http://localhost:8888/callback'

        # Create a SpotifyOAuth object
        scope = 'user-modify-playback-state'

        # Initiate Spotify Connection:
        sp_oauth = SpotifyOAuth(client_id=CLIENT_ID, client_secret=CLIENT_SECRET, redirect_uri=REDIRECT_URI, scope=scope)
        token_info = sp_oauth.get_access_token(as_dict=False)
        self.sp = spotipy.Spotify(auth=token_info)

    def play_music(self):
        self.sp.start_playback()

    def pause_music(self):
        self.sp.pause_playback()

    def skip_to_next(self):
        self.sp.next_track()

    def skip_to_previous(self):
        self.sp.previous_track()

    def set_volume(self, volume_percent):
        self.sp.volume(volume_percent)