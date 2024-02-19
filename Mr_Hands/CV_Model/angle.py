import cv2
import time
import serial
from hand_module import HandDetector

class HandControl:
    def __init__(self):
        self.thumb_up = False
        self.hand_up = False
        self.full_hand_up = False

    def process_hand_gestures(self, fingers_up):
        if sum(fingers_up) == 5 and not self.full_hand_up and not self.hand_up and not self.thumb_up:
            self.full_hand_up = True
            print("Hand up")
            self.ser.write(b'0')
        elif not sum(fingers_up) == 5 and self.full_hand_up and not self.hand_up and not self.thumb_up:
            self.full_hand_up = False
            print("Hand down")
            self.ser.write(b'1')

    def run(self):
        cap = cv2.VideoCapture(0)
        hand_detector = HandDetector(maxHands=1)

        self.ser = serial.Serial('COM5', baudrate=9600, timeout=1) 
        try:
            while True:
                ret, frame = cap.read()
                if not ret:
                     break

                hands, _ = hand_detector.findHands(frame, draw=True, flipType=True)

                if hands:
                    fingers_up = hand_detector.fingersUp(hands[0])
                    self.process_hand_gestures(fingers_up)
                    time.sleep(1.2)
                    
                cv2.imshow("Videocam Stream", frame)
                if cv2.waitKey(5) & 0xFF == 27:
                    break

        except serial.SerialException as e:
            print(f"Serial error: {e}")
        except OSError as e:
            print(f"OS error: {e}")
        except Exception as e:
            print(e)
        finally:
            cap.release()
            cv2.destroyAllWindows()
            self.ser.close()

if __name__ == "__main__":
    hand_control = HandControl()
    hand_control.run()