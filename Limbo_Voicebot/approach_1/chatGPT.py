import openai
from config import PREDEFINED_PROMPT, GPT_KEY

openai.api_key = GPT_KEY

def chatGPT(text, model="gpt-3.5-turbo"):
  client = openai.OpenAI()

  response = client.chat.completions.create(
    model=model,
    messages=[
      {"role": "system", "content": PREDEFINED_PROMPT},
      {"role": "user", "content": f"{text}"}
    ]
  )

  return response.choices[0].message.content

if __name__ == "__main__":
    while 1:
        print(chatGPT(input("-> ")))