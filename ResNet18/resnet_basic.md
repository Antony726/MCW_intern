# ResNet 18
- <b>Residual Network</b>
-  The key innovation in ResNet models is the <b>residual connection</b>, which helps train very deep networks effectively by addressing the <b>vanishing gradient problem</b>.
- Instead of learning the raw transformation F(x), the network learns the residual F(x) + x. This helps avoid the vanishing gradient problem, making it easier to train deep networks.
![alt text](image.png)

## ResNet-18 Layer-wise Details
- Inputs 1x3x224x224

| Layer    | Type             | Kernel Size | Stride | Output Channels |
|----------|----------------|-------------|--------|----------------|
| Conv1    | Convolution    | 7×7        | 2      | 64             |
| Pool1    | Max Pooling    | 3×3        | 2      | 64             |
| Block1 (x2) | 3×3 Conv   | 1          | 64             |
| Block2 (x2) | 3×3 Conv   | 2          | 128            |
| Block3 (x2) | 3×3 Conv   | 2          | 256            |
| Block4 (x2) | 3×3 Conv   | 2          | 512            |
| Global Pool | Average Pooling | -       | -      | 512            |
| FC Layer | Fully Connected | -       | -      | 1000           |


# ResNet 18
<!-- ![alt text](resnet18_Opset18.onnx.png) -->
<!-- ![alt text](resnet18_Opset18_2.onnx.png) -->
![alt text](resnet18v1.onnx.png)
