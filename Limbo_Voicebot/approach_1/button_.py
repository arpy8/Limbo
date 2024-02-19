import keyboard as kb

count =  0
key_pressed = False

while 1:
    if kb.is_pressed('a') and not key_pressed:
        count += 1
        key_pressed = True  
        print(key_pressed)
        # print("On" if count%2==0 else "Off")
        
    if not kb.is_pressed('a') and key_pressed:
        key_pressed = False