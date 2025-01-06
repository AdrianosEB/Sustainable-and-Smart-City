import cv2 as cv
import serial
import time
from vehicle_detector import VehicleDetector

# Serial Connect
serialcomm = serial.Serial(port='/dev/cu.usbmodem101', baudrate=115200, timeout=0.1)

# Import model
vd = VehicleDetector()

cap = cv.VideoCapture(0)
cap.set(cv.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv.CAP_PROP_FRAME_HEIGHT, 720)

while True:
    success, img = cap.read()
    if not success:
        print("No image")
        break

    # Detect vehicles
    vehicle_boxes = vd.detect_vehicles(img)
    vehicle_count = len(vehicle_boxes)

    # Inform serial
    time.sleep(2)
    serialcomm.write(f"{vehicle_count}\n".encode('utf-8'))
    print(f"{vehicle_count}\n".encode('utf-8'))

    print(vehicle_count)

    # Draw box
    for box in vehicle_boxes:
        x, y, w, h = box
        cv.rectangle(img, (x, y), (x+w, y+h), (25, 0, 180), 3)

    cv.imshow("Cars", img)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
serialcomm.close()
