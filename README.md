# 🚗 C++ Lane Detection (OpenCV)

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![OpenCV](https://img.shields.io/badge/OpenCV-4.x-green)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-blue)
![Computer Vision](https://img.shields.io/badge/Computer%20Vision-Lane%20Detection-orange)

A real-time **lane detection** pipeline implemented in **C++17** using **OpenCV**.

The project demonstrates a classical computer vision approach to detecting road lane markings from video frames. The pipeline combines edge detection, region-of-interest filtering, the Probabilistic Hough Transform, temporal smoothing, and an augmented-reality overlay to produce stable left and right lane boundaries.

> 📷 **Screenshot**
>
> <img width="1718" height="962" alt="Screenshot from 2026-08-16 20-32-04" src="https://github.com/user-attachments/assets/62918ea7-5d22-47b1-86d7-668190ba8a3d" />

---

## 🚀 Key Features

* 🛣️ **Real-Time Lane Detection:** Processes video frames and continuously estimates the left and right lane boundaries.
* 🧹 **Noise Reduction:** Uses Gaussian Blur before edge detection to reduce image noise.
* 🎯 **Canny Edge Detection:** Extracts strong road edges for subsequent line detection.
* 🔺 **Dynamic ROI:** Automatically scales the Region of Interest according to the input video resolution.
* 📐 **Hough Line Detection:** Uses the Probabilistic Hough Transform (`HoughLinesP`) to detect lane segments.
* 🧠 **Lane Classification:** Separates detected line segments into left and right lane candidates based on their geometry.
* 📈 **Temporal Smoothing:** Applies an Exponential Moving Average to reduce frame-to-frame instability.
* 🛡️ **Flicker Protection:** Maintains information from previous frames to prevent lane lines from suddenly disappearing or jumping.
* 🟩 **AR Lane Overlay:** Extrapolates lane boundaries toward the horizon and renders a semi-transparent driving corridor.

---

## 🧠 Computer Vision Pipeline

The processing pipeline consists of the following stages:

```text
Input Video Frame
       │
       ▼
Grayscale Conversion
       │
       ▼
Gaussian Blur
       │
       ▼
Canny Edge Detection
       │
       ▼
Dynamic ROI Mask
       │
       ▼
Probabilistic Hough Transform
       │
       ▼
Left / Right Lane Separation
       │
       ▼
Temporal Smoothing
       │
       ▼
Lane Extrapolation
       │
       ▼
AR Visualization
```

### 1. Grayscale & Gaussian Blur

The input frame is converted to grayscale and filtered with a Gaussian blur to reduce high-frequency noise before edge detection.

### 2. Canny Edge Detection

The Canny algorithm detects strong intensity gradients corresponding to road boundaries and lane markings.

### 3. Region of Interest

A dynamically scaled trapezoidal mask limits processing to the road area, eliminating irrelevant regions such as the sky and surrounding environment.

### 4. Probabilistic Hough Transform

`HoughLinesP` extracts line segments from the detected edges.

### 5. Lane Separation & Smoothing

Detected segments are classified as either left or right lane candidates. Their parameters are then smoothed over time using an **Exponential Moving Average (EMA)**.

### 6. Lane Extrapolation & Visualization

The detected line segments are extrapolated toward the horizon to create continuous lane boundaries. A semi-transparent green polygon is rendered between them to visualize the estimated driving corridor.

---

## 📁 Project Structure

```text
lane_detection/
├── LaneDetector.cpp      # Lane detection implementation
├── LaneDetector.hpp      # LaneDetector class definition
├── CMakeLists.txt
├── main.cpp              # Application entry point
└── README.md
```

---

## 🛠️ Requirements

* C++17 or newer
* OpenCV 4.x
* CMake 3.10 or newer

---

## ⚙️ Build

Clone the repository and build the project locally:

```bash
git clone https://github.com/atykymschwep/Lane_Assist_Project.git
cd lane_detection

mkdir build
cd build

cmake ..
make
```

---

## 🎮 Usage

Run the lane detection application:

```bash
./LaneDetection
```

The application will open the input video and process each frame in real time.

Press **ESC** to exit.

---

## 📄 License

This project is intended for educational and research purposes.
