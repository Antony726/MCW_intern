- Enables inference on TI hardware – You can train your model using standard frameworks and then run it efficiently on TI devices.
- Supports multiple deep learning frameworks – Makes it easy to bring models from different ecosystems into TIDL.
- Optimized for embedded systems – TIDL converts models into an optimized format that runs faster on low-power edge devices.


# Takes the trained model files from these frameworks and converts them into TIDL format.
- Caffe model → TIDL format (.prototxt + .caffemodel → TIDL)
- TensorFlow model → TIDL format (.pb → TIDL)
- ONNX model → TIDL format (.onnx → TIDL)

# **TIDL - TI Deep Learning Product**  

TIDL (TI Deep Learning) is a **software package** developed by **Texas Instruments (TI)** to accelerate **Deep Neural Networks (DNNs)** on TI's embedded devices. It is **part of TI’s Edge AI solution** and helps both **Data Scientists** (who train AI models) and **Embedded Engineers** (who deploy AI models on embedded systems).  

---

## **📌 Key Features & Components of TIDL**  
| **Feature** | **Explanation** |
|------------|--------------|
| **DNN Acceleration** | TIDL speeds up deep learning inference on **TI’s embedded processors**. |
| **Heterogeneous Execution** | It runs DNNs across **Cortex-A processors**, **C7x DSPs**, and **TI's DNN accelerator (MMA)** for better performance. |
| **Part of SDK (Software Development Kit)** | TIDL is included in **TI’s SDK** along with optimized libraries like **OpenCV** for computer vision. |
| **Supports Multiple AI Frameworks** | Works with **TensorFlow, ONNX, TFLite, and TVM/Neo-AI**. |
| **Runs on Edge Devices** | Designed for **low-power embedded systems** like **TDA4VM (used in automotive & industrial applications)**. |

---

## **📌 Who Uses TIDL?**
| **Role** | **Responsibilities** |
|----------|---------------------|
| **Data Scientists** | Train AI models using TensorFlow, PyTorch, or ONNX. Optimize models for TI hardware. |
| **Embedded Engineers** | Deploy AI models on **TI devices** for real-time inference. Optimize performance on **low-power systems**. |

---

## **📌 Tools & Resources in TIDL**
| **Tool** | **Purpose** |
|---------|-------------|
| **Model Zoo** | A collection of pre-trained models for TI’s embedded devices. |
| **Training & Quantization Tools** | Helps optimize AI models for better performance on TI hardware. |
| **Edge AI Cloud** | Free **online service** to test AI models on TI hardware from a browser. |
| **Edge AI Benchmark** | A Python framework to **test accuracy & performance** of AI models on TI devices. |

---

## **📌 Deployment Options in TIDL**  
TIDL allows you to deploy AI models using different **Open Source Run Times (OSRT)**:

| **Run Time** | **Framework Used** | **Execution** |
|-------------|-----------------|--------------|
| **TFLite Runtime** | TensorFlow Lite | Runs on Cortex-A + C7x-MMA |
| **ONNX Runtime** | ONNX models | Runs on Cortex-A + C7x-MMA |
| **TVM/Neo-AI Runtime** | TVM-based models | Runs on Cortex-A + C7x-MMA |
| **TIDL-RT (OpenVX-based)** | TIDL’s optimized inference engine | Runs only on C7x-MMA |

✅ **Recommendation**: TI suggests using **OSRT (Open Source Run Times)** for **better user experience & broader model support**.

---

## **📌 What is the Hardware Used?**
TIDL is optimized for **TI processors**, mainly:
- **TDA4VM** (used in automotive & edge AI applications)  
- It has a **Cortex-A72 processor** (MPU) for AI inference.  

To check the exact processor used, refer to the **Technical Reference Manual (TRM)** for the device.

---

## **🔹 Key Takeaways**  
✔ **TIDL accelerates AI inference on TI embedded processors.**  
✔ **It supports TensorFlow, ONNX, TFLite, and TVM models.**  
✔ **Optimized for low-power edge AI applications.**  
✔ **Uses multiple processing units (Cortex-A, DSP, MMA) for efficiency.**  
✔ **Includes tools for model selection, training, and deployment.**  


# **TI Deep Learning RT (TIDL-RT) Summary**

TIDL-RT (TI Deep Learning Runtime) is designed to accelerate **Deep Neural Networks (DNNs)** on **Texas Instruments (TI) embedded devices**. It abstracts hardware complexities, allowing users to focus on **algorithm development** without worrying about deployment optimization.

## **Key Features of TIDL-RT**  

- **Interoperability:**  
  - Supports multiple **AI frameworks** (e.g., TensorFlow, PyTorch, TFLite, ONNX).  
  - Accepts both **floating-point and fixed-point models** for inference.  

- **Best Accuracy:**  
  - Utilizes **Post-Training Quantization (PTQ)** and **advanced calibration** to minimize accuracy loss during fixed-point inference.  
  - Supports **mixed-precision (8-bit & 16-bit) inference** for efficiency.  

- **Best Performance:**  
  - Optimized for **latency-sensitive applications**, leveraging **C7x-MMA accelerators** and **on-chip memory** to process models efficiently.  
  - Supports **batch processing** and **high-resolution images (2-4MP)**.  

- **Scalability:**  
  - Supports various **network topologies**, **input resolutions**, **TI hardware (1-10+ TOPS)**, and different **sensor modalities** (vision, radar, LiDAR, etc.).  
  - Allows adding **custom operators** if needed.  

---

## **TIDL-RT Deployment Workflow**  

### **1️⃣ Compilation (Model Importer)**
- Performed on an **x86 PC**.  
- Converts models into **TI’s internal format**.  
- Includes **quantization & DNN graph compilation** based on device specifications.  

### **2️⃣ Inference (Deployment on TI SoC)**
- Runs on **TI embedded devices** (e.g., **TDA4VM development board**).  
- Uses **generated artifacts** from the compilation stage for optimal inference.  
- Supports **PC-based functional testing** (without a TI device) but performance benchmarking requires a TI board.  

---

TIDL-RT enables **efficient, scalable, and accurate** deep learning deployment on **TI’s edge AI platforms**, making it ideal for **robotics, industrial automation, and automotive AI applications**. 🚀


