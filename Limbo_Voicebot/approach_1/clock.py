import time
from utils import play_sound, speak_print, custom_listen


def set_timer(raw_string):
    print(raw_string)
    try:
        string = "".join([char for char in raw_string if char.isdigit()])

    except (ValueError and UnboundLocalError):
        speak_print("Okay, when should I remind you?")
        set_timer(custom_listen())

    else:
        if len(string) <= 2:
            if ("minutes" or "minute") in raw_string:
                duration_in_seconds = int(string) * 60
                speak_print(f"Reminder set for {string} minutes.\n")
            elif ("seconds" or "second") in raw_string:
                duration_in_seconds = int(string)
                speak_print(f"Reminder set for {string} seconds.\n")

            while duration_in_seconds > 0:
                minutes, seconds = divmod(duration_in_seconds, 60)
                timeformat = f"{minutes:02d}:{seconds:02d}"
                print(f"Time remaining: {timeformat}", end="\r")
                time.sleep(1)
                duration_in_seconds -= 1

        elif len(string) == 4:
            pass

        play_sound("assets/alarm.mp3")