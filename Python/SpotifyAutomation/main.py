import spotipy
from spotipy.oauth2 import SpotifyOAuth

# Spotify API credentials
CLIENT_ID = '3f9b11ed0985455f836851e29f4f73fb'
CLIENT_SECRET = '42a0f652ec61441281d533eda99d3f0f'
REDIRECT_URI = 'http://localhost:8888/callback'

# Create a SpotifyOAuth object
scope = 'user-modify-playback-state'

sp_oauth = SpotifyOAuth(client_id=CLIENT_ID, client_secret=CLIENT_SECRET, redirect_uri=REDIRECT_URI, scope=scope)
token_info = sp_oauth.get_access_token(as_dict=False)
sp = spotipy.Spotify(auth=token_info)

def start_music():
    sp.start_playback()

def pause_music():
    sp.pause_playback()

def skip_to_next():
    sp.next_track()

def skip_to_previous():
    sp.previous_track()

def set_volume(volume_percent):
    sp.volume(volume_percent)
