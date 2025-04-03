```python
import tensorflow as tf
import numpy as np

# Define the input shape
input_shape = (48, 240, 320)  # (batch_size, height, width, channels)

# Define the input layer
input_layer = tf.keras.Input(shape=input_shape)

# Convolutional layer applied to the input
conv_layer = tf.keras.layers.Conv2D(64, kernel_size=(3, 3), padding='same', name="conv1")(input_layer)

# Branch 1: Apply Sigmoid activation
sigmoid_branch = tf.keras.layers.Activation('sigmoid')(conv_layer)

# Branch 2: No operation (just the conv layer output)
no_op_branch = conv_layer  # No operation, just pass through

# Multiply both branches
mul_output = tf.keras.layers.Multiply()([sigmoid_branch, no_op_branch])

# Create the model
model = tf.keras.Model(inputs=input_layer, outputs=mul_output)

# 2. Convert the model to TensorFlow Lite format
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# 3. Save the TFLite model
tflite_model_path = "sigmoid_mul_model.tflite"
with open(tflite_model_path, "wb") as f:
    f.write(tflite_model)

print(f"\nTFLite model successfully converted and saved as '{tflite_model_path}'")
```