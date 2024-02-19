import requests
from config import DICTIONARY_URL
from utils import speak_print


def define_word(word):
    data = requests.get(DICTIONARY_URL + word).json()

    # Access the meanings of the word "hello"
    meanings = data[0]['meanings']

    # Now you can iterate over the meanings and access the information
    for meaning in meanings:
        part_of_speech = meaning['partOfSpeech']
        definitions = meaning['definitions']

        print(f"Part of Speech: {part_of_speech}")
        limit = 0
        for i, definition in enumerate(definitions, 1):
            if limit < 5:
                if 'example' in definition:
                    speak_print(f"Definition {i}: {definition['definition']}\nExample: {definition['example']}\n")
                else:
                    speak_print(f"Definition {i}: {definition['definition']}\n")
            limit += 1

        print('-' * 30)


define_word("test")

