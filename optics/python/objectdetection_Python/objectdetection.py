import cv2 
import numpy as np

webcam = cv2.VideoCapture(0)

weights = "frozen_inference_graph.pb"
model = "ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt"
net = cv2.dnn.readNetFromTensorflow(weights, model)

class_names = []
with open("coco_names.txt", 'r') as f:
    class_names = f.read().strip().split('\n')

np.random.seed(90)
colors = np.random.randint(0, 255, size=(len(class_names), 3))

while True:
    success, frame = webcam.read()
    frame = cv2.flip(frame, 1)
    h = frame.shape[0]
    w = frame.shape[1]

    blob = cv2.dnn.blobFromImage(frame, 1.0 / 127.5, (320, 320), [127.5, 127.5, 127.5])
    net.setInput(blob)
    output = net.forward()

    for detection in output[0, 0, :, :]:
        probability = detection[2]
        if probability < 0.5:
            continue

        class_id = int(detection[1])
        color = colors[class_id]
        B, G, R = int(color[0]), int(color[1]), int(color[2])
        box = [int(a * b) for a, b in zip(detection[3:7], [w, h, w, h])]
        box = tuple(box)
        cv2.rectangle(frame, box[:2], box[2:], (B, G, R), 2)
        class_id = int(detection[1])
        label = f"{class_names[class_id - 1]} {probability * 100:.2f}"
        cv2.putText(frame, label, (box[0], box[1] + 15), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    cv2.imshow("webcam", frame)
    key = cv2.waitKey(1)
    if key == ord("q"):
        break