import pygame
import random
import datetime
from chatGPT import chatGPT
import speech_recognition as sr

from clock import set_timer
from config import GREETINGS
from utils import speak_print, SpeakText

playing_song = False

def play_sound(file_path):
    pygame.mixer.init()
    pygame.mixer.music.load(file_path)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

def listen_for_wake_word(source, recognizer):
    print("Bot: Listening for the wake word ...")

    while True:
        audio = recognizer.listen(source)
        try:
            text = recognizer.recognize_google(audio)  
            print("Bot: Listening for the wake word ...")
            text_list = [word.lower() for word in text.lower().split()]
            print(text_list)
            wake_words = ["hey", "hi", "hello", "over"]
            if any(word in text_list for word in wake_words):
                print("Bot: Wake word detected.")
                SpeakText(random.choice(GREETINGS))
                listen_and_respond(source, recognizer)
                break
        except sr.UnknownValueError:
            pass
        except AssertionError:
            print(text_list)


def listen_and_respond(source, recognizer):
    while True:
        print("Listening...")
        audio = recognizer.listen(source)

        try:
            text = recognizer.recognize_google(audio)
            print(f"You: {text}")

            if not text:
                continue

            text_list = text.split()

            if "pause" in text_list:
                print("Bot: Session paused")
                play_sound("assets/swoosh.mp3")
                listen_for_wake_word(source, recognizer)

            elif any(word in text_list for word in ["set", "reminder"]):
                set_timer(text_list)

            elif any(word in text_list for word in ["time", "right"]):
                speak_print(f"It's {datetime.datetime.now().strftime('%H:%M')} right now.")

            else:
                gpt_reply = chatGPT(text)
                # speak_print(gpt_reply)

        except sr.UnknownValueError:
            print("Bot: Silence found, shutting up")
            play_sound("assets/swoosh.mp3")
            listen_for_wake_word(source, recognizer)
            break

        except sr.RequestError as e:
            print(f"Bot: Could not request results; {e}")
            play_sound("assets/swoosh.mp3")
            listen_for_wake_word(source, recognizer)
            break

def main():
    recognizer = sr.Recognizer()
    with sr.Microphone(device_index=2) as source:
        listen_for_wake_word(source, recognizer)

if __name__ == "__main__":
    main()