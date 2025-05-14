# BEVFormer

# Intro
![alt text](image.png)

# Key Components
![alt text](image-1.png)

# Architecture
![alt text](image-2.png)

![alt text](image-3.png)

# Flow
![alt text](image-4.png)

```plaintext
              +----------------+
              |  Input Image   |
              +----------------+
                      |
                      v
        +---------------------------+
        |  Image Backbone (ResNet)  |
        |  -> Extract deep features |
        +---------------------------+
                      |
                      v
        +---------------------------+
        |  Image Neck (FPN)         |
        |  -> Refine & aggregate    |
        |     image features        |
        +---------------------------+
                      |
                      v
        +---------------------------+
        |  BEVFormer Transformer    |
        |   (PerceptionTransformer) |
        +---------------------------+
                      |
         +------------+--------------+
         |                           |
         v                           v
+-----------------+     +-------------------------+
| Temporal Self   |     | Spatial Cross Attention |
| Attention       |     | + MSDeformableAttention |
+-----------------+     +-------------------------+
         \_____________________/
                  |
                  v
    +-----------------------------------+
    |  Transformer Decoder              |
    | (DetectionTransformerDecoder)     |
    | - Self-attn + Cross-attn on BEV   |
    | - Uses learned query embeddings   |
    +-----------------------------------+
                  |
                  v
    +-----------------------------------+
    |  Prediction Head (BEVFormerHead)  |
    |  - bbox reg / class logits        |
    +-----------------------------------+
                  |
                  v
         +--------------------+
         | Final 3D BBoxes    |
         +--------------------+
```
