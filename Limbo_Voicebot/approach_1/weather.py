import requests
from config import WEATHERSTACK_URL, WEATHERSTACK_API
from utils import speak_print


def get_weather(city="ghaziabad"):
    params = {
        'access_key': WEATHERSTACK_API,
        'query': city
    }

    api_result = requests.get('http://api.weatherstack.com/current', params)
    api_response = api_result.json()

    speak_print(u'Current temperature in %s is %d℃' % (
        api_response['location']['name'], api_response['current']['temperature']))


def weather(raw_string):
    try:
        if "my city" in raw_string:
            get_weather()
        else:
            new_city = ""
            try:
                new_city = raw_string.split("in")[1]
            except IndexError:
                pass
            finally:
                get_weather(new_city)
    except Exception as e:
        print(f"An error occurred: {e}")


weather("new york")
