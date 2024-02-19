from os import environ
environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'

import pygame

import os
import time

import pyttsx3
import pyautogui as pg
import speech_recognition as sr

r = sr.Recognizer()


def custom_call(source):
    audio = r.listen(source)
    try:
        return r.recognize_google(audio)
    except sr.UnknownValueError:
        pass


def custom_listen():
    try:
        with sr.Microphone(device_index=3) as source:
            text = custom_call(source)
            if not None: return text
    except AttributeError:
        with sr.Microphone(device_index=1) as source:
            text = custom_call(source)
            if not None: return text


def play_sound(path):
    pygame.mixer.init()
    pygame.mixer.music.load(path)
    pygame.mixer.music.play()
    pygame.mixer.music.wait()


def SpeakText(text, voice_id=1, speed=130):
    engine = pyttsx3.init()
    voices = engine.getProperty('voices')
    engine.setProperty('voice', voices[voice_id].id)
    engine.setProperty('rate', speed)
    engine.say(text)
    engine.runAndWait()


def speak_print(text, skip="", only_speak=False, skip_skip_value_while_printing=False):
    if skip_skip_value_while_printing:
        print(text)
    if skip in text:
        text = text.replace(skip, "")
    text = text.replace("\n", "")
    text = text.replace("Bot: ", "")
    if not only_speak:
        print(text)
    SpeakText(text)


def whatsapp_close_tab():
    pg.hotkey('alt', 'f4')
    pg.hotkey('alt', 'tab')
    pg.hotkey('ctrl', 'w')


def close_application():
    pg.hotkey("alt", "f4")


def shutdown():
    speak_print("Shutting down")
    pg.hotkey('ctrl', 'win', 'd')
    pg.hotkey('alt', 'f4')
    pg.press('enter')


def lock_system():
    pg.hotkey('win', 'r')
    pg.write("cmd")
    pg.press("enter")
    time.sleep(0.5)
    pg.write(os.getenv("LOCK_COMMAND"))
    pg.press("enter")


